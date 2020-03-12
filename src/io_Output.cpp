/*
 *	Output class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-12, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/assert.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>

#include <elm/io/BufferedOutStream.h>
#include <elm/io/io.h>
#include <elm/io/StringOutput.h>
#include <elm/io/FileOutput.h>
#include <elm/compare.h>
#include <elm/data/List.h>
#include <elm/sys/System.h>

namespace elm { namespace io {

/**
 * @class Output
 *
 * Class providing formatted output.
 *
 * Beside a set of print() functions, this class also supports
 * a collection of format configuration classes:
 *	* @ref elm::io::IntFormat
 *	* @ref elm::io;;FloatFormat
 *	* @ref elm::io::StringFormat
 *
 * Below is an example of the use of these classes:
 * @code
 * 	void *p;
 * 	cout << "pointer = " << io::fmt(t::uint64(p)).right().pad('0').width(32) << io::endl;
 * @endcode
 *
 * Additionally, this class provides simple facilities to output to a file and to
 * manage release of created streams.
 *
 * @ingroup ios
 */

/**
 * Convert an integer to character using the horner method.
 * @param p			Pointer on top of buffer.
 * @param val		Integer value to convert.
 * @param base		Base of the conversion.
 * @param enc		Base character for encoding digits upper than 10.
 * @return				First character.
 */
char *Output::horner(char *p, t::uint64 val, int base, char enc) {

	// Special case of 0
	if(!val)
		*--p = '0';

	// Horner method
	else
		while(val) {

			// Compute the digit
			int digit = val % base;
			val /= base;

			// Put the character
			if(digit < 10)
				*--p = '0' + digit;
			else
				*--p = enc + digit - 10;
		}

	// Return the first character position
	return p;
}


/**
 * Build a formatted output on the standard output.
 */
Output::Output(void): strm(&out), ansi(-1) {
}

/**
 * Build a formatted output on the given stream.
 */
Output::Output(OutStream& stream): strm(&stream), ansi(-1) {
}

/**
 * @fn OutStream& Output::stream(void) const;
 * Get the stream used by the output.
 * @return Output stream.
 */

/**
 * Change the output stream of the current output object.
 * @param stream	New stream to use.
 */
void Output::setStream(OutStream& stream) {
	ansi = -1;
	strm = &stream;
}


/**
 * Test if the current stream supports ANSI codes.
 * @return	True if the current stream supports ANSI codes, false else.
 */
bool Output::supportsANSI() {
	if(ansi == -1)
		ansi = strm->supportsANSI();
	return ansi;
}


/**
 * Print a boolean value, 'true' or 'false'.
 * @param value	Value to write.
 */
void Output::print(bool value) {
	print(value ? "true" : "false");
}

/**
 * Print a character.
 * @param chr	Character to print.
 */
void Output::print(char chr) {
	if(strm->write(chr) < 0)
		throw IOException(strm->lastErrorMessage());
}

/**
 * Print an integer.
 * @param value	Integer to print.
 * @deprecated
 */
void Output::print(t::int32 value) {
	char buffer[16];
	bool neg = false;
	t::uint32 uval;

	// Process sign
	if(value < 0) {
		neg = true;
		uval = -value;
	}
	else
		uval = value;

	// Write the digits
	char *p = horner(buffer + sizeof(buffer), uval, 10);

	// Add the sign
	if(neg)
		*--p = '-';

	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException(strm->lastErrorMessage());
}


/**
 * Print a long long integer.
 * @param value	Long long integer to print.
 * @deprecated
 */
void Output::print(t::int64 value) {
	char buffer[64];
	bool neg = false;
	t::uint64 uval;

	// Process sign
	if(value < 0) {
		neg = true;
		uval = -value;
	}
	else
		uval = value;

	// Write the digits
	char *p = horner(buffer + sizeof(buffer), uval, 10);

	// Add the sign
	if(neg)
		*--p = '-';

	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException(strm->lastErrorMessage());
}


/**
 * Print an unsigned integer.
 * @param value	Integer to print.
 * @deprecated
 */
