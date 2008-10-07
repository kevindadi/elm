/*
 *	$Id$
 *	System class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
 * 
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software 
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <elm/assert.h>
#include <elm/deprecated.h>
#include <elm/io/RandomAccessStream.h>
#include <elm/system/System.h>
#include <elm/system/SystemException.h>

namespace elm { namespace system {

/**
 * @defgroup system_inter System Interface
 * 
 * These classes provides a unified interface to the OS services.
 * 
 * @section file_man File Management
 * 
 * The first file management class is @ref Path that is used to represent file
 * paths and provides many operations:
 * @li appending path,
 * @li extracting / setting file and directory part,
 * @li getting absolute form,
 * @li getting and setting extension.
 * 
 * It provides also system information about paths:
 * @li getting / setting current path,
 * @li getting home directory,
 * @li getting path item separator,
 * @li getting path separator in path lists.
 * 
 * Other classes represent files themselves. They are derivated from the
 * @ref FileItem class and may be either @ref Directory or @ref File. A file
 * item is obtained by the @ref FileItem::get() method taking the path of
 * looked file. The file item gives the information as name, path, type and
 * access rights. The files provides also information about their size while
 * directories content may be retrieved using the @ref Directory::Iterator or
 * made using the @ref Directory::make method. Once their use is completed,
 * this objects must be released with the method @ref FileItem::release().
 * 
 * @section proc_man Process Management
 * 
 * The @ref Process objects provides control on the process of the OS:
 * @li getting liveness,
 * @li getting return code after death,
 * @li killing,
 * @li waiting until end of the process.
 * 
 * A process may be created using the @ref ProcessBuilder class. It allows
 * to set process configuration like arguments and standard IO. Once the
 * method ProcessBuilder::run() is called, the process is created, either
 * a duplication of the current one, or a new command,
 * with the set configuration and a process object is returned.
 * 
 * @section misc_ser Miscalleneous Classes
 * 
 * First, ELM provides a class to measure times as precisely as possible on
 * the current OS: the class @ref StopWatch.
 * 
 * Then, the static class @ref System provides some services like:
 * @li @ref System::pipe() -- to create piped streams.
 */

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
 * @ingroup system_inter
 */
 

/**
 * Create a  pipe with input / output end streams.
 * @return	Linked streams.
 * @throws	System exception.
 */
Pair<PipeInStream *, PipeOutStream *> System::pipe(void) throw(SystemException) {
	int fds[2];
	
	// Create the pair
	if(::pipe(fds) < 0) {
		ASSERT(errno != EFAULT);
		throw SystemException(errno, "pipe creation");
	}
	
	/* Configure the close-on-exec flag
	 * !!WARNING!! added to implement a working ProcessBuilder: I'm not sure
	 * if it is the best way to do this (yet it is POSIX compliant). */
	fcntl(fds[0], F_SETFD, FD_CLOEXEC);
	fcntl(fds[1], F_SETFD, FD_CLOEXEC);
	
	// Return result
	return pair(
		new PipeInStream(fds[0]),
		new PipeOutStream(fds[1]));
}


/**
 * Generate an integer random number in interval [0, top[.
 * @param top	Maximum exclusive value.
 * @return		Random number.
 */
unsigned int System::random(unsigned int top) {
	int op = rand();
	return int(double(op) * top / RAND_MAX);
}


/**
 * Create a new file and open it to write.
 * The created file must be fried by the caller (causing the file closure).
 * @param path	Path of the file to open.
 * @return		Opened file.
 * @throws		SystemException	Thrown if there is an error.
 */
io::OutStream *System::createFile(const Path& path) throw(SystemException) {
	int fd = ::open(&path.toString(), O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if(fd == -1)
		throw SystemException(errno, "file creation");
	return new SystemOutStream(fd);
}


/**
 * Open a file for reading.
 * The opened file must be fried by the caller (causing the closure).
 * @param path	Path of the file to open.
 * @return		Opened file.
 * @throws		SystemException	Thrown if there is an error.
 */
io::InStream *System::readFile(const Path& path) throw(SystemException) {
	int fd = ::open(&path.toString(), O_RDONLY);
	if(fd == -1)
		throw SystemException(errno, "file reading");
	return new SystemInStream(fd);
}

/**
 * Open a file for appending write.
 * The opened file must be fried by the caller (causing the closure).
 * @param path	Path of the file to open.
 * @return		Opened file.
 * @throws		SystemException	Thrown if there is an error.
 */
io::OutStream *System::appendFile(const Path& path) throw(SystemException) {
	int fd = ::open(&path.toString(), O_APPEND | O_CREAT | O_WRONLY, 0777);
	if(fd == -1)
		throw SystemException(errno, "file appending");
	return new SystemOutStream(fd);
}


// UnixRandomAccessStream class
class UnixRandomAccessStream: public io::RandomAccessStream {
public:
	inline UnixRandomAccessStream(int _fd): fd(_fd) { }
	virtual ~UnixRandomAccessStream(void)
		{ close(fd); }
	
	virtual int read(void *buffer, int size)
		{ return ::read(fd, buffer, size); }
	virtual int write(const char *buffer, int size)
		{ return ::write(fd, buffer, size); }
	cstring lastErrorMessage(void)
		{ DEPRECATED; return strerror(errno); }
	int flush(void)
		{ return 0; }

	virtual pos_t pos(void) const
		{ return lseek(fd, 0, SEEK_CUR); }
	virtual size_t size(void) const
		{ struct stat s; fstat(fd, &s); return s.st_size; }
	virtual bool moveTo(pos_t pos)
		{ return (pos_t)lseek(fd, pos, SEEK_SET) == pos; }
	virtual bool moveForward(pos_t pos)
		{ return (pos_t)lseek(fd, pos, SEEK_CUR) == pos; }
	virtual bool moveBackward(pos_t _pos)
		{ return (pos_t)lseek(fd, pos() - _pos, SEEK_SET) == _pos; }

private:
	int fd;
};


// Build the flags
static inline int makeFlags(System::access_t access) {
	switch(access) {
	case System::READ: return O_RDONLY;
	case System::WRITE: return O_WRONLY;
	case System::READ_WRITE: return O_RDWR;
	default: ASSERT(false); return 0;
	}
}


/**
 * Open a random access stream from a file.
 * @param path			Path of the file to open.
 * @param access		Type of access (one of READ, WRITE, READ_WRITE).
 * @return				Opened file.
 * @throws IOException	Thrown if there is an error.
 */
io::RandomAccessStream *System::openRandomFile(
	const system::Path& path,
	access_t access )
	throw(SystemException)
{
	int fd = ::open(&path.toString(), makeFlags(access));
	if(fd < 0)
		throw SystemException(errno, _ << "cannot open \"" << path << "\"");
	else
		return new UnixRandomAccessStream(fd);
};


/**
 * Create a random access stream from a file, removing it if it already exists.
 * @param path			Path of the file to open.
 * @param access		Type of access (one of READ, WRITE, READ_WRITE).
 * @return				Opened file.
 * @throws IOException	Thrown if there is an error.
 */
io::RandomAccessStream *System::createRandomFile(
	const system::Path& path,
	access_t access)
	throw(SystemException)
{
	ASSERTP(access != READ, "file creation requires at least a write mode");
	int fd = ::open(&path.toString(), makeFlags(access) | O_CREAT | O_TRUNC, 0666);
	if(fd < 0)
		throw SystemException(errno, _ << "cannot create \"" << path << "\"");
	else
		return new UnixRandomAccessStream(fd);
	return 0;
}

} } // elm::system
