/*
 *	test facilities implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/data/Vector.h>
#include <elm/io.h>
#include <elm/io/ansi.h>
#include <elm/test.h>

namespace elm {

/**
 * @defgroup test Testing
 *
 * @def CHECK_BEGIN(name)
 * This is the first statement of a unit test case. Usually, a unit test case
 * is structured as below:
 * @code
 * 	CHECK_BEGIN(test case name);
 * 	CHECK(test1);
 * 	CHECK(test2);
 * 	...
 * 	CHECK_END;
 * @endcode
 * This statement display a state header, each CHECK displays a check status line
 * and TEST_END a summary of the full test case. A test case defines also
 * an environment like in C blocks { ... }.
 * @param name	Name of the test case (string).
 *
 * In addition, all declared test cases are record in @ref TestSet::def.
 * Testing may be embedded in a command using the macro @ref TEST_MAIN : no more
 * need to define a main that calls all tests. In addition, @ref TEST_MAIN allows
 * to select which tests to perform and to list available tests.
 *
 * @note	These macros definition may be discarded defining the ELM_NO_SHORTCUT
 * identifier, for avoiding name clashes for example.
 *
 * @seealso @ref CHECK_END, @ref CHECK, @ref elm::TestCase, @ref elm::TestSet
 */

/**
 * @def TEST_BEGIN(test)
 * This macro is used to create and to record an integrated test case.
 * Following the macro must be inserted the checked tests with macros based on CHECK
 * and the test must be ended by the macro @ref TEST_END.
 * @par
 * The test cases may be specified independently but may be also grouped inside a test set,
 * implemented by the class @ref elm::TestSet. This class is a singleton, @ref elm::TestSet::def,
 * containing the list of uses cases. The list of test cases can be explored using @ref elm::TestSet::Iterator.
 * @par
 * In this case, the macro @ref TEST_BEGIN and @ref TEST_END must be used as in the example below:
 * @code
 * 	TEST_BEGIN(my_test)
 * 		CHECK(test1);
 * 		CHECK(test2);
 * 		...
 * 	TEST_END
 * @endcode
 * @param test	Name of the test (must be unquoted !).
 * @ingroup test
 * @seealso @ref TEST_END, @ref CHECK, @ref elm::TestCase, @ref elm::TestSet
 */


/**
 * @def TEST_END
 * End a test declared with @ref TEST_BEGIN.
 * @ingroup test
 * @seealso @ref TEST_BEGIN, @ref CHECK, @ref elm::TestCase, @ref elm::TestSet
 */


/**
 * @def TEST_MAIN
 * Insert a main() function that scans the command parameters and launch
 * corresponding tests.
 * @ingroup test
 * @seealso @ref ELM_TEST_MAIN, @ref TEST_BEGIN, @ref elm::TestSet
 */


/**
 * @def ELM_TEST_MAIN
 * Same as @ref TEST_MAIN.
 * @ingroup test
 * @seealso @ref TEST_MAIN
 */


/**
 * @def CHECK(test)
 * See @ref ELM_CHECK.
 * @param test	Test to check.
 * @ingroup test
 * @seealso @ref ELM_CHECK, @ref REQUIRE, @ref CHECK_EQUAL, @ref CHECK_EXCEPTION, @ref FAIL_ON_EXCEPTION
 */


/**
 * @def CHECK_END
 * See @ref CHECK_END.
 * @ingroup test
 * @seealso @ref CHECK_BEGIN, @ref CHECK, @ref elm::TestCase, @ref elm::TestSet
 */


/**
 * @def ELM_CHECK_BEGIN(name)
 * Same as @ref CHECK_BEGIN.
 * @ingroup test
 */


/**
 * @def ELM_CHECK(test)
 * Same as @ref CHECK.
 * @ingroup test
 */


/**
 * @def ELM_CHECK_END
 * Same as @ref CHECK_END
 * @ingroup test
 */

