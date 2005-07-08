/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_utility.cpp -- unit tests for elm/utility.h.
 */

#include <elm/util/test.h>
#include <elm/utility.h>

using namespace elm;

// Utility tests
void test_utility(void) {
	CHECK_BEGIN("Utility");
	
	// Optional test
	{
		Option<int> one(666), none;
		CHECK(one.isOne() == true);
		CHECK(one.isNone() == false);
		CHECK(one.value() == 666);
		CHECK(none.isOne() == false);
		CHECK(none.isNone() == true);
	}
	
	// Hashing tests
	{
		HashKey<int>& hkey = HashKey<int>::def;
		CHECK(hkey.hash(0) == hkey.hash(0));
		CHECK(hkey.hash(666) == hkey.hash(666));
		CHECK(hkey.hash(-111) == hkey.hash(-111));
		CHECK(hkey.equals(0, 0) == true);
		CHECK(hkey.equals(666, 666) == true);
		CHECK(hkey.equals(666, -111) == false);
	}
	{
		HashKey<void *>& hkey = HashKey<void *>::def;
		char val;
		CHECK(hkey.hash(0) == hkey.hash(0));
		CHECK(hkey.hash(&val) == hkey.hash(&val));
		CHECK(hkey.equals(0, 0) == true);
		CHECK(hkey.equals(&val, &val) == true);
		CHECK(hkey.equals(&val, 0) == false);
	}
	{
		HashKey<String>& hkey = HashKey<String>::def;
		String s1("0123456789"), s2, s3("0123456789");
		CHECK(hkey.hash(s2) == hkey.hash(s2));
		CHECK(hkey.hash(s1) == hkey.hash(s1));
		CHECK(hkey.hash(s1) == hkey.hash(s3));
		CHECK(hkey.equals(s2, s2) == true);
		CHECK(hkey.equals(s1, s1) == true);
		CHECK(hkey.equals(s1, s3) == true);
		CHECK(hkey.equals(s1, s2) == false);
	}
	{
		HashKey<CString>& hkey = HashKey<CString>::def;
		CString s1("0123456789"), s2, s3("0123456789");
		CHECK(hkey.hash(s2) == hkey.hash(s2));
		CHECK(hkey.hash(s1) == hkey.hash(s1));
		CHECK(hkey.hash(s1) == hkey.hash(s3));
		CHECK(hkey.equals(s2, s2) == true);
		CHECK(hkey.equals(s1, s1) == true);
		CHECK(hkey.equals(s1, s3) == true);
		CHECK(hkey.equals(s1, s2) == false);
	}
	
	// Comparators tests
	{
		Comparator<int>& int_comp = Comparator<int>::def;
		CHECK(int_comp.compare(-111, 666) < 0);
		CHECK(int_comp.compare(666, -111) > 0);
		CHECK(int_comp.compare(666, 666) == 0);
		CHECK(int_comp.compare(-111, -111) == 0);
		CHECK(int_comp.compare(0, 0) == 0);
		CHECK(int_comp.compare(0, 666) < 0);
		CHECK(int_comp.compare(666, 0) > 0);
		CHECK(int_comp.compare(0, -111) > 0);
		CHECK(int_comp.compare(-111, 0) < 0);
	}
	{
		static char v[2];
		char *v1 = v, *v2 = v + 1;
		Comparator<void *>& pointer_comp = Comparator<void *>::def;
		CHECK(pointer_comp.compare(v1,v2) < 0);
		CHECK(pointer_comp.compare(v2, v1) > 0);
		CHECK(pointer_comp.compare(v2, v2) == 0);
		CHECK(pointer_comp.compare(v1, v1) == 0);
		CHECK(pointer_comp.compare(0, 0) == 0);
		CHECK(pointer_comp.compare(0, v2) != 0);
		CHECK(pointer_comp.compare(v2, 0) != 0);
	}
	{
		String v1("ok"), v2("ko"), v3("ok"), v4("okk");
		Comparator<String>& string_comp = Comparator<String>::def;
		CHECK(string_comp.compare(v1, v1) == 0);		// Reflexive
		CHECK(string_comp.compare(v1, v2) > 0);		// Symetric
		CHECK(string_comp.compare(v2, v1) < 0);
		CHECK(string_comp.compare(v1, v4) < 0);		// Transitive
		CHECK(string_comp.compare(v2, v4) < 0);
		CHECK(string_comp.compare(v1, v3) == 0);		// Internal representation
	}
	{
		CString v1("ok"), v2("ko"), v3("ok"), v4("okk");
		Comparator<CString>& string_comp = Comparator<CString>::def;
		CHECK(string_comp.compare(v1, v1) == 0);		// Reflexive
		CHECK(string_comp.compare(v1, v2) > 0);		// Symetric
		CHECK(string_comp.compare(v2, v1) < 0);
		CHECK(string_comp.compare(v1, v4) < 0);		// Transitive
		CHECK(string_comp.compare(v2, v4) < 0);
		CHECK(string_comp.compare(v1, v3) == 0);		// Internal representation
	}
	
	CHECK_END;
}
