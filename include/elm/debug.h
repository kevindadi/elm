/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * debug.h -- useful for debugging.
 */
#ifndef ELM_DEBUG_H
#define ELM_DEBUG_H

#include <elm/io.h>

namespace elm {

// Debugging macros
#ifdef NDEBUG
#	define TRACE
#	define BREAK(cond)
#	define HERE
#else
#	define TRACE elm::trace(__FILE__, __LINE__)
#	define BREAK(cond)	if(cond)
#	define HERE { int x = 0; };
#endif

// Inlines
inline void trace(CString file, int line) {
	cerr << "TRACE(" << file << ':' << line << ")\n";
	cerr.flush();
}
	
}	// elm
	
#endif	// ELM_DEBUG_H
