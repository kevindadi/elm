/*
 * $Id$
 * Copyright (c) 2003, Alfheim Corporation.
 *
 * test.cc -- unit tests.
 */
#include <stdio.h>
#include <stdlib.h>
#include <elm/string.h>
#include <elm/string/StringBuffer.h>
#include <elm/utility.h>
#include <elm/io.h>
#include <elm/options.h>

#include <elm/inhstruct/SLList.h>
#include <elm/genstruct/SLList.h>
#include <elm/inhstruct/DLList.h>
#include <elm/genstruct/DLList.h>
#include <elm/genstruct/Vector.h>
#include <elm/genstruct/HashTable.h>

#include <elm/inhstruct/BinTree.h>
#include <elm/inhstruct/SortedBinTree.h>
#include <elm/genstruct/SortedBinTree.h>
#include <elm/genstruct/SortedBinMap.h>

#include <elm/datastruct/Collection.h>
#include <elm/datastruct/Map.h>
#include <elm/datastruct/SortedSet.h>
#include <elm/datastruct/Indexed.h>
#include <elm/datastruct/Vector.h>
#include <elm/datastruct/HashTable.h>

#include <elm/genstruct/FragArray.h>

using namespace elm;


// Test macros
static int failures = 0;
#define TEST_UNIT(name) cout << "\n[" name "]\n"
#define TEST(test) \
	cout << __FUNCTION__ << '.' << __LINE__ << ":[" << \
		((test) ? "OK" : (failures++, "FAILED")) << "]\n"; \
	cout.flush()
#define TEST_END cout << "Result: " << (failures ? "FAILED" : "SUCCESS") << '\n'

// Utility class
class LockTest: public Lock {
	bool *alloc;
public:
	LockTest(bool *_alloc): alloc(_alloc) { *alloc = true; };
	~LockTest(void) { *alloc = false; };
	inline bool getAlloc(void) const { return *alloc; };
};

// DList class
/*class MyDLNode: public inhstruct::DLNode {
public:
	int v;
	inline MyDLNode(int _v): v(_v) {
	};
};*/

