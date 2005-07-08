/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * test/test_SLList/test_SLList.cpp -- test program for SLList class.
 */

#include <elm/util/test.h>
#include <elm/genstruct/SLList.h>

using namespace elm;
using namespace genstruct;

void test_sllist(void) {
	
	CHECK_BEGIN("SLList");

	// Test initial
	{
		SLList<int> list;
		CHECK(list.count() == 0);
	}
	
	// Test addFirst
	{
		SLList<int> list;
		for(int i = 0; i < 10; i++)
			list.addFirst(i);
		CHECK(list.count() == 10);
		int i = 9;
		bool good = true;
		for(SLList<int>::Iterator iter(list); iter; iter++, i--)
			if(iter.item() != i) {
				good = false;
				break;
			}
		CHECK(good);
	}
	
	CHECK_END;
}

