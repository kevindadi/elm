/*
 * $Id$
 * Copyright (c) 2004-2006, IRIT-UPS.
 *
 * elm/io/Output.h -- interface for Output class.
 */
#ifndef ELM_IO_OUTPUT_H
#define ELM_IO_OUTPUT_H

#include <elm/system/SystemIO.h>
#include <elm/util/VarArg.h>

namespace elm { namespace io {

// alignment_t enum
typedef enum alignment_t {
	NONE = 0,
	LEFT,
	CENTER,
	RIGHT
} alignment_t;


// IntFormat class
class IntFormat {
	inline void init(bool _sign);
public:
	inline IntFormat(char value);
	inline IntFormat(unsigned char value);
	inline IntFormat(short value);
	inline IntFormat(unsigned short value);
	inline IntFormat(int value);
	inline IntFormat(unsigned int value);
	inline IntFormat(long value);
	inline IntFormat(unsigned long value);
	
	long val;
	unsigned char base;
	unsigned char width;
	unsigned align : 6;
	unsigned upper : 1;
	unsigned sign : 1;
	char pad;
};


// Output class
class Output {
	OutStream *strm;
	char *horner(char *p, unsigned long val, int base, char enc = 'a');
	char *horner(char *p, unsigned long long val, int base);
public:
	inline Output(void): strm(&stdout) { };
	inline Output(OutStream& stream): strm(&stream) { };
	inline OutStream& stream(void) const { return *strm; };
	inline void setStream(OutStream& stream) { strm = &stream; };
	void flush(void);
	
	void print(bool value);
	void print(char chr);
	void print(long value);
	void print(unsigned long value);
	void print(long long value);
	void print(unsigned long long value);
	void print(double value);
	void print(void *value);
	inline void print(const char *str) { print(CString(str)); };
	void print(const CString str);
	void print(const String& str);
	void print(const IntFormat fmt);
	void format(CString fmt, ...);
	void format(CString fmt, VarArg& args);
	
	inline Output& operator<<(bool value) { print(value); return *this; };
	inline Output& operator<<(char value) { print(value); return *this; };
	inline Output& operator<<(int value) { print((long)value); return *this; };
	inline Output& operator<<(unsigned int value) { print((unsigned long)value); return *this; };
	inline Output& operator<<(long value) { print(value); return *this; };
	inline Output& operator<<(unsigned long value) { print(value); return *this; };
	inline Output& operator<<(long long value) { print(value); return *this; };
	inline Output& operator<<(unsigned long long value) { print(value); return *this; };
	inline Output& operator<<(double value) { print(value); return *this; };
	inline Output& operator<<(void *value) { print(value); return *this; };
	inline Output& operator<<(const char *value) { print(value); return *this; };
	inline Output& operator<<(const CString value) { print(value); return *this; };
	inline Output& operator<<(const String& value) { print(value); return *this; };
	inline Output& operator<<(IntFormat value) { print(value); return *this; };
};


// End-of-line
const char endl = '\n';

// IntFormat Inlines
inline void IntFormat::init(bool _sign) {
	base = 10;
	width = 0;
	align = LEFT;
	pad = ' ';
	upper = false;
	sign = _sign;
};


inline IntFormat::IntFormat(long value): val(value) {
	init(true);
}

inline IntFormat::IntFormat(unsigned long value): val(value) {
	init(false);
}

inline IntFormat::IntFormat(int value): val(value) {
	init(true);
}

inline IntFormat::IntFormat(unsigned int value): val(value) {
	init(false);
}

inline IntFormat::IntFormat(char value): val(value) {
	init(true);
}

inline IntFormat::IntFormat(unsigned char value): val(value) {
	init(false);
}
	
inline IntFormat::IntFormat(short value): val(value) {
	init(true);
}

inline IntFormat::IntFormat(unsigned short value): val(value) {
	init(false);
}

inline IntFormat base(int base, IntFormat fmt) {
	fmt.base = base;
	return fmt;
}

inline IntFormat bin(IntFormat fmt) {
	fmt.base = 2;
	return fmt;
}

inline IntFormat hex(IntFormat fmt) {
	fmt.base = 16;
	return fmt;
}

inline IntFormat width(int width, IntFormat fmt) {
	fmt.width = width;
	return fmt;
}

inline IntFormat align(alignment_t align, IntFormat fmt) {
	fmt.align = align;
	return fmt;
}

inline IntFormat left(IntFormat fmt) {
	fmt.align = LEFT;
	return fmt;
}

inline IntFormat right(IntFormat fmt) {
	fmt.align = RIGHT;
	return fmt;
}

inline IntFormat center(IntFormat fmt) {
	fmt.align = CENTER;
	return fmt;
}

inline IntFormat pad(char pad, IntFormat fmt) {
	fmt.pad = pad;
	return fmt;
}

inline IntFormat uppercase(IntFormat fmt) {
	fmt.upper = true;
	return fmt;
}

inline IntFormat lowercase(IntFormat fmt) {
	fmt.upper = false;
	return fmt;
}

inline IntFormat pointer(const void *p) {
	return width(8, pad('0', hex((unsigned long)p)));
}

} } // elm::io

#endif	// ELM_IO_OUTPUT_H
