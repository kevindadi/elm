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

#include <elm/data/util.h>
#include <elm/data/Vector.h>
#include "../include/elm/test.h"

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

	// simple predicate functions
	{
		CHECK_EQUAL(count(v, _pair), 5);
		CHECK(!forall(v, _pair));
		CHECK(forall(v, pos));
		CHECK(exists(v, _pair));
		CHECK(!exists(v, neg));
		CHECK(find(*v, _pair));
		CHECK(!find(*v, neg));
	}

	// predicate with argument
	{
		CHECK_EQUAL(count(v, ::mult, 2), 5);
		CHECK(!forall(v, lt, 5));
		CHECK(forall(v, lt, 10));
		CHECK(exists(v, gt, 5));
		CHECK(!exists(v, lt, 0));
		CHECK(find(*v, gt, 5));
		CHECK(!find(*v, gt, 10));
	}

	// transformation functions without argument
	{
		Vector<int> w;
		map(v, inc, w);
		bool ok = true;
		for(int i = 0; i < 10; i++)
			ok = ok && v[i] + 1 == w[i];
		CHECK(ok);
		CHECK_EQUAL(fold(v, single<Add<int> >()), 45);
		CHECK_EQUAL(sum(v), 45);
		CHECK_EQUAL(product(v), 0);
	}


TEST_END
