/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_vector.cpp -- unit tests for elm::xxx::Vector classes.
 */

#include <elm/util/test.h>
#include <elm/datastruct/Vector.h>

using namespace elm;

// test_vector()
void test_vector(void) {
	CHECK_BEGIN("Vector");
	
	// Simple test
	{
		datastruct::Vector<int> v;
		v.add(0);
		v.add(1);
		v.add(2);
		v.add(3);
		CHECK(v.count() == 4);
		CHECK(v.item(0) == 0);
		CHECK(v.item(1) == 1);
		CHECK(v.item(2) == 2);
		CHECK(v.item(3) == 3);
	}
	
	// Grow test
	{
		datastruct::Vector<int> v;
		for(int i = 0; i < 32; i++)
			v.add(i);
		bool ok = true;
		for(int i = 0; i < 32; i++)
			if(v.item(i) != i)
				ok = false;
		CHECK(ok);
	}
	
	// Insertion
	{
		datastruct::Vector<int> v;
		v.add(0);
		v.add(1);
		v.add(3);
		v.insert(2, 2);
		CHECK(v.item(0) == 0);
		CHECK(v.item(1) == 1);
		CHECK(v.item(2) == 2);
		CHECK(v.item(3) == 3);
		v.insert(4, 4);
		CHECK(v.item(3) == 3);
		CHECK(v.item(4) == 4);
	}
	
	// Contains and index
	{
		datastruct::Vector<int> v;
		v.add(0);
		v.add(1);
		v.add(0);
		v.add(1);
		v.add(0);
		v.add(1);
		CHECK(v.contains(1) == true);
		CHECK(v.contains(2) == false);
		CHECK(v.indexOf(1) == 1);
		CHECK(v.indexOf(2) < 0);
		CHECK(v.indexOf(1, 2) == 3);
		CHECK(v.indexOf(1, 6) < 0);
		CHECK(v.lastIndexOf(1) == 5);
		CHECK(v.lastIndexOf(2) < 0);
		CHECK(v.lastIndexOf(1, 4) == 3);
		CHECK(v.lastIndexOf(1, 1) < 0);
	}
	
	// Removal test
	{
		datastruct::Vector<int> v;
		v.add(0);
		v.add(1);
		v.add(2);
		v.add(3);
		v.add(4);
		v.removeAt(4);
		CHECK(v.count() == 4);
		CHECK(v.item(3) == 3);
		v.removeAt(1);
		CHECK(v.count() == 3);
		CHECK(v.item(0) == 0);
		CHECK(v.item(1) == 2);
		CHECK(v.item(2) == 3);
		v.remove(3);
		CHECK(v.count() == 2);
		CHECK(v.item(0) == 0);
		CHECK(v.item(1) == 2);
		v.clear();
		CHECK(v.count() == 0);
	}
	
	CHECK_END;
}