void Output::print(t::uint32 value) {
	char buffer[16];

	// Write the digits
	char *p = horner(buffer + sizeof(buffer), value, 10);

	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException(strm->lastErrorMessage());
}


/**
 * Print an unsigned long long integer.
 * @param value	Integer to print.
 * @deprecated
 */
void Output::print(t::uint64 value) {
	char buffer[32];

	// Write the digits
	char *p = horner(buffer + sizeof(buffer), value, 10);

	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException(strm->lastErrorMessage());
}


/**
 * Print a double value.
 * @param value	Double value to print.
 */
void Output::print(double value) {
	// !!TODO!!
	char buffer[32];
	snprintf(buffer, sizeof(buffer), "%g", value);
	if(strm->write(buffer, strlen(buffer)) < 0)
		throw IOException(strm->lastErrorMessage());
}

/**
 * Print a pointer.
 * @param value	Pointer value.
 */
void Output::print(void *value) {
	if(!value)
		print("<null>");
	else {
		char buffer[sizeof(void *) * 2];
		char *p = horner(buffer + sizeof(buffer), t::intptr(value), 16);
		while(p != buffer)
			*--p = '0';
		if(strm->write(buffer, sizeof(buffer)) < 0)
			throw IOException(strm->lastErrorMessage());
	}
}

/**
 * Print a C string.
 * @param str	C string to print.
 */
void Output::print(const CString str) {
	if(strm->write(str.chars(), str.length()) < 0)
		throw IOException(strm->lastErrorMessage());
}

/**
 * Print a string.
 * @param str	String to print.
 */
void Output::print(const String& str) {
	if(strm->write(str.chars(), str.length()) < 0)
		throw IOException(strm->lastErrorMessage());
}

/**
 * Flush the underlying stream.
 * @throw IOException	If there is a stream error.
 */
void Output::flush(void) {
	if(strm->flush() < 0)
		throw IOException(strm->lastErrorMessage());
}


/**
 * Print a formatted string a-la C prinf().
 * @param fmt	Format string.
 * @param ...	Other arguments.
 */
void Output::format(CString fmt, ...) {
	VARARG_BEGIN(args, fmt)
		format(fmt, args);
	VARARG_END
}


/**
 * Print a formatted string a-la C prinf().
 * @param fmt	Format string.
 * @param args	Other arguments.
 */
void Output::format(CString fmt, VarArg& args) {
	char buf[256];

	// Allocate remaining memory
	int size = vsnprintf(buf, sizeof(buf), &fmt, args.args());

	// It's ok
	if(size <= (int)sizeof(buf))
		strm->write(buf, size);

	// Else use a bigger one
	else {
		char newbuf[size + 1];
		size = vsnprintf(newbuf, sizeof(newbuf), &fmt, args.args());
		ASSERT(size <= (int)sizeof(newbuf));
		strm->write(newbuf, size);
	}
}


/**
 * Print a formatted long value.
 * @param fmt	Formatted value to display.
 */
void Output::print(const IntFormat& fmt) {

	// To horner
	t::uint64 uval;
	if(fmt._sign && fmt._val < 0)
		uval = -fmt._val;
	else
		uval = fmt._val;
	if(!fmt._sign && fmt._size != 8)
		uval &= (1ULL << (fmt._size * 8)) - 1;
	char buffer[33];
	char *res = horner(buffer + 32, uval, fmt._base, fmt._upper ? 'A' : 'a');
	if(fmt._sign && fmt._val < 0)
		*(--res) = '-';
        if (fmt._displaySign && fmt._val > 0)
                *(--res) = '+';
	int size = buffer + 32 - res;

	// Compute pads
	int lpad = 0, rpad = 0;
	if(fmt._width)
		switch(fmt._align) {
		case NONE:
		case LEFT:
			rpad = fmt._width - size;
			break;
		case RIGHT:
			lpad = fmt._width - size;
			break;
		case CENTER:
			lpad = (fmt._width - size) / 2;
			rpad = fmt._width - size - lpad;
			break;
		default:
			ASSERTP(0, "unknown alignment constant");
			break;
		}

	// Perform the display
	for(int i = 0; i < lpad; i++)
		strm->write(fmt._pad);
	strm->write(res, size);
	for(int i = 0; i < rpad; i++)
		strm->write(fmt._pad);
}


