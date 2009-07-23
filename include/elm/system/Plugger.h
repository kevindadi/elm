/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/Plugger.h -- Plugger class interface.
 */
#ifndef ELM_SYSTEM_PLUGGER_H
#define ELM_SYSTEM_PLUGGER_H

#include <elm/PreIterator.h>
#include <elm/system/Plugin.h>
#include <elm/genstruct/Vector.h>
#include <elm/system/Directory.h>
#include <elm/system/Path.h>
#include <elm/util/ErrorHandler.h>

namespace elm { namespace system {

// Plugger class
class Plugger: public ErrorBase {
	friend class Plugin;
public:
	typedef enum error_t {
		OK = 0,
		NO_PLUGIN,
		NO_HOOK,
		BAD_VERSION,
		NO_MAGIC
	} error_t;

public:
	Plugger(CString hook, const Version& plugger_version, String paths = "*");
	virtual ~Plugger(void);
	void addPath(String path);
	void removePath(String path);
	void resetPaths(void);
	Plugin *plug(const string& path);
	Plugin *plugFile(String path);
	inline String hook(void) const;

	// deprecated
	virtual void onError(String message);
	virtual void onWarning(String message);
	error_t lastError(void);
	String lastErrorMessage(void);

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

	class PathIterator: public genstruct::Vector<string>::Iterator {
	public:
		inline PathIterator(const Plugger& plugger)
			: genstruct::Vector<string>::Iterator(plugger.paths) { }
		inline PathIterator(const PathIterator& iter)
			: genstruct::Vector<string>::Iterator(iter) { }
	};

private:

	static genstruct::Vector<Plugger *> pluggers;
	CString _hook;
	Version per_vers;
	genstruct::Vector<Plugin *> plugins;
	genstruct::Vector<String> paths;
	error_t err;
	static void leave(Plugin *plugin);
	Plugin *plug(Plugin *plugin, void *handle);
	inline genstruct::Vector<Plugin *>& statics(void);
	string getLastError(void);
	void onError(error_level_t level, const string& message);
};

// Inlines
inline String Plugger::hook(void) const {
	return _hook;
}

inline genstruct::Vector<Plugin *>& Plugger::statics(void) {
	return Plugin::static_plugins;
}

} } // elm::system

#endif // ELM_SYSTEM_PLUGGER_H
