/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/Directory.h -- Directory class interface.
 */
#ifndef ELM_SYSTEM_DIRECTORY_H
#define ELM_SYSTEM_DIRECTORY_H

#include <sys/types.h>
#include <dirent.h>
#include <elm/Iterator.h>
#include <elm/system/FileItem.h>

namespace elm { namespace system {

// File class
class Directory: public FileItem {
	friend class FileItem;
	Directory(Path path, ino_t inode);
public:

	// Constructors
	static Directory *make(Path path);

	// Children iterator
	class Iterator: public PreIterator<Iterator, FileItem *> {
		Path path;
		DIR *dir;
		FileItem *file;
		void go(void);
	public:
		Iterator(Directory *directory);
		~Iterator(void);
		bool ended(void) const;
		FileItem *item(void) const;
		void next(void);
	};

	// Overload
	virtual Directory *toDirectory(void);
};

} } // elm::system

#endif // ELM_SYSTEM_DIRECTORY_H

