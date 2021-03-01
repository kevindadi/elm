/*
 * test_array.h
 *
 *  Created on: 5 janv. 2011
 *      Author: casse
 */

#include <elm/array.h>
#include <elm/sys/StopWatch.h>
#include "../include/elm/test.h"

using namespace elm;
using namespace elm::sys;

static bool flag = false;

class Deep {
public:
	inline Deep& operator=(const Deep& d) { flag = true; return *this; }
};

class Integer {
public:
	inline Integer(void) { i = 0; }
	Integer& operator=(int ii) { i = ii; return *this; }
	Integer& operator=(const Integer& d) { i = d.i; return *this; }
	inline int get() const { return i; }
	inline bool operator==(const Integer& ii) const { return i == ii.i; }
	inline bool operator>(const Integer& ii) const { return i > ii.i; }
private:
	int i;
};

TEST_BEGIN(util_array)

	{
		int t1[20], t2[20];
		array::copy(t1, t2, 20);
	}

	{
		Deep t1[20], t2[20];
		array::copy(t1, t2, 20);
		CHECK(flag);
	}

	{
		static const int size = 100000, count = 1000;
		int t1[size], t2[size];
		Integer u1[size], u2[size];
		StopWatch sw;

		// shallow copy
		sw.start();
		for(int i = 0; i < count; i++)
			array::copy(t1, t2, size);
		sw.stop();
		auto t_shallow = sw.stopTime() - sw.startTime();

		// deep copy
		sw.start();
		for(int i = 0; i < count; i++)
			array::copy(u1, u2, size);
		sw.stop();
		auto t_deep = sw.stopTime() - sw.startTime();

		// compare
		cerr << "shallow time = " << t_shallow << io::endl;
		cerr << "deep time = " << t_deep << io::endl;
		cerr << "factor = " << (t_deep / t_shallow) << io::endl;
		CHECK(t_shallow < t_deep);
	}

	{
		int t1[100];
		array::clear(t1, 100);
		int s = 0;
		for(auto i: t1)
			s |= i;
		CHECK_EQUAL(s, 0);
		Integer t2[100];
		array::clear(t2, 100);
		s = 0;
		for(auto i: t2)
			s |= i.get();
		CHECK_EQUAL(s, 0);
	}

	{
		int t1i[100], t2i[100];
		for(int i = 0; i < 100; i++)
			t1i[i] = t2i[i] = 0;
		CHECK(array::equals(t1i, t2i, 100));
		t1i[0] = 1;
		t2i[1] = 1;
		CHECK(!array::equals(t1i, t2i, 100));
	}

	{
		Integer t1[100], t2[100];
		CHECK(array::equals(t1, t2, 100));
		t1[0] = 1;
		t2[1] = 1;
		CHECK(!array::equals(t1, t2, 100));
	}

	{
		char t[sizeof(Integer) * 100];
		array::construct(t, 100);
		array::destruct(t, 100);
		Integer *p = (Integer *)t;
		array::construct(p, 100);
		int s = 0;
		for(int i = 0; i < 100; i++)
			s += p[i].get();
		CHECK_EQUAL(s, 0);
		array::destruct(p, 100);
	}

TEST_END

