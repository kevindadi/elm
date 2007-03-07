/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * Debugging classes and functions
 */

#include <stdlib.h>

namespace elm {

/**
 * This function cause a crash of the program. According the system, it may
 * cause a core dump, GDB invocation or any other debugging solution.
 */
void crash(void) {
	abort();
}

} // elm
