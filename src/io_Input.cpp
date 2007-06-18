/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * src/io_Input.h -- Input class implementation.
 */

#include <elm/assert.h>
#include <elm/io/io.h>
#include <elm/io/Input.h>
#include <math.h>
#include <ctype.h>

namespace elm { namespace io {
	
/**
 * @class Input <elm/io/Input.h>
 * This class provides formatted scanning to input streams.
 */


/**
 * Get the next character.
 * @return	Next character or -1 if there is no more character available.
 */
int Input::get(void) {
	char res;
	if(buf >= 0) {
		res = buf;
		buf = -1;
	}
	else
		switch(strm->read(&res, 1)) {
		case 0:
			return -1;
		case 1:
			return (unsigned char)res;
		default:
			throw IOException(strm->lastErrorMessage());
		}
}


/**
 * Push back a read character.
 * @param chr	Back-pushed character.
 */
void Input::back(int chr) {
	ASSERTP(buf < 0, "buffer is empty");
	buf = chr;
}


/**
 * @fn Input::Input(void);
 * Build a new input using the standard.
 */


/**
 * @fn Input::Input(InStream& stream);
 * Build a new input with the given input stream.
 * @param stream	Used input stream.
 */


/**
 * @fn InStream& Input::stream(void) const;
 * Get the current input stream.
 * @return	Current input stream.
 */


/**
 * @fn void Input::setStream(InStream& stream);
 * change the used input stream.
 */


/**
 * Read a boolean value, that is, 'true' or 'false'.
 * @return	Read boolean value.
 */	
bool Input::scanBool(void) {
	char *pattern;
	bool res;
	
	// Look first character
	int chr = get();
	if(chr == 't') {
		pattern = "true";
		res = true;
	}
	else if(chr == 'f') {
		pattern = "false";
		res = false;
	}
	else
		pattern = "";
	
	// Look other characters
	while(*pattern == chr) {
		pattern++;
		if(*pattern == '\0')
			return res;
		chr = get();
	}
	throw IOException("bad format for boolean");
}


/**
 * Read the next character.
 * @return	Next character.
 */
char Input::scanChar(void) {
	int res = get();
	if(res <  0)
		throw IOException("no more character to read");
	else
		return res;
}


/**
 * Scan a decimal integer.
 * @return	Integer value.
 */
long Input::scanInt(void) {
	unsigned long val = 0;
	bool neg = false;
	
	// Read sign
	int chr = get();
	if(chr == '-') {
		neg = true;
		chr = get();
	}
	else if(chr == '+')
		chr = get();
	
	// Read the characters
	if(chr < '0' || chr > '9')
		throw IOException("bad formatted integer");
	while(chr >= '0' && chr <= '9') {
		val = val * 10 + (chr - '0');
		chr = get();
	}
	back(chr);
	return neg ? -val : val;
}


/**
 * Scan a decimal long integer.
 * @return	Read long value.
 */
long long Input::scanLong(void) {
	unsigned long long val = 0;
	bool neg = false;
	
	// Read sign
	int chr = get();
	if(chr == '-') {
		neg = true;
		chr = get();
	}
	else if(chr == '+')
		chr = get();
	
	// Read the characters
	if(chr < '0' || chr > '9')
		throw IOException("bad formatted integer");
	while(chr >= '0' && chr <= '9') {
		val = val * 10 + (chr - '0');
		chr = get();
	}
	back(chr);
	return neg ? -val : val;
}


/**
 * Scan a floating value.
 * @return	Read value.
 */
double Input::scanDouble(void) {
	double value = 0;
	bool neg = false;
	
	// Read sign
	int chr = get();
	if(chr == '-') {
		neg = true;
		chr = get();
	}
	else if(chr == '+')
		chr = get();
	
	// Read integer part
	if(chr != '.' && (chr < '0' || chr > '9'))
		throw IOException("bad formatted float value");
	while(chr >= '0' && chr <= '9') {
		value = value * 10 + (chr - '0');
		chr = get();
	}
	
	// Read decimal part
	if(chr == '.') {
		chr = get();
		double dec = 0.1;
		while(chr >= '0' && chr <='9') {
			value += (chr - '0') * dec;
			dec = dec / 10;
			chr = get();
		}
	}
	
	// Read exponent part
	if(chr == 'e' || chr == 'E') {
		int exp = 0;
		bool eneg = false;
		chr = get();
		if(chr == '-') {
			eneg = true;
			chr = get();
		}
		else if(chr == '+')
			chr = get();
		if(chr < '0' || chr > '9')
			throw IOException("bad formatted float value");
		while(chr >= '0' || chr <= '9') {
			exp = exp * 10 + (chr - '0');
			chr = get();
		}
		value = value + pow(10, exp);
	}
	
	// Return result
	back(chr);
	return neg ? -value : value;
}


/**
 * Scan a word from the text and return it.
 * @note A word is separated from other words by a blank character.
 * @return	Read word.
 */
String Input::scanWord(void) {
	StringBuffer buf;
	int chr = get();
	while(chr >= 0 && !isspace(chr)) {
		buf << (char)chr;
		chr = get();
	}
	back(chr);
	return buf.toString();
}


/**
 * Scan a full line.
 * @return	Read line (final \n, if any, is appended).
 */
String Input::scanLine(void) {
	StringBuffer buf;
	int chr = get();
	while(chr >= 0) {
		buf << (char)chr;
		if(chr == '\n')
			break;
		chr = get();
	}
	return buf.toString();	
}


/**
 * Read a character if it is equal to the given one or throw @ref an IOException.
 * @param chr	Character to read.
 */
void Input::swallow(char chr) {
	int read = get();
	if((unsigned char)chr == read)
		return;
	else {
		back(chr);
		throw IOException("bad character");
	}
}


/**
 * Read the character of the given string until finding a not matching
 * character (and throw an exception in this case).
 * @param str	String to read.
 */
void Input::swallow(CString str) {
	for(int i = 0; str[i]; i++)
		swallow(str[i]);
}


/**
 * Read the character of the given string until finding a not matching
 * character (and throw an exception in this case).
 * @param str	String to read.
 */
void Input::swallow(const String& str) {
	for(int i = 0; i < str.length(); i++)
		swallow(str[i]);
}


/**
 * Swallow one or more characters.
 * @return	True if some blanks have swallowed, false else.
 */
void Input::swallowBlank(void) {
	int chr = get();
	while(isspace(chr) && chr >= 0)
		chr = get();
	back(chr);
}


/**
 * @fn Input& Input::operator>>(bool& value);
 * Shortcut @ref scanBool.
 */


/**
 * @fn Input& Input::operator>>(char& value);
 * Shortcut to @ref scanChar().
 */


/**
 * @fn Input& Input::operator>>(unsigned char& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(short& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(unsigned short& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(int& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(unsigned int& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(long& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(unsigned long& value);
 * Shortcut to @ref scanInt().
 */


/**
 * @fn Input& Input::operator>>(long long& value);
 * Shortcut to @ref scanLong().
 */


/**
 * @fn Input& Input::operator>>(unsigned long long& value);
 * Shortcut to @ref scanLong().
 */


/**
 * @fn Input& Input::operator>>(float& value);
 * Shortcut to @ref scanDouble().
 */


/**
 * @fn Input& Input::operator>>(double& value);
 * Shortcut to @ref scanDouble().
 */


/**
 * @fn Input& Input::operator>>(String& value);
 * Shortcut to @ref scanLine().
 */


/**
 * @fn Input& Input::operator>>(char value);
 * Shortcut to @ref swallow(char).
 */


/**
 * @fn Input& Input::operator>>(CString value);
 * Shortcut to @ref swallow(CString).
 */


/**
 * @fn Input& Input::operator>>(const String& value);
 * shortcut @ref swallow(String).
 */

} // io

/**
 * Formatted input.
 */
io::Input cin;

} // eml
