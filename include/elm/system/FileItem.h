/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/FileIem.h -- FileItem class interface.
 */
#ifndef ELM_SYSTEM_FILE_ITEM_H
#define ELM_SYSTEM_FILE_ITEM_H

#include <sys/stat.h>
#include <elm/system/Path.h>

namespace elm { namespace system {

// External
class File;
class Directory;

// FileItem class
class FileItem {
	int usage;
protected:
	Directory *parent;
	Path _path;
	ino_t ino;
	FileItem(Path path, ino_t inode);
	virtual ~FileItem(void);
public:
	static FileItem *get(Path path);
	void use(void);
	void release(void);
	
	// Accessors
	virtual File *toFile(void);
	virtual Directory *toDirectory(void);
	String name(void);
	Path& path(void);
	bool isReadable(void);
	bool isWritable(void);
	bool isDeletable(void);
};

} } // elm::system

#endif // ELM_SYSTEM_FILE_ITEM_H
