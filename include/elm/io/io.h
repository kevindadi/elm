/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * io.h -- formatted IO classes interfaces.
 */
#ifndef ELM_IO_IO_H
#define ELM_IO_IO_H

#include <elm/utility.h>
#include <elm/io/InStream.h>
#include <elm/io/OutStream.h>
#include <elm/io/Output.h>

namespace elm { namespace io {

// IOException class
class IOException: public Exception {
	String msg;
public:
	IOException(void);
	inline IOException(CString message): msg(message) { };
	inline IOException(String message): msg(message) { };
	virtual String message(void) { return msg; };	
};

} // io

// Standard environment
extern io::Output cout;
extern io::Output cerr;

} // elm

#endif	// ELM_IO_IO_H