// String test
void test_string(void) {
	TEST_UNIT("String");
	
	// Comparison overload test
	{
		elm::String s1 = "ok", s2 = "ko";
		elm::CString c1 = "ok", c2 = "ko";
		
		TEST(s1 != s2);
		TEST(s1 == c1);
		TEST(s1 == "ok");
		
		TEST(c1 == s1);
		TEST(c1 != s2);
		TEST(c1 != c2);
		TEST(c1 == "ok");
		
		TEST("ok" == s1);
		TEST("ok" == c1);
		TEST("ok" != s2);
		TEST("ok" != c2);
	}
	
	// Basic information
	{
		elm::String s("0123");
		TEST(s.length() == 4);
		TEST(s.chars()[0] == '0');
		TEST(s.chars()[1] == '1');
		TEST(s.chars()[2] == '2');
		TEST(s.chars()[3] == '3');
	}
	{
		elm::CString s("0123");
		TEST(s.length() == 4);
		TEST(s.chars()[0] == '0');
		TEST(s.chars()[1] == '1');
		TEST(s.chars()[2] == '2');
		TEST(s.chars()[3] == '3');
	}
	
	// charAt test
	{
		elm::String s("01234");
		TEST(s.charAt(0) == '0');
		TEST(s.charAt(1) == '1');
		TEST(s.charAt(2) == '2');
		TEST(s.charAt(3) == '3');
	}
	{
		elm::CString s("01234");
		TEST(s.charAt(0) == '0');
		TEST(s.charAt(1) == '1');
		TEST(s.charAt(2) == '2');
		TEST(s.charAt(3) == '3');
	}

	// Comparisons
	{
		elm::String s1("ok"), s2("ko"), s3("oko"), s4("ok");
		TEST(s1.compare(s1) == 0);
		TEST(s1.compare(s2) > 0);
		TEST(s1.compare(s3) < 0);
		TEST(s1.compare(s4) == 0);
	}
	{
		elm::String s1("ok");
		elm::CString s2("ko"), s3("oko"), s4("ok");
		TEST(s1.compare(s2) > 0);
		TEST(s1.compare(s3) < 0);
		TEST(s1.compare(s4) == 0);
	}
	{
		elm::CString s1("ok");
		elm::CString s2("ko"), s3("oko"), s4("ok");
		TEST(s1.compare(s2) > 0);
		TEST(s1.compare(s3) < 0);
		TEST(s1.compare(s4) == 0);
	}
	
	// Comparison with substring
	 {
		elm::String s("okoko");
		{
			elm::String s1 = s.substring(2, 2);
			elm::String s2("ko"), s3("oko"), s4("ok");
			TEST(s1.compare(s1) == 0);
			TEST(s1.compare(s2) > 0);
			TEST(s1.compare(s3) < 0);
			TEST(s1.compare(s4) == 0);
		}
		{
			elm::String s1 = s.substring(2, 2);
			elm::CString s2("ko"), s3("oko"), s4("ok");
			TEST(s1.compare(s2) > 0);
			TEST(s1.compare(s3) < 0);
			TEST(s1.compare(s4) == 0);
		}
	}
	
	// Assignment
	{
		elm::String lhs, rhs("ok");
		lhs = rhs;
		TEST(lhs == rhs);
	}
	{
		elm::CString lhs, rhs("ok");
		lhs = rhs;
		TEST(lhs == rhs);
	}
	{
		elm::String lhs;
		elm::CString rhs("ok");
		lhs = rhs;
		TEST(lhs == rhs);
	}
	
	// Substrings
	{
		elm::String s("0123456789"), r;
		TEST((r = s.substring(0)) == s);
		TEST((r = s.substring(4)) == "456789");
		TEST((r = s.substring(0, 4)) == "0123");
		TEST((r = s.substring(4, 4)) == "4567");
		TEST((r = s.substring(4, 0)) == "");
	}
	{
		elm::CString s("0123456789");
		elm::String r;
		TEST((r = s.substring(0)) == s);
		TEST((r = s.substring(4)) == "456789");
		TEST((r = s.substring(0, 4)) == "0123");
		TEST((r = s.substring(4, 4)) == "4567");
		TEST((r = s.substring(4, 0)) == "");
	}
	
	// Concatenation
	{
		elm::String s1("0123"), s2("45"), s3("");
		TEST(s1.concat(s1) == "01230123");
		TEST(s1.concat(s2) == "012345");
		TEST(s1.concat(s3) == s1);
		TEST(s2.concat(s1) == "450123");
		TEST(s3.concat(s1) == s1);
	}
	{
		elm::CString s1("0123"), s2("45"), s3("");
		TEST(s1.concat(s1) == "01230123");
		TEST(s1.concat(s2) == "012345");
		TEST(s1.concat(s3) == s1);
		TEST(s2.concat(s1) == "450123");
		TEST(s3.concat(s1) == s1);
	}
	{
		elm::CString s1("0123");
		elm::String s2("45"), s3("");
		TEST(s1.concat(s1) == "01230123");
		TEST(s1.concat(s2) == "012345");
		TEST(s1.concat(s3) == s1);
		TEST(s2.concat(s1) == "450123");
		TEST(s3.concat(s1) == s1);
	}
	{
		elm::String s1("0123");
		elm::CString s2("45"), s3("");
		TEST(s1.concat(s1) == "01230123");
		TEST(s1.concat(s2) == "012345");
		TEST(s1.concat(s3) == s1);
		TEST(s2.concat(s1) == "450123");
		TEST(s3.concat(s1) == s1);
	}
	
	// Index of
	{
		elm::String s("00010010010");
		TEST(s.indexOf('1') == 3);
		TEST(s.indexOf('2') < 0);
		TEST(s.indexOf('1', 4) == 6);
		TEST(s.indexOf('2', 4) < 0);
		TEST(s.indexOf('1', 10) < 0);
		TEST(s.indexOf('2', 10) < 0);
	}
	{
		elm::CString s("00010010010");
		TEST(s.indexOf('1') == 3);
		TEST(s.indexOf('2') < 0);
		TEST(s.indexOf('1', 4) == 6);
		TEST(s.indexOf('2', 4) < 0);
		TEST(s.indexOf('1', 10) < 0);
		TEST(s.indexOf('2', 10) < 0);
	}
	{
		elm::String s("00010010010");
		TEST(s.lastIndexOf('1') == 9);
		TEST(s.lastIndexOf('2') < 0);
		TEST(s.lastIndexOf('1', 8) == 6);
		TEST(s.lastIndexOf('2', 8) < 0);
		TEST(s.lastIndexOf('1', 3) < 0);
		TEST(s.lastIndexOf('2', 3) < 0);
	}
	{
		elm::CString s("00010010010");
		TEST(s.lastIndexOf('1') == 9);
		TEST(s.lastIndexOf('2') < 0);
		TEST(s.lastIndexOf('1', 8) == 6);
		TEST(s.lastIndexOf('2', 8) < 0);
		TEST(s.lastIndexOf('1', 3) < 0);
		TEST(s.lastIndexOf('2', 3) < 0);
	}
	
	// startsWith tests
	{
		elm::String s("0123456789"), s1("0123"), s2("ok"), s3("");
		TEST(s.startsWith(s) == true);
		TEST(s.startsWith(s1) == true);
		TEST(s.startsWith(s2) == false);
		TEST(s.startsWith(s3) == true);
		TEST(s1.startsWith(s) == false);
		TEST(s2.startsWith(s) == false);
		TEST(s3.startsWith(s) == false);
	}
	{
		elm::CString s("0123456789"), s1("0123"), s2("ok"), s3("");
		TEST(s.startsWith(s) == true);
		TEST(s.startsWith(s1) == true);
		TEST(s.startsWith(s2) == false);
		TEST(s.startsWith(s3) == true);
		TEST(s1.startsWith(s) == false);
		TEST(s2.startsWith(s) == false);
		TEST(s3.startsWith(s) == false);
	}
	{
		elm::CString s("0123456789");
		elm::String s1("0123"), s2("ok"), s3("");
		TEST(s.startsWith(s) == true);
		TEST(s.startsWith(s1) == true);
		TEST(s.startsWith(s2) == false);
		TEST(s.startsWith(s3) == true);
		TEST(s1.startsWith(s) == false);
		TEST(s2.startsWith(s) == false);
		TEST(s3.startsWith(s) == false);
	}
	{
		elm::String s("0123456789");
		elm::CString s1("0123"), s2("ok"), s3("");
		TEST(s.startsWith(s) == true);
		TEST(s.startsWith(s1) == true);
		TEST(s.startsWith(s2) == false);
		TEST(s.startsWith(s3) == true);
		TEST(s1.startsWith(s) == false);
		TEST(s2.startsWith(s) == false);
		TEST(s3.startsWith(s) == false);
	}
	
	// endsWith tests
	{
		elm::String s("0123456789"), s1("6789"), s2("ok"), s3("");
		TEST(s.endsWith(s) == true);
		TEST(s.endsWith(s1) == true);
		TEST(s.endsWith(s2) == false);
		TEST(s.endsWith(s3) == true);
		TEST(s1.endsWith(s) == false);
		TEST(s2.endsWith(s) == false);
		TEST(s3.endsWith(s) == false);
	}
	{
		elm::CString s("0123456789"), s1("6789"), s2("ok"), s3("");
		TEST(s.endsWith(s) == true);
		TEST(s.endsWith(s1) == true);
		TEST(s.endsWith(s2) == false);
		TEST(s.endsWith(s3) == true);
		TEST(s1.endsWith(s) == false);
		TEST(s2.endsWith(s) == false);
		TEST(s3.endsWith(s) == false);
	}
	{
		elm::String s("0123456789");
		elm::CString s1("6789"), s2("ok"), s3("");
		TEST(s.endsWith(s) == true);
		TEST(s.endsWith(s1) == true);
		TEST(s.endsWith(s2) == false);
		TEST(s.endsWith(s3) == true);
		TEST(s1.endsWith(s) == false);
		TEST(s2.endsWith(s) == false);
		TEST(s3.endsWith(s) == false);
	}
	{
		elm::CString s("0123456789");
		elm::String s1("6789"), s2("ok"), s3("");
		TEST(s.endsWith(s) == true);
		TEST(s.endsWith(s1) == true);
		TEST(s.endsWith(s2) == false);
		TEST(s.endsWith(s3) == true);
		TEST(s1.endsWith(s) == false);
		TEST(s2.endsWith(s) == false);
		TEST(s3.endsWith(s) == false);
	}
	
}

