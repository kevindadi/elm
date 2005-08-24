/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_file.cpp -- system/file classes test.
 */

#include <elm/util/test.h>
#include <elm/system/Directory.h>
#include <elm/io.h>

using namespace elm;
using namespace elm::system;

// Entry point
void test_file(void) {
	CHECK_BEGIN("file");

	// Read directory
	FileItem *file = FileItem::get(Path::current());
	CHECK(file);
	Directory *dir = file->toDirectory();
	CHECK(dir);
	for(Directory::Iterator item(dir); item; item++)
		cout << item->path() << "\n";
	
	CHECK_END;
}
