/*
 *	compare module test
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
#include <elm/compare.h>
#include "../include/elm/test.h"
using namespace elm;


TEST_BEGIN(compare)

// integer case
{
	CHECK_EQUAL(min(0, 10), 0);
	CHECK_EQUAL(max(0, 10), 10);
}

// cstring case
{
	string god("god"), devil("devil");
	CHECK_EQUAL(min(god, devil), devil);
	CHECK_EQUAL(max(god, devil), god);
	elm::ReverseComparator<string, Comparator<string> > rcmp;
	CHECK_EQUAL(min(god, devil, rcmp), god);
	CHECK_EQUAL(max(god, devil, rcmp), devil);
}

// collection case with int
{
	Vector<int> v;
	v.add(0);
	v.add(10);
	v.add(-5);
	v.add(3);
	v.add(100);
	CHECK_EQUAL(min(v), -5);
	CHECK_EQUAL(max(v), 100);
}

TEST_END


