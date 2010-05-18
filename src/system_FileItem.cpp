/*
 *	$Id$
 *	FileItem class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
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

#include <elm/assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <elm/system/FileItem.h>
#include <elm/system/File.h>
#include <elm/system/Directory.h>
#include <elm/genstruct/HashTable.h>
#include <elm/system/SystemException.h>
#include <elm/util/strong_type.h>

namespace elm {

STRONG_TYPE(inode_t, ino_t);

// inode_t hash key
template <>
class HashKey<inode_t> {
public:
	static t::hash hash(inode_t v)
		{ return t::hash(v); }
	static bool equals(inode_t key1, inode_t key2)
		{ return key1 == key2; }
};

// Used for retrieving files by name.
static genstruct::HashTable<inode_t, system::FileItem *> *files = 0;


namespace system {

/**
 * @class FileItem
 * This class represents an item of the file systems. It is inheited from
 * @ref File and @ref Directory classes.
 * @ingroup system_inter
 */
 

/**
 */ 
FileItem::FileItem(Path path, ino_t inode):	usage(0), _path(path), ino(inode) {
	ASSERTP(path, "null path");
}


/**
 * Virtual destructor.
 */
FileItem::~FileItem(void) {
	ASSERT(!usage);
}


/**
 * Find a file by its name.
 * @param path				Path of the looked file.
 * @return					File matching the given path or null if file does not exists.
 * @throw SystemException	If the file does not exist or can not be accessed.
 */
FileItem *FileItem::get(Path path) throw(SystemException) {
	
	// Need to initialize ?
	if(!files)
		files = new genstruct::HashTable<inode_t, FileItem *>;;
	
	 // Look at stat
	 struct stat st;
	 if(stat(&path.toString(), &st) < 0) {
	 	if(errno == ENOENT || errno == ENOTDIR)
	 		return 0;
	 	else
	 		throw SystemException(errno, "filesystem");
	 }
	 
	// Look in the created files
	FileItem *result = files->get(st.st_ino, 0);
	
	// Create the file
	if(!result) {
		if(S_ISDIR(st.st_mode))
			result = new Directory(path, st.st_ino);
		else if(S_ISREG(st.st_mode))
			result = new File(path, st.st_ino);
		else
			result = new FileItem(path, st.st_ino);
		files->put(st.st_ino, result);
	}
	
	// Return found file
	result->usage++;
	return result;
}


/**
 */
void FileItem::use(void) {
	usage++;
}


/**
 * This method must be called when a file item is no more usable by its getter.
 * According other usage, it may be fully deleted.
 */
void FileItem::release(void) {
	usage--;
	if(!usage) {
		files->remove(ino);
		delete this;
	}
}


/**
 * Convert the file item to file if it is consistent.
 * @return	Matching file or null (if it is a directory for example).
 */
File *FileItem::toFile(void) {
	return 0;
}


/**
 * Convert the file item to directory if it is consistent.
 * @return Matching directory or null (if it is a regular file for example).
 */
Directory *FileItem::toDirectory(void) {
	return 0;
}


/**
 * Get the name of the file.
 * @return	File name.
 */
String FileItem::name(void) {
	return _path.namePart();
}


/**
 * Get the path of the file.
 * @return File path.
 */
Path& FileItem::path(void) {
	return _path;
}


/**
 * Test if the file is readble.
 * @return True if it is readable.
 */
bool FileItem::isReadable(void) {
	if(!access(&_path.toString(), R_OK))
		return true;
	else if(errno == EACCES)
		return false;
	else
		throw SystemException(errno, "filesystem");
}


/**
 * Test if the file is readble.
 * @return True if it is readable.
 */
bool FileItem::isWritable(void) {
	if(!access(&_path.toString(), W_OK))
		return true;
	else if(errno == EACCES)
		return false;
	else
		throw SystemException(errno, "filesystem");
}


/**
 * Test if the file may be deleted.
 * @return True if is deletable, false else.
 */
bool FileItem::isDeletable(void) {
	if(!access(&_path.parent().toString(), W_OK))
		return true;
	else if(errno == EACCES)
		return false;
	else
		throw SystemException(errno, "filesystem");	
}
	
} } // elm::system
