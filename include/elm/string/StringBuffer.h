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
#include <elm/io/BlockOutStream.h>
#include <elm/io/Output.h>

namespace elm {

// StringBuffer class
class StringBuffer: public io::Output {
	io::BlockOutStream stream;
public:
	inline StringBuffer(int capacity = 64, int increment = 32);
	inline String toString(void);
	/*inline void put(char chr);
	inline void put(const char *block, int size);
	inline void put(const char *block);
	inline void put(const CString str);
	inline void put(const String& str);
	inline void format(const char *fmt, ...);
	inline void formatArg(const char *fmt, va_list args);*/
	inline int length(void) const;
	inline void reset(void);
};


// Inlines
inline StringBuffer::StringBuffer(int capacity, int increment)
: io::Output(stream), stream(capacity, increment) {
	String::buffer_t str = { 0 };
	stream.write((char *)&str, sizeof(unsigned short));
}
inline String StringBuffer::toString(void) {
	int len = length();
	stream.write('\0');
	return String((String::buffer_t *)stream.detach(), sizeof(unsigned short), len);
}
/*inline void StringBuffer::put(char chr) {
	output.print(chr);
}
inline void StringBuffer::put(const char *block, int size) {
	stream.write(block, size);
}
inline void StringBuffer::put(const char *block) {
	output.print(block);
}
inline void StringBuffer::put(const CString str) {
	output.print(str);
}
inline void StringBuffer::put(const String& str) {
	output.print(str);
}*/
inline int StringBuffer::length(void) const {
	return stream.size() - sizeof(unsigned short);
}
inline void StringBuffer::reset(void) {
	stream.setSize(sizeof(String::buffer_t));
}
/*inline void StringBuffer::format(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	output.formatArg(fmt, args);
	va_end(args);
}
inline void StringBuffer::formatArg(const char *fmt, va_list args) {
	output.formatArg(fmt, args);
}*/

} // elm

#endif // ELM_STRING_STRING_BUFFER_H
