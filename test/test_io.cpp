/*
 *	$Id$
 *	IO module test program
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2007, IRIT UPS.
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

#include <elm/util/test.h>
#include <elm/io/RandomAccessStream.h>

using namespace elm;
using namespace elm::io;

// test_RandomAccessStream()
void test_RandomAccessStream(void) {
	CHECK_BEGIN("io::RandomAccessStream");
	int data[] = { 111, 666, 0, 1, 2, 3 };
	
	// Write to the file
	{
		OutStream *stream = RandomAccessStream::createFile("random_access.txt");
		CHECK(stream);
		CHECK(stream->write((char *)data, sizeof(data)) == sizeof(data));
		delete stream;
	}
	
	// Read from the file
	{
		InStream *stream = RandomAccessStream::openFile("random_access.txt");
		CHECK(stream);
		int read_data[sizeof(data) / sizeof(int)];
		CHECK(stream->read((char *)read_data, sizeof(read_data)) == sizeof(read_data));
		delete stream;
		for(int i = 0; i < sizeof(data) / sizeof(int); i++)
			CHECK_EQUAL(read_data[i], data[i]);
	}
	
	// Random read the file
	{
		RandomAccessStream *stream = RandomAccessStream::openFile("random_access.txt");
		CHECK(stream);
		for(int i = sizeof(data) / sizeof(int) - 1; i >= 0; i--) {
			CHECK(stream->moveTo(i * sizeof(int)));
			int x;
			CHECK(stream->read((char *)&x, sizeof(int)) == sizeof(int));
			CHECK_EQUAL(x, data[i]);
		}
		delete stream;
	}
	CHECK_END
}	

int main(void) {
	test_RandomAccessStream();
	return 0;
}

