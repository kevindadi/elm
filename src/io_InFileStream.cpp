/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * src/InFileStream.cpp -- implementation for InFileStream class.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elm/io/InFileStream.h>
#include <elm/io/io.h>

namespace elm { namespace io {

/**
 * Stream for outputting to a file.
 */

/**
 * Build an output file stream by creating a new file or deleting an old one.
 * @param path Path of the file to wriet to.
 */
InFileStream::InFileStream(CString path)
: SystemInStream(open(path.chars(), O_RDONLY, 0777)) {
	if(fd() < 0)
		throw IOException("cannot open file \"%s\" : %s", &path, &lastErrorMessage());
}

/**
 * Destructor (close the file if it is opened).
 */
InFileStream::~InFileStream(void) {
	close();
}

/**
 * Close the file. Subsequent writes will fail.
 */
void InFileStream::close() {
	if(_fd >= 0) {
		::close(_fd);
		_fd = -1;
	}
}

} } // elm::io
