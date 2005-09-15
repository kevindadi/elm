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
 * @class Output
 * Formatted output class.
 */

/**
 * Convert an integer to character using the horner method.
 * @param p			Pointer on top of buffer.
 * @param val		Integer value to convert.
 * @param base	Base of the conversion.
 * @return				First character.
 */
char *Output::horner(char *p, unsigned long val, int base) {
	
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
		throw IOException();
}

/**
 * Print an integer.
 * @param value	Integer to print.
 */
void Output::print(int value) {
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
		throw IOException();
}

/**
 * Print an unsigned integer.
 * @param value	Integer to print.
 */
void Output::print(unsigned int value) {
	char buffer[16];
	
	// Write the digits
	char *p = horner(buffer + sizeof(buffer), value, 10);
	
	// Write it
	if(strm->write(p, buffer + sizeof(buffer) - p) < 0)
		throw IOException();
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
		throw IOException();
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
			throw IOException();
	}
}

/**
 * Print a C string.
 * @param str	C string to print.
 */
void Output::print(const CString str) {
	if(strm->write(str.chars(), str.length()) < 0)
		throw IOException();
}

/**
 * Print a string.
 * @param str	String to print.
 */
void Output::print(const String& str) {
	if(strm->write(str.chars(), str.length()) < 0)
		throw IOException();
}

/**
 * Flush the underlying stream.
 * @throw IOException	If there is a stream error.
 */
void Output::flush(void) {
	if(strm->flush() < 0)
		throw IOException();
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
