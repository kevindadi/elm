/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * Debugging classes and functions
 */

#include <elm/debug/CrashHandler.h>

namespace elm {

/**
 * This function cause a crash of the program. According the system, it may
 * cause a core dump, GDB invocation or any other debugging solution.
 */
void crash(void) {
	CrashHandler::crash();
}

} // elm
