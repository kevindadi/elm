/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom/UTF8String.h -- UTF8String class.
 */
#ifndef ELM_XOM_UTF8STRING_H
#define ELM_XOM_UTF8STRING_H

#include <string.h>
#include <stdlib.h>

namespace elm { namespace xom {

// UTF8String class
class String {
public:
	typedef unsigned char char_t;
private:
	char_t *buf;
public:

	// Constructors
	inline String(const char *str);
	
	// Buffer management
	
	// Accessors
	inline char_t *buffer(void) const;
	inline void copy(void);
	inline void free(void);
	
	// Operators
	
};

// UTF8String inlines
inline String::String(const char *str)
: buf((char_t *)str) {
}

inline String::char_t *String::buffer(void) const {
	return buf;
}

inline void String::copy(void) {
	buf = (char_t *)strdup((char *)buf);
}

inline void String::free(void) {
	::free(buf);
	buf = (char_t *)"";
}

} } // elm::xom

#endif // ELM_XOM_UTF8STRING_H
