/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_io_format.cpp -- formatted io classes test.
 */

#include <elm/util/test.h>
#include <elm/io.h>
#include <elm/string.h>
#include <elm/io/BlockInStream.h>

using namespace elm;
using namespace elm::io;

inline String test(IntFormat fmt) {
	StringBuffer buf;
	buf << fmt;
	return buf.toString();
}

// Entry point
void test_io_format(void) {
	CHECK_BEGIN("io_format");
	
	// Testing the base
	CHECK_EQUAL(test(666), String("666"));
	CHECK_EQUAL(test(hex(666)), String("29a"));
	CHECK_EQUAL(test(bin(666)), String("1010011010"));
		
	// Testing width
	CHECK_EQUAL(test(width(8, 666)), String("666     "));
	CHECK_EQUAL(test(width(2, 666)), String("666"));
	
	// Testing alignment
	CHECK_EQUAL(test(left(width(8, 666))), String("666     "));
	CHECK_EQUAL(test(right(width(8, 666))), String("     666"));
	CHECK_EQUAL(test(center(width(8, 666))), String("  666   "));
	CHECK_EQUAL(test(left(666)), String("666"));
	CHECK_EQUAL(test(right(666)), String("666"));
	CHECK_EQUAL(test(center(666)), String("666"));
	
	// Testing padding
	CHECK_EQUAL(test(left(width(8, pad('!', 666)))), String("666!!!!!"));
	CHECK_EQUAL(test(right(width(8, pad('!', 666)))), String("!!!!!666"));
	CHECK_EQUAL(test(center(width(8, pad('!', 666)))), String("!!666!!!"));
	
	// Test special numbers
	CHECK_EQUAL(test(center(width(8, pad('!', -666)))), String("!!-666!!"));
	CHECK_EQUAL(test(center(width(8, pad('!', 0)))), String("!!!0!!!!"));
	CHECK_EQUAL(test(hex(t::uint32(-1))), String("ffffffff"));
	CHECK_EQUAL(test(hex(t::int32(-1))), String("ffffffffffffffff"));
	
	// Test upper case
	CHECK_EQUAL(test(hex(uppercase(666))), String("29A"));
	
	// Type test
	CHECK_EQUAL(test(hex((char)111)), String("6f"));
	CHECK_EQUAL(test(hex((signed char)111)), String("6f"));
	CHECK_EQUAL(test(hex((unsigned char)111)), String("6f"));
	CHECK_EQUAL(test(hex((short)111)), String("6f"));
	CHECK_EQUAL(test(hex((signed short)111)), String("6f"));
	CHECK_EQUAL(test(hex((unsigned short)111)), String("6f"));
	CHECK_EQUAL(test(hex((long)111)), String("6f"));
	CHECK_EQUAL(test(hex((signed long)111)), String("6f"));
	CHECK_EQUAL(test(hex((unsigned long)111)), String("6f"));
	CHECK_EQUAL(test(hex((int)111)), String("6f"));
	CHECK_EQUAL(test(hex((signed int)111)), String("6f"));
	CHECK_EQUAL(test(hex((unsigned int)111)), String("6f"));
	CHECK_EQUAL(test(hex((signed)111)), String("6f"));
	CHECK_EQUAL(test(hex((unsigned)111)), String("6f"));
	
	BlockInStream instream("666", 3);
	Input in(instream);
	int x;
	FAIL_ON_EXCEPTION(IOException, in >> x);
	CHECK_EQUAL(x, 666);

	CHECK_END;	
}
