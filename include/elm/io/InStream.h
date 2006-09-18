/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/InStream.h -- interface for InStream class.
 */
#ifndef ELM_IO_INSTREAM_H
#define ELM_IO_INSTREAM_H

#include <elm/string/CString.h>

namespace elm { namespace io {

// InStream class
class InStream {
public:
	static const int FAILED = -1;
	static const int ENDED = -2;
	virtual ~InStream(void) { };
	virtual int read(char *buffer, int size) = 0;
	virtual int read(void);
	virtual CString lastErrorMessage(void);
};

// Standard IO streams	
extern InStream& stdin;

} }	// io::elm

#endif // ELM_IO_INSTREAM_H
