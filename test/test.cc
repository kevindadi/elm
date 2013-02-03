/*
 * $Id$
 * Copyright (c) 2003-07 IRIT-UPS <casse@irit.fr>
 *
 * Unit tests
 */

#include <elm/io.h>
#include <elm/util/test.h>

using namespace elm;

// Prototypes
void test_array(void);
void test_autostr(void);
void test_avl(void);
void test_bitvector(void);
void test_dllist(void);
void test_file(void);
void test_formatter(void);
void test_frag_table(void);
void test_hashtable(void);
void test_int(void);
void test_io_format(void);
void test_lock(void);
void test_md5(void);
void test_option(void);
void test_plugin(void);
void test_process(void);
void test_ref(void);
void test_sllist(void);
void test_sorted_bintree(void);
void test_stree(void);
void test_string(void);
void test_string_buffer(void);
void test_table(void);
//void test_thread(void);
void test_utility(void);
void test_vararg(void);
void test_vector(void);
void test_vector_queue(void);
void test_wah(void);
void test_hashkey(void);
#ifdef HAS_LIBXML
	void test_serial(void);
	void test_xom(void);
#endif

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
		for(TestSet::Iterator test; test; test++)
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
			for(TestSet::Iterator test; test; test++)
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
		for(TestSet::Iterator test; test; test++)
			test->perform();
	}
}
