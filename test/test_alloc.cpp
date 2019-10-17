/*
 *	$Id$
 *	test for alloc module
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2009, IRIT UPS.
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

#include <elm/alloc/BlockAllocator.h>
#include <elm/alloc/BlockAllocatorWithGC.h>
#include <elm/alloc/StackAllocator.h>
#include <elm/sys/System.h>
#include <elm/io.h>
#include <elm/test.h>

using namespace elm;

class GC: public BlockAllocatorWithGC<int> {
public:

	GC(int size = 256): BlockAllocatorWithGC<int>(size), collected(false), bad_destroy(false) {
	}

	void collect(void) override {
		bad_destroy = false;
		for(auto p: alives) {
			mark(p);
			//cerr << "alive : " << p << io::endl;
		}
		collected = true;
	}

	void destroy(int *p) {
		bad_destroy = bad_destroy || alives.contains(p);
	}

	Vector<int *> alives;
	bool collected;
	bool bad_destroy;
};

TEST_BEGIN(alloc)
	{
		Vector<void *> v;
		StackAllocator stack;
		for(int i = 0; i < 1000; i++) {
			elm::t::size size = sys::System::random(4096);
			void *p = stack.allocate(size);
			v.add(p);
			//cout << "allocate(" << size << ") = " << p << io::endl;
		}
	}

	{
		BlockAllocator<int> b;
		int *i = b.allocate();
		b.free(i);
	}

	// Asynchronous block allocator with GC
	{
		GC gc(4 * sizeof(void *));
		CHECK(!gc.collected);
		gc.alives.add(gc.allocate());
		CHECK(!gc.collected);
		gc.alives.add(gc.allocate());
		CHECK(!gc.collected);
		gc.alives.add(gc.allocate());
		CHECK(!gc.collected);
		int *p = gc.allocate();
		CHECK(!gc.collected);
		int *q = gc.allocate();
		CHECK(gc.collected);
		CHECK(!gc.bad_destroy);
		CHECK(p == q);
	}

	// Synchronous block allocator with GC
	{
		GC gc(4 * sizeof(void *));
		gc.setSync();
		CHECK(!gc.collected);
		gc.alives.add(gc.allocate());
		CHECK(!gc.collected);
		gc.alives.add(gc.allocate());
		CHECK(!gc.collected);
		gc.alives.add(gc.allocate());
		CHECK(!gc.collected);
		gc.allocate();
		CHECK(!gc.collected);
		gc.allocate();
		CHECK(!gc.collected);
		//cout << "total = " << gc.totalCount() << io::endl;
		//cout << "free = " << gc.freeCount() << io::endl;
		gc.collectGarbage();
		CHECK(gc.collected);
		CHECK(!gc.bad_destroy);
		//cout << "total = " << gc.totalCount() << io::endl;
		//cout << "free = " << gc.freeCount() << io::endl;
		CHECK_EQUAL(gc.usedCount(), 3);
	}

	// robustness of block allocator with GC
	{
		GC gc(4096);
		const int cnt = 10000, alive = 40, dead = 40;
		bool robust = true;
		int gc_cnt = 0, alive_sum = 0;
		for(int i = 0; i < cnt; i++) {
			int a = sys::System::random(100);
			if(a < alive)
				gc.alives.add(gc.allocate());
			else if(gc.alives.count() == 0 || a < alive + dead)
				gc.allocate();
			else
				gc.alives.removeAt(sys::System::random(gc.alives.count() - 1));
			if(gc.bad_destroy) {
				robust = false;
				break;
			}
			if(gc.collected) {
				gc_cnt++;
				alive_sum += gc.alives.count();
			}
			gc.collected = false;
		}
		cout << "GC collections = " << gc_cnt << io::endl;
		cout << "Alive = " << gc.alives.count() << io::endl;
		cout << "Average alive = " << (double(alive_sum) / gc_cnt) << io::endl;
		CHECK(robust);
	}

TEST_END
