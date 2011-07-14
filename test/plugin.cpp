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

#if !defined(__WIN32) && !defined(__WIN64)
extern bool startup_flag;
extern bool cleanup_flag;
#endif

// MyPlugin class
void MyPlugin::startup(void) {
	cout << "Startup performed !\n";
#if !defined(__WIN32) && !defined(__WIN64)
	startup_flag = true;
	cleanup_flag = false;
#endif
}

void MyPlugin::cleanup(void) {
	cout << "Cleanup performed !\n";
#if !defined(__WIN32) && !defined(__WIN64)
	startup_flag = false;
	cleanup_flag = true;
#endif
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

