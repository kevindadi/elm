/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom/String.h -- String class.
 */
#ifndef ELM_XOM_STRING_H
#define ELM_XOM_STRING_H

#include <string.h>
#include <elm/string.h>
#include <elm/io.h>
#include <stdlib.h>

namespace elm { namespace xom {

/**
 * XOM character type.
 */
typedef unsigned char char_t;

// String class
class String: public CString {
public:

	// Constructors
	inline String(void);
	inline String(const char *str);
	inline String(const char_t *str);
	inline String(const CString& str);
	inline String(const String& str);
	
	// Buffer management
	
	// Accessors
	inline void copy(void);
	inline void free(void);
	
	// Operators
	inline String& operator=(const String& str);
	inline operator CString(void) const;
	inline operator char_t *(void) const;
};


// String inlines
inline String::String(void) {
}

inline String::String(const char *str)
: CString(str) {
}

inline String::String(const char_t *str)
: CString((const char *)str) {
}

inline String::String(const CString& str)
: CString(str) {
}

inline String::String(const String& str): CString(str) {
}

inline void String::copy(void) {
	buf = strdup(chars());
}

inline void String::free(void) {
	::free((void *)buf);
	buf = "";
}

inline String& String::operator=(const String& str) {
	buf = str.buf;
	return *this;
}

inline String::operator CString(void) const {
	return (const char *)buf;
}

inline String::operator char_t *(void) const {
	return (char_t *)buf;
}

} } // elm::xom

#endif // ELM_XOM_STRING_H
