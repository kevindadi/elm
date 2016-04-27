/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test_plugin.cpp -- test the plugin feature.
 */

#include <elm/sys/System.h>
#include <elm/sys/Thread.h>
#include <elm/util/test.h>

using namespace elm;
using namespace elm::sys;

const t::int64 N = 1000000;
t::int64 t[N];
t::int64 s1, s2;

class Sum: public Runnable {
public:
	Sum(t::int64& _r, t::int64 _s, t::int64 _n): r(_r), s(_s), n(_n) { }

	virtual void run(void) {
		t::int64 sum = 0;
		for(t::int64 i = 0; i < n; i++)
			sum += ::t[i + s];
		r = sum;
	}

private:
	t::int64& r;
	t::int64 s, n;
};

class KeyRunnable: public Runnable {
public:
	KeyRunnable(Thread::Key<int> *key, int number, int& ref): k(key), n(number), r(ref) { }

	virtual void run(void) {
		k->set(n);
		int s = 0;
		int m = int(sys::System::random(1000000));
		for(int i = 0; i < m; i++)
			s += i;
		r = k->get();
	}

private:
	Thread::Key<int> *k;
	int n;
	int& r;
};


// test routine
TEST_BEGIN(thread)

	{
		// fill the array
		for(t::int64 i = 0; i < N; i++)
			::t[i] = i;

		// launch both threads
		Sum sum1(s1, 0, N / 2);
		Sum sum2(s2, N / 2, N / 2);
		Thread *t1 = Thread::make(sum1);
		CHECK(t1);
		Thread *t2 = Thread::make(sum2);
		CHECK(t2);
		t1->start();
		t2->start();
		t1->join();
		t2->join();
		CHECK_EQUAL(s1 + s2, (N * (N - 1) / 2));
	}

	{
		const static int n = 10;
		Thread *ts[n];
		KeyRunnable *rs[n];
		int res[n];

		// run thread
		Thread::Key<int> *k = Thread::key<int>();
		for(int i = 0; i < n; i++) {
			rs[i] = new KeyRunnable(k, i, res[i]);
			ts[i] = Thread::make(*rs[i]);
			ts[i]->start();
		}

		// join them and clean them
		for(int i = 0; i < n; i++) {
			ts[i]->join();
			delete ts[i];
			delete rs[i];
		}

		// check result
		int c = 0;
		for(int i = 0; i < n; i++)
			if(res[i] == i)
				c++;
		CHECK_EQUAL(c, n);
	}

TEST_END

