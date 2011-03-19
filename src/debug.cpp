/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * Debugging classes and functions
 */

#if defined(__WIN32) || defined(__WIN64)
#	include <stdlib.h>
#else
#	include <elm/debug/CrashHandler.h>
#endif

namespace elm {

/**
 * This function cause a crash of the program. According the system, it may
 * cause a core dump, GDB invocation or any other debugging solution.
 */
void crash(void) {
#	if defined(__WIN32) || defined(__WIN64)
		abort();
#	else
		CrashHandler::crash();
#	endif
}

} // elm
