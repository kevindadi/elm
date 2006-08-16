/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * src/util_MessageException.cpp -- MessageException class implementation.
 */

#include <elm/util/MessageException.h>

namespace elm {

/**
 * @class MessageException <elm/utility.h>
 * This class is dedicated to the exception management with a human-readable
 * message.
 */


/**
 * Build an exception with an empty message.
 */
MessageException::MessageException(void) {
}



/**
 * Build the exception message with a printf-like format string.
 * @param message	Format message.
 * @param args		Arguments.
 */
void MessageException::buildMessage(CString message, VarArg& args) {
	StringBuffer buffer;
	buffer.format(message, args);
	msg = buffer.toString();
}


/**
 * Build an empty with a string message possibly containing printf-like
 * escape sequences for arguments.
 * @param message	Message formats.
 * @param ...		Arguments.
 */
MessageException::MessageException(CString message, ...) {
	VARARG_BEGIN(args, message)
	buildMessage(message, args);
	VARARG_END
}


/**
 * Build an empty with a string message possibly containing printf-like
 * escape sequences for arguments.
 * @param message	Message formats.
 * @param args		Arguments.
 */
MessageException::MessageException(CString message, VarArg& args) {
	buildMessage(message, args);
}


/**
 */	
String MessageException::message(void) {
	return msg;
}

} // elm

