/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/MessageException.h -- MessageException class interface.
 */
#ifndef ELM_UTIL_MESSAGE_EXCEPTION_H
#define ELM_UTIL_MESSAGE_EXCEPTION_H

#include <assert.h>
#include <elm/string.h>
#include <elm/utility.h>
#include <elm/util/VarArg.h>

namespace elm {
	
// MessageException class
class MessageException: public Exception {
	String msg;
protected:
	MessageException(void);
	void buildMessage(CString message, VarArg& args);
public:
	MessageException(CString message, ...);
	MessageException(CString message, VarArg& args);
	
	// Overload
	virtual String message(void);
};

} // elm

#endif // ELM_UTIL_MESSAGE_EXCEPTION_H

