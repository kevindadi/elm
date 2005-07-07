/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test/plugin.cpp -- plugin for testing plugin feature.
 */

#include <elm/io.h>
#include <elm/system/Plugin.h>
#include "plugin.h"

using namespace elm;
using namespace elm::system;

extern bool startup_flag;
extern bool cleanup_flag;

// MyPlugin class
void MyPlugin::startup(void) {
	cout << "Startup performed !\n";
	startup_flag = true;
	cleanup_flag = false;
}

void MyPlugin::cleanup(void) {
	cout << "Cleanup performed !\n";
	startup_flag = false;
	cleanup_flag = true;
}

elm::String MyPlugin::get(void) {
	return "hello";
}

MyPlugin::MyPlugin(void): Plugin("myplugin", elm::Version(0, 0, 0)) {
	_description = "myplugin description";
	_licence = "myplugin licence";
	_plugin_version = Version(1, 2, 3);
}

// Plugin hook
MyPlugin my_plugin;

