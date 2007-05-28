/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS.
 *
 * autostr class interface
 */
#ifndef ELM_STRING_AUTOSTRING_H
#define ELM_STRING_AUTOSTRING_H

#include <elm/string/StringBuffer.h>
#ifdef ELM_TEST_AUTOSTR
#	include <elm/io.h>
#endif

namespace elm {

// AutoString class
class AutoString {
public:
	template <class T>
	inline AutoString& operator<<(const T& value)
		{ buf << value; return *this; }

	inline operator String(void) {
		String result = buf.toString();
		delete this;
		return result;
	}

	// Debugging
	#ifdef ELM_TEST_AUTOSTR
		inline AutoString(void) { cout << "allocated " << this << io::endl; }
		inline ~AutoString(void) { cout << "fried " << this << io::endl; }
	#endif

private:
	StringBuffer buf;
};

// AutoStringStartup class
class AutoStringStartup {
public:
	template <class T>
	inline AutoString& operator<<(const T& value) {
		AutoString *str = new AutoString();
		return (*str) << value;
	}
};

// autostr object
extern AutoStringStartup autostr;
extern AutoStringStartup &_;

// Even faster autostring
#ifndef ELM_AUTOSTR_FAST_NO
template <class T>
inline AutoString& operator<<(CString string, const T& value)
	{ return autostr << string << value; }
template <class T>
inline AutoString& operator<<(const String& string, const T& value)
	{ return autostr << string << value; }
#endif // ELM_AUTOSTR_FAST_NO

} // elm

#endif // ELM_STRING_AUTOSTRING_H
