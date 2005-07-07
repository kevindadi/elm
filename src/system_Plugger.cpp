/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/system_Plugger.h -- Plugger class implementation.
 */

#include <assert.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <elm/system/Plugger.h>
#include <elm/io.h>

namespace elm { namespace system {

/**
 * @class Plugger
 * This class is used for connecting Plugin object from dynamic loaded code
 * unit. The Plugin object is retrieved as a global data matching the hook name
 * passed to the plugger creation. The dynamic loaded code units are retrieved
 * from the paths given to the plugger object. See @ref Plugin.
 */


/**
 * Build a new plugger.
 * @param _hook				Hook name for retrieving plugin in the code unit.
 * @param plugger_version	Plugger version for compatibility checking.
 * @param _paths			List of path separated by ":" for retrieving
 * 							the plugin. Pass "*" for initializing with the
 * 							default system paths.
 */
Plugger::Plugger(String _hook, const Version& plugger_version, String _paths)
: hook(_hook), per_vers(plugger_version), err(OK) {
	
	// Look in the system paths
	if(_paths == "*")
		_paths = getenv("LD_LIBRARY_PATH");
	
	// Scan the paths
	int index = _paths.indexOf(':');
	while(index >= 0) {
		if(index)
			paths.add(_paths.substring(0, index));
		_paths = _paths.substring(index + 1);
		index = _paths.indexOf(':');
	}
	if(_paths)
		paths.add(_paths);
}


/**
 * Add new path for retrieving plugins.
 * @param path	Added path.
 */
void Plugger::addPath(String path) {
	paths.add(path);
}


/**
 * Remove a path.
 * @param path	Removed path.
 */
void Plugger::removePath(String path) {
	paths.remove(path);
}


/**
 * Remove all paths.
 */
void Plugger::resetPaths(void) {
	paths.clear();
}


/**
 * Get a plugin by its name.
 * @param name	Name of the plugin to get.
 * @return		Found plugin or null.
 */
Plugin *Plugger::plug(String name) {
	err = OK;

	// Look in opened plugins
	for(int i = 0; i < plugs.length(); i++)
		if(plugs[i].name == name) {
			plugs[i].plugin->use();
			return plugs[i].plugin;
		}
	
	// Attempt to open it
	for(int i = 0; i < paths.length(); i++) {
		
		// Try to link the SO library
		StringBuffer buf;
		buf << paths[i] << "/" << name << ".so";
		String path = buf.toString();
		//cout << "Opening " << path << "...";
		void *handle = dlopen(&path, RTLD_LAZY);
		if(!handle) {
			//cout << "failed (" << dlerror() << ")\n";
			err = NO_PLUGIN;
			continue;
		}
		//cout << "success\n";
			
		// Look for the plugin symbol
		Plugin *plugin = (Plugin *)dlsym(handle, &hook);
		if(!plugin) {
			err = NO_HOOK;
			continue;
		}
		
		// Check plugger version
		if(!plugin->pluggerVersion().accepts(per_vers)) {
			err = BAD_VERSION;
			continue;
		}
		
		// Create the entry
		err = OK;
		plug_t plug = { name, handle, plugin };
		plugs.add(plug);
		plugin->plug(this);
		return plugin;
	}
	
	// Plug failure
	return 0;
}


/**
 * For internal use only.
 */
void Plugger::unplug(Plugin *plugin) {
	assert(plugin);
	
	// Find the plug
	int i;
	for(i = 0; i < plugs.length(); i++)
		if(plugs[i].plugin == plugin)
			break;
	assert(i < plugs.length());
	
	// Remove it
	dlclose(plugs[i].handle);
	plugs.removeAt(i);
}


/**
 * @fn error_t Plugger::lastError(void);
 * Get the last error.
 * @return	Last error.
 */


/**
 * Get the message for the last error.
 * @return	Error message.
 */
String Plugger::lastErrorMessage(void) {
	switch(err) {
	case OK:
		return "Success.";
	case NO_PLUGIN: {
			StringBuffer buf;
			buf << "cannot open the plugin(" << dlerror() << ").";
			return buf.toString();
		}
	case NO_HOOK:
		return "Found plugin does not contain a hook symbol.";
	case BAD_VERSION:
		return "Found plug-in is incompatible.";		
	default:
		assert(0);
	}
}

} }	// elm::system
