/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * util/test.cpp -- facilities for performing unit test.
 */

#include <elm/io.h>
#include <elm/util/test.h>

namespace elm {

/**
 * @class TestCase
 * This class is used for implementing macro for unit tests.
 */


/**
 * Build a new tes case.
 * @param name	Name of the test case.
 */
TestCase::TestCase(CString name): _name(name), tests(0), errors(0) {
	cout << "\x1b[1;4mTEST CASE: " << name << "\x1b[0m\n";
}


/**
 * Check if a test has returned true.
 * @param file		Source file containing the test.
 * @param line		Line in the source file of the test.
 * @param text		Explanation about the test.
 * @param result	Result of the test.
 */
void TestCase::check(CString file, int line, CString text, bool result) {
	tests++;
	cout << file << ':' << line << ": " << text << '\t';
	if(result)
		cout << "\x1b[32m[OK]\x1b[0m\n";
	else {
		cout << "\x1b[31m[FAILED]\x1b[0m\n";
		errors++;
	}
}


/**
 * Final display of the test case.
 */
void TestCase::complete(void) {
	if(errors)
		cout << "\x1b[1;31mFAILURE: \x1b[0m";
	else
		cout << "\x1b[1;32mSUCCESS: \x1b[0m";
	cout << tests << " tests, " << errors  << " errors\n";
}


} //elm
