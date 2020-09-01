/*
 *	list class test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005, IRIT UPS.
 *
 *	ELM is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	ELM is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with ELM; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/data/List.h>
#include <elm/data/ListSet.h>
#include <elm/data/SortedList.h>
#include <elm/data/ListMap.h>
#include <elm/data/Vector.h>
#include "../include/elm/test.h"

using namespace elm;

inline void get_bool(bool b) { }

class Eq {
public:
	bool isEqual(int x, int y) const { return x == y; }
};

TEST_BEGIN(list)

	// instantiate at least once each item
	{
		if(false) {
			List<int> l;
			l.equivalence();
			l.allocator();
			l.copy(l);
			l.items();
			*l;
			l.begin();
			l.end();
			l.count();
			l.contains(0);
			l.isEmpty();
			l.equals(l);
			get_bool(l == l);
			get_bool(l != l);
			l.at(l.begin());
			l.clear();
			l.add(0);
			l.addAll(l);
			l.removeAll(l);
			l.remove(0);
			List<int>::PrecIter pi(l);
			l.remove(pi);
			l.first();
			l.last();
			l.nth(0);
			l.find(0);
			l.find(0, *l);
			l.addFirst(0);
			l.addLast(0);
			l.addAfter(pi, 0);
			l.addBefore(pi, 0);
			l.removeFirst();
			l.removeLast();
			l.set(*l, 0);
			l.top();
			l.pop();
			l.push(0);
			l.reset();

			const List<int> cl;
			cl.at(cl.begin());
			cl.first();
			cl.last();
			l.nth(0);
		}
	}

	// Test initial
	{
		List<int> list;
		CHECK(list.count() == 0);
	}

	// Test addFirst
	{
		List<int> list;
		for(int i = 0; i < 10; i++)
			list.addFirst(i);
		CHECK(list.count() == 10);
		int i = 9;
		bool good = true;
		for(List<int>::Iter iter(list); iter(); iter++, i--)
			if(iter.item() != i) {
				good = false;
				break;
			}
		CHECK(good);
	}

	// list clone test
	{
		List<int> list1;
		list1.add(1);
		list1.add(2);
		list1.add(3);
		List<int> list2(list1);
		CHECK(!list2.isEmpty());
		CHECK(list2 & 1);
		CHECK(list2.contains(2));
		CHECK(list2.contains(3));
		CHECK(!list1.isEmpty());
		CHECK(list1.contains(1));
		CHECK(list1.contains(2));
		CHECK(list1.contains(3));
		list2.remove(2);
		CHECK(!list2.contains(2));
		CHECK(list1.contains(2));
		list2.remove(3);
		CHECK(!list2.contains(3));
		CHECK(list1.contains(3));
		list2.remove(1);
		CHECK(!list2.contains(1));
		CHECK(list1.contains(1));
	}


	// List copy test
	{
		List<int> list1, list2;
		list1.add(1);
		list1.add(2);
		list1.add(3);
		CHECK(list2.isEmpty());
		list2 = list1;
		CHECK(!list2.isEmpty());
		CHECK(list2 & 1);
		CHECK(list2.contains(2));
		CHECK(list2.contains(3));
		CHECK(!list1.isEmpty());
		CHECK(list1.contains(1));
		CHECK(list1.contains(2));
		CHECK(list1.contains(3));
		list2.remove(2);
		CHECK(!list2.contains(2));
		CHECK(list1.contains(2));
		list2.remove(3);
		CHECK(!list2.contains(3));
		CHECK(list1.contains(3));
		list2.remove(1);
		CHECK(!list2.contains(1));
		CHECK(list1.contains(1));
	}

	// test addAll, removeAll
	{
		Vector<int> v;
		v.add(1);
		v.add(2);
		v.add(3);
		List<int> l;
		l.addAll(v);
		CHECK(l.contains(1));
		CHECK(l.contains(2));
		CHECK(l.contains(3));
	}

	// duplication
	{
		List<int> l1;
		for(int i = 0; i < 10; i++)
			l1 += i;
		List<int> l2;
		int i = 9;
		bool eq = true;
		for(const auto ii: l2) {
			if(ii != i) {
				eq = false;
				break;
			}
			i--;
		}
		CHECK(eq);
	}

	// test remove with iterator
	{
		List<int> l;
		for(int i = 0; i < 10; i++)
			l += i;
		for(List<int>::PrecIter i(l); i();) {
			if(*i % 2 == 0)
				l.remove(i);
			else
				i++;
		}
		int pairs = 0;
		for(List<int>::Iter i(l); i(); i++)
			if(*i % 2 == 0)
				pairs++;
		CHECK_EQUAL(pairs, 0);
	}

	// sub-list iterator
	{
		List<int> l;
		for(int i = 9; i >= 0; i--)
			l += i;
		List<int>::Iter b, e;
		for(List<int>::Iter i(l); i(); i++) {
			if(*i == 3)
				b = i;
			else if(*i == 8)
				e = i;
		}
		CHECK(b());
		CHECK(e());
		List<int>::SubIter s(b, e);
		for(int i = 3; i < 8; i++) {
			CHECK(s());
			CHECK(*s == i);
			s++;
		}
		CHECK(!s);
	}

	// equality and inclusion test
	{
		List<int> l1, l2;
		for(int i = 0; i < 10; i++) {
			l1 += i;
			if(i % 2 == 0 || i == 6)
				l2 += i;
		}
		CHECK(l1 == l1);
		CHECK(l1 != l2);
	}

	// special equivalence
	{
		List<int, Eq > l;
	}

	// sorted list
	{
		SortedList<int> s;

		if(false) {
			SortedList<int> cs;
			s.comparator();
			cs.comparator();
			s.allocator();
			s.removeFirst();
			s.removeLast();
			s.count();
			s.contains(0);
			s.containsAll(s);
			s.isEmpty();
			s.items();
			s.equals(s);
			s.contains(s);
			s.clear();
			s.add(0);
			s.addAll(s);
			s.removeAll(s);
			s.remove(s.begin());
			s.first();
			s.last();
			s.find(0);
			s.at(s.begin());
		}

		s.add(0);
		s.add(10);
		s.add(5);
		SortedList<int>::Iter i(s);
		CHECK_EQUAL(*i, 0);
		i++;
		CHECK_EQUAL(*i, 5);
		i++;
		CHECK_EQUAL(*i, 10);
		i++;
		CHECK(i.ended());
	}

	// list set test
	{
		ListSet<int> l;

		if(false) {
			l.insert(0);
			l.join(l);
			l.meet(l);
			l.diff(l);
			l.add(0);
		}

		CHECK_EQUAL(l.count(), 0);
		CHECK(!l.contains(0));
		l.insert(0);
		CHECK_EQUAL(l.count(), 1);
		CHECK(!l.contains(1));
	}

	// join set operation
	{
		ListSet<int> l, ll;
		l.insert(0);
		l.insert(2);
		ll.insert(1);
		ll.insert(3);
		l.join(ll);
		CHECK_EQUAL(l.count(), 4);
		CHECK(l.contains(0));
		CHECK(l.contains(1));
		CHECK(l.contains(2));
		CHECK(l.contains(3));
	}

	// meet set operation
	{
		ListSet<int> l, ll;
		l.insert(0);
		l.insert(1);
		ll.insert(1);
		ll.insert(2);
		l.meet(ll);
		CHECK_EQUAL(l.count(), 1);
		CHECK(!l.contains(0));
		CHECK(l.contains(1));
		CHECK(!l.contains(2));
	}

	// diff set operation
	{
		ListSet<int> l, ll;
		l.insert(0);
		l.insert(1);
		l.insert(2);
		ll.insert(1);
		ll.insert(3);
		l.diff(ll);
		CHECK_EQUAL(l.count(), 2);
		CHECK(l.contains(0));
		CHECK(!l.contains(1));
		CHECK(l.contains(2));
		CHECK(!l.contains(3));
	}

	// operator test
	{
		ListSet<int> l;
		l += 0;
		l += 1;
		l += 2;
		CHECK(1 <= l);
		l -= 1;
		CHECK(!(1 <= l));
	}

	{
		List<int> l;
		for(int i = 0; i < 10; i++)
			l.add(i);
		bool ok = true;
		int i = 9;
		for(auto x: l) {
			ok = ok || (x == i);
			i--;
		}
		CHECK(ok);
	}

	{
		if(false) {
			ListMap<int, int> m;
			const ListMap<int, int> cm;
			m.equivalence();
			m.begin();
			m.end();
			m.count();
			m.contains(0);
			m.containsAll(m);
			m.isEmpty();
			m.get(0);
			m.get(0, 0);
			m.hasKey(0);
			m.keys();
			m.pairs();
			m.put(1, 1);
			m.remove(m.begin());
			m.remove(1);
		}
	}

	// test map
	{
		ListMap<int, string> m;
		CHECK_EQUAL(m.count(), 0);
		m.put(0, "zero");
		CHECK_EQUAL(m.count(), 1);
		m.put(1, "one");
		CHECK_EQUAL(m.count(), 2);
		CHECK(m.contains("zero"));
		CHECK_EQUAL(m.get(0, ""), string("zero"));

		int c = 0;
		for(auto x: m)
			c++;
		CHECK_EQUAL(c, 2);

		c = 0;
		for(auto x: m.keys())
			c += x;
		CHECK_EQUAL(c, 1);
	}

#if 0
	// compatibility test
	/* TODO
	{
		ListMap<int, int> a;
		a.put(0, 0);
		CHECK(a.hasKey(0));
		for(typename ListMap<int, int>::Iter i(a); i; i++)
			;
	}*/
#endif

TEST_END