/**
 * Print a float with the given format.
 * @param fmt	Float format to print.
 */
void Output::print(const FloatFormat& fmt) {
	// %e	[-]d.ddde+/-dd (precision 6)
	// %f	[-]ddd.ddd (precision 6, if precision 0, no decimal, at least one integer)
	// %g	f or e (e if e < -4 or e >= precision)
	char buf[1/*-*/ + 1/*d*/ + 1/*.*/ + fmt._decw + 2/*e[+-]*/ + 3];
	const char *b;
	int s;
	int prec = fmt._decw;
	if(prec == 0)
		prec = 6;

	// simple special case
	double x = fmt._val;
	switch(fpclassify(x)) {

	case FP_NAN:
		b = "NaN";
		s = 3;
		break;

	case FP_INFINITE:
		b = x > 0 ? "+inf" : "-inf";
		s = 4;
		break;

	default:
		{
			char *p = &buf[sizeof(buf)];

			// prepare the number
			int p10 = log10(x);
			bool neg = false;
			x = fmt._val;
			if(x < 0) {
				x = -x;
				neg = true;
			}

			// select the format
			bool sci = false;
			switch(fmt._style) {
			case FloatFormat::SCIENTIFIC:
				sci = true;
				break;
			case FloatFormat::DECIMAL:
				sci = false;
				break;
			default:
				sci = p10 < -4 || p10 > prec;
				break;
			}

			// decimal notation
			if(!sci) {
				t::uint64 n = x * pow(10., prec);
				bool f = false;
				while(n > 0) {
					int d = n % 10;
					n /= 10;
					if(d != 0 || prec < 0 || f) {
						f = true;
						*--p = d + '0';
					}
					prec--;
					if(prec == 0) {
						f = true;
						*--p = '.';
					}
				}
				if(!f) {
					*--p = '.';
					*--p = '0';
				}
				else if(*p == '.')
					*--p = '0';
			}

			// scientific notation
			else {

				// generate the exponent
				int mp = fabs(p10);
				if(mp < 10) {
					*--p = '0' + mp;
					*--p = '0';
				}
				else {
					while(mp > 0) {
						*--p = '0' + mp % 10;
						mp /= 10;
					}
				}
				*--p = p10 < 0 ? '-' : '+';
				*--p = 'e';

				// generate the decimal
				t::uint64 n = x * pow(10., prec - p10);
				for(int i = 0; i < prec; i++) {
					*--p = '0' + n % 10;
					n /= 10;
				}
				*--p = '.';
				*--p = '0' + n;
			}

			// finalization
			if(neg)
				*--p = '-';
			b = p;
			s = &buf[sizeof(buf)] - p;
		}
		break;
	}

	// perform the display
	int pref = 0, suff = 0, spaces = max(0, fmt._width - s);
	switch(fmt._align) {
	case NONE:		strm->write(b, s); return;
	case LEFT:		suff = spaces; break;
	case RIGHT:		pref = spaces; break;
	case CENTER:	pref = spaces/2; suff = spaces - pref; break;
	}
	char buf2[max(pref, suff)];
	array::set(buf2, sizeof(buf2), char(fmt._pad));
	if(pref)
		strm->write(buf2, pref);
	strm->write(b, s);
	if(suff)
		strm->write(buf2, suff);
}


/**
 * Print a formatted string.
 * @param fmt	Format to print.
 */
void Output::print(const StringFormat& fmt) {
	if(!fmt._width)
		*this << fmt.s;
	else if(fmt.s.length() >= fmt._width)
		*this << fmt.s.substring(0, fmt._width);
	else {

		// compute padding size
		int b, a;
		switch(fmt._align) {
		case LEFT:
			b = 0;
			a = fmt._width - fmt.s.length();
			break;
		case CENTER:
			b = (fmt._width - fmt.s.length()) / 2;
			a = fmt._width - b - fmt.s.length();
			break;
		case RIGHT:
			b = fmt._width - fmt.s.length();
			a = 0;
			break;
		default:
			ASSERT(false);
			return;
		}

		// perform the display
		for(int i = 0; i < b; i++)
			*this << char(fmt._pad);
		*this << fmt.s;
		for(int i = 0; i < a; i++)
			*this << char(fmt._pad);
	}
}


