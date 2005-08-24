/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test_plugin.cpp -- test the plugin feature.
 */

#include <elm/util/test.h>
#include <elm/system/Plugger.h>

using namespace elm;
using namespace elm::system;

bool startup_flag = false;
bool cleanup_flag = false;

// test routine
void test_plugin(void) {
	CHECK_BEGIN("Plugin");
	
	// Simple open
	Plugger plugger("my_plugin", Version(0, 0, 0), ".");
	Plugin *plugin = plugger.plug("myplugin");
	REQUIRE(plugin, return);
	CHECK(startup_flag);
	CHECK(!cleanup_flag);
	
	// Check content
	CHECK(plugin->name() == "myplugin");
	CHECK(plugin->pluggerVersion() == Version(0, 0, 0));
	CHECK(plugin->description() == "myplugin description");
	CHECK(plugin->licence() == "myplugin licence");
	CHECK(plugin->pluginVersion() == Version(1, 2, 3));
	
	// Check reopen
	startup_flag = false;
	Plugin *plugin2 = plugger.plug("myplugin");
	REQUIRE(plugin2, return)
	CHECK(!startup_flag);
	CHECK(!cleanup_flag);
	CHECK(plugin == plugin2);
	plugin2->release();
	CHECK(!startup_flag);
	CHECK(!cleanup_flag);
	
	// Check release
	plugin->release();
	CHECK(!startup_flag);
	CHECK(cleanup_flag);

	// Check iterator
	int count = 0;
	for(Plugger::Iterator plugin(plugger); plugin; plugin++, count++)
		CHECK(plugin == "myplugin");
	CHECK(count == 1);	
	CHECK_END;
}
