/*
 *	avl module test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2013, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "../include/elm/test.h"
#include <elm/avl/Set.h>
#include <elm/avl/Map.h>
#include <elm/sys/System.h>
#include <elm/io.h>
 
using namespace elm;
using namespace elm::avl;

static const int maxv = 10000;
static const int _count = 10000;

// Entry point
TEST_BEGIN(avl)

	// small tree
	{
		avl::Set<int> set;
		set.add(10);
		CHECK(set.contains(10));
		CHECK(!set.contains(5));
		CHECK(!set.contains(15));
		set.add(5);
		CHECK(set.contains(10));
		CHECK(set.contains(5));
		CHECK(!set.contains(15));
		set.add(15);
		CHECK(set.contains(10));
		CHECK(set.contains(5));
		CHECK(set.contains(15));
	}

	// worst case on right
	{
		avl::Set<int> set;
		for(int i = 0; i < 20; i++)
			set.add(i);
		bool all = true;
		for(int i = 0; i < 20; i++)
			all = all || set.contains(i);
		CHECK_EQUAL(set.count(), 20);

		// test iterator
		bool ok = true;
		int n = 0;
		for(auto i = set.begin(); i(); i++, n++)
			ok = ok || *i == n;
		CHECK(ok);
	}

	// worst case on left
	{
		avl::Set<int> set;
		for(int i = 20; i > 0; i--)
			set.add(i);
		bool all = true;
		for(int i = 0; i < 20; i++)
			all = all || set.contains(i);
		CHECK_EQUAL(set.count(), 20);

		// test iterator
		bool ok = true;
		int n = 1;
		for(auto i = set.begin(); i(); i++, n++)
			ok = ok || *i == n;
		CHECK(ok);
	}

	// copy test case
	{
		int t[] = { 3, 5, 0, 2, 1, 8, 7, 6, -1 };
		avl::Set<int> set;
		for(int i = 0; t[i] >= 0; i++)
			set.add(t[i]);
		avl::Set<int> setp;
		setp = set;
		CHECK_EQUAL(set.count(), setp.count());
		auto i = set.begin(), ip = setp.begin();
		for(; i() && ip(); i++, ip++)
			if(*i != *i)
				break;
		CHECK(!i && !ip);
	}

	// failing use case
	{
		avl::Set<int> set;
		set.add(1);
		set.remove(1);
		set.add(2);
		set.remove(2);
		set.add(6);
		CHECK(!set.contains(7));
		set.add(7);
		CHECK(set.contains(7));
		set.remove(7);
		CHECK(!set.contains(7));
	}

	// unit test
	{
		Set<int> tree;
		CHECK(tree.isEmpty());
		tree.add(100);
		CHECK(!tree.isEmpty());
		CHECK(tree.contains(100));
		CHECK(!tree.contains(0));
	}

	// copy and clear
	{
		Set<int> tree;
		tree.add(10);
		tree.add(15);
		tree.add(0);
		tree.add(-10);
		tree.add(8);
		tree.add(20);
		CHECK(tree.contains(10));
		CHECK(tree.contains(15));
		CHECK(tree.contains(0));
		CHECK(tree.contains(-10));
		CHECK(tree.contains(8));
		CHECK(tree.contains(20));
		Set<int> tree2;
		tree2 = tree;
		CHECK(!tree2.isEmpty());
		CHECK(tree2.contains(10));
		CHECK(tree2.contains(15));
		CHECK(tree2.contains(0));
		CHECK(tree2.contains(-10));
		CHECK(tree2.contains(8));
		CHECK(tree2.contains(20));
		CHECK(tree == tree2);
		tree.clear();
		CHECK(tree.isEmpty());

	}

	{
		Set<int> set;
		set.add(7);
		set.add(9);
		set.add(4);
		set.add(3);
		set.remove(4);
		set.remove(7);
		CHECK(set.contains(3));
		CHECK(set.contains(9));
		CHECK(!set.contains(7));
	}

	{
		Set<int> set;
		set.add(20); 	// adding 2299
		set.add(10);	// adding 1780
		set.add(8);		// adding 832
		set.add(90);	// adding 9819
		set.remove(8);	// removing 832
	}

	// check AVLTree
	{
		Vector<int> ints;
		Set<int> tree;
		bool intensive = true;
		
		int rem_cnt = 0,
			ins_cnt = 0,
			chk_cnt = 0;
		for(int i = 0; intensive && i < _count; i++) {
			int a = sys::System::random(maxv * 2);

			// remove
			if(a < maxv && ints.count()) {
				int n = ints[a % ints.count()];
				//cerr << "removing " << ints[a % ints.count()] << io::endl;
				ints.remove(n);
				tree.remove(n);
				intensive = !tree.contains(n);
				rem_cnt++;
			}

			// insert
			else {
				int n = a % maxv;
				//cerr << "adding " << n << io::endl;
				if(!ints.contains(n))
					ints.add(n);
				tree.add(n);
				intensive = tree.contains(n);
				ins_cnt++;
			}

			// check
			//tree.printTree(cout);
			bool ok = true;
			for(int i = 0; ok && i < ints.count(); i++)
				if(!tree.contains(ints[i]))
					ok = false;
			intensive = ok;
			chk_cnt++;
		}
		cerr << "INFO: rem_cnt = " << rem_cnt
			 <<     ", ins_cnt = " << ins_cnt
			 <<     ", chk_cnt = " << chk_cnt << io::endl;
		CHECK(intensive);
	}

	// Map::PairIterator test
	{
		avl::Map<int, int> map;
		map.put(0, 0);
		map.put(1, 1);
		map.put(2, 2);
		map.put(3, 3);
		map.put(4, 4);
		bool equals = true;
		for(avl::Map<int, int>::PairIterator i(map); i(); i++)
			if((*i).fst != (*i).snd)
				equals = false;
		CHECK(equals);
	}

	// map with setting
	{
		avl::Map<int, int> map;
		map.put(0, 0);
		map.put(1, 1);
		map.put(2, 2);
		map.put(3, 3);
		map.put(4, 4);
		for(avl::Map<int, int>::MutableIterator i(map); i(); i++)
			if((*i).fst % 2 == 0)
				i.set(0);
		CHECK(*map.get(0) == 0);
		CHECK(*map.get(1) == 1);
		CHECK(*map.get(2) == 0);
		CHECK(*map.get(3) == 3);
		CHECK(*map.get(4) == 0);
	}

TEST_END

