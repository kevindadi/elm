/*
 *	$Id$
 *	Plugin class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <stdio.h>
#if defined(__unix) || defined(__APPLE__)
#	include "../config.h"
#elif defined(__WIN32) || defined(__WIN64)
#	include "../config.h"
#endif

#include <elm/assert.h>
#ifdef WITH_LIBTOOL
#	include <ltdl.h>
#elif defined(__WIN32) || defined(__WIN64)
#	include <windows.h>
#	undef min
#	undef max
#else
#	include <dlfcn.h>
#endif
#include <elm/sys/Plugin.h>
#include <elm/sys/Plugger.h>

namespace elm { namespace sys {

/* Maximal age for unused plugins before deletion
 * (expressed in plugin getting cycles).
 */
#define MAX_AGE	16


/**
 * @defgroup plugins Plugins
 *
 * @section use_plugins Using a Plugin
 *
 * ELM provides classes to implement plug-ins in an OS-independent way.
 * To work-around some shortcomings found on some OS, ELM provides also an
 * independent way to optionally represent dependencies between plug-ins based
 * on textual file with ".ini" syntax.
 *
 * A plug-in is a piece of code that provides some service based on an interface
 * implemented by the plug-in and used by a third-party program. The retrieval
 * of the plug-in, isolated in its own binary file, is based on its name
 * and a list of directories or from an absolute path. The object is in charge
 * of managing the plug-in is called a plugger and allows to plug many different
 * plug-ins to implement the same service.
 *
 * In ELM, the plugger is declared with a hook - an identifier allowing
 * an application to support different kinds of services and matching plug-ins -
 * and a version - for the current implemented plug-in interface. In the example
 * below, the plugger provides a service named "net_plugin" with an interface version
 * 1.0.0 (see @ref elm::Version for more details).
 * @code
 * #define NET_HOOK	net_plugin
 * elm::system::Plugger net_plugger(ELM_STRING(NET_HOOK), Version(1, 0, 0), ".:/usr/local/net_plugins");
 * @endcode
 *
 * To open a specific plugin named, for example, "my_net_plugin", one has only
 * to call the method Plugger::plug().
 * @code
 * elm::system::Plugin *plugin = net_plugger.plug("my_net_plugin");
 * @endcode
 * If the plugin is found, is loadable and has a compatible version, it is loaded,
 * initialized and its instance is returned. If there is an error, a null
 * pointer is returned and the method Plugger::lastErrorMessage() may give
 * some information about the error.
 * @code
 * if(plugin == NULL)
 * 	cout << "ERROR: " << plugger.lastErrorMessage() << io::endl;
 * @endcode
 *
 * Having just a plugin pointer does not provide any service. To do this, we have
 * usually to define an interface that is implemented by the plug-in instance.
 * Let's call it "NetPlugin": it must be derived from the elm::system::Plugin class.
 *
 * @code
 * class NetPlugin: public Plugin {
 * public:
 *	NetPlugin(const make& maker): Plugin(make(name, version))
 *		{ }
 * 	virtual void performService(void) = 0;
 * };
 * @endcode
 *
 * Then, we can cast the plug-in to its required interface and we can call the
 * service:
 * @code
 * NetPlugin *net_plugin = static_cast<NetPlugin *>(plugin);
 * net_plugin->performService();
 * @endcode
 *
 * When the plugin is no more needed, we can simply unplug it:
 * @code
 * net_plugin->unplug();
 * @endcode
 *
 *
 * @section creating_plugins Creating Plugins
 *
 * To create a plug-in, one has to define a class implementing the service
 * interface of the plugger to plug to. Let's continue the example started
 * in the previous section. Notice that we must implement
 * the pure virtual functions of the interface in order to be able to create
 * an instance of the plugin class.
 * @code
 * class MyNetPlugin: public NetPlugin {
 * public:
 *		MyNetPlugin(void);
 * 		void performService(void) override;
 * };
 * @endcode
 *
 * Then, the constructor must pass to the elm::system::Plugin class the name
 * of the service to be hooked to the right plugger with the service version
 * supported by the plugin.
 * @code
 * MyNetPlugin::MyNetPlugin(void): NetPlugin(make("my_net_plugin", Version(1, 0, 0))) {
 * }
 * @endcode
 *
 * Notice how the version is encoded in the plug-in code. If this plug-in is then
 * used with an incompatible version of the plugger, say 2.1.0. The compatibility
 * comparison will compare the version 1.0.0 (from the plug-in) with the version
 * 1.2.0 (from the plugger) and will detect possible binary incompatibility and
 * prevent the invalid linkage.
 *
 * Then we need to provide a hook to let the plugger found the plugin object.
 * @code
 * MyNetPlugin my_net_plugin;
 * ELM_PLUGIN(my_net_plugin, NET_HOOK);
 * @endcode
 * The result source must then be compiled to produce a shared code with
 * your preferred compiler For example, with GCC on a Unix OS.
 * @code
 * gcc -shared -o my_net_plugin.so my_net_plugin.cpp
 * @endcode
 *
 * It is a good practice, for the plug-in interface provide, to provide a macro
 * in the header file to provide the current version of the interface:
 * @code
 * #define NET_VERS		Version(1, 0, 0)
 * @endcode
 *
 * If this macro is used in  a plug-in, this will ensure without any additional work
 * that a plug-in is compatible with the compiled version of the plugger. If there is
 * some evolution in the interface that is incompatible with the compiled plug-in,
 * it will be detected and reported by the compiler:
 * @code
 * MyNetPlugin::MyNetPlugin(void): NetPlugin(make("my_net_plugin", NET_VERS)) {
 * }
 * @endcode
 *
 *
 * @section eld_files ELD Files
 *
 * ELM Linkage Description Files (ELD) allows to circumvent limitations found on some OSes
 * for the management of dynamic libraries.
 * Basically, ELD files are textual files with ".eld" extension implementing the
 * [".ini" file](https://en.wikipedia.org/wiki/INI_file) syntax. They must placed in the same
 * directory as the plug-in binary they apply to and get the same
 * name as the plug-in with the dynamic library extension replaced by ".eld".
 *
 * As usual ".ini" files, they can contain as many sections as possible but ELM is only interested
 * by the "elm-plugin" section that may contain the following definitions:
 * @li "author" -- author of the plug-in in the form "AUTHOR <EMAIL>",
 * @li "copyright" -- name and, optionally, link to the license,
 * @li "deps" -- ";" separated list of plug-in names that the current plug-in is dependent to,
 * @li "description" -- description of the plug-in for human user,
 * @li "libs" -- ";" separated list of library names or paths (absolute or relative) that the current plug-in is dependent to,
 * @li "name" -- alternative name of the plug-in,
 * @li "path" -- absolute or relative path to the actual plug-in (support for aliasing),
 * @li "rpaths" -- ";" separated list of paths to look for require plug-ins,
 * @li "site" -- URL to the web site publishing the plug-in.
 *
 * "path" definition allows to cope with the lack of support for symbolic links on some OSes.
 *
 * "rpaths" and "libs" are used to handle easily dependencies between plug-ins and libraries when the OSes
 * does not support linkage lookup path encoded in executable.
 *
 * Paths found in "path", "libs" and "rpaths" can be prefixed by "$ORIGIN" that is replaced,
 * at run time, by the path of the directory containing the considered plug-in binary.
 *
 * Below is an example of ELD files for our example requiring two other libraries that should be found
 * in the directory containing the plug-in or in directory "/usr/lib".
 * It is named "net_plugin.eld" and put in the same directory
 * as "net_plugin.so".
 * @code
 * [elm-plugin]
 * libs=libxml2;libxslt
 * rpath=$ORIGIN;/usr/lib
 * @endcode
 *
 * Below another example implements an alias, "net_plugin_v2" to "net_plugin". The file is named
 * "net_plugin_v2.eld":
 * @code
 * [elm-plugin]
 * path=$ORIGIN/net_plugin
 * @endcode
 *
 * This last example links with library libxml2 from the OS path:
 * @code
 * [elm-plugin]
 * libs=libxml2
 * @endcode
 *
 */

