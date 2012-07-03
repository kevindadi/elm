/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_file.cpp -- system/file classes test.
 */

#include <elm/util/test.h>
#include <elm/sys/Directory.h>
#include <elm/io.h>

using namespace elm;
using namespace elm::sys;

cstring files[] = {
	"a.txt",
	"b.txt",
	"c.txt",
	"CVS",
	".",
	".."
};
int found = 0;

static bool lookup(FileItem *item) {
	string name = item->path().namePart();
	for(int i = 0; i < 6; i++)
		if(name == files[i]) {
			if(found & (1 << i)) {
				cerr << name << " found several times\n";
				return false;
			}
			found |= 1 << i;
			return true;
		}
	cerr << name << " not in the list\n";
	return false;
}

static bool look_all(void) {
	for(int i = 0; i < 6; i++)
	if(!(found & (1 << i))) {
		cerr << files[i] << " has not been found !\n";
		return false;
	}
	return true;
}

// Entry point
void test_file(void) {
	CHECK_BEGIN("file");

	// Read directory
	FileItem *file = FileItem::get(sys::Path::current() / "test-file");
	CHECK(file->path().namePart() == "test-file");
	CHECK(file);
	Directory *dir = file->toDirectory();
	CHECK(dir);
	CHECK(dir->path().namePart() == "test-file");
	for(Directory::Iterator item(dir); item; item++)
		CHECK(lookup(item));
	CHECK(look_all());	
	CHECK_END;
}
