/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/Plugger.h -- Plugger class interface.
 */
#ifndef ELM_SYSTEM_PLUGGER_H
#define ELM_SYSTEM_PLUGGER_H

#include <elm/system/Plugin.h>
#include <elm/genstruct/Vector.h>

namespace elm { namespace system {

// Plugger class
class Plugger {
	friend class Plugin;
public:
	typedef enum error_t {
		OK = 0,
		NO_PLUGIN,
		NO_HOOK,
		BAD_VERSION
	} error_t;

private:	
	typedef struct plug_t {
		String name;
		void *handle;
		Plugin *plugin;
	} plug_t;
	
	String hook;
	Version per_vers;
	elm::genstruct::Vector<plug_t> plugs;
	elm::genstruct::Vector<String> paths;
	error_t err;
	void unplug(Plugin *plugin);
public:
	Plugger(String hook, const Version& plugger_version, String paths = "*");
	void addPath(String path);
	void removePath(String path);
	void resetPaths(void);
	Plugin *plug(String name);
	inline error_t lastError(void);
	String lastErrorMessage(void);
};

// Inlines
inline Plugger::error_t Plugger::lastError(void) {
	return err;
}

} } // elm::system

#endif // ELM_SYSTEM_PLUGGER_H
