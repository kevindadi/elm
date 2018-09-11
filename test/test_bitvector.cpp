/*
 *	BitVector class test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2010, IRIT UPS.
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

#include <elm/util/BitVector.h>
#include "../include/elm/test.h"

using namespace elm;

BitVector make(int size, t::uint32 v) {
	BitVector vec(size);
	for(int i = 0; i < size; i++, v >>= 1)
		if(v & 0x00000001)
			vec.set(i);
	return vec;
}

bool equals(const BitVector& vec, t::uint32 v) {
	for(int i = 0; i < vec.size(); i++, v >>= 1)
		if(vec.bit(i) != (v & 0x00000001))
			return false;
	return true;
}

t::uint32 rotate_left(t::uint32 v, int n) {
	return (v << n) | (v >> (32 - n));
}

t::uint32 rotate_right(t::uint32 v, int n) {
	return (v >> n) | (v << (32 - n));
}

TEST_BEGIN(bitvector)
	
	// Initial test
	BitVector v1(13);
	CHECK(v1.isEmpty());
	CHECK(v1.size() == 13);
	
	// Bit Access
	v1.set(2);
	CHECK(v1.bit(2));
	CHECK(!v1.isEmpty());
	v1.set(11);
	CHECK(v1.bit(11));
	v1.clear(2);
	CHECK(!v1.bit(2));
	v1.clear(11);
	CHECK(!v1.bit(11));
	CHECK(v1.isEmpty());
	v1.set(2);
	v1.set(4);
	CHECK(v1.bit(2) && v1.bit(4));
	v1.clear(2);
	CHECK(!v1.bit(2) && v1.bit(4));
	v1.clear();
	CHECK(v1.isEmpty());
	
	// Copy and equality
	BitVector v2(13);
	v2.set(1);
	v2.set(5);
	v2.set(6);
	v2.set(12);
	BitVector v3(13);
	v3.copy(v2);
	cerr << "DEBUG: v3 = " << v3 << io::endl;
	cerr << "DEBUG: v2 = " << v2 << io::endl;
	CHECK(v2.equals(v3));
	CHECK(!v1.equals(v2));

	// Check inclusion
	CHECK(v2.includes(v3));
	CHECK(!v2.includesStrictly(v3));
	v3.clear(5);
	CHECK(v2.includes(v3));
	CHECK(v2.includesStrictly(v3));
	CHECK(!v3.includes(v2));
	CHECK(!v3.includesStrictly(v2));

	BitVector v4 = make(13, 0x0303);
	BitVector v5 = make(13, 0x0505);

	// Check applies
	BitVector v9 = v4;
	v9.applyAnd(v5);
	CHECK(equals(v9, 0x0101));
	BitVector v10 = v4;
	v10.applyOr(v5);
	CHECK(equals(v10, 0x0707));
	BitVector v11 = v4;
	v11.applyReset(v5);
	CHECK(equals(v11, 0x0202));
	BitVector v13 = v4;
	v13.applyNot();
	CHECK(equals(v13, 0xfcfc));
	
	// Check makes
	BitVector v6 = v4.makeAnd(v5);
	CHECK(equals(v6, 0x0101));
	BitVector v7 = v4.makeOr(v5);
	CHECK(equals(v7, 0x0707));
	BitVector v8 = v4.makeReset(v5);
	CHECK(equals(v8, 0x0202));
	BitVector v12 = v4.makeNot();
	CHECK(equals(v12, 0xfcfc));

	// resize tests
	{
		BitVector bv;
		bv.resize(4);
		CHECK(bv.size() == 4);
	}
	{
		BitVector bv(64);
		bv.set(3);
		bv.set(4);
		bv.set(31);
		bv.resize(65);
		CHECK(bv.bit(3));
		CHECK(bv.bit(4));
		CHECK(bv.bit(31));
	}

#ifdef EXPERIMENTAL
	// left shift
	{
		t::uint32 pat = 0xf0ccba56;
		BitVector v1 = make(32, pat);
		v1.shiftLeft(1);
		CHECK_EQUAL(v1, make(32, pat << 1));
		v1 = make(32, pat);
		v1.shiftLeft(3);
		CHECK_EQUAL(v1, make(32, pat << 3));
		v1 = make(32, pat);
		v1.shiftLeft(8);
		CHECK_EQUAL(v1, make(32, pat << 8));
		v1 = make(32, pat);
		v1.shiftLeft(10);
		CHECK_EQUAL(v1, make(32, pat << 10));
		v1 = make(32, pat);
		v1.shiftLeft(17);
		CHECK_EQUAL(v1, make(32, pat << 17));
	}

	// right shift
	{
		t::uint32 pat = 0xf0ccba56;
		BitVector v1 = make(32, pat);
		v1.shiftRight(1);
		CHECK_EQUAL(v1, make(32, pat >> 1));
		v1 = make(32, pat);
		v1.shiftRight(3);
		CHECK_EQUAL(v1, make(32, pat >> 3));
		v1 = make(32, pat);
		v1.shiftRight(8);
		CHECK_EQUAL(v1, make(32, pat >> 8));
		v1 = make(32, pat);
		v1.shiftRight(10);
		CHECK_EQUAL(v1, make(32, pat >> 10));
		v1 = make(32, pat);
		v1.shiftRight(17);
		CHECK_EQUAL(v1, make(32, pat >> 17));
	}

	// left rotate
	{
		t::uint32 pat = 0xf0ccba56;
		BitVector v1 = make(32, pat);
		v1.rotateLeft(1);
		CHECK_EQUAL(v1, make(32, rotate_left(pat, 1)));
		v1 = make(32, pat);
		v1.rotateLeft(3);
		CHECK_EQUAL(v1, make(32, rotate_left(pat, 3)));
		v1 = make(32, pat);
		v1.rotateLeft(8);
		CHECK_EQUAL(v1, make(32, rotate_left(pat, 8)));
		v1 = make(32, pat);
		v1.rotateLeft(10);
		CHECK_EQUAL(v1, make(32, rotate_left(pat, 10)));
		v1 = make(32, pat);
		v1.rotateLeft(17);
		CHECK_EQUAL(v1, make(32, rotate_left(pat, 17)));
	}

	// right rotate
	{
		t::uint32 pat = 0xf0ccba56;
		BitVector v1 = make(32, pat);
		v1.rotateRight(1);
		CHECK_EQUAL(v1, make(32, rotate_right(pat, 1)));
		v1 = make(32, pat);
		v1.rotateRight(3);
		CHECK_EQUAL(v1, make(32, rotate_right(pat, 3)));
		v1 = make(32, pat);
		v1.rotateRight(8);
		CHECK_EQUAL(v1, make(32, rotate_right(pat, 8)));
		v1 = make(32, pat);
		v1.rotateRight(10);
		CHECK_EQUAL(v1, make(32, rotate_right(pat, 10)));
		v1 = make(32, pat);
		v1.rotateRight(17);
		CHECK_EQUAL(v1, make(32, rotate_right(pat, 17)));
	}
#endif

	TEST_END

