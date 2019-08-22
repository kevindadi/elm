/*
 *	meta module test
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

#include <typeinfo>

#include <elm/meta.h>
#include <elm/test.h>

using namespace elm;

// type checking
template <typename...> struct _require { };
template <typename T> struct _empty_construct { };

template <class T>
struct is_class {
	template <class C> static _true test(int C::*);
	template <class C> static _false test(...);
	static const bool _ = decltype(test<T>(0))::_;
};

struct A {

};


template <class T> using has_f2 = decltype(meta::declval<T>().f());
template <class T> using has_f2_int = decltype(meta::declval<T>().f(meta::declval<int>()));


class WithF {
public:
	void f() { }
	void f(int) { }
};

class WithoutF {
};

TEST_BEGIN(meta)

// new_if test
{
	bool r = _if<true, _true, _false>::_;
	CHECK(r);
	r = _if<false, _true, _false>::_;
	CHECK(!r);
	r = _if<false, _true, _if<false, _true, _false> >::_;
	CHECK(!r);

	cout << "is_class<int>::_ = " << is_class<int>::_ << io::endl;
	cout << "is_class<int *>::_ = " << is_class<int *>::_ << io::endl;
	cout << "is_class<string>::_ = " << is_class<string>::_ << io::endl;
	cout << "is_class<A>::_ = " << is_class<A>::_ << io::endl;

	bool e = meta::is_same<int, int>::_;
	CHECK(e);
	e = meta::is_same<int, char>::_;
	CHECK(!e);

	e = meta::is_supported<WithF, has_f2>::_;
	CHECK(e);
	e = meta::is_supported<WithoutF, has_f2>::_;
	CHECK(!e);

	e = meta::is_supported<WithF, has_f2_int>::_;
	CHECK(e);
	e = meta::is_supported<WithoutF, has_f2_int>::_;
	CHECK(!e);
}


TEST_END


