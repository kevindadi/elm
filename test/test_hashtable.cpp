/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_hastable.cpp -- unit tests for elm::xxx::HashTable classes.
 */

#include <elm/data/HashMap.h>
#include <elm/data/HashSet.h>
#include <elm/data/Vector.h>
#include <elm/util/BitVector.h>
#include "../include/elm/test.h"

using namespace elm;

// test_hashtable()
TEST_BEGIN(hashtable)

	// HashTable
	{
		if(false) {
			HashTable<int> t;
			HashTable<int> ct(t);
			t.hash();
			ct.hash();
			t.allocator();
			ct.allocator();
			t.isEmpty();
			t.count();
			t.get(1);
			t.hasKey(1);
			t.put(1);
			t.add(1);
			t.putAll(t);
			t.remove(1);
			t.remove(t.begin());
			t.clear();
			t.begin();
			t.end();
			t = ct;
			t.equals(t);
			t == t;
			t != t;
			t += 1;
			t -= 1;
		}
	}

	// HashMap
	{
		if(false) {
			HashMap<int, int> m;
			HashMap<int, int> cm;
			m.hash();
			cm.hash();
			m.allocator();
			cm.allocator();
			m.equivalence();
			cm.equivalence();
			m.clear();
			m.add(1, 1);
			m.get(1);
			m.get(1, 2);
			m.hasKey(1);
			m.keys();
			m.pairs();
			m.count();
			m.isEmpty();
			static_cast<bool>(m);
			m.begin();
			m.end();
			m.contains(1);
			m.containsAll(m);
			m.equals(m);
			m == m;
			m != m;
			m.includes(m);
			m <= m;
			m >= m;
			m < m;
			m > m;
			m.put(1, 1);
			m.remove(1);
			m.remove(m.begin());
			m.putAll(m);
			m[1];
			cm[1];
			m[1] = 1;
			m.fetch(1);
		}
	}

	// HashSet
	{
		if(false) {
			HashSet<int> s;
			const HashSet<int> cs(s);
			s.hash();
			cs.hash();
			s.allocator();
			cs.allocator();
			s.count();
			s.contains(1);
			s.isEmpty();
			static_cast<bool>(s);
			s.begin();
			s.end();
			s.equals(s);
			s == s;
			s != s;
			s.subsetOf(s);
			s <= s;
			s >= s;
			s < s;
			s > s;
			s.clear();
			s.add(1);
			s.addAll(s);
			s.remove(1);
			s.removeAll(s);
			s.remove(s.begin());
			s.copy(s);
			s = s;
			s += 1;
			s -= 1;
			s.insert(1);
			s.join(s);
			s.diff(s);
			s.meet(s);
			s += s;
			s |= s;
			s -= s;
			s *= s;
			s &= s;
			HashSet<int> r = s + s;
			r = s | s;
			r = s - s;
			r = s * s;
			r = s & s;
		}
	}

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
		for(HashMap<int, int>::KeyIter key(map); key(); key++) {
			CHECK(mask & (1 << *key));
			mask &= ~(1 << *key);
		}
		CHECK(!mask);
		mask = 0x3ff;
		for(HashMap<int, int>::Iter item(map); item(); item++) {
			CHECK(mask & (1 << *item));
			mask &= ~(1 << *item);
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
			auto o = map2.get(k);
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

	// HashMap test
	{
		HashSet<int> set;
		CHECK(set.isEmpty());
		CHECK_EQUAL(set.count(), 0);
		set.add(111);
		CHECK(!set.isEmpty());
		CHECK_EQUAL(set.count(), 1);
		CHECK(set.contains(111));
		CHECK(!set.contains(666));
		set.add(666);
		CHECK(!set.isEmpty());
		CHECK_EQUAL(set.count(), 2);
		CHECK(set.contains(111));
		CHECK(set.contains(666));
		set.remove(111);
		CHECK(!set.isEmpty());
		CHECK_EQUAL(set.count(), 1);
		CHECK(!set.contains(111));
		CHECK(set.contains(666));

		HashSet<int>::Iter i = set.items();
		CHECK(*i);
		CHECK_EQUAL(*i, 666);
		i++;
		CHECK(!i);

		Vector<int> v;
		v.add(666);
		CHECK(set.containsAll(v));
		v.add(111);
		CHECK(!set.containsAll(v));
		set.addAll(v);
		CHECK(!set.isEmpty());
		CHECK_EQUAL(set.count(), 2);
		CHECK(set.contains(111));
		CHECK(set.contains(666));
		set.removeAll(v);
		CHECK(set.isEmpty());
		CHECK_EQUAL(set.count(), 0);
	}

	// C++ for statement
	{
		HashMap<int, int> map;
		const int N = 10;
		for(int i = 0; i < N; i++)
			map.put(i, i);

		BitVector bv(N);
		for(auto x: map)
			bv.set(x);
		CHECK(bv.countBits() == N);

		bv.clear();
		for(auto x: map.keys())
			bv.set(x);
		CHECK(bv.countBits() == N);

		bv.clear();
		for(auto x: map.pairs())
			bv.set(x.snd);
		CHECK(bv.countBits() == N);
	}

	{
		HashSet<int> set;
		const int N = 10;
		for(int i = 0; i < N; i++)
			set.add(i);

		BitVector bv(N);
		for(auto x: set)
			bv.set(x);
		CHECK(bv.countBits() == N);
	}

TEST_END
