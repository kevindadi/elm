/*
 *	Slice class test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2020, IRIT UPS.
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
#include <elm/data/Slice.h>
#include <elm/data/util.h>
#include <elm/data/Vector.h>
#include <elm/test.h>
#include "check-concept.h"

using namespace elm;

TEST_BEGIN(slice)
	Vector<int> v;
	for(int i = 0; i < 10; i++)
		v.add(i);
	Slice<Vector<int>> s(v, 3, 4);

	{
		checkCollection(s, s, 666);
		checkArray(s, 666);
	}

	{
		Vector<int> &r = s.array();
		CHECK_EQUAL(&r, &v);
		CHECK_EQUAL(3, s.firstIndex());
		CHECK_EQUAL(6, s.lastIndex());
	}

	{
		int sum = 0;
		for(auto x: s)
			sum += x;
		CHECK_EQUAL(sum, 18);
	}

	{
		Vector<int> v;
		for(int i = 0; i < 10; i++)
			v.add(i);
		auto s = slice(v, 5, 5);
		for(auto& x: s)
			x = 0;
		CHECK_EQUAL(elm::sum(v), 10);
	}

TEST_END
