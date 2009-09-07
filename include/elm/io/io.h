/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * io.h -- formatted IO classes interfaces.
 */
#ifndef ELM_IO_IO_H
#define ELM_IO_IO_H

#include <elm/util/MessageException.h>
#include <elm/system/SystemIO.h>
#include <elm/io/Output.h>
#include <elm/io/Input.h>
#include <elm/string.h>

namespace elm { namespace io {

// IOException class
class IOException: public MessageException {
	String msg;
public:
	inline IOException(const String& message);
};

// IOException inlines
inline IOException::IOException(const String& message)
: MessageException(message) {
}

} // io

// Standard environment
extern io::Output cout;
extern io::Output cerr;
extern io::Input cin;

} // elm

#endif	// ELM_IO_IO_H
