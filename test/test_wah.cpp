/*
 *	$Id$
 *	test for WAHBitVector
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
#include <elm/util/WAHBitVector.h>
#include <elm/system/System.h>
#include <elm/genstruct/Vector.h>
#include <elm/util/test.h>

#define SIZE		256
#define TESTS		10000

using namespace elm;
using namespace elm::system;

class Action {
public:
	typedef enum {
		NONE,
		SET,
		CLR
	} t;

	t k;
	int i;

	Action(t kind = NONE, int index = 0): k(kind), i(index) { }
	Action& operator=(const Action& a) { k = a.k; i = a.i; return *this; }

	void perform(WAHBitVector& v) {
		switch(k) {
		case NONE:
			break;
		case SET:
			v.set(i, true);
			break;
		case CLR:
			v.set(i, false);
			break;
		}
	}

	void perform(BitVector& v) {
		switch(k) {
		case NONE:
			break;
		case SET:
			v.set(i, true);
			break;
		case CLR:
			v.set(i, false);
			break;
		}
	}
};
io::Output& operator<<(io::Output& out, Action& act) {
	switch(act.k) {
	case Action::NONE:
		out << "none";
		break;
	case Action::SET:
		out << "set " << act.i;
		break;
	case Action::CLR:
		out << "set " << act.i;
		break;
	}
	return out;
}

void test_wah(void) {
	CHECK_BEGIN("wah")

	// append 1 bit
	{ WAHBitVector v; v.set(5, true); CHECK(v.bit(5)); }

	// fill single + append 1 bit
	{ WAHBitVector v; v.set(32, true); CHECK(v.bit(32)); }

	// fill multiple + append 1 bit
	{ WAHBitVector v; v.set(65, true); CHECK(v.bit(65)); }

	// append 1 bit + check clear others
	{
		WAHBitVector v;
		v.set(5, true);
		CHECK(!v.bit(4));
		CHECK(!v.bit(6));
		CHECK(!v.bit(200));
	}

	// fill single + append 1 bit + check clear others
	{
		WAHBitVector v;
		v.set(35, true);
		CHECK(!v.bit(32));
		CHECK(!v.bit(40));
		CHECK(!v.bit(5));
	}

	// set several bits
	{
		WAHBitVector v;
		v.set(5, true);
		v.set(32, true);
		CHECK(v.bit(5));
		CHECK(v.bit(32));
	}

	// set several bits with fill
	{
		WAHBitVector v;
		v.set(5, true);
		v.set(65, true);
		CHECK(v.bit(5));
		CHECK(v.bit(65));
	}

	// set with fill and set inside fill
	{
		WAHBitVector v;
		v.set(32, true);
		v.set(5, true);
		CHECK(v.bit(5));
		CHECK(v.bit(32));
	}

	// split fill in middle
	{
		WAHBitVector v;
		v.set(94, true);
		v.set(32, true);
		CHECK(v.bit(94));
		CHECK(v.bit(32));
	}

	// split fill at start
	{
		WAHBitVector v;
		v.set(94, true);
		v.set(15, true);
		CHECK(v.bit(94));
		CHECK(v.bit(15));
	}

	// split fill at end
	{
		WAHBitVector v;
		v.set(94, true);
		v.set(63, true);
		CHECK(v.bit(94));
		CHECK(v.bit(63));
	}

	// test one fill single
	{
		WAHBitVector v;
		for(int i = 0; i < 31; i++)
			v.set(i, true);
		bool one = true;
		for(int i = 30; i >= 0; i--)
			if(!v.bit(i)) {
				cerr << "failed for i=" << i << io::endl;
				one = false;
			}
		CHECK(one);
	}

	// test one fill and packing after
	{
		WAHBitVector v;
		for(int i = 31; i < 62; i++)
			v.set(i, true);
		for(int i = 0; i < 31; i++)
			v.set(i, true);
		bool one = true;
		for(int i = 0; i < 62; i++)
			if(!v.bit(i)) {
				cerr << "failed for i=" << i << io::endl;
				one = false;
			}
		CHECK(one);
	}

	// test one fill and packing before
	{
		WAHBitVector v;
		for(int i = 0; i < 31; i++)
			v.set(i, true);
		for(int i = 31; i < 62; i++)
			v.set(i, true);
		bool one = true;
		for(int i = 0; i < 62; i++)
			if(!v.bit(i)) {
				cerr << "failed for i=" << i << io::endl;
				one = false;
			}
		CHECK(one);
	}

	// test one fill and packing on both ends
	{
		WAHBitVector v;
		for(int i = 0; i < 31; i++)
			v.set(i, true);
		for(int i = 62; i < 93; i++)
			v.set(i, true);
		for(int i = 31; i < 62; i++)
			v.set(i, true);
		bool one = true;
		for(int i = 0; i < 93; i++)
			if(!v.bit(i)) {
				cerr << "failed for i=" << i << io::endl;
				one = false;
			}
		CHECK(one);
	}

	// test zero fill and packing before
	{
		WAHBitVector v;
		v.set(62, true);
		v.set(5, true);
		v.set(5, false);
		bool zero = true;
		for(int i = 0; i < 62; i++)
			if(v.bit(i)) {
				zero = false;
				cerr << "failed for i=" << i << io::endl;
				break;
			}
		CHECK(zero);
		CHECK(v.bit(62));
	}

	// test zero fill and packing after
	{
		WAHBitVector v;
		v.set(62, true);
		v.set(32, true);
		v.set(32, false);
		bool zero = true;
		for(int i = 0; i < 62; i++)
			if(v.bit(i)) {
				zero = false;
				cerr << "failed for i=" << i << io::endl;
				break;
			}
		CHECK(zero);
		CHECK(v.bit(62));
	}

	// test zero fill and packing in middle
	{
		WAHBitVector v;
		v.set(93, true);
		v.set(32, true);
		v.set(32, false);
		bool zero = true;
		for(int i = 0; i < 93; i++)
			if(v.bit(i)) {
				zero = false;
				cerr << "failed for i=" << i << io::endl;
				break;
			}
		CHECK(zero);
		CHECK(v.bit(93));
	}

	// zero packing at end
	{
		WAHBitVector v;
		v.set(93, true);
		v.set(93, false);
		bool zero = true;
		for(int i = 0; i < 93; i++)
			if(v.bit(i)) {
				zero = false;
				cerr << "failed for i=" << i << io::endl;
				break;
			}
		CHECK(zero);
	}

	// single vector
	/*{
		genstruct::Vector<Action> acts;
		BitVector v1(SIZE);
		WAHBitVector v2;
		for(int i = 0; i < TESTS; i++) {
			Action act(
				System::random(20) < 10 ? Action::SET : Action::CLR,
				System::random(SIZE));
			acts.add(act);

			act.perform(v1);

			act.perform(v2);
			cerr << act << io::endl;
			v2.__print(cerr);

			for(int i = 0; i < SIZE; i++)
				if(v1.bit(i) != v2.bit(i)) {
					for(int i = 0; i < acts.count(); i++)
						cerr << acts[i] << io::endl;
					cerr << "error: " << i << io::endl;
					return;
				}
			cerr << io::endl;
		}
	}*/

	CHECK_END

}
