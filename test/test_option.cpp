/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_option.cpp -- option module test.
 */

#include <elm/util/test.h>
#include <elm/options.h>

using namespace elm;
using namespace elm::option;

Manager man;

// test_option()
void test_option(void) {
	CHECK_BEGIN("Option");

	// Unknown option
	{
		char *argv[] = {
			"command",
			"--bad",
			0
		};
		CHECK_EXCEPTION(OptionException, man.parse(2, argv));
	};

	CHECK_END
}
