/*
 *	SubCollection test
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

#include <elm/data/Vector.h>
#include "../include/elm/data/Range.h"
#include "../include/elm/test.h"

using namespace elm;

TEST_BEGIN(sub_coll)

// full vector
{
	Vector<int> v;
	for(int i = 0; i < 10; i++)
		v.add(i);

	Vector<int>::Iter b(v);
	for(int i = 0; i < 3; i++)
		b++;
	CHECK(bool(b));

	Vector<int>::Iter e(v);
	for(int i = 0; i < 6; i++)
		e++;
	CHECK(bool(e));

	Range<Vector<int>::Iter> s(b, e);
	Range<Vector<int>::Iter>::Iter i(s);
	CHECK(!i.ended());
	CHECK_EQUAL(*i, 3);
	i++;
	CHECK(!i.ended());
	CHECK_EQUAL(*i, 4);
	i++;
	CHECK(!i.ended());
	CHECK_EQUAL(*i, 5);
	i++;
	CHECK(!bool(i));
	CHECK_EQUAL(s.count(), 3);
	CHECK(!s.isEmpty());
	CHECK(s.contains(4));
	CHECK(!s.contains(0));
	CHECK(!s.contains(8));
	CHECK(!s.contains(6));
	CHECK(s.contains(3));
}

TEST_END



