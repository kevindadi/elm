/*
 *	With and WithPtr classes test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2023, IRIT UPS.
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
#include <elm/util/With.h>
#include <elm/test.h>

using namespace elm;

class EnterAndLeave {
public:
public:
	void enter() {
		entered = true;
	}

	void leave() {
		left = true;
	}

	bool entered = false, left = false;
};

static bool fried = true;
class Alloc {
public:
	Alloc() { fried = false; }
	~Alloc() { fried = true; }
};

TEST_BEGIN(with)

	// With test
	EnterAndLeave x;

	CHECK(!x.entered);
	CHECK(!x.left);
	{
		auto p = with(x);
		CHECK(x.entered);
		CHECK(!x.left);
	}
	CHECK(x.entered);
	CHECK(x.left);

	// WithPtr test
	CHECK(fried);
	{
		auto p = with_ptr(new Alloc());
		CHECK(!fried);
	}
	CHECK(fried);

TEST_END
