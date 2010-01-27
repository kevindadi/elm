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

#include <stdio.h>
#include <iostream>
#include <elm/type_info.h>
#include <elm/util/test.h>

using namespace elm;

typedef enum enm_t {
	A,
	B,
	C
} enm_t;

int main(void) {
	CHECK_BEGIN("inhstruct_Tree")

	CHECK(type_info<signed char>::null == 0);
	CHECK(type_info<signed char>::is_signed == true);
	CHECK(type_info<signed char>::min == -0x80);
	CHECK(type_info<signed char>::max == 0x7f);

	CHECK(type_info<unsigned char>::null == 0);
	CHECK(type_info<unsigned char>::is_signed == false);
	CHECK(type_info<unsigned char>::min == 0);
	CHECK(type_info<unsigned char>::max == 0xff);

	CHECK(type_info<signed short>::null == 0);
	CHECK(type_info<short>::is_signed == true);
	CHECK((int)type_info<signed short>::min == (int)-32768);
	CHECK(type_info<signed short>::max == 0x7fff);

	CHECK(type_info<unsigned short>::null == 0);
	CHECK(type_info<unsigned short>::is_signed == false);
	CHECK(type_info<unsigned short>::min == 0);
	CHECK(type_info<unsigned short>::max == 0xffff);

	CHECK(type_info<int>::null == 0);
	CHECK(type_info<int>::is_signed == true);
	CHECK(type_info<int>::min == (int)-0x80000000);
	CHECK(type_info<int>::max == 0x7fffffff);		 
		 
	CHECK(type_info<unsigned>::null == 0);
	CHECK(type_info<unsigned>::is_signed == false);
	CHECK(type_info<unsigned>::min == 0);
	CHECK(type_info<unsigned>::max == 0xffffffff);		 

	CHECK(type_info<long>::null == 0);
	CHECK(type_info<long>::is_signed == true);
	CHECK(type_info<long>::min == (long)-0x80000000);
	CHECK(type_info<long>::max == 0x7fffffff);		 
		 
	CHECK(type_info<unsigned long>::null == 0);
	CHECK(type_info<unsigned long>::is_signed == false);
	CHECK(type_info<unsigned long>::min == 0);
	CHECK(type_info<unsigned long>::max == 0xffffffff);		 

	CHECK(type_info<long long>::null == 0);
	CHECK(type_info<long long>::is_signed == true);
	CHECK(type_info<long long>::min == (long long)-0x8000000000000000LL);
	CHECK(type_info<long long>::max == 0x7fffffffffffffffLL);		 
		 
	CHECK(type_info<unsigned long long>::null == 0);
	CHECK(type_info<unsigned long long>::is_signed == false);
	CHECK(type_info<unsigned long long>::min == 0LL);
	CHECK(type_info<unsigned long long>::max == 0xffffffffffffffffLL);	 

	CHECK(type_info<enm_t>::is_ptr == 0);
	//cerr << io::hex(type_info<unsigned long long>::max) << io::endl;
	
	CHECK_END
}
