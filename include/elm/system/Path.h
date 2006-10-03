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
	inline Path(const char *path);
	inline Path(CString path);
	inline Path(const String& path);
	inline Path(const Path& path);
	Path canonical(void);
	Path absolute(void);
	static void setCurrent(Path& path);
	Path append(Path path);
	Path parent(void);
	Path setExtension(CString new_extension);
	
	// Accessors
	inline const String& toString(void) const;
	String namePart(void) const;
	String dirPart(void) const;
	Path basePart(void) const;
	String extension(void) const;
	bool isAbsolute(void) const;
	bool isRelative(void) const;
	bool isHomeRelative(void) const;
	inline bool equals(Path& path) const;
	inline bool contains(Path& path) const;
	static Path current(void);
	static Path home(void);
	
	// Operator
	inline Path& operator=(Path& path);
	inline bool operator==(Path& path);
	inline bool operator!=(Path& path);
	inline Path operator/(Path path);
	inline operator const String& (void) const;
	inline operator bool (void) const;
	inline const char *operator&(void) const { return &buf; };
};


// Inlines
inline Path::Path(const char *path): buf(path) {
}

inline Path::Path(CString path): buf(path) {
}

inline Path::Path(const String& path): buf(path) {
}

inline Path::Path(const Path& path): buf(path.buf) {
}


inline const String& Path::toString(void) const {
	return buf;
}

inline bool Path::equals(Path& path) const {
	return buf == path.buf;
}

inline bool Path::contains(Path& path) const {
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

inline Path::operator const String& (void) const {
	return toString();
}

inline Path::operator bool (void) const {
	return buf;
}

inline io::Output& operator<<(io::Output& out, const Path& path) {
	out << path.toString();
	return out;
}

} } // elm::system

#endif // ELM_SYSTEM_PATH_H