// Utility tests
void test_utility(void) {
	TEST_UNIT("Utility");
	
	// Optional test
	{
		Option<int> one(666), none;
		TEST(one.isOne() == true);
		TEST(one.isNone() == false);
		TEST(one.value() == 666);
		TEST(none.isOne() == false);
		TEST(none.isNone() == true);
	}
	
	// Hashing tests
	{
		HashKey<int>& hkey = HashKey<int>::def;
		TEST(hkey.hash(0) == hkey.hash(0));
		TEST(hkey.hash(666) == hkey.hash(666));
		TEST(hkey.hash(-111) == hkey.hash(-111));
		TEST(hkey.equals(0, 0) == true);
		TEST(hkey.equals(666, 666) == true);
		TEST(hkey.equals(666, -111) == false);
	}
	{
		HashKey<void *>& hkey = HashKey<void *>::def;
		char val;
		TEST(hkey.hash(0) == hkey.hash(0));
		TEST(hkey.hash(&val) == hkey.hash(&val));
		TEST(hkey.equals(0, 0) == true);
		TEST(hkey.equals(&val, &val) == true);
		TEST(hkey.equals(&val, 0) == false);
	}
	{
		HashKey<String>& hkey = HashKey<String>::def;
		String s1("0123456789"), s2, s3("0123456789");
		TEST(hkey.hash(s2) == hkey.hash(s2));
		TEST(hkey.hash(s1) == hkey.hash(s1));
		TEST(hkey.hash(s1) == hkey.hash(s3));
		TEST(hkey.equals(s2, s2) == true);
		TEST(hkey.equals(s1, s1) == true);
		TEST(hkey.equals(s1, s3) == true);
		TEST(hkey.equals(s1, s2) == false);
	}
	{
		HashKey<CString>& hkey = HashKey<CString>::def;
		CString s1("0123456789"), s2, s3("0123456789");
		TEST(hkey.hash(s2) == hkey.hash(s2));
		TEST(hkey.hash(s1) == hkey.hash(s1));
		TEST(hkey.hash(s1) == hkey.hash(s3));
		TEST(hkey.equals(s2, s2) == true);
		TEST(hkey.equals(s1, s1) == true);
		TEST(hkey.equals(s1, s3) == true);
		TEST(hkey.equals(s1, s2) == false);
	}
	
	// Comparators tests
	{
		Comparator<int>& int_comp = Comparator<int>::def;
		TEST(int_comp.compare(-111, 666) < 0);
		TEST(int_comp.compare(666, -111) > 0);
		TEST(int_comp.compare(666, 666) == 0);
		TEST(int_comp.compare(-111, -111) == 0);
		TEST(int_comp.compare(0, 0) == 0);
		TEST(int_comp.compare(0, 666) < 0);
		TEST(int_comp.compare(666, 0) > 0);
		TEST(int_comp.compare(0, -111) > 0);
		TEST(int_comp.compare(-111, 0) < 0);
	}
	{
		static char v[2];
		char *v1 = v, *v2 = v + 1;
		Comparator<void *>& pointer_comp = Comparator<void *>::def;
		TEST(pointer_comp.compare(v1,v2) < 0);
		TEST(pointer_comp.compare(v2, v1) > 0);
		TEST(pointer_comp.compare(v2, v2) == 0);
		TEST(pointer_comp.compare(v1, v1) == 0);
		TEST(pointer_comp.compare(0, 0) == 0);
		TEST(pointer_comp.compare(0, v2) != 0);
		TEST(pointer_comp.compare(v2, 0) != 0);
	}
	{
		String v1("ok"), v2("ko"), v3("ok"), v4("okk");
		Comparator<String>& string_comp = Comparator<String>::def;
		TEST(string_comp.compare(v1, v1) == 0);		// Reflexive
		TEST(string_comp.compare(v1, v2) > 0);		// Symetric
		TEST(string_comp.compare(v2, v1) < 0);
		TEST(string_comp.compare(v1, v4) < 0);		// Transitive
		TEST(string_comp.compare(v2, v4) < 0);
		TEST(string_comp.compare(v1, v3) == 0);		// Internal representation
	}
	{
		CString v1("ok"), v2("ko"), v3("ok"), v4("okk");
		Comparator<CString>& string_comp = Comparator<CString>::def;
		TEST(string_comp.compare(v1, v1) == 0);		// Reflexive
		TEST(string_comp.compare(v1, v2) > 0);		// Symetric
		TEST(string_comp.compare(v2, v1) < 0);
		TEST(string_comp.compare(v1, v4) < 0);		// Transitive
		TEST(string_comp.compare(v2, v4) < 0);
		TEST(string_comp.compare(v1, v3) == 0);		// Internal representation
	}
}

