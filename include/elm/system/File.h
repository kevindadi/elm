/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/File.h -- File class interface.
 */
#ifndef ELM_SYSTEM_FILE_H
#define ELM_SYSTEM_FILE_H

#include <elm/system/FileItem.h>

namespace elm { namespace system {

// File class
class File: public FileItem {
	friend class FileItem;
	File(Path path, ino_t inode);
public:

	// Accessors
	int size(void);
	
	// Overload
	virtual File *toFile(void);
};

} } // elm::system

#endif // ELM_SYSTEM_FILE_H

