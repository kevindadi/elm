/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/prog/system_Plugin.h -- Plugin class implementation.
 */

#include <elm/system/Plugin.h>
#include <elm/system/Plugger.h>

namespace elm { namespace system {

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
 * Build a new plugin.
 * @param name				Plugin name.
 * @param plugger_version	Plugger version (used for checking compatibility
 * 							between plugin and user application API).
 */
Plugin::Plugin(String name, const Version& plugger_version)
: _name(name), per_vers(plugger_version), usage(0), plugger(0) {
}


/**
 * For internal use only.
 */
void Plugin::use(void) {
	usage++;
}


/**
 * For internal use only.
 */
void Plugin::plug(Plugger *_plugger) {
	assert(_plugger);
	assert(!plugger);
	plugger = _plugger;
	use();
	startup();
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
 * When a plugin is no more useful, this method must be called for letting
 * the system cleaning its data structures.
 */
void Plugin::release(void) {
	usage--;
	if(!usage && plugger) {
		cleanup();
		plugger->unplug(this);		
	}
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
 
} } // elm::system