// test_list()
/*static void test_list() {
	TEST_UNIT("List");
	
	// Base methods
	{
		List<int> empty = List<int>::nil();
		TEST(empty.isEmpty());
		TEST(empty.tail() == empty);
		TEST(empty.length() == 0);
		List<int> l1(666, empty);
		TEST(l1.head() == 666);
		TEST(l1.tail() == empty);
		TEST(l1.length() == 1);
		List<int> l2(111, l1);
		TEST(l2.head() == 111);
		TEST(l2.tail() == l1);
		TEST(l2.length() == 2);
	}
	
	// Super building
	{
		List<int> l(3, 1, 2, 3);
		TEST(l.length() == 3);
		TEST(l.head() == 1);
		TEST(l.tail().head() == 2);
		TEST(l.tail().tail().head() == 3);
		List<int> l2 = l.reverse();
		TEST(l2.head() == 3);
		TEST(l2.tail().head() == 2);
		TEST(l2.tail().tail().head() == 1);
	}
	
	// Append
	{
		List<int> l1(2, 1, 2);
		List<int> l2(2, 3, 4);
		List<int> l3 = l1.appends(l2);
		TEST(l3.length() == 4);
		TEST(l3.head() == 1);
		TEST(l3.tail().head() == 2);
		TEST(l3.tail().tail().head() == 3);
		TEST(l3.tail().tail().tail().head() == 4);
		TEST(l1.appends(List<int>::nil()) == l1);
		TEST(List<int>::nil().appends(l1) == l1);
	}
	
	// Contains
	{
		List<int> l(5, 0, 1, 2, 3, 4);
		TEST(l.contains(0) == true);
		TEST(l.contains(3) == true);
		TEST(l.contains(4) == true);
		TEST(l.contains(666) == false);
	}
	
}*/

