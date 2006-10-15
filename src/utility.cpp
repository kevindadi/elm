/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * collection.cc -- collection classes implementation.
 */

#include <elm/utility.h>

namespace elm {

// int_comp
class IntComparator: public Comparator<int> {
	virtual int compare(int v1, int v2) {
		return v1 > v2 ? 1 : (v1 == v2 ? 0 : -1);
	};
};
static IntComparator int_comp_obj;
template <> Comparator<int>& Comparator<int>::def = int_comp_obj;

// pointer_comp
class PointerComparator: public Comparator<void *> {
	virtual int compare(void *v1, void *v2) {
		return v1 > v2 ? 1 : (v1 == v2 ? 0 : -1);
	};
};
static PointerComparator pointer_comp_obj;
template <> Comparator<void *>& Comparator<void *>::def = pointer_comp_obj;

// cstring_comp
class CStringComparator: public Comparator<CString> {
	virtual int compare(CString v1, CString v2) {
		return v1.compare(v2);
	};
};
static CStringComparator cstring_comp_obj;
template <> Comparator<CString>& Comparator<CString>::def = cstring_comp_obj;

// string_comp
class StringComparator: public Comparator<String> {
	virtual int compare(String v1, String v2) {
		return v1.compare(v2);
	};
};
static StringComparator string_comp_obj;
template <> Comparator<String>& Comparator<String>::def = string_comp_obj;


/**
 * @class Exception <elm/utility.h>
 * The base class of exceptions in Elm.
 */


/**
 */
Exception::~Exception(void) {
}


/**
 * Return a message describing the exception.
 * @return	Exception message.
 */
String Exception::message(void) {
	return "";	
}

};
