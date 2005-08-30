/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_vararg.cpp -- unit tests for elm/util/VarArg.h.
 */

#include <elm/util/test.h>
#include <elm/util/VarArg.h>

using namespace elm;

// Test function
static void perform(int x, ...) {
	CHECK_BEGIN("VarArg");

	VARARG_BEGIN(args, x)
		CHECK(args.next<bool>() == true);
		CHECK(args.next<int>() == 666);
		CHECK(args.next<double>() == 111.666);
		CHECK(!strcmp(args.next<char *>(), "123"));
		CHECK(args.next<unsigned int>() == 111);
	VARARG_END

	CHECK_END;	
}

// Utility tests
void test_vararg(void) {
	perform(0, true, 666, 111.666, "123", 111);
}