// test_vector()
static void test_vector(void) {
	TEST_UNIT("Vector");
	
	// Simple test
	{
		datastruct::Vector<int> v;
		v.add(0);
		v.add(1);
		v.add(2);
		v.add(3);
		TEST(v.count() == 4);
		TEST(v.item(0) == 0);
		TEST(v.item(1) == 1);
		TEST(v.item(2) == 2);
		TEST(v.item(3) == 3);
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
		TEST(ok);
	}
	
	// Insertion
	{
		datastruct::Vector<int> v;
		v.add(0);
		v.add(1);
		v.add(3);
		v.insert(2, 2);
		TEST(v.item(0) == 0);
		TEST(v.item(1) == 1);
		TEST(v.item(2) == 2);
		TEST(v.item(3) == 3);
		v.insert(4, 4);
		TEST(v.item(3) == 3);
		TEST(v.item(4) == 4);
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
		TEST(v.contains(1) == true);
		TEST(v.contains(2) == false);
		TEST(v.indexOf(1) == 1);
		TEST(v.indexOf(2) < 0);
		TEST(v.indexOf(1, 2) == 3);
		TEST(v.indexOf(1, 6) < 0);
		TEST(v.lastIndexOf(1) == 5);
		TEST(v.lastIndexOf(2) < 0);
		TEST(v.lastIndexOf(1, 4) == 3);
		TEST(v.lastIndexOf(1, 1) < 0);
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
		TEST(v.count() == 4);
		TEST(v.item(3) == 3);
		v.removeAt(1);
		TEST(v.count() == 3);
		TEST(v.item(0) == 0);
		TEST(v.item(1) == 2);
		TEST(v.item(2) == 3);
		v.remove(3);
		TEST(v.count() == 2);
		TEST(v.item(0) == 0);
		TEST(v.item(1) == 2);
		v.clear();
		TEST(v.count() == 0);
	}
}

