/*
 *	Bag class test
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
#include <elm/data/Bag.h>
#include <elm/test.h>
#include "check-concept.h"

using namespace elm;

TEST_BEGIN(bag)
	int t[] = { 1, 2, 3 };

	{
		auto b = Bag<int>::make(3, t);
		checkCollection(*b, *b, 666);
		checkArray(*b, 666);
		delete b;
	}

	{
		Bag<int> *b = Bag<int>::make(3, t);
		int s = 0;
		for(auto x: *b)
			s += x;
		CHECK_EQUAL(s, 6);
		delete b;
	}

TEST_END