/**
 * @class IntFormat
 * This class is used to perform formatting on integer passed to the @ref Output
 * class.
 *
 * It is rarely used as-is but with some inlines functions performing formatting:
 * @ref io::base, @ref io::bin, @ref io::hex, @ref op::width, @ref io::align,
 * @ref io::left, @ref io::center, @ref io::right, @ref io::pad,
 * @ref io::uppercase, @ref io::lowercase.
 * @ingroup ios
 */

/**
 * @var IntFormat IntFormat::_base;
 * Numeric base used to display the integer (default to 10).
 */

/**
 * @var unsigned char IntFormat::_width;
 * Width of the field where the integer will be displayed. Default 0 for
 * no field width constraint. If the displayed integer size is less than the
 * width, it will be aligned according the @ref IntFormat::align attribute
 * and padded according the @ref IntFormat::pad attribute.
 */

/**
 * @var unsigned IntFormat::_align;
 * Alignment of integer in the field. One of LEFT, CENTER or RIGHT.
 */

/**
 * @var unsigned IntFormat::_upper;
 * If true, upper case characters will be used to display integer whose base
 * is greater than 10. If false (default), lower case characters will be used.
 */

/**
 * @var unsigned IntFormat::_sign;
 * If true, ever display the sign. If false (default), only display negative
 * sign.
 */

/**
 * @var char IntFormat::_pad;
 * Character used to pad the displayed integer in the field (default '0').
 */

/**
 * @var char IntFormat::_displaySign;
 * If true, the sign of signed value is always displayed. Else only the minus is displayed when needed.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::int8	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::uint8	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::int16	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::uint16	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::int32	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::uint32	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::int64	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::operator()(t::uint64	value);
 * Instantiate the format for the given integer.
 * @param value	Integer to format.
 * @return		New integer format.
 */

/**
 * @fn IntFormat IntFormat::base(int b);
 * Set the base.
 * @param b	Base of the format.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::bin(void);
 * Set the base to binary.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::oct(void);
 * Set the base to octal.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::dec(void);
 * Set the base to decimal.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::hex(void);
 * Set the base to hexadecimal.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::width(int w);
 * Set the width of the format.
 * @param w		Width in characters.
 * @return		Built format.
 */

/**
 * @fn IntFormat IntFormat::align(alignment_t a);
 * Set the alignment of the format.
 * @param a	Alignment (one of io::LEFT, io::CENTER or io::RIGHT).
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::left(void);
 * Set the format to left alignment.
 * @return Built format.
 */

/**
 * @fn IntFormat IntFormat::center(void);
 * Set the format to centered alignment.
 * @return Built format.
 */

/**
 * @fn IntFormat IntFormat::right(void);
 * Set the format to right alignment.
 * @return Built format.
 */

/**
 * @fn IntFormat IntFormat::upper(void);
 * Use upper case letters for base greater than 10.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::lower(void);
 * Use lower case letters for base greater than 10.
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::sign(void);
 * Ever display the sign of the integer (even for positives).
 * @return	Built format.
 */

/**
 * @fn IntFormat IntFormat::pad(char p);
 * Set the padding character.
 * @param p	Padding characrer.
 * @return	Built format.
 */


/**
 * @fn IntFormat base(int base, IntFormat fmt);
 * Format an integer with the given base.
 * @param base	Numeric base.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat bin(IntFormat fmt);
 * Used a binary base to display an integer.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat hex(IntFormat fmt);
 * Used an hexadecimal base to display an integer.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat width(int width, IntFormat fmt);
 * Select the width of field where the integer will be displayed to.
 * @param width	Field width.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat align(alignment_t align, IntFormat fmt);
 * Used the given alignment to display the integer in its field.
 * @param align		Alignment.
 * @param fmt		Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat left(IntFormat fmt);
 * Align the integer to the left in its field.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat right(IntFormat fmt);
 * Align the integer to the right in its field.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat center(IntFormat fmt);
 * Center the integer in its field.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat pad(char pad, IntFormat fmt);
 * Select the padding character.
 * @param pad	Padding character.
 * @param fmt	Displayed integer.
  * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat uppercase(IntFormat fmt);
 * Select uppercase characters for digits bigger than 10.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */

