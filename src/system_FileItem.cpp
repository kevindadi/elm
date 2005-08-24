/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * system_FileIem.h -- FileItem class implementation.
 */

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <elm/system/FileItem.h>
#include <elm/system/File.h>
#include <elm/system/Directory.h>
#include <elm/genstruct/HashTable.h>
#include <elm/system/SystemException.h>


namespace elm {

// ino_t hashing
class InoHashKey: public HashKey<ino_t> {
	virtual unsigned long hash(ino_t v) {
		return (unsigned long)v;
	};
	virtual bool equals(ino_t key1, ino_t key2) {
		return key1 == key2;
	};
};
static InoHashKey ino_hkey_obj;
template <> HashKey<ino_t>& HashKey<ino_t>::def = ino_hkey_obj;


// Used for retrieving files by name.
static genstruct::HashTable<ino_t, system::FileItem *> *files = 0;


namespace system {

/**
 * @class FileItem
 * This class represents an item of the file systems. It is inheited from
 * @ref File and @ref Directory classes.
 */
 

/**
 */ 
FileItem::FileItem(Path path, ino_t inode): _path(path), usage(0), ino(inode) {
	assert(path);
}


/**
 * Virtual destructor.
 */
FileItem::~FileItem(void) {
	assert(!usage);
}


/**
 * Find a file by its name.
 * @param path	Path of the looked file.
 * @return		File matching the given path or null if file does not exists.
 */
FileItem *FileItem::get(Path path) {
	
	// Need to initialize ?
	if(!files)
		files = new genstruct::HashTable<ino_t, FileItem *>;;
	
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
