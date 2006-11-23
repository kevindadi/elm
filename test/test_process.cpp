/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/test_lock.cpp -- unit tests for elm::Lock class.
 */

#include <elm/util/test.h>
#include <elm/system/ProcessBuilder.h>
#include <elm/system/System.h>
#include <elm/io.h>
#include <elm/io/OutFileStream.h>

using namespace elm;
using namespace elm::system;

// test_process()
void test_process(void) {
	CHECK_BEGIN("Process");

	ProcessBuilder builder("ls");
	Pair<PipeInStream *, PipeOutStream *> pipes = System::pipe();
	builder.setOutput(pipes.snd);
	io::OutFileStream err_file("error.txt");
	builder.setError(&err_file);
	Process *process = builder.run();
	delete pipes.snd;
	CHECK(process);
	io::Input input(*pipes.fst);
	String line;
	input >> line;
	while(line) {
		cout << "> " << line;
		input >> line;
	}
	process->wait();
	CHECK_EQUAL(process->returnCode(), 0);
	
	CHECK_END;
}
