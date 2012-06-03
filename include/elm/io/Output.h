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
	inline void init(bool s)  {
		_base = 10;
		_width = 0;
		_align = LEFT;
		_pad = ' ';
		_upper = false;
		_sign = s;
		_displaySign = false;
	}
public:
	inline IntFormat(void): _val(0) { init(true); }
	inline IntFormat(t::int8	value): _val(value) { init(true); }
	inline IntFormat(t::uint8	value): _val(value) { init(false); }
	inline IntFormat(t::int16	value): _val(value) { init(true); }
	inline IntFormat(t::uint16	value): _val(value) { init(false); }
	inline IntFormat(t::int32	value): _val(value) { init(true); }
	inline IntFormat(t::uint32	value): _val(value) { init(false); }
	inline IntFormat(t::int64	value): _val(value) { init(true); }
	inline IntFormat(t::uint64	value): _val(value) { init(false); }

	inline IntFormat operator()(t::int8	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::uint8	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::int16	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::uint16	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::int32	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::uint32	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::int64	value) { IntFormat f = *this; f._val = value; return f; }
	inline IntFormat operator()(t::uint64	value) { IntFormat f = *this; f._val = value; return f; }

	inline IntFormat base(int b) { _base = b; return *this; }
	inline IntFormat bin(void) { _base = 2; _sign = false; return *this; }
	inline IntFormat oct(void) { _base = 8; _sign = false; return *this; }
	inline IntFormat dec(void) { _base = 10; return *this; }
	inline IntFormat hex(void) { _base = 16; _sign = false; return *this; }
	inline IntFormat width(int w) { _width = w; return *this; }
	inline IntFormat align(alignment_t a) { _align = a; return *this; }
	inline IntFormat left(void) { _align = LEFT; return *this; }
	inline IntFormat center(void) { _align = CENTER; return *this; }
	inline IntFormat right(void) { _align = RIGHT; return *this; }
	inline IntFormat upper(void) { _upper = true; return *this; }
	inline IntFormat lower(void) { _upper = false; return *this; }
	inline IntFormat sign(void) { _displaySign = true; return *this; }
	inline IntFormat pad(char p) { _pad = p; return *this; }

	t::int64 _val;
	unsigned char _base;
	unsigned char _width;
	unsigned _align : 5;
	unsigned _upper : 1;
	unsigned _sign : 1;
	unsigned _displaySign : 1;
	char _pad;
};


// FloatFormat class
class FloatFormat {
public:
	typedef enum {
		SHORTEST = 0,
		DECIMAL = 1,
		SCIENTIFIC = 2
	} style_t;

	inline FloatFormat(void): _val(0) { init(); }
	inline FloatFormat(float val): _val(val) { init(); }
	inline FloatFormat(double val): _val(val) { init(); }

	inline FloatFormat operator()(float val) { FloatFormat f = *this; f._val = val; return f; }
	inline FloatFormat operator()(double val) { FloatFormat f = *this; f._val = val; return f; }

	inline FloatFormat width(int w) { _width = w; return *this; }
	inline FloatFormat width(int w, int d) { _width = w; _decw = d; return *this; }
	inline FloatFormat style(style_t s) { _style = s; return *this; }
	inline FloatFormat shortest(void) { _style = SHORTEST; return *this; }
	inline FloatFormat decimal(void) { _style = DECIMAL; return *this; }
	inline FloatFormat scientific(void) { _style = SCIENTIFIC; return *this; }
	inline FloatFormat align(alignment_t a) { _align = a; return *this; }
	inline FloatFormat left(void) { _align = LEFT; return *this; }
	inline FloatFormat center(void) { _align = CENTER; return *this; }
	inline FloatFormat right(void) { _align = RIGHT; return *this; }
	inline FloatFormat upper(void) { _upper = true; return *this; }
	inline FloatFormat lower(void) { _upper = false; return *this; }
	inline FloatFormat pad(char p) { _pad = p; return *this; }

	double _val;
	unsigned char _width;
	unsigned char _decw;
	unsigned char _style;
	unsigned char _align: 2;
	unsigned char _upper: 1;
	unsigned char _pad;

private:
	void init(void) {
		_width = 0;
		_decw = 5;
		_style = SHORTEST;
		_align = LEFT;
		_upper = true;
		_pad = ' ';
	}
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
	void print(const IntFormat& fmt);
	void print(const FloatFormat& fmt);
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
inline Output& operator<<(Output& out, const IntFormat& value) { out.print(value); return out; };
inline Output& operator<<(Output& out, const FloatFormat& value) { out.print(value); return out; }


// End-of-line
const char endl = '\n';

// starter macro
inline IntFormat f(t::int8	value)		{ return IntFormat(value); }
inline IntFormat f(t::uint8	value) 		{ return IntFormat(value); }
inline IntFormat f(t::int16	value) 		{ return IntFormat(value); }
inline IntFormat f(t::uint16	value)	{ return IntFormat(value); }
inline IntFormat f(t::int32	value) 		{ return IntFormat(value); }
inline IntFormat f(t::uint32	value) 	{ return IntFormat(value); }
inline IntFormat f(t::int64	value) 		{ return IntFormat(value); }
inline IntFormat f(t::uint64	value) 	{ return IntFormat(value); }
inline FloatFormat f(float value)		{ return FloatFormat(value); }
inline FloatFormat f(double value)		{ return FloatFormat(value); }

// predefined styles
IntFormat pointer(const void *p);
IntFormat byte(t::uint8 b);

// set style macros (deprecated)
inline IntFormat base(int base, IntFormat fmt) { return fmt.base(base); }
inline IntFormat bin(IntFormat fmt) { return fmt.bin(); }
inline IntFormat oct(IntFormat fmt) { return fmt.oct(); }
inline IntFormat hex(IntFormat fmt) { return fmt.hex(); }
inline IntFormat sign(IntFormat fmt) { return fmt.sign(); }
inline IntFormat width(int width, IntFormat fmt) { return fmt.width(width); }
inline IntFormat align(alignment_t align, IntFormat fmt) { return fmt.align(align); }
inline IntFormat left(IntFormat fmt) { return fmt.left(); }
inline IntFormat right(IntFormat fmt) { return fmt.right(); }
inline IntFormat center(IntFormat fmt) { return fmt.center(); }
inline IntFormat pad(char pad, IntFormat fmt) { return fmt.pad(pad); }
inline IntFormat uppercase(IntFormat fmt) { return fmt.upper(); }
inline IntFormat lowercase(IntFormat fmt) { return fmt.lower(); }

} } // elm::io

#endif	// ELM_IO_OUTPUT_H
