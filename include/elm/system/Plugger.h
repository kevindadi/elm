/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/Plugger.h -- Plugger class interface.
 */
#ifndef ELM_SYSTEM_PLUGGER_H
#define ELM_SYSTEM_PLUGGER_H

#include <elm/Iterator.h>
#include <elm/system/Plugin.h>
#include <elm/genstruct/Vector.h>
#include <elm/system/Directory.h>

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
	
	static genstruct::Vector<Plugger *> pluggers;
	String _hook;
	Version per_vers;
	genstruct::Vector<Plugin *> plugins;
	genstruct::Vector<String> paths;
	error_t err;
	static void leave(Plugin *plugin);
	Plugin *plug(Plugin *plugin, void *handle);
	inline genstruct::Vector<Plugin *>& statics(void);

public:
	Plugger(String hook, const Version& plugger_version, String paths = "*");
	~Plugger(void);
	void addPath(String path);
	void removePath(String path);
	void resetPaths(void);
	Plugin *plug(String name);
	Plugin *plugFile(String path);
	inline error_t lastError(void);
	String lastErrorMessage(void);
	inline String hook(void) const;
	
	// Iterator class
	class Iterator: public PreIterator<Iterator, String> {
		Plugger& plugger;
		genstruct::Vector<Plugin *>& statics;
		int i;
		int path;
		Directory::Iterator *file;
		void go(void);
	public:
		Iterator(Plugger& _plugger);
		~Iterator(void);
		bool ended(void) const;
		String item(void) const;
		void next(void);
		Plugin *plug(void) const;
	};
};

// Inlines
inline Plugger::error_t Plugger::lastError(void) {
	return err;
}

inline String Plugger::hook(void) const {
	return _hook;
}

inline genstruct::Vector<Plugin *>& Plugger::statics(void) {
	return Plugin::static_plugins;
}

} } // elm::system

#endif // ELM_SYSTEM_PLUGGER_H
