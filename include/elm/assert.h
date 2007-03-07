/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * Specialized assertion management
 */
#ifndef ELM_ASSERT_H
#define ELM_ASSERT_H

// Useful functions
namespace elm {

void crash(void);

} // elm

// Macros
#ifndef NDEBUG
#	include <elm/io.h>
#	define ELM_ASSERT_MSG(msg) \
		cerr << "ASSERT:" << __FILE__ << ":" << __LINE__ << ": " << msg << io::endl
#	define ELM_ASSERT(cond) \
		if(!(cond)) { ELM_ASSERT_MSG("assert failure: " #cond); crash(); }
#	define ELM_ASSERTP(cond, msg) \
		if(!(cond)) { ELM_ASSERT_MSG(msg); crash(); }
#else
#	define ELM_ASSERT(cond)	;
#	define ELM_CHECK(cond, msg) ;
#endif

// Macros without prefix
#ifndef ELM_NO_ASSERT_SHORTCUT
#	define ASSERT(cond) ELM_ASSERT(cond)
#	define ASSERTP(cond, msg) ELM_ASSERTP(cond, msg)
#endif

#endif // ELM_ASSERT_H
