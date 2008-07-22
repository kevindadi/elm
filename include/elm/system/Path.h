/*
 *	$Id$
 *	Path class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-8, IRIT UPS.
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
#ifndef ELM_SYSTEM_PATH_H
#define ELM_SYSTEM_PATH_H

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

	// path testing
	bool exists(void) const;
	bool isFile(void) const;
	bool isDir(void) const;
	bool isReadable(void) const;
	bool isWritable(void) const;
	bool isExecutable(void) const;
	
	// Operator
	inline Path& operator=(const char *str) { buf = str; return *this; }
	inline Path& operator=(CString str) { buf = str; return *this; }
	inline Path& operator=(const String& str) { buf = str; return *this; }
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
	return *this;
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

}	// system

typedef elm::system::Path Path;

} // elm

#endif // ELM_SYSTEM_PATH_H
