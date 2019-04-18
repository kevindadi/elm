/*
 *	dyndata module test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2018, IRIT UPS.
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
#include <elm/dyndata/Collection.h>
#include <elm/test.h>
using namespace elm;


TEST_BEGIN(dyndata)

	dyndata::MutableCollection<int, Vector<int> > coll;
	CHECK(coll.isEmpty());

	for(int i = 0; i < 10; i++)
		coll.add(i);
	CHECK_EQUAL(coll.count(), 10);
	CHECK(!coll.isEmpty());

	bool error = false;
	int cnt = 0;
	for(auto i = *coll; i(); i++) {
		if(*i < 0 || *i >= 10) {
			error = true;
			break;
		}
		cnt++;
	}
	CHECK(!error);
	CHECK(cnt == 10);

	error = false;
	for(int i = 0; i < 10; i++)
		if(!coll.contains(i)) {
			error = true;
			break;
		}
	CHECK(!error);

	coll.clear();
	CHECK(coll.isEmpty());
	CHECK_EQUAL(coll.count(), 0);

	for(int i = 0; i < 10; i++)
		coll.add(i);
	for(int i = 0; i < 10; i += 2)
		coll.remove(i);
	CHECK_EQUAL(coll.count(), 5);

	while(!coll.isEmpty())
		coll.remove(*coll);
	CHECK_EQUAL(coll.count(), 0);

	for(int i = 0; i < 10; i += 2)
		coll.add(i);
	dyndata::MutableCollection<int, Vector<int> > coll2;
	for(int i = 1; i < 10; i += 2)
		coll2.add(i);
	coll.addAll(coll2);
	CHECK_EQUAL(coll.count(), 10);

	coll.removeAll(coll2);
	CHECK_EQUAL(coll.count(), 5);

TEST_END


