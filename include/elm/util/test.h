/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * util/test.h -- facilities for performing unit test.
 */
#ifndef ELM_UTIL_TEST_H
#define ELM_UTIL_TEST_H

#include <elm/string.h>
#include <elm/io.h>

namespace elm {

// TestCase class
class TestCase {
	CString _name;
	int tests;
	int errors;
public:
	TestCase(CString name);
	void test(CString file, int line, CString text);
	void failed(void);
	void succeeded(void);
	void check(CString file, int line, CString text, bool result);
	bool require(CString file, int line, CString text, bool result);
	template <class T> inline void check_equal(CString file, int line, 
		CString text, const T& result, const T& reference);
	void complete(void);
};


// Inlines
template <class T>
inline void TestCase::check_equal(CString file, int line, CString text,
const T& result, const T& reference) {
	check(file, line, text, result == reference);
	if(result != reference)
		cout << '\t' << result << " != " << reference << "\n";
}


// Macros
#define ELM_CHECK_BEGIN(name)	{ elm::TestCase __case(name);
#define ELM_CHECK(tst)			__case.check(__FILE__, __LINE__, #tst, tst)
#define ELM_CHECK_END 			__case.complete(); }
#define ELM_REQUIRE(tst, action)	if(!__case.require(__FILE__, __LINE__, #tst, tst)) action
#define ELM_CHECK_EQUAL(res, ref)	__case.check_equal(__FILE__, __LINE__, #res " == " #ref, res, ref)
#define ELM_CHECK_EXCEPTION(exn, stat)	{ __case.test(__FILE__, __LINE__, #stat); \
	try { stat; __case.failed(); } catch(exn) { __case.succeeded(); } }
#ifndef ELM_NO_SHORTCUT
#	define CHECK_BEGIN(name) ELM_CHECK_BEGIN(name)
#	define CHECK(tst) ELM_CHECK(tst)
#	define REQUIRE(tst, action) ELM_REQUIRE(tst, action)
#	define CHECK_EQUAL(res, ref) ELM_CHECK_EQUAL(res, ref)
#	define CHECK_END ELM_CHECK_END
#	define CHECK_EXCEPTION(exn, stat) ELM_CHECK_EXCEPTION(exn, stat)
#endif

} // elm

#endif // ELM_UTIL_TEST_H