/**
 * @fn IntFormat lowercase(IntFormat fmt);
 * Select lowercase characters for digits bigger than 10.
 * @param fmt	Displayed integer.
 * @deprecated
 * @ingroup ios
 */


/**
 * Format a pointer for display.
 * @param p		Pointer to format.
 * @return		Formatted pointer.
 * @ingroup ios
 */
IntFormat pointer(const void *p) {
	return fmt(t::intptr(p)).hex().width(sizeof(t::intptr) * 2).pad('0');
}


/**
 * Format an integer to display it as an hexadecimal byte.
 * @param b		Byte to format.
 * @return		Formatted byte.
 * @ingroup ios
 */
IntFormat byte(t::uint8 b) {
	return fmt(b).hex().width(2).pad('0').right();
}

/**
 * @class StringFormat
 * Store formatting information for character string.
 * To automatically build a string format, uses the @ref fmt() function.
 * @ingroup ios
 */

/**
 * @fn StringFormat StringFormat::width(int w);
 * Select width of the display. As a default, there is o width
 * and the full string is displayed.
 * @param w		Width in character.
 */

/**
 * @fn StringFormat StringFormat::align(alignment_t a);
 * Select alignment position when string is bigger than the selected width.
 * Default alignment value is left.
 * @param a		One of LEFT, CENTER or RIGHT.
 */

/**
 * @fn StringFormat StringFormat::left(void);
 * Align string display to left.
 */

/**
 * @fn StringFormat StringFormat::right(void);
 * Align string display to right.
 */

/**
 * @fn StringFormat StringFormat::center(void);
 * center string display.
 */

/**
 * @fn StringFormat StringFormat::pad(char p);
 * Select the padding character when a width is selected.
 * As a default, it is a space.
 * @param p		Padding character.
 */

/**
 * @class Tag
 * This convenient class allow controlling the way an object
 * is displayed, usually when the display must not conform to
 * the default display method.
 *
 * Its template parameter P must be a class defining a type t,
 * the type of the object to display and static function, print,
 * that will be called to display the object of type t.
 *
 * What does @ref Tag class is just to record an instance of t
 * and call P::print method on it at display time. This let
 * the user to specialize the way the oibject is displayed at this
 * point of the program.
 *
 * @ingroup ios
 */


/**
 * @fn IntFormat fmt(t::int8 i);
 * Build a formatted signed 8-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::uint8 i);
 * Build a formatted unsigned 8-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::int16 i);
 * Build a formatted signed 16-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::uint16 i);
 * Build a formatted unsigned 16-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::int32 i);
 * Build a formatted signed 32-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::uint32 i);
 * Build a formatted unsigned 32-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::int64 i);
 * Build a formatted signed 64-bit integer.
 * @ingroup ios
 */

/**
 * @fn IntFormat fmt(t::uint64 i);
 * Build a formatted unsigned 64-bit integer.
 * @ingroup ios
 */


/**
 * @class FloatFormat
 * Format description for float or double data to display in the
 * @ref Output class.
 * @ingroup ios
 */

///
void FloatFormat::init(void) {
	_width = 0;
	_decw = 6;
	_style = SHORTEST;
	_align = NONE;
	_upper = true;
	_pad = ' ';
}


/**
 * @fn FloatFormat fmt(float f);
 * Build a formatted single floating-point number.
 */

/**
 * @fn FloatFormat fmt(double f);
 * Build a formatted double floating-point number.
 */

/**
 * @fn StringFormat fmt(string s);
 * Build a formatted string.
 */

/**
 * @fn StringFormat fmt(cstring s);
 * Build a formatted string.
 */

/**
 * @fn StringFormat fmt(const char *s);
 * Build a formatted string.
 */

