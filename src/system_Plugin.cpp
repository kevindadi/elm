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

#if defined(__LINUX)
#define WITH_LIBTOOL
#endif

#include <elm/assert.h>
#ifdef WITH_LIBTOOL
#	include <ltdl.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#else
#	include <dlfcn.h>
#endif
#include <elm/system/Plugin.h>
#include <elm/system/Plugger.h>

namespace elm { namespace system {

/* Maximal age for unused plugins before deletion
 * (expressed in plugin getting cycles).
 */
#define MAX_AGE	16


/**
 * @defgroup plugins Plugins
 *
 * @section use_plugins Using a Plugin
 *
 * ELM provides classes to implement plugins in an OS-indepedent way. As this
 * system is based on the libtool package, it may be used on systems with
 * or without shared code facilities.
 *
 * To use plugins, we need to entity kind. A plugin is a piece of code that
 * provides some service while the plugger allows to plug many different
 * plugins to implement this service.
 *
 * In ELM, the plugger is declared with a hook - an identifier allowing
 * an application to have different kinds of services and matching plugins -
 * and a version for the current implemented plugin interface. For example,
 * below, the plugger provides "net_plugin" services at version 1.0.0 (see
 * @ref elm::Version for more details). We may also gives a list of directory
 * to look for finding the plugin.
 * @code
 * elm::system::Plugger net_plugger("net_plugin", Version(1, 0, 0),
 * 	".:/usr/local/net_plugins");
 * @endcode
 *
 * To open a specific plugin named, for example, "my_net_plugin", we have only
 * to call the method Plugger::plug().
 * @code
 * elm::system::Plugin *plugin = net_plugger.plug("my_net_plugin");
 * @endcode
 * If the plugin is found, is loadable and has a compatible version, it loaded,
 * initialized and its instance is returned. If there is an error, a null
 * pointer is returned and the method Plugger::lastErrorMessage() may give
 * some information about the error.
 * @code
 * if(plugin == NULL)
 * 	cout << "ERROR: " << plugger.lastErrorMessage() << io::endl;
 * @endcode
 *
 * Having just a plugin pointer does not provide any service. To do it, we have
 * usually to define an interface that is implemented by the plugin instance.
 * Let's call it "NetPlugin": it must be implement the elm::system::Plugin class.
 * Notice that the interface pass the right name of the service but should not
 * pass the version. Otherwise, the service version would be ever compatible
 * while the actual binary would be compiled for an incompatible version.
 * @code
 * class NetPlugin: public Plugin {
 * public:
	Plugin(String name, const Version& version)
		: Plugin(name, version, "net_plugin") {
 *  	};
 * 	virtual void performService(void) = 0;
 * };
 * @endcode
 * Then, we can cast the plugin to its required interface and we can call the
 * service:
 * @code
 * NetPlugin *net_plugin = (NetPlugin *)plugin;
 * net_plugin->performService();
 * @endcode
 *
 * When the plugin is no more needed, we can simply unplug it:
 * @code
 * net_plugin->unplug();
 * @endcode
 *
 * @section creating_plugins Creating Plugins
 *
 * To create a plugin, we have to define a class implementing the service
 * interface of the plugger to plug to. Let's conteinue the example started
 * in the example from the previous section. Notice that we must implemented
 * the pure virtual functions of the interface in order to be able to create
 * an instance of the plugin class.
 * @code
 * class MyNetPlugin: public NetPlugin {
 * public:
 *		MyNetPlugin(void);
 * 		virtual void performService(void);
 * };
 * @endcode
 *
 * Then, the constructor must pass to the elm::system::Plugin class the name
 * of the service to be hooked to the right plugger with the service version
 * supported by the plugin.
 * @code
 * MyNetPlugin::MyNetPlugin(void): NetPlugin("my_net_plugin", Version(1, 0, 0)) {
 * }
 * @endcode
 * Notice how the version is encoded in the plugin code. If this plugin is then
 * used with in incompatible version of the plugger, say 1.2.0. The compatibility
 * comparison will compare the version 1.0.0 (from the plugin) with the version
 * 1.2.0 (from the plugger) and will detect possible binary incompatibility and
 * prevent the invalid linkage.
 *
 * Then we need to declare the plugin instance, a global variable with the
 * name of the service.
 * @code
 * MyNetPlugin my_net_plugin;
 * Plugin *ney_plugin = &my_net_plugin;
 * @endcode
 * The result source must then be compiled to produce a shared code with
 * libtool.
 * @code
 * libtool --mode=link g++ -module -o my_net_plugin.la my_net_plugin.cpp \
 * 		-rpath /usr/local/net_plugins
 * @endcode
 */

/**
 * @class Plugin <elm/system/Plugin.h>
 * The class Plugin allows implementing plug-ins in OS-independent way. See
 * @ref plugins for more details.
 * @ingroup plugins
 */


/**
 * List of static plugins.
 */
genstruct::Vector<Plugin *> Plugin::static_plugins;


/**
 * List of unused plugins.
 */
genstruct::Vector<Plugin *> Plugin::unused_plugins;


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
	_hook(hook),
	_name(name),
	per_vers(plugger_version),
	_handle(0),
	state(0),
	_aliases(aliases),
	magic(MAGIC)
{
	if(hook)
		static_plugins.add(this);
	//cout << "Construct " << this << io::endl;
}


/**
 */
Plugin::~Plugin(void) {
	//cout << "Destruct " << this << io::endl;
}


/**
 * For internal use only.
 */
void Plugin::plug(void *handle) {
	// Usage incrementation
	if(state > 0)
		state++;

	// Initialization
	else if(state == 0) {
		startup();
		state = 1;
		if(handle) {
#if defined(__LINUX)
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
			#ifdef WITH_LIBTOOL
				lt_dlclose((lt_dlhandle)_handle);
			#elif defined(__WIN32) || defined(__WIN64)
				FreeLibrary(reinterpret_cast<HMODULE&>(_handle));
			#else
				dlclose(_handle);
			#endif
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

} } // elm::system
