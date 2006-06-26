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
class String {
protected:
	const char_t *buf;
	static const char_t null_buf[1];
public:

	// Constructors
	inline String(void);
	inline String(const char *str);
	inline String(const char_t *str);
	inline String(const String& string);
	
	// Buffer management
	
	// Accessors
	inline const char_t *buffer(void) const;
	inline void copy(void);
	inline void free(void);
	
	// Operators
	inline operator const char *(void) const;
	inline String& operator=(const String& string);
	inline operator CString(void) const;
};

inline elm::io::Output& operator<<(elm::io::Output& out, const String& string) {
	out.print((const char *)(string.buffer()));
	return out;
}


// String inlines
inline String::String(void): buf(null_buf) {
}

inline String::String(const char *str)
: buf(str ? (char_t *)str : null_buf) {
}

inline String::String(const char_t *str)
: buf(str ? str : null_buf) {
}

inline String::String(const String& string): buf(string.buf) {
}


inline const char_t *String::buffer(void) const {
	return buf;
}

inline void String::copy(void) {
	buf = (char_t *)strdup((char *)buf);
}

inline void String::free(void) {
	if(buf != null_buf) {
		::free((void *)buf);
		buf = null_buf;
	}
}

inline String::operator const char *(void) const {
	return (const char *)buf;
}

inline String& String::operator=(const String& string) {
	buf = string.buf;
}

inline String::operator CString(void) const {
	return (const char *)buf;
}

} } // elm::xom

#endif // ELM_XOM_STRING_H
