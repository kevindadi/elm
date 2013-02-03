/*
 * test_int.cpp
 *
 *  Created on: 6 janv. 2011
 *      Author: casse
 */

#include <elm/util/test.h>
#include <elm/int.h>

using namespace elm;

TEST_BEGIN(int)
	for(int i = 0; i < 32; i++)
		CHECK_EQUAL(msb(1UL << i), i);
	for(int i = 1; i < 32; i++)
		CHECK_EQUAL(msb((1UL << i) | (1UL << (i - 1))), i);
TEST_END

