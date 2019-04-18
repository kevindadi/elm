/*
 *	FragTable class test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2017, IRIT UPS.
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

#include <elm/data/FragTable.h>
#include "../include/elm/test.h"

using namespace elm;

TEST_BEGIN(frag_table)
	
	FragTable<int> tab(2);
	
	// Fill the table
	CHECK(tab.isEmpty());
	bool test_length = true;
	for(int i = 0; i < 123; i++) {
		if(tab.length() != i) {
			test_length = false;
			break;
		}
		tab.add(i);
	}
	CHECK(test_length);
	CHECK_EQUAL(tab.length(), 123);
	
	// Test the content
	bool test_content = true;
	for(int i = 0; i < 123; i++)
		if(tab[i] != i) {
			test_content = false;
			break;
		}
	CHECK(test_content);
	
	// Test iterator
	bool test_iter = true;
	int i = 0;
	for(FragTable<int>::Iter iter(tab); iter(); iter++, i++)
		if(*iter != i) {
			test_iter = false;
			break;
		}
	CHECK(test_iter);
	CHECK_EQUAL(i, 123);
	
	// Test assignment
	for(int i = 0, j = 122; i < j; i++, j--) {
		int tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
	}
	bool test_set = true;
	for(int i = 0; i < 123; i++)
		if(tab[i] != 122 - i) {
			test_set = false;
			cerr << "tab[" << i << "] = " << tab[i] << io::endl;
			break;
		}	
	CHECK(test_set);
	

	// test C++ for
	{
		FragTable<int> t;
		const int l = 10;
		for(int i = 0; i < l; i++)
			t.add(i);
		int i = 0;
		bool ok = true;
		for(auto x: t) {
			ok = ok && (x == i);
			i++;
		}
		CHECK(ok);
		CHECK(i == 10);
	}

	// Test mutable table
	/*i = 0;
	for(FragTable<int>::MutableIterator iter(tab); iter; iter++, i++)
		iter = i;
	bool test_mut_iter = true;
	for(int i = 0; i < 123; i++)
		if(tab[i] != i) {
			test_mut_iter = false;
			break;
		}
	CHECK(test_mut_iter);*/
	
TEST_END