/**
 * @def ELM_CHECK_EQUAL(res, ref)
 * Test if the result of a test is equal to a reference value.
 * @param res	Result of the test.
 * @param ref	Reference value.
 * @ingroup test
 * @seealso @ref CHECK, @ref REQUIRE, @ref CHECK_EXCEPTION, @ref FAIL_ON_EXCEPTION
 */


/**
 * @def CHECK_EQUAL(res, ref)
 * See ELM_CHECK_EQUAL.
 * @ingroup test
 */


/**
 * @class TestCase
 * This class is used for implementing macro for unit tests.
 * @seealso @ref TestSet, @ref CHECK, @ref TEST_BEGIN, @ref CHECK_BEGIN
 * @ingroup test
 */


/**
 * Build a new tes case.
 * @param name	Name of the test case.
 */
TestCase::TestCase(CString name):
	_name(name),
	tests(0),
	errors(0),
	__case(*this),
	full_path(false)
{
	TestSet::def.record(this);
}


/**
 * Perform the display before the test execution.
 */
void TestCase::prepare(void) {
#if defined(__unix) || defined(__APPLE__)
	cout << "\x1b[1;4mTEST CASE: " << name() << "\x1b[0m" << io::endl;
#elif defined(__WIN32) || defined(__WIN64)
	cout << "TEST CASE: " << name() << io::endl;
#endif
}


/**
 * Prepare to do a test.
 * @param file	Source file.
 * @param line	Source line.
 * @param text	Code text to test.
 */
void TestCase::test(CString file, int line, CString text) {
	tests++;
	if(full_path)
		cout << file;
	else
		cout << sys::Path(file).namePart();
	cout << ':' << line << ": " << text << '\t';
}


/**
 * Display a performed action for test understanding.
 * @param file		Source file path.
 * @param line		Source line number.
 * @param action	Identifier of the action.
 */
void TestCase::perform(cstring file, int line, cstring action) {
	cout << io::BLUE << io::BOLD << "INFO: " << io::PLAIN << action << " (";
	if(full_path)
		cout << file;
	else
		cout << sys::Path(file).namePart();
	cout << ':' << line << ')' << io::endl;
}



/**
 * Inform that the current test has failed.
 */
void TestCase::failed(void) {
#if defined(__unix) || defined(__APPLE__)
	cout << "\x1b[31m[FAILED]\x1b[0m" << io::endl;
#elif defined(__WIN32) || defined(__WIN64)
	cout << "FAILED" << io::endl;
#endif
	errors++;
}


/**
 * Inform that the current test has succeeded.
 */
void TestCase::succeeded(void) {
#if defined(__unix) || defined(__APPLE__)
	cout << "\x1b[32m[OK]\x1b[0m" << io::endl;
#elif defined(__WIN32) || defined(__WIN64)
	cout << "[OK] " << io::endl;
#endif
}


/**
 * Check if a test has returned true.
 * @param file		Source file containing the test.
 * @param line		Line in the source file of the test.
 * @param text		Explanation about the test.
 * @param result	Result of the test.
 */
void TestCase::check(CString file, int line, CString text, bool result) {
	test(file, line, text);
	if(result)
		succeeded();
	else
		failed();
}



/**
 * For internal work only. Don't call it.
 */
void TestCase::initialize(void) {
	TestSet::def.add(this);
}


/**
 * Final display of the test case.
 */
void TestCase::complete(void) {
	if(errors)
#if defined(__unix) || defined(__APPLE__)
		cout << "\x1b[1;31mFAILURE: " << io::PLAIN;
#elif defined(__WIN32)
		cout << "FAILURE :";
#endif
	else
#if defined(__unix) || defined(__APPLE__)
		cout << "\x1b[1;32mSUCCESS: " << io::PLAIN;
#elif defined(__WIN32) || defined(__WIN64)
		cout << "SUCCESS: ";
#endif
	cout << tests << " tests, " << errors  << " errors" << io::endl;
}


/**
 * Same as check but also returns value and specific message for ending the
 * test due to main failure.
 * @param file		File containing the test source.
 * @param line		Line where the test is implemented.
 * @param text		Text describing the test.
 * @param result	Result of the test.
 * @return			Result of the test.
 */
