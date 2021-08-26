/*
 *	Test for SortedSLList class.
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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
#include <elm/data/SortedList.h>
#include <elm/data/ListMap.h>
#include <elm/data/ListSet.h>
#include <elm/test.h>
#include "check-concept.h"

using namespace elm;

TEST_BEGIN(sorted_list)

	SortedList<int> list;
	
	// concept test
	{
		checkCollection(list, list, 111);
		checkMutableCollection(list, 111);
		checkList(list, 111);
	}

	{
		// Addition
		list.add(5);
		CHECK(list.contains(5));
		CHECK(!list.contains(0));
		CHECK(!list.isEmpty());
		list.add(9);
		CHECK(list.contains(9));
		CHECK(list.contains(5));
		list.add(2);
		CHECK(list.contains(2));
		CHECK(list.contains(9));

		// Traversal
		SortedList<int>::Iter item(list);
		CHECK(item());
		if(item()) {
			CHECK(*item == 2);
			item++;
			CHECK(*item);
			if(item()) {
				CHECK(*item == 5);
				item++;
				CHECK(item());
				if(item()) {
					CHECK(*item == 9);
					item++;
					CHECK(!item);
				}
			}
		}

		// Removal
		list.remove(5);
		CHECK(!list.contains(5));
		CHECK(list.contains(2));
		CHECK(list.contains(9));
		list.remove(9);
		CHECK(!list.contains(5));
		CHECK(list.contains(2));
		CHECK(!list.contains(9));
		list.remove(2);
		CHECK(!list.contains(5));
		CHECK(!list.contains(2));
		CHECK(!list.contains(9));
		CHECK(list.isEmpty());

		// Sorted list clone
		list.add(3);
		list.add(0);
		list.add(5);
		SortedList<int> cloned_list(list);
		CHECK(!list.isEmpty());
		CHECK(list.contains(3));
		CHECK(list.contains(0));
		CHECK(list.contains(5));
		CHECK(!list.contains(2));
	}
	
	{
		// basic operations
		ListSet<int> l;
		CHECK(!(0 <= l));
		l.add(0);
		CHECK(0 <= l);
		l.add(0);
		CHECK_EQUAL(l.count(), 1);
		l += 1;
		CHECK(1 <= l);
		CHECK(!(2 <= l));
		l += 2;
		CHECK(2 <= l);
		l -= 2;
		CHECK(!(2 <= l));

		// join operation
		ListSet<int> ll;
		ll += -1;
		ll += 0;
		ll += 2;
		ll += l;
		CHECK_EQUAL(ll.count(), 4);
		CHECK(-1 <= ll);
		CHECK(0 <= ll);
		CHECK(1 <= ll);
		CHECK(2 <= ll);

		// diff operation
		ll -= l;
		CHECK_EQUAL(ll.count(), 2);
		CHECK(-1 <= ll);
		CHECK(!(0 <= ll));
		CHECK(!(1 <= ll));
		CHECK(2 <= ll);

		// intersection operation
		ll &= l;
		CHECK(ll.isEmpty());
	}

	// list map
	{
		ListMap<int, const char *> l;
		CHECK(!l.hasKey(0));
		l.put(0, "ok");
		CHECK(l.hasKey(0));
		Option<const char *> o = l.get(1);
		CHECK(!o);
		o = l.get(0);
		CHECK(o);
		if(o)
			CHECK_EQUAL(cstring(o), cstring("ok"));
		cstring r = l.get(0, "");
		CHECK_EQUAL(r, cstring("ok"));
		CHECK_EQUAL(cstring(l.get(1, "ko")), cstring("ko"));
		l.put(1, "ko");
		CHECK(l.hasKey(1));
		l.remove(1);
		CHECK(!l.hasKey(1));
	}
	
	// list map mutability
	{
		ListMap<int, int> l;
		l.put(1, 1);
		l.put(2, 2);
		l.put(3, 3);
		for(auto& x: l)
			if(x == 2)
				x = 666;
		CHECK_EQUAL(l.get(2, 0), 666);
	}
	
	// dedicated comparator
	{
		class C {
		public:
			int doCompare(int x, int y) const { return y - x; }
		};
		ListMap<int, int, C> l;
		l.put(1, 1);
		l.put(2, 2);
		l.put(3, 3);
		int s = 0;
		for(auto x: l)
			s += x;
		CHECK_EQUAL(s, 6);
	}

TEST_END
