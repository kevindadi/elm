#include <elm/sys/System.h>
#include "../include/elm/test.h"

using namespace elm;

TEST_BEGIN(system)

	cerr << "core count: " << sys::System::coreCount() << io::endl;

	// remove a single file
	{
		sys::Path p = "system.file";
		io::OutStream *out = p.write();
		out->write('E');
		delete out;
		FAIL_ON_EXCEPTION(sys::SystemException,
			sys::System::remove(p));
		CHECK(!p.exists());
	}

	// remove an empty directory
	{
		sys::Path p = "system.dir";
		sys::System::makeDir(p);
		FAIL_ON_EXCEPTION(sys::SystemException,
			sys::System::remove(p));
		CHECK(!p.exists());
	}

	// remove a directory full of files
	{
		sys::Path p = "system.dir";
		sys::System::makeDir(p);
		for(int i = 0; i < 10; i++) {
			io::OutStream *out = (p / string(_ << "system-" << i << ".file")).write();
			out->write('0' + i);
			delete out;
		}
		FAIL_ON_EXCEPTION(sys::SystemException,
			sys::System::remove(p));
		CHECK(!p.exists());
	}

	// remove files and directories
	{
		sys::Path p = "system.dir";
		sys::System::makeDir(p);
		for(int j = 0; j < 5; j++) {
			Path dp = p / string(_ << "dir-" << j);
			sys::System::makeDir(dp);
			for(int i = 0; i < 5; i++) {
				io::OutStream *out = (dp / string(_ << "system-" << i << ".file")).write();
				out->write('0' + i);
				delete out;
			}
		}
		FAIL_ON_EXCEPTION(sys::SystemException,
			sys::System::remove(p));
		CHECK(!p.exists());
	}

TEST_END
