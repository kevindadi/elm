/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/Output.h -- interface for Output class.
 */
#ifndef ELM_IO_OUTPUT_H
#define ELM_IO_OUTPUT_H

#include <elm/utility.h>
#include <elm/io/OutStream.h>

namespace elm { namespace io {

// Output class
class Output {
	OutStream& strm;
	char *horner(char *p, unsigned long val, int base);
public:
	inline Output(void): strm(stdout) { };
	inline Output(OutStream& stream): strm(stream) { };
	inline OutStream& stream(void) const { return strm; };
	
	void print(bool value);
	void print(char chr);
	void print(int value);
	void print(unsigned int value);
	void print(double value);
	void print(void *value);
	inline void print(const char *str) { print(CString(str)); };
	void print(const CString str);
	void print(const String& str);
	void flush(void);
	
	inline Output& operator<<(bool value) { print(value); return *this; };
	inline Output& operator<<(char value) { print(value); return *this; };
	inline Output& operator<<(int value) { print(value); return *this; };
	inline Output& operator<<(unsigned int value) { print(value); return *this; };
	inline Output& operator<<(double value) { print(value); return *this; };
	inline Output& operator<<(void *value) { print(value); return *this; };
	inline Output& operator<<(const char *value) { print(value); return *this; };
	inline Output& operator<<(const CString value) { print(value); return *this; };
	inline Output& operator<<(const String& value) { print(value); return *this; };
};

} } // elm::io

#endif	// ELM_IO_OUTPUT_H
