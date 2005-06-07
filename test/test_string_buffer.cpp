/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test_string_buffer.cpp -- unit tests for StringBuffer..
 */

#include <elm/util/test.h>

using namespace elm;

void test_string_buffer(void) {
	CHECK_BEGIN("StringBuffer");
	
	// Empty string
	{
		StringBuffer buffer;
		CHECK(buffer.length() == 0);
		String str = buffer.toString();
		CHECK(str == "");
	}
	
	// C String puts
	{
		StringBuffer buffer;
		buffer.put("0123");
		CHECK(buffer.length() == 4);
		buffer.put("");
		CHECK(buffer.length() == 4);
		buffer.put("4567");
		CHECK(buffer.length() == 8);
		String str = buffer.toString();
		CHECK(str == "01234567");
	}
	
	// Different put types
	{
		StringBuffer buffer;
		buffer.put('0');
		buffer.put("1");
		CString cstr("2");
		buffer.put(cstr);
		String str("3");
		buffer.put(str);
		String res = buffer.toString();
		CHECK(res == "0123");
	}
	
	// Formatted test
	{
		StringBuffer buffer;
		buffer.print("%s%s%s%s", "0", "1", "2", "3");
		String str = buffer.toString();
		CHECK(str == "0123");
	}
	
	CHECK_END;
}

