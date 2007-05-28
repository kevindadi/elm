/*
 * $Id$
 * Copyright (c) 2006-07 - IRIT-UPS <casse@irit.fr>
 *
 * MessageException class interface
 */
#ifndef ELM_UTIL_MESSAGE_EXCEPTION_H
#define ELM_UTIL_MESSAGE_EXCEPTION_H

#include <elm/util/Exception.h>
#include <elm/string.h>

namespace elm {
	
// MessageException class
class MessageException: public Exception {
public:
	MessageException(const String& message);
	virtual String message(void);

private:
	String msg;
};

} // elm

#endif // ELM_UTIL_MESSAGE_EXCEPTION_H

