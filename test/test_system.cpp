#include <elm/sys/System.h>
#include "../include/elm/test.h"

using namespace elm;

TEST_BEGIN(system)

	cerr << "core count: " << sys::System::coreCount() << io::endl;

TEST_END
