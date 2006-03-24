/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_vector_queue.cpp -- VectorQueue class test.
 */

#include <elm/genstruct/VectorQueue.h>
#include <elm/util/test.h>

using namespace elm::genstruct;

void test_vector_queue(void) {
	CHECK_BEGIN("vector_queue");
	
	{
		
		// Simple use
		VectorQueue<int> queue(2);
		CHECK(queue.isEmpty());
		queue.put(0);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 0);
		queue.put(1);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 0);
		queue.put(2);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 0);
		CHECK(queue.get() == 0);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 1);
		CHECK(queue.get() == 1);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 2);
		CHECK(queue.get() == 2);
		CHECK(queue.isEmpty());
		
		// Test of wrap
		CHECK(queue.isEmpty());
		queue.put(0);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 0);
		queue.put(1);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 0);
		queue.put(2);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 0);
		CHECK(queue.get() == 0);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 1);
		CHECK(queue.get() == 1);
		CHECK(!queue.isEmpty());
		CHECK(queue.head() == 2);
		CHECK(queue.get() == 2);
		CHECK(queue.isEmpty());
	}
	
	// Test with re-allocation
	{
			VectorQueue<int> queue(2);
			for(int i = 0; i < 20; i++) {
				queue.put(i);
				CHECK(queue.head() == 0);
			}
			CHECK(!queue.isEmpty());
			for(int i = 0; i < 20; i++) {
				CHECK(queue.head() == i);
				CHECK(queue.get() == i);
			}
			CHECK(queue.isEmpty());
	}
	
	CHECK_END;
}

