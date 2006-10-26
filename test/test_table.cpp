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

class TopTable {
public:
	AllocatedTable<int> tab;
	TopTable(void): tab(0) { }
	TopTable(int size): tab(size) { }
	TopTable(const TopTable& tt): tab(tt.tab) { }
};

class BottomTable {
public:
	AllocatedTable< TopTable > tab;
	BottomTable(int size): tab(size) { }
};

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
	
	// Complex tables
	{
		cout << "BEGIN\n";
		BottomTable tt(4);
		cout << "tt.tab[0] = TopTable(4);\n";
		tt.tab[0] = TopTable(4);
		cout << "tt.tab[1] = TopTable(4);\n";
		tt.tab[1] = TopTable(4);
		cout << "tt.tab[2] = TopTable(4);\n";
		tt.tab[2] = TopTable(4);
		cout << "tt.tab[3] = TopTable(4);\n";
		tt.tab[3] = TopTable(4);
		cout << "END\n";
	}
	CHECK_END;
}
	
