/*
 *	Test types for overloading.
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2021, IRIT UPS.
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

#include <elm/types.h>
#include <elm/io.h>

using namespace elm;

#define F(t) void f(t i) { cout << #t << io::endl; }
F(bool)
F(char)
F(unsigned char)
F(signed char)
F(int)
F(unsigned int)
F(short)
F(unsigned short)
F(long)
F(unsigned long)
F(long long)
F(unsigned long long)
F(float);
F(double);
F(long double);

int main() {
	
	cout << "ELM types" << io::endl;
	cout << "sizeof(t::int8) = " << sizeof(t::int8) << io::endl;
	cout << "sizeof(t::uint8) = " << sizeof(t::uint8) << io::endl;
	cout << "sizeof(t::int16) = " << sizeof(t::int16) << io::endl;
	cout << "sizeof(t::uint16) = " << sizeof(t::uint16) << io::endl;
	cout << "sizeof(t::int32) = " << sizeof(t::int32) << io::endl;
	cout << "sizeof(t::uint32) = " << sizeof(t::uint32) << io::endl;
	cout << "sizeof(t::int64) = " << sizeof(t::int64) << io::endl;
	cout << "sizeof(t::uint64) = " << sizeof(t::uint64) << io::endl;
	
	cout << io::endl << "immediate types" << io::endl;
	cout << "sizeof(111) = " << sizeof(111) << io::endl;
	cout << "sizeof(111U) = " << sizeof(111U) << io::endl;
	cout << "sizeof(111L) = " << sizeof(111L) << io::endl;
	cout << "sizeof(111UL) = " << sizeof(111UL) << io::endl;
	cout << "sizeof(111LL) = " << sizeof(111LL) << io::endl;
	cout << "sizeof(111ULL) = " << sizeof(111ULL) << io::endl;

	cout << io::endl << "basic types" << io::endl;
	cout << "sizeof(char) = " << sizeof(char) << io::endl;
	cout << "sizeof(signed char) = " << sizeof(signed char) << io::endl;
	cout << "sizeof(unsigned char) = " << sizeof(unsigned char) << io::endl;
	cout << "sizeof(int) = " << sizeof(int) << io::endl;
	cout << "sizeof(signed int) = " << sizeof(signed int) << io::endl;
	cout << "sizeof(unsigned int) = " << sizeof(unsigned int) << io::endl;
	cout << "sizeof(signed) = " << sizeof(signed) << io::endl;
	cout << "sizeof(unsigned) = " << sizeof(unsigned) << io::endl;
	cout << "sizeof(short) = " << sizeof(short) << io::endl;
	cout << "sizeof(signed short) = " << sizeof(signed short) << io::endl;
	cout << "sizeof(unsigned short) = " << sizeof(unsigned short) << io::endl;
	cout << "sizeof(long) = " << sizeof(long) << io::endl;
	cout << "sizeof(signed long) = " << sizeof(signed long) << io::endl;
	cout << "sizeof(unsigned long) = " << sizeof(unsigned long) << io::endl;
	cout << "sizeof(long long) = " << sizeof(long long) << io::endl;
	cout << "sizeof(signed long long) = " << sizeof(signed long long) << io::endl;
	cout << "sizeof(unsigned long long) = " << sizeof(unsigned long long) << io::endl;
	
	cout << io::endl << "constant overloading" << io::endl;
	cout << "'a' "; f('a');
	cout << "true "; f(true);
	cout << "111 "; f(111);
	cout << "111U "; f(111U);
	cout << "111L "; f(111L);
	cout << "111UL "; f(111UL);
	cout << "111LL "; f(111LL);
	cout << "111ULL "; f(111ULL);
	cout << "0. "; f(0.);
	cout << "0.F "; f(0.F);
	cout << "0.L "; f(0.L);

	cout << io::endl << "t:: overloading" << io::endl;
	{ bool x = false; f(x); }
	{ char x = 0; f(x); }
	{ t::int8 x = 0; f(x); }
	{ t::uint8 x = 0; f(x); }
	{ t::int16 x = 0; f(x); }
	{ t::uint16 x = 0; f(x); }
	{ t::int32 x = 0; f(x); }
	{ t::uint32 x = 0; f(x); }
	{ t::int64 x = 0; f(x); }
	{ t::uint64 x = 0; f(x); }
	{ signed x = 0; f(x); }
	{ unsigned x = 0; f(x); }
	{ float x = 0; f(x); }
	{ double x = 0; f(x); }
	{ long double x = 0; f(x); }
	
	return 0;
}
