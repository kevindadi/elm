/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_table.cpp -- unit tests for Table class.
 */

#include <elm/data/Array.h>
#include "../include/elm/test.h"

using namespace elm;

class TopArray {
public:
	AllocArray<int> tab;
	TopArray(void): tab(0) { }
	TopArray(int size): tab(size) { }
	TopArray(const TopArray& tt): tab(tt.tab) { }
};

class BottomTable {
public:
	AllocArray< TopArray > tab;
	BottomTable(int size): tab(size) { }
};


TEST_BEGIN(array)

	// Simple tests
	{
		int t[] = { 0, 1, 2, 3 };
		Array<int> tab(4, t);
		CHECK(tab[0] == 0);
		CHECK(tab[1] == 1);
		CHECK(tab[2] == 2);
		CHECK(tab[3] == 3);
		CHECK(tab.size() == 4);
		int i = 0;
		for(Array<int>::Iter n(tab); !n.ended(); n++, i++) {
			CHECK(i < 4);
			CHECK(n == t[i]);
		}
		CHECK(i == 4);
	}
	
	// Assignment tests
	{
		int t[] = { 0, 1, 2, 3 };
		Array<int> tab(4, t);
		CHECK(tab[2] == 2);
		tab[2] = 4;
		CHECK(tab[2] == 4);
		tab.set(2, 6);
		CHECK(tab[2] == 6);
	}
	
	// Complex tables
	{
		BottomTable tt(4);
		tt.tab[0] = TopArray(4);
		tt.tab[1] = TopArray(4);
		tt.tab[2] = TopArray(4);
		tt.tab[3] = TopArray(4);
	}
	
	// Boolean table
	{
		AllocArray<bool> tab(1024);
		tab[0] = false;
		CHECK(tab[0] == false);
		tab[1] = true;
		CHECK(tab[1] == true);
	}

	// Automatic maker
	{
		int t[4] = { 1, 2, 3, 4 };
		Array<int> a = _array(4, t);
		CHECK_EQUAL(a.size(), 4);
	}

TEST_END

	

