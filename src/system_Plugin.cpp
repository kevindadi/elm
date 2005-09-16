/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/prog/system_Plugin.h -- Plugin class implementation.
 */

#include <assert.h>
#include <dlfcn.h>
#include <elm/system/Plugin.h>
#include <elm/system/Plugger.h>

namespace elm { namespace system {

/* Maximal age for unused plugins before deletion
 * (expressed in plugin getting cycles).
 */
#define MAX_AGE	16


/**
 * @class Plugin
 * 
 * The class Plugin allows implementing plug-ins in OS-independent way.
 * For building a plugin, an object inheriting from Plugin class must be
 * declared global in the shared-library or code unit containing the plugin.
 * 
 * Usually, the plug-in user application interface with the plugin thanks
 * to a dedicated class. In order to let elm manage the plugin, this class
 * must inherit from Plugin class and the Plugger class will return the
 * plugin object from the selected code unit. Next, the user application can
 * cast this object in the interface class.
 * 
 * For ensuring compatibility, the plugin and the plugger must be ok about
 * the plugger version. This version is provided by the user application and
 * must follows the usual ELM version convention (See @ref Version). If the plugin
 * is ascendant-compatible with pluggger version, it will be plugged else
 * another plugin is looked for.
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
 */
Plugin::Plugin(String name, const Version& plugger_version, String hook)
: _name(name), per_vers(plugger_version), _hook(hook), state(0), _handle(0) {
	if(hook)
		static_plugins.add(this);
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
			_handle = handle;
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
	assert(state);
	
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
			dlclose(_handle);
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
 * @fn String Plugin::name(void) const;
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
	for(int i = unused_plugins.length() - 1; i >= 0; i--)
		unused_plugins[i]->unplug();
}


/**
 * For internal use only.
 */
Plugin *Plugin::get(String hook, String name) {
	
	// Find the plugin
	Plugin *found = 0;
	for(int i = 0; i < static_plugins.length(); i++)
		if(static_plugins[i]->hook() == hook
		&& static_plugins[i]->name() == name)
			return static_plugins[i];
	
	// Not found
	return 0;
}

} } // elm::system
