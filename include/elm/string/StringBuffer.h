/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/string/StringBuffer.h -- interface for StringBuffer class.
 */
#ifndef ELM_STRING_STRING_BUFFER_H
#define ELM_STRING_STRING_BUFFER_H

#include <stdarg.h>
#include <elm/string.h>
#include <elm/block/DynBlock.h>

namespace elm {

// StringBuffer class
class StringBuffer {
	block::DynBlock buf;
public:
	inline StringBuffer(int capacity = 64, int increment = 32);
	inline String toString(void);
	inline void put(char chr);
	inline void put(const char *block, int size);
	inline void put(const char *block);
	inline void put(const CString str);
	inline void put(const String& str);
	void print(const char *fmt, va_list args);
	inline void print(const char *fmt, ...);
	inline int length(void) const;
	inline void reset(void);
};


// Inlines
inline StringBuffer::StringBuffer(int capacity, int increment)
: buf(capacity, increment) {
	String::buffer_t str = { 0 };
	buf.put((char *)&str, sizeof(unsigned short));
}
inline String StringBuffer::toString(void) {
	int len = length();
	put('\0');
	return String((String::buffer_t *)buf.detach(), sizeof(unsigned short), len);
}
inline void StringBuffer::put(char chr) {
	put(&chr, 1);
}
inline void StringBuffer::put(const char *block, int size) {
	buf.put(block, size);
}
inline void StringBuffer::put(const char *block) {
	put(CString(block));
}
inline void StringBuffer::put(const CString str) {
	buf.put(str.chars(), str.length());
}
inline void StringBuffer::put(const String& str) {
	put(str.chars(), str.length());
}
inline int StringBuffer::length(void) const {
	return buf.size() - sizeof(unsigned short);
}
inline void StringBuffer::reset(void) {
	buf.setSize(sizeof(String::buffer_t));
}
inline void StringBuffer::print(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	print(fmt, args);
	va_end(args);
}

} // elm

#endif // ELM_STRING_STRING_BUFFER_H
