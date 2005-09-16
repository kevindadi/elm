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

// Linked plugin
class PluginTwo: public elm::system::Plugin {
protected:
	virtual void startup(void) {
		startup_flag = true;
		cleanup_flag = false;
		cout << "PluginTwo started.\n";
	}
	virtual void cleanup(void) {
		startup_flag = false;
		cleanup_flag = true;
		cout << "PluginTwo cleaned.\n";
	}
public:
	PluginTwo(void): Plugin("plugin_two", elm::Version(0, 0, 0), "my_plugin") {
		_description = "plugin_two description";
		_licence = "plugin_two licence";
		_plugin_version = Version(1, 2, 3);
	}
	virtual elm::String get(void) {
		return "bye";
	}
};
PluginTwo plugin_two;


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
	plugin2->unplug();
	CHECK(!startup_flag);
	CHECK(!cleanup_flag);
	
	// Check release
	int cnt = 0;
	while(!cleanup_flag) {
		plugin->unplug();
		cnt++;
	}
	CHECK(cnt == 17);
	CHECK(!startup_flag);
	CHECK(cleanup_flag);

	// Check static plugin
	{
		startup_flag = false;
		cleanup_flag = false;
		Plugin *plugin = plugger.plug("plugin_two");
		REQUIRE(plugin, return);
		CHECK(startup_flag);
		CHECK(!cleanup_flag);
		CHECK(plugin->name() == "plugin_two");
		CHECK(plugin->pluggerVersion() == Version(0, 0, 0));
		CHECK(plugin->description() == "plugin_two description");
		CHECK(plugin->licence() == "plugin_two licence");
		CHECK(plugin->pluginVersion() == Version(1, 2, 3));
		plugin->unplug();
		CHECK(startup_flag);
		CHECK(!cleanup_flag);
		cnt = 0;
		while(!cleanup_flag) {
			plugin->unplug();
			cnt++;
		}
		CHECK(cnt == 16);
		CHECK(!startup_flag);
		CHECK(cleanup_flag);
	}

	// Check iterator
	{
		Plugger::Iterator plugin(plugger);
		CHECK(plugin);
		CHECK(plugin == "plugin_two");
		plugin++;
		CHECK(plugin);
		CHECK(plugin == "myplugin");
		plugin++;
		CHECK(!plugin);
	}

	CHECK_END;
}
