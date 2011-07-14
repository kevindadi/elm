/*
 * test_thread.cpp
 *
 *  Created on: 24 janv. 2011
 *      Author: casse
 */

#include <elm/io.h>
#include <elm/system/Thread.h>
#include <elm/system/StopWatch.h>
#include <math.h>

using namespace elm;
using namespace elm::system;

double my_cos(double x) {
    double t , s ;
    static const double prec = 1e-10;
    int p;
    p = 0;
    s = 1.0;
    t = 1.0;
    while(fabs(t/s) > prec)
    {
        p++;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        s += t;
    }
    return s;
}

int int_comp(int x) {
	int s = 0;
	for(int i = 0; i < x; i++)
		for(int j = i; j < x; j++)
			s += i * j;
}

void work(long long m, long long n) {
	float x = 0;
	cerr << "WORK from " << m << " to " << n << io::endl;
	for(long long i = m; i < n; i++)
		//x += my_cos(i);
		x += int_comp(i);
}

class MyRunnable: public Runnable {
public:
	long long n, m;

	MyRunnable(long long _n, long long _m): n(_n), m(_m) { }

	virtual void run(void) {
		work(n, m);
	}
};

void test_thread(void) {
	static const long long N = 3000;

	// alone
	StopWatch sw;
	sw.start();
	work(0, N);
	sw.stop();
	cerr << "alone: " << sw.delay() << io::endl;

	// at two
	sw.start();
	MyRunnable run(0, N / 2);
	Thread *thread = Thread::make(run);
	thread->start();
	work(N / 2, N);
	thread->join();
	sw.stop();
	cerr << "two: " << sw.delay() << io::endl;
}
