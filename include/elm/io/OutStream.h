/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * stream.h -- abstract stream classes interfaces.
 */
#ifndef ELM_IO_OUTSTREAM_H
#define ELM_IO_OUTSTREAM_H

#include <elm/string/CString.h>

namespace elm { namespace io {

// OutStream class
class OutStream {
public:
	virtual ~OutStream(void) { };
	virtual int write(const char *buffer, int size) = 0;
	virtual int write(char byte);
	virtual int flush(void) = 0;
	virtual CString lastErrorMessage(void);
};

// Standard IO streams	
extern OutStream& stdout;
extern OutStream& stderr;	


} }	// elm::io

#endif // ELM_IO_OUTSTREAM_H
