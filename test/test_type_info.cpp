/*
 *	$Id$
 *	Test for type_info class.
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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

#include <elm/type_info.h>
#include <elm/util/Option.h>
#include <elm/test.h>
#include <elm/data/Vector.h>
#include <elm/data/HashMap.h>

using namespace elm;

typedef enum enm_t {
	A,
	B,
	C
} enm_t;

class MyClass { };

class Big {
public:
	int t[1000];
};

template <class T>
class Embed {
public:
	Embed(t::in<T> i) { t::put<T>(x, i); }
	inline void set(t::in<T> y) { t::put<T>(x, y); }
	inline void read(t::out<T> y) { t::put<T>(y, x); }
	inline t::ret<T> get() const { return t::get<T>(x); }
	inline t::mut<T> ref() { return t::ref<T>(x); }
private:
	t::var<T> x;
};

class Simple {
public:
	Simple(): x(0) { }
	Simple(int _x): x(_x) { }
	int x;
};

TEST_BEGIN(type_info)
	CHECK(type_info<t::int8>::null == 0);
	CHECK(type_info<t::int8>::is_signed == true);
	CHECK(type_info<t::int8>::min == -0x80);
	CHECK(type_info<t::int8>::max == 0x7f);
	CHECK(type_info<t::int8>::is_enum == false);
	CHECK(type_info<t::int8>::is_scalar == true);

	CHECK(type_info<t::uint8>::null == 0);
	CHECK(type_info<t::uint8>::is_signed == false);
	CHECK(type_info<t::uint8>::min == 0);
	CHECK(type_info<t::uint8>::max == 0xff);
	CHECK(type_info<t::uint8>::is_enum == false);
	CHECK(type_info<t::uint8>::is_scalar == true);

	CHECK(type_info<t::int16>::null == 0);
	CHECK(type_info<t::int16>::is_signed == true);
	CHECK(type_info<t::int16>::min == t::int16(-32768));
	CHECK(type_info<t::int16>::max == 0x7fff);
	CHECK(type_info<t::int16>::is_enum == false);
	CHECK(type_info<t::int16>::is_scalar == true);

	CHECK(type_info<t::uint16>::null == 0);
	CHECK(type_info<t::uint16>::is_signed == false);
	CHECK(type_info<t::uint16>::min == 0);
	CHECK(type_info<t::uint16>::max == 0xffff);
	CHECK(type_info<t::uint16>::is_enum == false);
	CHECK(type_info<t::uint16>::is_scalar == true);

	CHECK(type_info<int>::null == 0);
	CHECK(type_info<int>::is_signed == true);
	CHECK(type_info<int>::min == (int)-0x80000000);
	CHECK(type_info<int>::max == 0x7fffffff);
	CHECK(type_info<int>::is_enum == false);
	CHECK(type_info<int>::is_scalar == true);

	CHECK(type_info<unsigned>::null == 0);
	CHECK(type_info<unsigned>::is_signed == false);
	CHECK(type_info<unsigned>::min == 0);
	CHECK(type_info<unsigned>::max == 0xffffffff);
	CHECK(type_info<unsigned>::is_enum == false);
	CHECK(type_info<unsigned>::is_scalar == true);

	CHECK(type_info<t::int32>::null == 0);
	CHECK(type_info<t::int32>::is_signed == true);
	CHECK(type_info<t::int32>::min == t::int32(-0x80000000));
	CHECK(type_info<t::int32>::max == 0x7fffffff);
	CHECK(type_info<t::int32>::is_enum == false);
	CHECK(type_info<t::int32>::is_scalar == true);

	CHECK(type_info<t::uint32>::null == 0);
	CHECK(type_info<t::uint32>::is_signed == false);
	CHECK(type_info<t::uint32>::min == 0);
	CHECK(type_info<t::uint32>::max == 0xffffffff);
	CHECK(type_info<t::uint32>::is_enum == false);
	CHECK(type_info<t::uint32>::is_scalar == true);

	CHECK(type_info<t::int64>::null == 0);
	CHECK(type_info<t::int64>::is_signed == true);
	CHECK(type_info<t::int64>::min == t::int64(-0x8000000000000000LL));
	CHECK(type_info<t::int64>::max == 0x7fffffffffffffffLL);
	CHECK(type_info<t::int64>::is_enum == false);
	CHECK(type_info<t::int64>::is_scalar == true);

	CHECK(type_info<t::uint64>::null == 0);
	CHECK(type_info<t::uint64>::is_signed == false);
	CHECK(type_info<t::uint64>::min == 0LL);
	CHECK(type_info<t::uint64>::max == 0xffffffffffffffffLL);
	CHECK(type_info<t::uint64>::is_enum == false);
	CHECK(type_info<t::int64>::is_scalar == true);

	CHECK(type_info<enm_t>::is_ptr == 0);
	CHECK(type_info<enm_t>::is_enum == true);
	CHECK(type_info<enm_t>::is_scalar == true);

	CHECK_EQUAL(int(type_info<void *>::is_ptr), 1);
	CHECK(type_info<void *>::is_enum == false);
	CHECK(type_info<void *>::is_scalar == true);

	// bool embedding
	{
		CHECK_EQUAL(sizeof(t::var<bool>), sizeof(bool));
		Embed<bool> e(false);
		bool x;
		e.set(true);
		e.read(x);
		CHECK_EQUAL(x, true);
		CHECK_EQUAL(e.get(), true);
		CHECK_EQUAL(e.ref(), true);
		e.ref() = false;
		CHECK_EQUAL(e.get(), false);
	}

	// int embedding
	{
		CHECK_EQUAL(sizeof(t::var<int>), sizeof(int));
		Embed<int> e(0);
		int x;
		e.set(666);
		e.read(x);
		CHECK_EQUAL(x, 666);
		CHECK_EQUAL(e.get(), 666);
		CHECK_EQUAL(e.ref(), 666);
		e.ref() = 111;
		CHECK_EQUAL(e.get(), 111);
	}

	// ptr embedding
	{
		CHECK_EQUAL(sizeof(t::var<char *>), sizeof(char *));
		char c1, c2;
		Embed<char *> e(nullptr);
		char *x;
		e.set(&c1);
		e.read(x);
		CHECK_EQUAL(x, &c1);
		CHECK_EQUAL(e.get(), &c1);
		CHECK_EQUAL(e.ref(), &c1);
		e.ref() = &c2;
		CHECK_EQUAL(e.get(), &c2);
	}

	{
		CHECK_EQUAL(sizeof(t::var<char *>), sizeof(char *));
		const char *c1 = "ok", *c2 = "ko";
		Embed<const char *> e(nullptr);
		const char *x;
		e.set(c1);
		e.read(x);
		CHECK_EQUAL(x, c1);
		CHECK_EQUAL(e.get(), c1);
		CHECK_EQUAL(e.ref(), c1);
		e.ref() = c2;
		CHECK_EQUAL(e.get(), c2);

	}

	// cstring embedding
	{
		CHECK_EQUAL(sizeof(t::var<cstring>), sizeof(cstring));
		cstring s1 = "a", s2 = "b";
		Embed<cstring> e("");
		cstring x;
		e.set(s1);
		e.read(x);
		CHECK_EQUAL(x, s1);
		CHECK_EQUAL(e.get(), s1);
		CHECK_EQUAL(e.ref(), s1);
		e.ref() = s2;
		CHECK_EQUAL(e.get(), s2);
	}

	// string embedding
	{
		CHECK_EQUAL(sizeof(t::var<string>), sizeof(string));
		string s1 = "a", s2 = "b";
		Embed<string> e("");
		e.set(s1);
		cerr << &e.get() << " == " << s1 << io::endl;
		CHECK_EQUAL(e.get(), s1);

		string x;
		e.read(x);
		CHECK_EQUAL(x, s1);
		CHECK_EQUAL(e.ref(), s1);
		e.ref() = s2;
		CHECK_EQUAL(e.get(), s2);
	}

	// reference embedding
	{
		CHECK_EQUAL(sizeof(t::var<int&>), sizeof(int *));
		int i1 = 666, i2 = 111;
		Embed<int&> e(i2);
		string x;
		e.set(i1);
		CHECK_EQUAL(e.get(), i1);
		int& r = e.get();
		CHECK_EQUAL(r, i1);
		CHECK_EQUAL(&r, &i1);
		e.set(i2);
		CHECK_EQUAL(e.get(), i2);
		CHECK_EQUAL(&e.get(), &i2);
	}

	// reference embedding
	{
		CHECK_EQUAL(sizeof(t::var<const int&>), sizeof(const int *));
		const int i1 = 666, i2 = 111;
		Embed<const int&> e(i2);
		string x;
		e.set(i1);
		CHECK_EQUAL(e.get(), i1);
		const int& r = e.get();
		CHECK_EQUAL(r, i1);
		CHECK_EQUAL(&r, &i1);
		e.set(i2);
		CHECK_EQUAL(e.get(), i2);
		CHECK_EQUAL(&e.get(), &i2);
	}

	// embed simple class
	{
		CHECK_EQUAL(sizeof(t::var<Simple>), sizeof(Simple));
		Embed<Simple> e(Simple(666));
		CHECK_EQUAL(e.get().x, 666);
		const Simple *p = &e.get();
		Simple *q = &e.ref();
		CHECK_EQUAL(p, const_cast<const Simple *>(q));
		e.ref().x = 111;
		CHECK_EQUAL(e.get().x, 111);
		Simple s;
		e.read(s);
		CHECK_EQUAL(s.x, 111);
	}

TEST_END
