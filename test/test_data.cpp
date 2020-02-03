/*
 *	data module test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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

#include <elm/data/Range.h>
#include <elm/data/util.h>
#include <elm/data/Vector.h>
#include <elm/test.h>

using namespace elm;

struct Pair {
	bool operator()(int a) const { return a % 2 == 0; }
} _pair;

struct Positive {
	bool operator()(int a) const { return a >= 0; }
} pos;

struct Negative {
	bool operator()(int a) const { return a < 0; }
} neg;

struct MultipleOf {
	bool operator()(int a, int b) const { return a % b == 0; }
} mult;

struct GreaterThan {
	bool operator()(int a, int b) const { return a > b; }
} gt;

struct LesserThan {
	bool operator()(int a, int b) const { return a < b; }
} lt;

struct Inc {
	int operator()(int x) const { return x + 1; }
} inc;


TEST_BEGIN(data)
	Vector<int> v;
	for(int i = 0; i < 10; i++)
		v.add(i);

	// count test
	{
		CHECK_EQUAL(count(v, [](int i) { return i % 2 == 0; }), 5);
		CHECK_EQUAL(count(range(v.begin(), v.end()), [](int i) { return i % 2 == 0; }), 5);
	}

	// simple predicate functions
	{
		CHECK_EQUAL(count(v, _pair), 5);

		CHECK(!forall(v, _pair));
		CHECK(forall(v, pos));
		CHECK(exists(v, _pair));
		CHECK(!exists(v, neg));
		CHECK(find(v, _pair)());
		CHECK(!find(v, neg)());

		CHECK(!forall(range(v.begin(), v.end()), _pair));
		CHECK(forall(range(v.begin(), v.end()), pos));
		CHECK(exists(range(v.begin(), v.end()), _pair));
		CHECK(!exists(range(v.begin(), v.end()), neg));
		CHECK(find(range(v.begin(), v.end()), _pair)());
		CHECK(!find(range(v.begin(), v.end()), neg)());

	}

	// map
	{
		Vector<int> w;
		map(v, inc, w);
		bool ok = true;
		for(int i = 0; i < 10; i++)
			ok = ok && v[i] + 1 == w[i];
		CHECK(ok);

		w.clear();
		map(range(v.begin(), v.end()), inc, w);
		ok = true;
		for(int i = 0; i < 10; i++)
			ok = ok && v[i] + 1 == w[i];
		CHECK(ok);
	}

	// iter test
	{
		int s = 0;
		iter(v, [&s](int i) { s = s + i; });
		CHECK_EQUAL(s, 45);

		s = 0;
		auto i = v.begin();
		i++;
		iter(range(i, v.end()), [&s](int i) { s = s + i; });
		CHECK_EQUAL(s, 45);
	}

	// transformation functions without argument
	{
		CHECK_EQUAL(fold(v, [](int i, int s) { return i + s; }, 0), 45);
		CHECK_EQUAL(fold(range(v.begin(), v.end()), [](int i, int s) { return i + s; }, 0), 45);
		CHECK_EQUAL(sum(v), 45);
		CHECK_EQUAL(sum(nrange(0, 9)), 45);
		CHECK_EQUAL(product(nrange(1, 4)), 24);
	}

	// range test
	{
		CHECK_EQUAL(sum(range(v.begin(), v.end())), 45);
		CHECK_EQUAL(sum(select(v, [](int i) { return i % 2 == 0; })), 20);
		CHECK_EQUAL(sum(select(range(v.begin(), v.end()), [](int i) { return i % 2 == 0; })), 20);
	}

	// equals, mismatch test
	{
		Vector<int> v1, v2, v3;
		for(int i = 0; i < 10; i++)
			v1.add(i);
		for(int i = 0; i < 10; i++)
			v2.add(9 - i);
		for(int i = 0; i < 5; i++)
			v3.add(i);

		CHECK(equals(v1, v1));
		CHECK(!equals(v1, v2));
		CHECK(!equals(v1, v3));

		auto p = mismatch(v1, v1);
		CHECK(p.fst == v1.end() && p.snd == v1.end());
		p = mismatch(v1, v2);
		CHECK(p.fst == v1.begin() && p.snd == v2.begin());
		p = mismatch(v1, v3);
		CHECK(*p.fst == 5 && p.snd == v3.end());

		auto e = [](int x, int y) { return x == y; };
		p = mismatch(v1, v1, e);
		CHECK(p.fst == v1.end() && p.snd == v1.end());
		p = mismatch(v1, v2, e);
		CHECK(p.fst == v1.begin() && p.snd == v2.begin());
		p = mismatch(v1, v3, e);
		CHECK(*p.fst == 5 && p.snd == v3.end());
	}

TEST_END