/**
 * @class Printable
 *
 * This class is used to make easier the display of values controlled by a manager.
 * This concerns values that are not self-contained to be displayed (usually because
 * of memory place issues). The print() function is delegated to a manager object that
 * needs to be referenced in the display of the value. This class embeds together
 * the value and the manager to involve them in operator << display. The best usage
 * of this class is the function @ref elm::io::p() that avoids to manage all the type
 * stuff as below:
 * @code
 * class Value {
 * 	...
 * };
 *
 * class Manager {
 * 	...
 * 	void print(const Value& val, io::Output& out);
 * 	...
 * };
 * ...
 * Manager m;
 * Value v;
 * cout << io::p(v, m) << io::endl;
 * @endcode
 *
 * Notice that the manager class has to provide a print() function taking the value
 * as first parameter and the output stream as second parameter.
 *
 * @param T		Type of values.
 * @param M		Type of manager.
 * @ingroup	ios
 */

/**
 * @fn Printable<T, M> p(const T& data, const M& man);
 * Fast building of a managed printable.
 * Look to @ref Printable for more details.
 * @param data	Data to print.
 * @param man	Manager of the data.
 * @ingroup ios
 */


/**
 * @class StringOutput
 * Output performed into a string. This class is just a subclass of StringBuffer.
 * @ingroup ios
 */


/**
 * @class FileOutput
 * Shortcut to build an output to an opened file. Notice that the created file
 * overwrite any existing file.
 * @ingroup ios
 */

/**
 * Build a formatted output which stream is the opened corresponding to the given path.
 * If the file already exists, it is overwritten.
 * @param path					Path of the file to write to.
 * @param buf_size				Buffer size (optional).
 * @throw sys::SystemException	If the file can not be opened.
 */
FileOutput::FileOutput(const char *path, int buf_size)
	: FileOutput(sys::Path(path), buf_size)
	{ }

/**
 * Build a formatted output which stream is the opened corresponding to the given path.
 * If the file already exists, it is overwritten.
 * @param path					Path of the file to write to.
 * @param buf_size				Buffer size (optional).
 * @throw sys::SystemException	If the file can not be opened.
 */
FileOutput::FileOutput(cstring path, int buf_size)
	: FileOutput(sys::Path(path), buf_size)
	{ }

/**
 * Build a formatted output which stream is the opened corresponding to the given path.
 * If the file already exists, it is overwritten.
 * @param path					Path of the file to write to.
 * @param buf_size				Buffer size (optional).
 * @throw sys::SystemException	If the file can not be opened.
 */
FileOutput::FileOutput(string path, int buf_size)
	: FileOutput(sys::Path(path), buf_size)
	{ }

/**
 * Build a formatted output which stream is the opened corresponding to the given path.
 * If the file already exists, it is overwritten.
 * @param path					Path of the file to write to.
 * @param buf_size				Buffer size (optional).
 * @throw sys::SystemException	If the file can not be opened.
 */
FileOutput::FileOutput(sys::Path path, int buf_size)
:	_out(path.write()),
	_buf(*_out, buf_size)
{
	setStream(_buf);
}


/**
 */
FileOutput::~FileOutput(void) {
	_buf.flush();
	delete _out;
}


/**
 * @class ListPrinter
 * This class is dedicated to the printing of collection of values with
 * a separator. It is designed to be embeded in  a flow of output <<
 * operators. A faster to use is the call to the function @ref io::list().
 *
 * @ingroup io
 */


/**
 * @fn ListPrinter<T> list(const T& l, cstring s);
 * Generate a list printer displaying the given list which element are
 * separated using the given separator. The built list printer can be
 * displaying using io::Output << operators.
 *
 * @param T		Type of list of values to display.
 * @param l		List to display.
 * @param s		Separator between values.
 * @return		List printer ready to be displayed.
 * @ingroup		io
 */

} // io

/**
 * Standard output.
 * @ingroup ios
 */
io::Output cout(io::out);

/**
 * Standard error output.
 * @ingroup ios
 */
io::Output cerr(io::err);

} // elm
