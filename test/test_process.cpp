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

#include <windows.h>

using namespace elm;
using namespace elm::system;

// test_process()
void test_process(void) {
	CHECK_BEGIN("Process");

#if defined (__unix)
	ProcessBuilder builder("ls");
#elif defined(__WIN32) || defined(__WIN64)
	ProcessBuilder builder("C:\\Win16App\\MinGW\\bin\\gcc.exe");
#endif
	Pair<PipeInStream *, PipeOutStream *> pipes = System::pipe();
	builder.setOutput(pipes.snd);
	io::OutFileStream err_file("error.txt");
	builder.setError(&err_file);
	Process *process = builder.run();
	cout << "yapuka : " << GetLastError() << io::endl;
	delete pipes.snd;
	CHECK(process);
	cout << "yapuka : " << GetLastError() << io::endl;
	io::Input input(*pipes.fst);
	String line;
	input >> line;
	cout << "yapuka : " << GetLastError() << io::endl;
	while(line) {
		cout << "> " << line;
		input >> line;
	}
	process->wait();
	cout << "yapuka : " << GetLastError() << io::endl;
	CHECK_EQUAL(process->returnCode(), 0);
	
	CHECK_END;
}
