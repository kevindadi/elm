/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/OutFileStream.h -- out file stream implementation.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elm/io/OutFileStream.h>

namespace elm { namespace io {

/**
 * Stream for outputting to a file.
 */

/**
 * Build an output file stream by creating a new file or deleting an old one.
 * @param path Path of the file to wriet to.
 */
OutFileStream::OutFileStream(CString path)
: UnixOutStream(open(path.chars(), O_CREAT | O_TRUNC | O_WRONLY, 0777)) {
}

/**
 * Destructor (close the file if it is opened).
 */
OutFileStream::~OutFileStream(void) {
	close();
}

/**
 * Close the file. Subsequent writes will fail.
 */
void OutFileStream::close() {
	if(_fd >= 0) {
		::close(_fd);
		_fd = -1;
	}
}

} } // elm::io
