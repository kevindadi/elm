/*
 * $Id$
 * Copyright (c) 2003, Alfheim Corporation.
 *
 * test.cc -- unit tests.
 */

#include <elm/io.h>

using namespace elm;

// Prototypes
void test_string_buffer(void);
void test_sorted_bintree(void);
void test_dllist(void);
void test_plugin(void);
void test_avl(void);
void test_sllist(void);
void test_bitvector(void);
void test_string(void);
void test_utility(void);
void test_vector(void);
void test_hashtable(void);
void test_lock(void);

// List of tests
struct test_t {
	CString name;
	void (*fun)(void);
} tests[] = {
	{ "string", test_string },
	{ "utility", test_utility },
	{ "vector", test_vector },
	{ "hashtable", test_hashtable },
	{ "lock", test_lock },
	{ "sorted_bintree", test_sorted_bintree },
	{ "string_buffer", test_string_buffer },
	{ "dllist", test_dllist },
	{ "plugin", test_plugin },
	{ "avl", test_avl },
	{ "sllist", test_sllist },
	{ "bitvector", test_bitvector },
	{ "", 0 }
};

// Entry point
int main(int argc, char *argv[]) {
	
	// Test all
	if(argc == 1)
		for(struct test_t *test = tests; test->fun; test++)
			test->fun();
	
	// Test some
	else 
		for(int i = 1; i < argc; i++) {
			bool found = false;
			for(struct test_t *test = tests; test->fun; test++)
				if(test->name == argv[i]) {
					test->fun();
					found = true;
				}
			if(!found)
				cerr << "ERROR: no test called \"" << argv[i] << "\"\n";
		}
}
