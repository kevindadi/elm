/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_table.cpp -- unit tests for Table class.
 */

#include <elm/util/test.h>
#include <elm/genstruct/Table.h>

using namespace elm;
using namespace elm::genstruct;

void test_table(void) {
	CHECK_BEGIN("table");
	
	// Simple tests
	{
		int t[] = { 0, 1, 2, 3 };
		Table<int> tab(t, 4);
		CHECK(tab[0] == 0);
		CHECK(tab[1] == 1);
		CHECK(tab[2] == 2);
		CHECK(tab[3] == 3);
		CHECK(tab.count() == 4);
		CHECK(tab.table() == t);
	}
	
	// Assignment tests
	{
		int t[] = { 0, 1, 2, 3 };
		Table<int> tab(t, 4);
		CHECK(tab[2] == 2);
		tab[2] = 4;
		CHECK(tab[2] == 4);
		tab.set(2, 6);
		CHECK(tab[2] == 6);
	}
	
	CHECK_END;
}
	
