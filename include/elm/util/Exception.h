/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/Exception.h -- Exception class interface.
 */
#ifndef ELM_UTIL_EXCEPTION_H
#define ELM_UTIL_EXCEPTION_H

#include <assert.h>
#include <elm/string.h>

namespace elm {
	
// Exception class
class Exception {
public:
	virtual ~Exception(void);
	virtual String message(void);
};

} // elm

#endif // ELM_UTIL_EXCEPTION_H
