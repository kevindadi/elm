/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_hastable.cpp -- unit tests for elm::xxx::HashTable classes.
 */

#include <elm/util/test.h>
#include <elm/data/HashMap.h>
#include <elm/genstruct/HashTable.h>

using namespace elm;

// test_hashtable()
TEST_BEGIN(hashtable)


	// Simple key
	{
		HashMap<int, int> map;
		CHECK(map.isEmpty() == true);
		CHECK(map.count() == 0);
		map.put(666, 111);
		CHECK(map.isEmpty() == false);
		CHECK(map.count() == 1);
		CHECK(map.get(666, 0) == 111);
		CHECK(map.get(111, 0) == 0);
		map.put(777, 222);
		CHECK(map.isEmpty() == false);
		CHECK(map.count() == 2);
		CHECK(map.get(666, 0) == 111);
		CHECK(map.get(777, 0) == 222);
		CHECK(map.get(111, 0) == 0);
		map.remove(666);
		CHECK(map.count() == 1);
		CHECK(map.get(666, 0) == 0);
		CHECK(map.get(777, 0) == 222);
	}

	// Complex key
	{
		HashMap<String, int> map;
		String k1("key1"), k2("key2"), k3("key3");
		CHECK(map.isEmpty() == true);
		CHECK(map.count() == 0);
		map.put(k1, 111);
		CHECK(map.isEmpty() == false);
		CHECK(map.count() == 1);
		CHECK(map.get(k1, 0) == 111);
		CHECK(map.get(k3, 0) == 0);
		map.put(k2, 222);
		CHECK(map.isEmpty() == false);
		CHECK(map.count() == 2);
		CHECK(map.get(k1, 0) == 111);
		CHECK(map.get(k2, 0) == 222);
		CHECK(map.get(k3, 0) == 0);
		map.remove(k1);
		CHECK(map.count() == 1);
		CHECK(map.get(k1, 0) == 0);
		CHECK(map.get(k2, 0) == 222);
	}

	// Iterator test
	{
		HashMap<int, int> map;
		for(int i = 0; i < 10; i++)
			map.put(i, 9 - i);
		int mask = 0x3ff;
		for(HashMap<int, int>::KeyIter key(map); key; key++) {
			CHECK(mask & (1 << key));
			mask &= ~(1 << key);
		}
		CHECK(!mask);
		mask = 0x3ff;
		for(HashMap<int, int>::Iter item(map); item; item++) {
			CHECK(mask & (1 << item));
			mask &= ~(1 << item);
		}
		CHECK(!mask);
	}

	// operator[] test
	{
		HashMap<cstring, int> map;
		map[cstring("ok")] = 111;
		map[cstring("ko")] = 666;
		CHECK_EQUAL(*(map[cstring("ok")]), 111);
		CHECK_EQUAL(*(map[cstring("ko")]), 666);
	}

	// copy of table
	{
		HashMap<string, int> map1, map2;
		for(int i = 0; i < 100; i++)
			map1.put(_ << i << (-i), i);
		map2 = map1;
		bool failed = false;
		for(int i = 0; i < 100; i++) {
			string k = _ << i << (-i);
			Option<int> o = map2.get(k);
			if(!o || *o != i) {
				failed = true;
				break;
			}
		}
		CHECK(!failed);
	}

	// use of brackets
	{
		HashMap<string, int> map;
		map[str("god")] = 111;
		map[str("devil")] = 666;
		CHECK_EQUAL(111, *map[str("god")]);
		CHECK_EQUAL(666, *map[str("devil")]);
		map[str("god")] = 0;
		CHECK_EQUAL(0, *map[str("god")]);
		CHECK_EQUAL(666, *map[str("devil")]);
	}

TEST_END
