/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * util/test.h -- facilities for performing unit test.
 */
#ifndef ELM_UTIL_TEST_H
#define ELM_UTIL_TEST_H

#include <elm/string.h>

namespace elm {

// TestCase class
class TestCase {
	CString _name;
	int tests;
	int errors;
public:
	TestCase(CString name);
	void check(CString file, int line, CString text, bool result);
	bool require(CString file, int line, CString text, bool result);
	void complete(void);
};


// Macros
#define ELM_CHECK_BEGIN(name)	{ TestCase __case(name);
#define ELM_CHECK(tst)			__case.check(__FILE__, __LINE__, #tst, tst)
#define ELM_CHECK_END 			__case.complete(); }
#define ELM_REQUIRE(tst, action)	if(!__case.require(__FILE__, __LINE__, #tst, tst)) action
#ifndef ELM_NO_SHORTCUT
#	define CHECK_BEGIN(name) ELM_CHECK_BEGIN(name)
#	define CHECK(tst) ELM_CHECK(tst)
#	define REQUIRE(tst, action) ELM_REQUIRE(tst, action)
#	define CHECK_END ELM_CHECK_END
#endif

} // elm

#endif // ELM_UTIL_TEST_H
