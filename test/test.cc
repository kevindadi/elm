/*
 * $Id$
 * Copyright (c) 2003-07 IRIT-UPS <casse@irit.fr>
 *
 * Unit tests
 */

#include <elm/io.h>
#include <elm/util/test.h>

using namespace elm;

// List of tests
struct test_t {
	CString name;
	void (*fun)(void);
} tests[] = {
//	{ "thread", test_thread },
//		{ "serial", test_serial },
//		{ "xom", test_xom },
	//{ "wah", test_wah },
//	#ifdef HAS_LIBXML
//	#endif
	{ "", 0 }
};

// Entry point
int main(int argc, char *argv[]) {

	// process the help
	for(int i = 1; i < argc; i++)
		if(string("-h") == argv[i] || string("--help") == argv[i]) {
		cerr << "Modules:\n";
		for(struct test_t *test = tests; test->fun; test++)
			cerr << "\t" << test->name << io::endl;
		for(TestSet::Iterator test(TestSet::def); test; test++)
			cerr << "\t" << test->name() << io::endl;
		return 0;
	}
	
	// process the tests
	bool one = false;
	for(int i = 1; i < argc; i++) {
		bool found = false;
		one = true;

		// look in the old table
		for(struct test_t *test = tests; test->fun; test++)
			if(test->name == argv[i]) {
				found = true;
				test->fun();
			}

		// look in the test set
		if(!found)
			for(TestSet::Iterator test(TestSet::def); test; test++)
				if(test->name() == argv[i]) {
					found = true;
					test->perform();
				}

		// not found: error
		if(!found)
			cerr << "ERROR: no test called \"" << argv[i] << "\"\n";
	}

	// if none selected, test all
	if(!one) {

		// perform tests from the table
		for(struct test_t *test = tests; test->fun; test++)
			test->fun();

		// perform test from the test set
		for(TestSet::Iterator test(TestSet::def); test; test++)
			test->perform();
	}
}
