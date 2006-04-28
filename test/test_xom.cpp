/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_xom.cpp -- unit tests for elm::xom classes.
 */

#include <elm/util/test.h>
#include <elm/xom/Builder.h>
#include <elm/xom/Document.h>

using namespace elm;
using namespace xom;

// test_xom()
void test_xom(void) {
	CHECK_BEGIN("XOM");
	Builder builder;
	Document *doc = builder.build("file.xml");
	CHECK(doc);
	Element *root_element = doc->getRootElement();
	CHECK(root_element);
	CHECK_END;
}