// test_hashtable()
static void test_hashtable(void) {
	TEST_UNIT("HashTable");
	
	// Simple key
	{
		genstruct::HashTable<int, int> htab;
		TEST(htab.isEmpty() == true);
		TEST(htab.count() == 0);
		htab.put(666, 111);
		TEST(htab.isEmpty() == false);
		TEST(htab.count() == 1);
		TEST(htab.get(666, 0) == 111);
		TEST(htab.get(111, 0) == 0);
		htab.put(777, 222);
		TEST(htab.isEmpty() == false);
		TEST(htab.count() == 2);
		TEST(htab.get(666, 0) == 111);
		TEST(htab.get(777, 0) == 222);
		TEST(htab.get(111, 0) == 0);
		htab.remove(666);
		TEST(htab.count() == 1);
		TEST(htab.get(666, 0) == 0);
		TEST(htab.get(777, 0) == 222);
	}
	
	// Complex key
	{
		genstruct::HashTable<String, int> htab;
		String k1("key1"), k2("key2"), k3("key3");
		TEST(htab.isEmpty() == true);
		TEST(htab.count() == 0);
		htab.put(k1, 111);
		TEST(htab.isEmpty() == false);
		TEST(htab.count() == 1);
		TEST(htab.get(k1, 0) == 111);
		TEST(htab.get(k3, 0) == 0);
		htab.put(k2, 222);
		TEST(htab.isEmpty() == false);
		TEST(htab.count() == 2);
		TEST(htab.get(k1, 0) == 111);
		TEST(htab.get(k2, 0) == 222);
		TEST(htab.get(k3, 0) == 0);
		htab.remove(k1);
		TEST(htab.count() == 1);
		TEST(htab.get(k1, 0) == 0);
		TEST(htab.get(k2, 0) == 222);
	}
	
	// datastruct test
	{
		datastruct::HashTable<int, int> htab;
	}
}


// test_lock()
static void test_lock(void) {
	TEST_UNIT("Lock");
	
	// Simple test
	{
		bool alloc = false;
		{
			AutoPtr<LockTest> p = new LockTest(&alloc);
			TEST(alloc);
		}
		TEST(!alloc);
	}
	
	// Null assignment test
	{
		bool alloc = false;
		{
			AutoPtr<LockTest> p;
			TEST(!alloc);
			p = new LockTest(&alloc);
			TEST(alloc);
		}
		TEST(!alloc);
	}
	
	// Passing test
	{
		bool alloc = false;
		{
			AutoPtr<LockTest> p1;
			{
				AutoPtr<LockTest> p2 = new LockTest(&alloc);
				TEST(alloc);
				p1 = p2;
				TEST(alloc);
			}
			TEST(alloc);
		}
		TEST(!alloc);
	}
	
	// Passing null
	{
		bool alloc = false;
		AutoPtr<LockTest> p = new LockTest(&alloc);
		TEST(alloc);
		p = 0;
		TEST(!alloc);
	}
	
	// Transitivity
	{
		bool alloc = false;
		AutoPtr<LockTest> p1 = new LockTest(&alloc);
		TEST(alloc);
		AutoPtr<LockTest> p2 = p1;
		TEST(alloc);
		AutoPtr<LockTest> p3 = p2;
		TEST(alloc);
		p1 = 0;
		TEST(alloc);
		p3 = 0;
		TEST(alloc);
		p2 = 0;
		TEST(!alloc);
	}
	
	// Usage test
	{
		bool alloc = false;
		AutoPtr<LockTest> p = new LockTest(&alloc);
		TEST(p->getAlloc() == alloc);
	}
}	


