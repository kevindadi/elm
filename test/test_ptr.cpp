/*
 *	Test for pointer classes (AutoPtr, SharedPtr).
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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

#include <elm/util/SharedPtr.h>
#include <elm/test.h>
#include <elm/sys/System.h>
#include <elm/data/Vector.h>

using namespace elm;

bool del;

class C {
public:
	C(int _x): x(_x) { }
	~C(void) { del = true; }
	int x;
};

class R {
public:
	R(void) { cerr << "DEBUG: new " << (void *)(this) << io::endl; }
	~R(void) { cerr << "DEBUG: delete " << (void *)(this) << io::endl; }
};

void f(SharedPtr<R> p) {
	SharedPtr<R> q = p;
}

class L {
public:
	L(SharedPtr<L> q): p(q) { cerr << "DEBUG: new " << (void *)(this) << io::endl; }
	~L(void) { cerr << "DEBUG: delete " << (void *)(this) << io::endl; }
	SharedPtr<L> p;
};

SharedPtr<R> id(SharedPtr<R> p) {
	return p;
}

SharedPtr<R> make(void) {
	return new R;
}

TEST_BEGIN(ptr)

	// simple shared
	{
		del = false;
		{
			SharedPtr<C> p = new C(111);
			CHECK((bool)p == true);
			CHECK(p->x == 111);
		}
		CHECK(del == true);
	}

	// several pointers
	{
		del = false;
		{
			SharedPtr<C> p = new C(111);
			{
				SharedPtr<C> q = p;
				CHECK(q->x == 111);
				CHECK(p == q);
			}
			CHECK(del == false);
		}
		CHECK(del == true);
	}

	// array of references
	{
		del = false;
		{
			SharedPtr<C> p = new C(666);
			{
				SharedPtr<C> t[10];
				for(int i = 0; i < 10; i++)
					CHECK((bool)t[i] == false);
				for(int i = 0; i < 10; i++)
					t[i] = p;
				for(int i = 0; i < 10; i++)
					CHECK(t[i]->x == 666);
			}
			CHECK(del == false);
		}
		CHECK(del == true);
	}

	// parameter passing
	{
		cerr << "1\n";
		SharedPtr<R> p = new R;
		cerr << "2\n";
		SharedPtr<R> q = p;
		cerr << "3\n";
		f(p);
		cerr << "4\n";
		f(q);
		cerr << "5\n";
	}

	// list
	{
		cerr << "1\n";
		SharedPtr<L> l;
		cerr << "2\n";
		l = new L(l);
		cerr << "3\n";
		l = new L(l);
		cerr << "4\n";
		l = new L(l);
		cerr << "5\n";
	}

	// tree
	{
		cerr << "1\n";
		SharedPtr<L> t = new L(0);
		cerr << "2\n";
		SharedPtr<L> l = new L(t);
		cerr << "3\n";
		SharedPtr<L> r = new L(t);
		cerr << "4\n";
		SharedPtr<L> ll = new L(l);
		cerr << "5\n";
		SharedPtr<L> lr = new L(r);
		cerr << "5\n";
		lr = l;
		cerr << "6\n";
	}

	// as return
	{
		cerr << "1\n";
		SharedPtr<R> p = id(new R());
		cerr << "2\n";
		p = id(new R());
		cerr << "3\n";
		p = make();
		cerr << "4\n";
		p = make();
		cerr << "5\n";
	}

TEST_END
