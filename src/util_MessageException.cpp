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
 * Build an empty with a string message possibly containing printf-like
 * escape sequences for arguments.
 * @param message	Message formats.
 * @param args		Arguments.
 */
MessageException::MessageException(const String& message)
: msg(message) {
}


/**
 */	
String MessageException::message(void) {
	return msg;
}

} // elm

