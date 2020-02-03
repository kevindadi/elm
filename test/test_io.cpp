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
		buf << io::list(v, "|");
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

TEST_END

