/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/system_SystemException.h -- SystemException class implementation.
 */

#include <assert.h>
#include <errno.h>
#include <elm/system/SystemException.h>

namespace elm { namespace system {

/**
 * @class SystemException
 * This exception is usually thrown due to system related errors.
 */


/**
 * Build a simple system exception.
 * @param error		Error kind.
 * @param message	Message.
 */
SystemException::SystemException(error_t error, String message)
: err(error), msg(message) {
}


/**
 * Build a system exception from real error code getting message from the system
 * and appending the header with it.
 * @param code		Real code.
 * @param header	Header used for building the message.
 */
SystemException::SystemException(int code, String header) {
	
	// Compute error
	switch(code) {
	case EACCES:
	case EPERM:
	case EROFS:
		err = NO_ACCESS;
		break;
	case EIO:
		err = IO_ERROR;
		break;
	case ELOOP:
	case ENAMETOOLONG:
	case ENOMEM:
	case EMFILE:
	case ENFILE:
	case ENOSPC:
		err = NO_MORE_RESOURCE;
		break;
	case EFAULT:
	case ENOENT:
	case ENOTDIR:
	case ECHILD:
	case ESRCH:
		err = BAD_PATH;
		break;
	case EEXIST:
		err = ALREADY_EXIST;
		break;
	case EINVAL:
	case EINTR:
		assert(0);
	}
	
	// Compute message
	StringBuffer buf;
	buf << header << ": " << strerror(code);
	msg = buf.toString();
}


/**
 * @fn error_t SystemException::error(void) const;
 * Get the error kind.
 * @return	Error kind.
 */


/**
 */
String SystemException::message(void) {
	return msg;
}
	
} } // elm::system

