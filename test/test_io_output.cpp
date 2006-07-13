/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_io_output.cpp -- io output classes test.
 */

#include <elm/util/test.h>
#include <elm/io.h>
#include <elm/string.h>

using namespace elm;
using namespace elm::io;

// Entry point
void test_io_output(void) {	
	CHECK_BEGIN("io_output");
	
	// Standard output
	{
		Output &out = cout;
		out << "---------------------------------------------\n";
		
	}
	
	// Created file
	{
		elm::io::OutFileStream stream("log.txt");
		elm::io::Output out(stream);	
		out << "---------------------------------------------\n";
	}
	
	CHECK_END
}
