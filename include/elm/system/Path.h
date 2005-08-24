/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/Path.h -- Path class interface.
 */
#ifndef ELM_SYSTEM_PATH_H
#define ELM_SYSTEM_PATH_H

#include <assert.h>
#include <elm/string.h>
#include <elm/io.h>

namespace elm { namespace system {

// Path class
class Path {
	String buf;
public:
	static const char SEPARATOR = '/';
	static const char PATH_SEPARATOR = ':';
	
	// Constructors
	inline Path(String path);
	inline Path(Path& path);
	Path canonical(void);
	Path absolute(void);
	static void setCurrent(Path& path);
	Path append(Path path);
	Path parent(void);
	
	// Accessors
	inline String& toString(void);
	String namePart(void);
	String dirPart(void);
	bool isAbsolute(void);
	bool isRelative(void);
	bool isHomeRelative(void);
	inline bool equals(Path& path);
	inline bool contains(Path& path);
	static Path current(void);
	static Path home(void);
	
	// Operator
	inline Path& operator=(Path& path);
	inline bool operator==(Path& path);
	inline bool operator!=(Path& path);
	inline Path operator/(Path path);
	inline operator String& (void);
	inline operator bool (void);
};


// Inlines
inline Path::Path(String path): buf(path) {
}

inline Path::Path(Path& path): buf(path.buf) {
}


inline String& Path::toString(void) {
	return buf;
}

inline bool Path::equals(Path& path) {
	return buf == path.buf;
}

inline bool Path::contains(Path& path) {
	return path.buf.startsWith(path.buf);
}

inline Path& Path::operator=(Path& path) {
	buf = path.buf;
}

inline bool Path::operator==(Path& path) {
	return equals(path);
}

inline bool Path::operator!=(Path& path) {
	return !equals(path);
}

inline Path Path::operator/(Path path) {
	return append(path);
}

inline Path::operator String& (void) {
	return toString();
}

inline Path::operator bool (void) {
	return buf;
}

inline io::Output& operator<<(io::Output& out, Path& path) {
	out << path.toString();
	return out;
}

} } // elm::system

#endif // ELM_SYSTEM_PATH_H