bool TestCase::require(CString file, int line, CString text, bool result) {
	check(file, line, text, result);
	if(!result)
#if defined(__unix) || defined(__APPLE__)
		cout << "\x1b[1;31mMain failure: test must be interrupted." << io::PLAIN << io::endl;
#elif defined(__WIN32) || defined(__WIN64)
		cout << "Main failure: test must be interrupted" << io::endl;
#endif
	return result;
}


/**
 * Actual actions of the test.
 */
void TestCase::execute(void) {
}


/**
 * Execute the test case.
 */
void TestCase::perform(void) {
	tests = 0;
	errors = 0;
	prepare();
	execute();
	complete();
}


/**
 */
TestCase::~TestCase(void) {
}


/**
 * @fn bool TestCase::isFullPath() const;
 * Test if the source paths are fully displayed. Otherwise, only the name of
 * the source is display.
 * @return	True if the full path option is enabled, false else.
 */


/**
 * @fn void TestCase::setFullPath(bool x);
 * Set the full source option.
 * @param x		True to enable full path display.
 */


/**
 * @class TestSet
 * Singleton class containing all existing tests.
 * @seealso @ref elm::TestCase, @ref CHECK, @ref TEST_BEGIN
 * @ingroup test
 */


/**
 * Perform the tests of the test set.
 */
void TestSet::perform(void) {
	for(Iterator test(*this); test(); test++)
		test->perform();
}

/**
 * Execute the test as an application. argv is looked for tests to perform
 * and, if empty, run all tests and display statistics. It may called from main()
 * or by the macro @ TEST_MAIN.
 * @param argc	argc as passed to main.
 * @param argv	argv as passed to main.
 * @return		Error code to return from main.
 */
int TestSet::run(int argc, const char **argv) {

	// process the help
	for(int i = 1; i < argc; i++)
		if(string("-h") == argv[i] || string("--help") == argv[i]) {
			cerr << io::BLUE << io::BOLD << "Modules:\n" << io::PLAIN;
			for(TestSet::Iterator test(TestSet::def); test(); test++)
				cerr << "\t" << test->name() << io::endl;
			return 0;
		}

	// process the tests
	Vector<TestCase *> tests;
	for(int i = 1; i < argc; i++) {
		bool found = false;

		// look in the structure
		for(TestSet::Iterator test(TestSet::def); test(); test++)
			if(test->name() == argv[i]) {
				tests.add(*test);
				found = true;
				break;
			}

		// not found: error
		if(!found) {
			cerr << io::RED << io::BOLD << "ERROR:" << io::PLAIN << " no test called \"" << argv[i] << "\"\n";
			return 1;
		}
	}

	// if none selected, test all
	if(!tests)
		for(TestSet::Iterator test(TestSet::def); test(); test++)
			tests.add(*test);

	// perform tests
	bool failed = false;
	for(Vector<TestCase *>::Iter test(tests); test(); test++) {
		try {
			test->perform();
		}
		catch(Exception& e) {
			cerr << io::BOLD << io::RED << "FATAL: " << io::PLAIN << e.message() << io::endl;
			return 2;
		}
		if(test->hasFailed())
			failed = true;
	}

	// display summary
	cout.flush();
	if(!failed) {
		cerr << io::BOLD << io::GREEN << "SUCCESS:" << io::PLAIN
			 << " all test cases (" << tests.count() << ") successfully passed!\n";
		return 0;
	}
	else {
		cerr << io::BOLD << io::RED << "ERROR: " << io::PLAIN << "some tests failed:\n";
		for(Vector<TestCase *>::Iter test(tests); test(); test++)
			if(test->hasFailed())
				cerr << "  * " << test->name() << io::endl;
		return 1;
	}

	// success
	return 0;

}


/**
 * Singleton of TestSet.
 */
TestSet TestSet::def;


/**
 * Add the given test.
 * @param tcase		Test case to add.
 */
void TestSet::add(TestCase *tcase) {
	cases.add(tcase);
}

} //elm