/**
 * @class Plugin <elm/system/Plugin.h>
 * The class Plugin allows implementing plug-ins in OS-independent way. See
 * @ref plugins for more details.
 * @ingroup plugins
 */


/**
 * List of static plug-ins.
 */
Vector<Plugin *> Plugin::static_plugins;


/**
 * True when all static has been initialized.
 */
bool Plugin::static_done = false;


/**
 * List of unused plugins.
 */
Vector<Plugin *> Plugin::unused_plugins;


/**
 * Build a new plugin.
 * @param name				Plugin name.
 * @param plugger_version	Plugger version (used for checking compatibility
 * 							between plugin and user application API).
 * @param hook				Hook of a matching plugger
 * @param aliases			Name aliases for the plugin.
 */
Plugin::Plugin(
	string name,
	const Version& plugger_version,
	CString hook,
	const aliases_t& aliases
) :
	magic(MAGIC),
	_hook(hook),
	_name(name),
	per_vers(plugger_version),
	_handle(0),
	state(0)
{
	if(hook && !static_done)
		static_plugins.add(this);
	_aliases.copy(aliases);
}


/**
 * New-style builder for plugin using @ref Plugin::Maker.
 * @param maker	Maker for plugin.
 */
Plugin::Plugin(const Plugin::make& maker)
:	magic(MAGIC),
 	_description(maker._description),
 	_licence(maker._license),
 	_plugin_version(maker._plugin_version),
	_hook(maker._hook),
 	_name(maker._name),
 	per_vers(maker._plugger_version),
 	_handle(0),
 	state(0)
{
	if(_hook && !static_done)
		static_plugins.add(this);
	if(maker.aliases) {
		Vector<string> as;
		as.addAll(maker.aliases);
		_aliases = as.detach();
	}
}

