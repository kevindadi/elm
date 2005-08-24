/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/system_Path.h -- Path class implementation.
 */
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <elm/genstruct/Vector.h>
#include <elm/system/Path.h>
#include <elm/system/SystemException.h>

namespace elm { namespace system {

/**
 * @class Path
 * This class represents a file path in the current file system.
 */


/**
 * @fn Path::Path(String path);
 * Build a new path from the given string.
 * @param path	Path to store.
 */


/**
 * @fn Path::Path(Path& path);
 * Build a path from another path.
 */


/**
 * Get the canonical form of the current path.
 * Usually, a relative path becomes an absolute one. Relative operators (.., .)
 * are removed if it is possible.
 */
Path Path::canonical(void) {
	
	// Make it absolute
	String path = buf;
	if(isRelative()) {
		Path abs = absolute();
		path = abs.buf;
	}
	
	// Select kept components
	genstruct::Vector<String> comps;
	int stop = path.indexOf(SEPARATOR), start = 0;
	while(stop >= 0) {
		
		// Select the component
		String comp = path.substring(start, stop - start);
		if(!comp || comp == ".")
			;
		else if(comp == "..") {
			if(comps.length() > 0)
				comps.setLength(comps.length() - 1);
		}
		else
			comps.add(comp);
		
		// Go to next component
		start = stop + 1;
		stop = path.indexOf(SEPARATOR, start);
	}
	
	// Rebuild path
	StringBuffer buffer;
	for(int i = 0; i < comps.length(); i++)
		buffer << SEPARATOR << comps[i];
	return Path(buffer.toString());
}


/**
 * Get the absolute path matching the current path.
 * @return	Matching absolute path.
 */
Path Path::absolute(void) {
	if(isAbsolute())
		return *this;
	else if(isHomeRelative()) 
		return home() / Path(buf.substring(1));
	else
		return current() / *this;
}


/**
 * Change the current path.
 * @param path	New current path.
 */
void Path::setCurrent(Path& path) {
	if(chdir(&path.buf) < 0)
		throw SystemException(errno, "elm::system::Path");
}


/**
 * Build a new path by appending two paths.
 * @param path	Path to append.
 * @return		New path.
 */
Path Path::append(Path path) {
	if(!buf)
		return path;
	else if(!path)
		return *this;
	else {
		StringBuffer buffer;
		buffer << buf << SEPARATOR << path.buf;
		return Path(buffer.toString());
	}
}


/**
 * Find the parent path of the current or an empty path if there is no parent.
 * @return	Parent path.
 */
Path Path::parent(void) {
	int pos = buf.lastIndexOf(SEPARATOR);
	if(pos < 0)
		return Path("");
	else
		return Path(buf.substring(0, pos));
}


/**
 * @fn String& Path::toString(void);
 * Convert the path to string.
 * @return	Matching string.
 */


/**
 * Return the name part of the path.
 * @return	Name part.
 */
String Path::namePart(void) {
	int pos = buf.lastIndexOf(SEPARATOR);
	if(pos < 0)
		return buf;
	else
		return buf.substring(pos + 1);
}


/**
 * Return the directory part of the path.
 * @return	Directory part.
 */
String Path::dirPart(void) {
	int pos = buf.lastIndexOf(SEPARATOR);
	if(pos < 0)
		return "";
	else
		return Path(buf.substring(0, pos));
}


/**
 * Test if the path is absolute.
 * @return	True if it is absolute, false else.
 */
bool Path::isAbsolute(void) {
	return buf.length() > 0 && buf[0] == SEPARATOR;
}


/**
 * Test if the path is relative.
 * @return	True if it is relative, false else.
 */
bool Path::isRelative(void) {
	return !isAbsolute();
}


/**
 * Test if the path is home-relative. On Unix, it is usually starting with "~".
 * @return	True if it is home-relative, false else.
 */
bool Path::isHomeRelative(void) {
	return buf.length() > 0 && buf[0] == '~';	
}


/**
 * @fn bool Path::equals(Path& path);
 * Test if two paths are lexically equals.
 * @return	True if they equals, false else.
 */


/**
 * @fn bool Path::contains(Path& path);
 * Test if a path lexically contains another path.
 * @return	True if it contains, false else.
 */


/**
 * Get the current path.
 * @return	Current path.
 */
Path Path::current(void) {
	int size = 256;
	while(true) {
		char buf[size];
		if(getcwd(buf, size))
			return Path(buf);
		else
			size *= 2;
	}
	return Path("");
}


/**
 * Get the path of the home directory.
 * @return	Home directory.
 */
Path Path::home(void) {
	return Path(getenv("HOME"));
}


/**
 * @fn Path& Path::operator=(Path& path);
 * Allows assignment in the path.
 * @param path	Assigned value.
 */


/**
 * @fn bool Path::operator==(Path& path);
 * Same as @ref equals().
 */


/**
 * @fn bool Path::operator!=(Path& path);
 * Same as !@ref equals().
 */


/**
 * @fn Path Path::operator/(Path& path);
 * Same as @ref append.
 */


/**
 * @fn Path::operator String& (void);
 * Convert to string.
 */


/**
 * @fn Path::operator bool (void);
 * Test if the path is null.
 * @return	True if it is not null, false else.
 */

} } // elm::system
