/*
 * $Id$
 * Copyright (c) 2004-06, IRIT - UPS.
 *
 * src/UnixInStream.cpp -- implementation for UnixInStream class.
 */

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <elm/io/UnixInStream.h>

namespace elm { namespace io {

/**
 * @class UnixInStream
 * Input stream implementation using the Unix low-level IO system.
 */

	
/**
 * @fn UnixInStream::UnixInStream(int fd);
 * Build a new Unix input stream with the given file descriptor.
 * @param fd	File descriptor to use.
 */

	
/**
 * @fn int UnixInStream::fd(void) const;
 * Get the file descriptor of this Unix file stream.
 * @return	File descriptor.
 */


/**
 */	
int UnixInStream::read(char *buffer, int size) {
	return ::read(_fd, buffer, size);
}


/**
 */
CString UnixInStream::lastErrorMessage(void) {
	return strerror(errno);
}


/**
 * Stream pointing to the standard error input.
 */
/*static UnixInStream unix_stdin(0);
InStream& stdin = unix_stdin;*/	

} } // elm::io
