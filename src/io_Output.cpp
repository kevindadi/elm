/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * src/op_Output.cpp-- Output class implementation.
 */

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <elm/io/io.h>

namespace elm { namespace io {

/**
 * @class Output <elm/io.h>
 * Formatted output class.
 * 
 * See @ref IntFormat to format integers. The code below show how to format
 * an address with a size of 32 bits:
 * @code
 * 	void *p;
 * 	cout << io::right(io::pad('0', io::width(32, io::hex(o)))) << io::endl;
 * @endcode
 */

/**
 * Convert an integer to character using the horner method.
 * @param p			Pointer on top of buffer.
 * @param val		Integer value to convert.
 * @param base		Base of the conversion.
 * @param enc		Base character for encoding digits upper than 10.
 * @return				First character.
 */
char *Output::horner(char *p, unsigned long val, int base, char enc) {
	
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
 * Convert an integer to character using the horner method.
 * @param p			Pointer on top of buffer.
 * @param val		Integer value to convert.
 * @param base	Base of the conversion.
 * @return				First character.
 */
char *Output::horner(char *p, unsigned long long val, int base) {
	
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
				*--p = 'a' + digit - 10;
		}
	
	// Return the first character position
	return p;
}


/**
 * @fn Output::Output(void);
 * Build a formatted output on the standard output.
 */

/**
 * @fn Output::Output(OutStream& stream);
 * Build a formatted output on the given stream.
 */

/**
 * @fn OutStream& Output::stream(void) const;
 * Get the stream used by the output.
 * @return Output stream.
 */

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
		throw IOException("io error %d", __LINE__);
}

/**
 * Print an integer.
 * @param value	Integer to print.
 */
void Output::print(long value) {
	char buffer[16];
	bool neg = false;
	unsigned long uval;
	
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
		throw IOException("io error %d", __LINE__);
}


/**
 * Print a long long integer.
 * @param value	Long long integer to print.
 */
void Output::print(long long value) {
	char buffer[64];
	bool neg = false;
	unsigned long long uval;
	
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
		throw IOException("io error %d", __LINE__);
}


/**
 * Print an unsigned integer.
 * @param value	Integer to print.
 */
void Output::print(unsigned long value) {
	char buffer[16];
	
	// Write the digits
	char *p = horner(buffer + sizeof(buffer), value, 10);
	
	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException("io error %d", __LINE__);
}


/**
 * Print an unsigned long long integer.
 * @param value	Integer to print.
 */
void Output::print(unsigned long long value) {
	char buffer[32];
	
	// Write the digits
	char *p = horner(buffer + sizeof(buffer), value, 10);
	
	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException("io error %d", __LINE__);
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
		throw IOException("io error %d", __LINE__);
}

/**
 * Print a pointer.
 * @param value	Pointer value.
 */
void Output::print(void *value) {
	if(!value)
		print("<null>");
	else {
		char buffer[8];
		char *p = horner(buffer + sizeof(buffer), (unsigned long)value, 16);
		while(p != buffer)
			*--p = '0';
		if(strm->write(buffer, 8) < 0)
			throw IOException("io error %d", __LINE__);
	}
}

/**
 * Print a C string.
 * @param str	C string to print.
 */
void Output::print(const CString str) {
	if(strm->write(str.chars(), str.length()) < 0)
		throw IOException("io error %d", __LINE__);
}

/**
 * Print a string.
 * @param str	String to print.
 */
void Output::print(const String& str) {
	if(strm->write(str.chars(), str.length()) < 0)
		throw IOException("io error %d", __LINE__);
}

/**
 * Flush the underlying stream.
 * @throw IOException	If there is a stream error.
 */
void Output::flush(void) {
	if(strm->flush() < 0)
		throw IOException("io error %d", __LINE__);
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
	if(size <= sizeof(buf))
		strm->write(buf, size);
	
	// Else use a bigger one
	else {
		char newbuf[size + 1];
		size = vsnprintf(newbuf, sizeof(newbuf), &fmt, args.args());
		assert(size <= sizeof(newbuf));
		strm->write(newbuf, size);
	}
}


/**
 * Print a formatted long value.
 * @param fmt	Formatted value to display.
 */
void Output::print(const IntFormat fmt) {
	
	// To horner
	unsigned long uval;
	if(fmt.sign && fmt.val < 0)
		uval = -fmt.val;
	else
		uval = fmt.val;
	char buffer[33];
	char *res = horner(buffer + 32, uval, fmt.base, fmt.upper ? 'A' : 'a');
	if(fmt.sign && fmt.val < 0)
		*(--res) = '-';
	int size = buffer + 32 - res;
	
	// Compute pads
	int lpad = 0, rpad = 0;
	if(fmt.width)
		switch(fmt.align) {
		case NONE:
		case LEFT:
			rpad = fmt.width - size;
			break;
		case RIGHT:
			lpad = fmt.width - size;
			break;
		case CENTER:
			lpad = (fmt.width - size) / 2;
			rpad = fmt.width - size - lpad;
			break;
		default:
			assert(0);
		}
	
	// Perform the display
	for(int i = 0; i < lpad; i++)
		strm->write(fmt.pad);
	strm->write(res, size);
	for(int i = 0; i < rpad; i++)
		strm->write(fmt.pad);
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
 */
 
/**
 * @var unsigned char IntFormat::base;
 * Numeric base used to display the integer (default to 10).
 */
/**
 * @var unsigned char IntFormat::width;
 * Width of the field where the integer will be displayed. Default 0 for
 * no field width constraint. If the displayed integer size is less than the
 * width, it will be aligned according the @ref IntFormat::align attribute
 * and padded according the @ref IntFormat::pad attribute.
 */
/** 
 * @var unsigned IntFormat::align;
 * Alignment of integer in the field. One of LEFT, CENTER or RIGHT.
 */
/**
 * @var unsigned IntFormat::upper;
 * If true, upper case characters will be used to display integer whose base
 * is greater than 10. If false (default), lower case characters will be used.
 */
/**
 * @var unsigned IntFormat::sign;
 * If true, ever display the sign. If false (default), only display negative
 * sign.
 */
/**
 * @var char IntFormat::pad;
 * Character used to pad the displayed integer in the field (default '0').
 */


/**
 * @fn IntFormat base(int base, IntFormat fmt);
 * Format an integer with the given base.
 * @param base	Numeric base.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat bin(IntFormat fmt);
 * Used a binary base to display an integer.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat hex(IntFormat fmt);
 * Used an hexadecimal base to display an integer.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat width(int width, IntFormat fmt);
 * Select the width of field where the integer will be displayed to.
 * @param width	Field width.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat align(alignment_t align, IntFormat fmt);
 * Used the given alignment to display the integer in its field.
 * @param align		Alignment.
 * @param fmt		Displayed integer.
 */
/**
 * @fn IntFormat left(IntFormat fmt);
 * Align the integer to the left in its field.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat right(IntFormat fmt);
 * Align the integer to the right in its field.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat center(IntFormat fmt);
 * Center the integer in its field.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat pad(char pad, IntFormat fmt);
 * Select the padding character.
 * @param pad	Padding character.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat uppercase(IntFormat fmt);
 * Select uppercase characters for digits bigger than 10.
 * @param fmt	Displayed integer.
 */
/**
 * @fn IntFormat lowercase(IntFormat fmt);
 * Select lowercase characters for digits bigger than 10.
 * @param fmt	Displayed integer.
 */

} // io

/**
 * Standard output.
 */
io::Output cout(io::stdout);

/**
 * Standard error output.
 */
io::Output cerr(io::stderr);

} // elm
