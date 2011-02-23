/*
 * $Id$
 * Copyright (c) 2004-2006, IRIT-UPS.
 *
 * elm/io/Output.h -- interface for Output class.
 */
#ifndef ELM_IO_OUTPUT_H
#define ELM_IO_OUTPUT_H

#include <elm/types.h>
#include <elm/system/SystemIO.h>
#include <elm/util/VarArg.h>
#include <elm/string/String.h>
#include <elm/string/CString.h>

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
#	ifndef __LP64__
		inline IntFormat(long value);
		inline IntFormat(unsigned long value);
#	endif

	t::int32 val;
	unsigned char base;
	unsigned char width;
	unsigned align : 5;
	unsigned upper : 1;
	unsigned sign : 1;
	unsigned displaySign : 1;
	char pad;
};


// Output class
class Output {
	OutStream *strm;
	char *horner(char *p, t::uint32 val, int base, char enc = 'a');
	char *horner(char *p, t::uint64 val, int base);
public:
	inline Output(void): strm(&out) { };
	inline Output(OutStream& stream): strm(&stream) { };
	inline OutStream& stream(void) const { return *strm; };
	inline void setStream(OutStream& stream) { strm = &stream; };
	void flush(void);

	void print(bool value);
	void print(char chr);
	void print(t::int32 value);
	void print(t::uint32 value);
	void print(t::int64 value);
	void print(t::uint64 value);
	void print(double value);
	void print(void *value);
	inline void print(const char *str) { print(CString(str)); };
	void print(const CString str);
	void print(const String& str);
	void print(const IntFormat fmt);
	void format(CString fmt, ...);
	void format(CString fmt, VarArg& args);
};


// operators accesses
template <class T> inline Output& operator<<(Output& out, const T& v)
	{ out.print("<not printable>"); return out; }
template <class T> inline Output& operator<<(Output& out, T *v)
	{ out.print((void *)v); return out; }
inline Output& operator<<(Output& out, bool value) { out.print(value); return out; };
inline Output& operator<<(Output& out, char value) { out.print(value); return out; };
inline Output& operator<<(Output& out, unsigned char value) { out.print(t::uint32(value)); return out; };
inline Output& operator<<(Output& out, short value) { out.print(t::int32(value)); return out; };
inline Output& operator<<(Output& out, unsigned short value) { out.print(t::uint32(value)); return out; };
inline Output& operator<<(Output& out, int value) { out.print(t::int32(value)); return out; };
inline Output& operator<<(Output& out, unsigned int value) { out.print(t::uint32(value)); return out; };
#ifndef __LP64__
	inline Output& operator<<(Output& out, long value) { out.print(t::int32(value)); return out; };
	inline Output& operator<<(Output& out, unsigned long value) { out.print(t::uint32(value)); return out; };
#else
	inline Output& operator<<(Output& out, long value) { out.print(t::int64(value)); return out; };
	inline Output& operator<<(Output& out, unsigned long value) { out.print(t::uint64(value)); return out; };
#endif
inline Output& operator<<(Output& out, long long value) { out.print(t::int64(value)); return out; };
inline Output& operator<<(Output& out, unsigned long long value) { out.print(t::uint64(value)); return out; };
inline Output& operator<<(Output& out, float value) { out.print(value); return out; };
inline Output& operator<<(Output& out, double value) { out.print(value); return out; };
inline Output& operator<<(Output& out, const char *value) { out.print(value); return out; };
inline Output& operator<<(Output& out, char *value) { out.print(value); return out; };
inline Output& operator<<(Output& out, const CString value) { out.print(value); return out; };
inline Output& operator<<(Output& out, const string& value) { out.print(value); return out; };
inline Output& operator<<(Output& out, IntFormat value) { out.print(value); return out; };


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
	displaySign = false;
};

#ifndef __LP64__
	inline IntFormat::IntFormat(long value): val(value) {
		init(true);
	}

	inline IntFormat::IntFormat(unsigned long value): val(value) {
		init(false);
	}
#endif

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

inline IntFormat::IntFormat(signed short value): val(value) {
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
	fmt.sign = false;
	return fmt;
}

inline IntFormat oct(IntFormat fmt) {
	fmt.base = 8;
	fmt.sign = false;
	return fmt;
}

inline IntFormat hex(IntFormat fmt) {
	fmt.base = 16;
	fmt.sign = false;
	return fmt;
}

inline IntFormat sign(IntFormat fmt) {
	fmt.displaySign = true;
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

#ifndef __LP64__
	inline IntFormat pointer(const void *p) {
		return width(8, pad('0', hex(t::uint32(p))));
	}
#endif

} } // elm::io

#endif	// ELM_IO_OUTPUT_H
