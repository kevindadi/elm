/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/SystemException.h -- SystemException class interface.
 */
#ifndef ELM_SYSTEM_SYSTEM_EXCEPTION_H
#define ELM_SYSTEM_SYSTEM_EXCEPTION_H

#include <elm/utility.h>

namespace elm { namespace system {

// SystemException class
class SystemException: 	public Exception {
public:
	typedef enum error_t {
		OK = 0,
		NO_ACCESS,
		NO_MORE_RESOURCE,
		BAD_PATH,
		IO_ERROR,
		ALREADY_EXIST
	} error_t;

private:
	error_t err;
	String msg;

public:
	SystemException(error_t err, String msg);
	SystemException(int code, String header);
	inline error_t error(void) const;

	// Exception overload
	virtual String message(void);
};

// Inlines
inline SystemException::error_t SystemException::error(void) const {
	return err;
}

} } // elm::system

#endif // ELM_SYSTEM_SYSTEM_EXCEPTION_H

