/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * src/system_System.cpp -- System class implementatuib.
 */

#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <elm/system/System.h>
#include <elm/system/SystemException.h>

namespace elm { namespace system {

/**
 * @class  PipeInStream
 * A system stream implementing the input end of a pipe.
 */


/**
 * Create a pipe stream.
 * @param fd	Unix file descriptor.
 */
PipeInStream::PipeInStream(int fd): SystemInStream(fd) {
}


/**
 * Delete the pipe stream.
 */
PipeInStream::~PipeInStream(void) {
	close(fd());
}


/**
 * @class  PipeOutStream
 * A system stream implementing the output end of a pipe.
 */


/**
 * Build a pipe output stream.
 * @param fd	Unix file descriptor.
 */
PipeOutStream::PipeOutStream(int fd): SystemOutStream(fd) {
}


/**
 * Delete the pipe stream.
 */
PipeOutStream::~PipeOutStream(void) {
	close(fd());
}


/**
 * @class System
 * Non-instatiable object giving access to system facilities.
 */
 

/**
 * Create a  pipe with input / output end streams.
 * @return	Linked streams.
 * @throws	System exception.
 */
Pair<PipeInStream *, PipeOutStream *> System::pipe(void) {
	int fds[2];
	if(::pipe(fds) < 0) {
		assert(errno != EFAULT);
		throw SystemException(errno, "pipe creation");
	}
	return pair(
		new PipeInStream(fds[0]),
		new PipeOutStream(fds[1]));
}

} } // elm::system
