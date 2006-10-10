/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * io.h -- formatted IO classes interfaces.
 */
#ifndef ELM_IO_IO_H
#define ELM_IO_IO_H

#include <elm/utility.h>
#include <elm/system/SystemIO.h>
#include <elm/io/Output.h>
#include <elm/io/Input.h>

namespace elm { namespace io {

// IOException class
class IOException: public MessageException {
	String msg;
public:
	inline IOException(CString message, ...);
	inline IOException(CString message, VarArg& args);
};

// IOException inlines
inline IOException::IOException(CString message, ...) {
	VARARG_BEGIN(args, message)
		buildMessage(message, args);
	VARARG_END;
}

inline IOException::IOException(CString message, VarArg& args)
: MessageException(message, args) {
}

} // io

// Standard environment
extern io::Output cout;
extern io::Output cerr;
extern io::Input cin;

} // elm

#endif	// ELM_IO_IO_H
