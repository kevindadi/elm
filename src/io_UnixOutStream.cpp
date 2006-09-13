/*
 * $Id$
 * Copyright (c) 2004-06, IRIT - UPS.
 *
 * src/io_UnixOutStream.cpp -- implementation of UnixOutStream class.
 */

#include <unistd.h>
#include <errno.h>
#include <elm/io/UnixOutStream.h>

namespace elm { namespace io {

/**
 * @class UnixOutStream <elm/io.h>
 * Output stream implementation using the Unix low-level IO system.
 */

/**
 * @fn UnixOutStream::UnixOutStream(int _fd);
 * Build a Unix output stream using a file descriptor identifier.
 * @param _fd	File descriptor identifier.
 */


/**
 * Return the last occured error message.
 * @return	Last error message.
 */
CString UnixOutStream::lastErrorMessage(void) {
	return strerror(errno);
}


// Overloaded
int UnixOutStream::write(const char *buffer, int size) {
	return ::write(_fd, buffer, size);
}

// Overloaded
int UnixOutStream::flush(void) {
	return 0;
}


/**
 * Stream pointing to the standard output.
 */
static UnixOutStream unix_stdout(1);
OutStream& stdout = unix_stdout;

/**
 * Stream pointing to the standard error output.
 */
static UnixOutStream unix_stderr(2);
OutStream& stderr = unix_stderr;	

} } // elm::io
