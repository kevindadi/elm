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


/**
 * @class Plugger::Iterator
 * Used for exploring plugins hookable on the current plugger.
 */


/**
 */
void Plugger::Iterator::go(void) {
	bool found = false;
	while(!found) {
		
		// Next file
		if(file)
			file->next();
		
		// Next path
		if(!file || file->ended()) {
			if(file) {
				delete file;
				file = 0;
			}
			path++;
			if(path >= plugger.paths.length())
				return;
			FileItem *item = FileItem::get(Path(plugger.paths[path]));
			if(!item || !item->toDirectory())
					continue;
			else {
				file = new Directory::Iterator(item->toDirectory());
				if(file->ended())
					continue;
			}
		}
		
		// Look current file
		if(file->item()->path().toString().endsWith(".so"))
			return;
	}
}


/**
 * Build a new iterator.
 * @param plugger	Used plugger.
 */
Plugger::Iterator::Iterator(Plugger& _plugger): plugger(_plugger), path(-1),
file(0) {
	go();
}


/**
 */
Plugger::Iterator::~Iterator(void) {
	if(file)
		delete file;
}


/**
 * Test if the iteration is ended.
 * @return	True if it is ended.
 */
bool Plugger::Iterator::ended(void) const {
	return path >= plugger.paths.length();
}


/**
 * Get the current plugin name.
 * @return	Current plugin name.
 */
String Plugger::Iterator::item(void) const {
	Path path = (*file)->path();
	String name = path.namePart();
	name = name.substring(0, name.length() - 3);
	return name;
}


/**
 * Go to the next plugin.
 */
void Plugger::Iterator::next(void) {
	go();
}


/**
 * Plug the current plugin.
 * @return	Matching plugin.
 */
Plugin *Plugger::Iterator::plug(void) const {
	return plugger.plug(item());
}

} }	// elm::system
