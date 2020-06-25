/*
 *	io module test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2019, IRIT UPS.
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

#include <elm/test.h>
#include <elm/io/StringInput.h>
#include <elm/io/VarExpander.h>
#include <elm/string/StringBuffer.h>
#include <elm/sys/System.h>

using namespace elm;

class OSExpander: public io::VarExpander {
protected:
	string resolve(string name, bool& rec) override {
		if(name == "1")
			return "one";
		else if(name == "2")
			return "two";
		else
			return "???";
	}
};

class SpecInt {
public:
	typedef int t;
	static void print(io::Output& out, int i) {
		out << "!" << i << "!";
	}
};

class IntManager {
public:
	static cstring t[4];
	void print(int i, io::Output& out) const {
		if(i >= 4)
			out << "more";
		else
			out << t[i];
	}
};
cstring IntManager::t[4] = { "zero", "one", "two", "three" };


TEST_BEGIN(io)

	OSExpander e;
	CHECK_EQUAL(e.expand("ok"), string("ok"));
	CHECK_EQUAL(e.expand("o${1}k"), string("oonek"));
	CHECK_EQUAL(e.expand("o${1}k${2}o"), string("oonektwoo"));
	CHECK_EQUAL(e.expand("o${1}k${1}o"), string("oonekoneo"));
	CHECK_EQUAL(e.expand("ok${3}ko"), string("ok???ko"));

	// ListPrinter test
	{
		Vector<int> v;
		for(int i = 0; i < 5; i++)
			v.add(i);
		StringBuffer buf;
		buf << io::list(v, "|", [](io::Output& out, int x) { cout << "-> " << x << io::endl; out << x; });
		CHECK_EQUAL(buf.toString(), string("0|1|2|3|4"));
	}

	// Tag example
	{
		typedef io::Tag<SpecInt> SPEC_INT;
		StringBuffer buf;
		buf << SPEC_INT(666);
		CHECK_EQUAL(buf.toString(), string("!666!"));
	}

	// Printable example
	{
		IntManager man;
		StringBuffer buf;
		buf << io::p(2, man);
		CHECK_EQUAL(buf.toString(), string("two"));
	}

	// input
	{
		CHECK_EQUAL(io::read("123").scanULong(), 123U);
		CHECK_EQUAL(io::read("033").scanULong(), 27U);
		CHECK_EQUAL(io::read("0xff").scanULong(), 255U);
		CHECK_EQUAL(io::read("0b101").scanULong(), 5U);
		CHECK_EQUAL(io::read("FF").scanULong(16), 255U);

		CHECK_EQUAL(io::read("123").scanULLong(), 123UL);
		CHECK_EQUAL(io::read("033").scanULLong(), 27UL);
		CHECK_EQUAL(io::read("0xff").scanULLong(), 255UL);
		CHECK_EQUAL(io::read("0b101").scanULLong(), 5UL);
		CHECK_EQUAL(io::read("FF").scanULLong(16), 255UL);

		auto x = io::read("1 2 3");
		CHECK_EQUAL(x.scanLong(), 1);
		CHECK(!x.ended());
		CHECK(!x.failed());
		CHECK_EQUAL(x.scanLong(), 2);
		CHECK(!x.ended());
		CHECK(!x.failed());
		CHECK_EQUAL(x.scanLong(), 3);
		CHECK(x.ended());
		CHECK(!x.failed());
		x.scanLong();
		CHECK(x.failed());

		CHECK_EQUAL(io::read("ok ko").scanWord(), string("ok"));
		CHECK_EQUAL(io::read("ok").scanWord(), string("ok"));
		CHECK_EQUAL(io::read("ok\nko").scanLine(), string("ok\n"));

		CHECK_EQUAL(io::read("1.5").scanDouble(), 1.5);
		CHECK_EQUAL(io::read("1e3").scanDouble(), 1e3);
		CHECK_EQUAL(io::read("1.5e3").scanDouble(), 1.5e3);

		CHECK_EQUAL(io::read("true").scanBool(), true);
		CHECK_EQUAL(io::read("false").scanBool(), false);
		CHECK_EQUAL(io::read("1").scanBool(), true);
		CHECK_EQUAL(io::read("0").scanBool(), false);
	}

	{
		auto x = io::read("1\n2\n3");
		CHECK_EQUAL(x.scanLine(), string("1\n"));
		CHECK_EQUAL(x.scanLine(), string("2\n"));
		CHECK_EQUAL(x.scanLine(), string("3"));
		CHECK_EQUAL(x.scanLine(), string(""));
	}

	{
		cstring ss[] = { "1\n", "2\n", "3" };
		int i = 0;
		auto in = io::read("1\n2\n3");
		for(auto s: in.lines()) {
			if(ss[i] != s)
				break;
			i++;
		}
		CHECK_EQUAL(i, 3);
	}

TEST_END