/**
 */
Plugin::~Plugin(void) {
}


/**
 * For internal use only.
 */
void Plugin::plug(void *handle) {

	// no static if there is an handle
	if(handle)
		static_plugins.remove(this);

	// usage incrementation
	if(state > 0)
		state++;

	// Initialization
	else if(state == 0) {
		startup();
		state = 1;
		if(handle) {
#if defined(__unix)
			_handle = handle;
#elif defined(__WIN32) || defined(__WIN64)
			_handle = reinterpret_cast<HMODULE&>(handle);
#endif

			static_plugins.remove(this);
		}
	}

	// Revival for unused plugins
	else if(state < 0) {
		unused_plugins.remove(this);
		state = 1;
	}

	// Make other older
	step();
}


/**
 * Call it when the plugin is no more used.
 */
void Plugin::unplug(void) {
	ASSERT(state);

	// Decrement usage
	state--;

	// Plugin become unused ?
	if(!state) {
		unused_plugins.add(this);
		state = -1;
	}

	// Unused plugin become too old ?
	else if(state < -MAX_AGE) {
		Plugger::leave(this);
		cleanup();
		unused_plugins.remove(this);
		if(_handle)
			Plugger::unlink(_handle);
	}
}


/**
 * This method is called just after the plugin has been plugged into the user
 * application. It may be overriden for performing specific initializations.
 */
void Plugin::startup(void) {
}


/**
 * This method is called just before the plugin removal from the user
 * application. It may be overriden for performing specific clean up.
 */
void Plugin::cleanup(void) {
}


/**
 * @fn string Plugin::name(void) const;
 * Get the plugin name.
 * @return	Plugin name.
 */


/**
 * @fn String Plugin::description(void) const;
 * Get the plugin description.
 * @return	Plugin description.
 */


/**
 * @fn String Plugin::licence(void) const;
 * Get the plugin licence.
 * @return Plugin licence.
 */


/**
 * @fn Version& Plugin::pluginVersion(void) const;
 * Get the plugin version.
 * @return Plugin version.
 */


/**
 * @fn Version& Plugin::pluggerVersion(void) const;
 * Get the plugger version.
 * @return Plugger version.
 */


/**
 * @fn String Plugin::hook(void) const;
 * Get the hook of the current plugin.
 * @return	Plugin hook.
 */


/**
 * For internal use only.
 */
void Plugin::step(void) {
	for(int i = unused_plugins.count() - 1; i >= 0; i--)
		unused_plugins[i]->unplug();
}


/**
 * For internal use only.
 */
Plugin *Plugin::get(cstring hook, const string& name) {

	// Find the plugin
	for(int i = 0; i < static_plugins.count(); i++)
		if(static_plugins[i]->hook() == hook
		&& static_plugins[i]->matches(name))
			return static_plugins[i];

	// Not found
	return 0;
}


/**
 * @fn const aliases_t& Plugin::aliases(void) const;
 * Get the table of aliases of the plugin.
 * @return	Table of aliases.
 */


/**
 * Test if the current plugin matches the given name, that is, if the name
 * or one of the aliases matches the name.
 * @param name	Name to test.
 * @return		True if the name is matched, false else.
 */
bool Plugin::matches(const string& name) const {
	if(_name == name)
		return true;
	for(int i = 0; i < _aliases.count(); i++)
		if(name == _aliases[i])
			return true;
	return false;
}

} } // elm::sys
