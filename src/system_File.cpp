/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/system_File.cpp -- File class implementation.
 */

#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <elm/system/File.h>
#include <elm/system/SystemException.h>

namespace elm { namespace system {

/**
 * @class File
 * This class represents a regular file.
 */


/**
 */
File::File(Path path, ino_t inode): FileItem(path, inode) {
	assert(path);
}


/**
 * Get the size of the file.
 * @return	File size.
 */
int File::size(void) {
	struct stat st;
	if(stat(&path().toString(), &st) < 0)
		throw SystemException(errno, "filesystem");
	return st.st_size;
}


/**
 */
File *File::toFile(void) {
	return this;
}

} } // elm::system
