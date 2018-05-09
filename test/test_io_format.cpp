/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_io_format.cpp -- formatted io classes test.
 */

#include <elm/io.h>
#include <elm/string.h>
#include <elm/io/BlockInStream.h>
#include <elm/test.h>
#include <elm/io/FileInput.h>
#include <elm/io/StringOutput.h>
#include <elm/io/FileOutput.h>
#include <elm/io/RandomAccessStream.h>
#include <elm/checksum/Fletcher.h>
#include <elm/io/InFileStream.h>
#include <elm/sys/System.h>

using namespace elm;
using namespace elm::io;

inline String do_test(IntFormat fmt) {
	StringBuffer buf;
	buf << fmt;
	return buf.toString();
}

// Entry point
TEST_BEGIN(io_format)
	
	// Testing the base
	CHECK_EQUAL(do_test(666), String("666"));
	CHECK_EQUAL(do_test(hex(666)), String("29a"));
	CHECK_EQUAL(do_test(bin(666)), String("1010011010"));
		
	// Testing width
	CHECK_EQUAL(do_test(width(8, 666)), String("666     "));
	CHECK_EQUAL(do_test(width(2, 666)), String("666"));
	
	// Testing alignment
	CHECK_EQUAL(do_test(left(width(8, 666))), String("666     "));
	CHECK_EQUAL(do_test(right(width(8, 666))), String("     666"));
	CHECK_EQUAL(do_test(center(width(8, 666))), String("  666   "));
	CHECK_EQUAL(do_test(left(666)), String("666"));
	CHECK_EQUAL(do_test(right(666)), String("666"));
	CHECK_EQUAL(do_test(center(666)), String("666"));
	
	// Testing padding
	CHECK_EQUAL(do_test(left(width(8, pad('!', 666)))), String("666!!!!!"));
	CHECK_EQUAL(do_test(right(width(8, pad('!', 666)))), String("!!!!!666"));
	CHECK_EQUAL(do_test(center(width(8, pad('!', 666)))), String("!!666!!!"));
	
	// Test special numbers
	CHECK_EQUAL(do_test(center(width(8, pad('!', -666)))), String("!!-666!!"));
	CHECK_EQUAL(do_test(center(width(8, pad('!', 0)))), String("!!!0!!!!"));
	CHECK_EQUAL(do_test(hex(t::uint32(-1))), String("ffffffff"));
	CHECK_EQUAL(do_test(hex(t::int32(-1))), String("ffffffff"));
	
	// Test upper case
	CHECK_EQUAL(do_test(hex(uppercase(666))), String("29A"));
	
	// Type test
	CHECK_EQUAL(do_test(hex((char)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((signed char)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((unsigned char)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((short)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((signed short)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((unsigned short)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((long)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((signed long)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((unsigned long)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((int)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((signed int)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((unsigned int)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((signed)111)), String("6f"));
	CHECK_EQUAL(do_test(hex((unsigned)111)), String("6f"));
	
	BlockInStream instream("666", 3);
	Input in(instream);
	int x;
	FAIL_ON_EXCEPTION(IOException, in >> x);
	CHECK_EQUAL(x, 666);

	{
		string r = _ << fmt(666);
		CHECK_EQUAL(r, string("666"));
		string rr = _ << fmt(1.2);
		CHECK_EQUAL(rr, string("1.2"));
		string rrr = _ << fmt("ok");
		CHECK_EQUAL(rrr, string("ok"));
	}


	// test StringInput
	{
		string s = "666";
		io::StringInput in(s);
		int x;
		in >> x;
		CHECK_EQUAL(x, 666);
	}

	// test FileInput
	{
		io::FileInput in("io.txt");
		int x;
		in >> x;
		CHECK_EQUAL(x, 666);
	}

	// test StringOutput
	{
		io::StringOutput out;
		out << 666;
		string s = out.toString();
		io::StringInput in(s);
		int x;
		in >> x;
		CHECK_EQUAL(x, 666);
	}

	// test FileOutput
	{
		sys::Path p = "temp-io.txt";
		io::FileOutput out(p);
		out << 666;
		out.flush();
		io::FileInput in(p);
		int x;
		in >> x;
		CHECK_EQUAL(x, 666);
		p.remove();
	}

	// RandomAccessStream test
	{
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
			for(int i = 0; i < (int)(sizeof(data) / sizeof(int)); i++)
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

	}

	// BufferedInStream test
	{
		{
			InFileStream in1("test_io");
			InFileStream _in("test_io");
			BufferedInStream in2(_in, 128);
			char buf1[2], buf2[2];
			bool done = true;
			while(1) {
				int size1 = in1.read(buf1, 2);
				int size2 = in2.read(buf2, 2);
				done = size1 == size2;
				if(!done)
					break;
				if(size1 <= 0)
					break;
				done = buf1[0] == buf2[0] && buf1[1] == buf2[1];
				if(!done)
					break;
			}
			CHECK(done);
		}

		unsigned long sum1;
		{
			checksum::Fletcher sum;
			InFileStream in("test_io");
			CHECK(in.isReady());
			sum.put(in);
			sum1 = sum.sum();
		}
		unsigned long sum2;
		{
			checksum::Fletcher sum;
			InFileStream in("test_io");
			CHECK(in.isReady());
			BufferedInStream buf(in, 129);
			sum.put(buf);
			sum2 = sum.sum();
		}
		CHECK(sum1 == sum2);
		cerr << "sum1 = " << io::hex(sum1) << ", sum2 = " << io::hex(sum2) << io::endl;
	}

	// BufferedOutStream test
	{
		// copy the file
		{
	#		define BUF_SIZE 64
			char buf[BUF_SIZE];
			InStream *in = sys::System::readFile("file.xml");
			OutStream *str = sys::System::createFile("out.xml");
			BufferedOutStream out(*str, 32);
			int len;
			while((len = in->read(buf, sys::System::random(BUF_SIZE))) > 0)
				out.write(buf, len);
		}

		// compare the file
		{
			bool ok = true;
			int res1, res2;
			char buf1[BUF_SIZE], buf2[BUF_SIZE];
			InStream *in1 = sys::System::readFile("file.xml");
			InStream *in2 = sys::System::readFile("out.xml");
			while(1) {
				res1 = in1->read(buf1, BUF_SIZE);
				res2 = in2->read(buf2, BUF_SIZE);
				if(res1 != res2)
					break;
				if(res1 == 0)
					break;
				if(memcmp(buf1, buf2, BUF_SIZE) != 0) {
					ok = false;
					break;
				}
			}
			CHECK(res1 == res2);
			CHECK(ok);
		}

	}

	// Input test
	{
#		define TINPUT(t, c) \
		{ \
			io::BlockInStream stream(#c); \
			io::Input in(stream); \
			t v; \
			in >> v; \
			CHECK(v == c); \
		}

	try {
		TINPUT(long, 666);
		TINPUT(long, -666);
		TINPUT(long, +666);
		TINPUT(unsigned long, 666);

		TINPUT(long, 0xff);
		TINPUT(long, -0xff);
		TINPUT(long, +0xff);
		TINPUT(unsigned long, 0xff);

		TINPUT(long long, 666);
		TINPUT(long long, -666);
		TINPUT(long long, +666);
		TINPUT(unsigned long long, 666);

		TINPUT(long long, 0xff);
		TINPUT(long long, -0xff);
		TINPUT(long long, +0xff);
		TINPUT(unsigned long long, 0xff);
	}
	catch(elm::Exception& e) {
		cerr << "ERROR: exception raised: " << e.message() << io::endl;
	}


	}

	// StringInput test
	{
		{
			StringInput in("128");
			t::int32 v;
			in >> v;
			CHECK_EQUAL(v, 128);
		}

		{
			string in = "128";
			t::int32 v;
			in >> v;
			CHECK_EQUAL(v, 128);
		}

		{
			string in = "0x80";
			t::int32 v;
			in >> v;
			CHECK_EQUAL(v, 0x80);
		}

		{
			string in = "aa";
			t::int32 v;
			CHECK_EXCEPTION(elm::io::IOException, in >> v);
		}

		{
			string in = "0xffffffffff";
			t::int32 v;
			CHECK_EXCEPTION(elm::io::IOException, in >> v);
		}

	}

TEST_END

