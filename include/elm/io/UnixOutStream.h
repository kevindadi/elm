/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/OutStream.h -- interface for OutStream class.
 */
#ifndef ELM_IO_UNIX_OUTSTREAM_H
#define ELM_IO_UNIX_OUTSTREAM_H

#include <elm/io/OutStream.h>

namespace elm { namespace io {

// UnixOutStream class
class UnixOutStream: public OutStream {
protected:
	int _fd;
public:
	inline UnixOutStream(int fd): _fd(fd) { };
	inline int fd(void) const { return _fd; };
	virtual int write(const char *buffer, int size);	
	virtual int flush(void);
};

} } // elm::io

#endif	// ELM_IO_UNIX_OUTSTREAM_H
