/*
 *	templates to check concepts
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2019, IRIT UPS.
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
#ifndef ELM_TEST_CHECK_CONCEPT_H_
#define ELM_TEST_CHECK_CONCEPT_H_

#include <elm/util/Option.h>

namespace elm {

template <class C, class T>
void checkCollection(C& c, const C& cc, const T& x) {
	if(false) {
		c.count();
		c.contains(1);
		c.containsAll(cc);
		c.isEmpty();
		static_cast<bool>(c);
		c.begin();
		c.end();
		c.equals(cc);
		c == cc;
		c != cc;
	}
}

template <class C, class T>
void checkMutableCollection(C& c, const T& x) {
	if(false) {
		c.clear();
		c.add(x);
		c.addAll(c);
		c.remove(x);
		c.removeAll(c);
		c.remove(c.begin());
		c += x;
		c -= x;
		c.copy(c);
		c = c;
	}
}

template <class L, class T>
void checkList(const L& l, const T& x) {
	if(false) {
		l.first();
		l.last();
		l.find(x);
		l.find(x, l.begin());
		l.nth(1);
		l[1];
	}
}

template <class L, class T>
void checkMutableList(L& l, const T& x) {
	if(false) {
		l.first() = x;
		l.last() = x;
		l.addFirst(x);
		l.addLast(x);
		l.removeFirst();
		l.removeLast();
		l.addAfter(l.begin(), x);
		l.addBefore(l.begin(), x);
		l.removeBefore(l.begin());
		l.removeAfter(l.begin());
		l.set(l.begin(), x);
		l[1] = x;
	}
}

template <class S, class T>
void checkStack(S& s, const S& cs, const T& x) {
	if(false) {
		s.isEmpty();
		s.top() = x;
		cs.top();
		s.pop();
		s.push(x);
		s.reset();
	}
}

template <class Q, class T>
void checkQueue(Q& q, const T& x) {
	if(false) {
		q.isEmpty();
		q.head();
		T y = q.get();
		q.put(y);
		q.reset();
	}
}

template <class M, class K, class T>
void checkMap(const M& m, const K& k, const T& v) {
	if(false) {
		Option<T> o = m.get(k);
		cout << o;
		const T& r = m.get(k, v);
		cout << r;
		bool b = m.hasKey(k);
		cout << b;
		for(const K& k: m.keys())
			m.get(k);
		for(const Pair<K, T>& p: m.pairs())
			m.get(p.fst);
		const T& rr = m[k];
		cout << rr;
	}
}

template <class M, class K, class T>
void checkMutableMap(M& m, const K& k, const T& v) {
	if(false) {
		m.clear();
		m.put(k, v);
		m.removeByKey(k);
		m.remove(k.begin());
		T& r = m[k];
	}
}

template <class S, class T>
void checkSet(S& s, const T& x) {
	if(false) {
		s.insert(x);
		bool b = s.subsetOf(s);
		cout << b;
		b = s >= s;
		b = s > s;
		b = s < s;
		b = s <= s;
		s.join(s);
		s.meet(s);
		s.diff(s);
		s += s;
		s |= s;
		s -= s;
		s &= s;
		s *= s;
		S ss = s + s;
		ss = s | s;
		ss = s * s;
		ss = s & s;
		ss = s - s;
	}
}

template <class A, class T>
void checkArray(const A& a, const T& x) {
	if(false) {
		static int l = 0, i = 1;
		static const T *p = nullptr, *q = nullptr;
		l = a.length();
		p = &a.get(l);
		p = &a[i];
		p = q;
		i = a.indexOf(x);
		i = a.indexOf(x, 2);
		i = a.lastIndexOf(x);
		i = a.lastIndexOf(x, 2);
		q = p;
	}
}

}	// elm

#endif /* ELM_TEST_CHECK_CONCEPT_H_ */