// test_dllist()
/*static void test_dllist(void) {
	TEST_UNIT("DLList");
	
	// Base tests
	{
		obj::DLList<int> l;
		TEST(l.isEmpty());
		l.addLast(666);
		TEST(!l.isEmpty());
		TEST(l.count() == 1);
		TEST(l.contains(666));
		TEST(!l.contains(111));
		l.addLast(111);
		TEST(!l.isEmpty());
		TEST(l.count() == 2);
		TEST(l.contains(666));
		TEST(l.contains(111));
	}
	
	// Removal tests
	{
		obj::DLList<int> l;
		l.addLast(0);
		l.addLast(1);
		l.addLast(2);
		TEST(l.count() == 3);
		l.remove(1);
		TEST(l.count() == 2);
		TEST(l.contains(0));
		TEST(!l.contains(1));
		TEST(l.contains(2));
		l.remove(2);
		TEST(l.count() == 1);
		TEST(l.contains(0));
		TEST(!l.contains(1));
		TEST(!l.contains(2));
		l.remove(0);
		TEST(l.count() == 0);
		TEST(!l.contains(0));
		TEST(!l.contains(1));
		TEST(!l.contains(2));
	}
	
	// Iterator test
	{
		obj::DLList<int> l;
		l.addLast(0);
		l.addLast(1);
		l.addLast(2);
		l.addLast(3);
		l.addLast(4);
		TEST(l.count() == 5);
		int i = 0;
		for(Iterator<int> iter(l); iter; iter++, i++)
			TEST(*iter == i);
	}
	
	// Bi-directionnal walk test
	{
		inh::DLList list;
		list.addLast(new MyDLNode(0));
		list.addLast(new MyDLNode(1));
		list.addLast(new MyDLNode(2));
		TEST(list.count() == 3);
		int cnt = 0;
		for(MyDLNode *node = (MyDLNode *)list.first(); !node->atEnd();
		node = (MyDLNode *)node->next(), cnt++)
			TEST(node->v == cnt);
		TEST(cnt == 3);
		cnt--;
		for(MyDLNode *node = (MyDLNode *)list.last(); !node->atBegin();
		node = (MyDLNode *)node->previous(), cnt--)
			TEST(node->v == cnt);
		TEST(cnt == -1);
	}
	
	// Insert before and efter tests
	{
		inh::DLList list;
		list.addLast(new MyDLNode(0));
		list.addLast(new MyDLNode(2));
		list.addLast(new MyDLNode(4));
		inh::DLNode *node = list.first();
		TEST(!node->atEnd());
		node = node->next();
		TEST(!node->atEnd());
		node->insertBefore(new MyDLNode(1));
		node->insertAfter(new MyDLNode(3));
		int cnt = 0;
		for(MyDLNode *node = (MyDLNode *)list.first(); !node->atEnd();
		node = (MyDLNode *)node->next(), cnt++)
			TEST(node->v == cnt);
		TEST(cnt == 5);
		cnt--;
		for(MyDLNode *node = (MyDLNode *)list.last(); !node->atBegin();
		node = (MyDLNode *)node->previous(), cnt--)
			TEST(node->v == cnt);
		TEST(cnt == -1);		
	}
}*/

// test_sorted_bintree()
class MyVisitor: public genstruct::SortedBinTree<int>::Visitor {
	int count;
public:
	inline MyVisitor(void): count(0) {
	};
	virtual int process(int value) {
		TEST(count <= 5);
		TEST(count == value);
		count++;
	};
};
static void test_sorted_bintree(void) {
	TEST_UNIT("SortedBinTree");
	
	// Base test
	{
		genstruct::SortedBinTree<int> tree;
		tree.insert(5);
		tree.insert(0);
		tree.insert(1);
		tree.insert(2);
		tree.insert(4);
		tree.insert(3);
		TEST(!tree.contains(10));
		TEST(tree.contains(0));
		TEST(tree.contains(1));
		TEST(tree.contains(2));
		TEST(tree.contains(3));
		TEST(tree.contains(4));
		TEST(tree.contains(5));
		MyVisitor visitor;
		tree.visit(&visitor);
	}
}


// StringBuffer test
static void test_string_buffer(void) {
	TEST_UNIT("StringBuffer");
	
	// Empty string
	{
		StringBuffer buffer;
		TEST(buffer.length() == 0);
		String str = buffer.toString();
		TEST(str == "");
	}
	
	// C String puts
	{
		StringBuffer buffer;
		buffer.put("0123");
		TEST(buffer.length() == 4);
		buffer.put("");
		TEST(buffer.length() == 4);
		buffer.put("4567");
		TEST(buffer.length() == 8);
		String str = buffer.toString();
		TEST(str == "01234567");
	}
	
	// Different put types
	{
		StringBuffer buffer;
		buffer.put('0');
		buffer.put("1");
		CString cstr("2");
		buffer.put(cstr);
		String str("3");
		buffer.put(str);
		String res = buffer.toString();
		TEST(res == "0123");
	}
	
	// Formatted test
	{
		StringBuffer buffer;
		buffer.print("%s%s%s%s", "0", "1", "2", "3");
		String str = buffer.toString();
		TEST(str == "0123");
	}
}


// Entry point
int main(void) {
	test_string();
	test_utility();
	//test_list();
	test_vector();
	test_hashtable();
	test_lock();
	//test_dllist();
	test_sorted_bintree();
	test_string_buffer();
	TEST_END;
	return failures ? EXIT_FAILURE : EXIT_SUCCESS;
}
