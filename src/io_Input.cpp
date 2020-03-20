/*
 *	Input class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
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
#include <elm/io/io.h>
#include <elm/io/Input.h>
#include <elm/io/StringInput.h>
#include <elm/io/FileInput.h>
#include <elm/string/StringBuffer.h>
#include <math.h>
#include <ctype.h>

namespace elm { namespace io {

/**
 * @class Input
 * This class provides formatted scanning to input streams.
 *
 * It is supported to support scan of several items separated by spaces.
 * The possible errors are accumulated inside the state of the class and can
 * accessed at the end of a scan session.
 *
 * Each scan of a value can result in a success, in a failure (bad format) or
 * in error (reflecting an error in the underlying stream). In addition its
 * states records also the end of the stream.
 *
 * @ingroup ios
 */

/**
 */
Input::Input(): strm(&in), buf(-1), state(0) {
}

/**
 */
Input::Input(InStream& stream): strm(&stream), buf(-1), state(0) {
}


/**
 * Raise an exception claiming that the IO is not supported.
 */
void Input::unsupported(void) {
	throw io::IOException("unsupported input");
}


/**
 * Get the next character.
 * @return	Next character or -1 if there is no more character available.
 */
int Input::get(void) {
	int res;
	if(buf >= 0) {
		res = buf;
		buf = -1;
	}
	else {
		res = strm->read();
		if(res < 0) {
			switch(res) {
			case InStream::FAILED:
				state |= IO_ERROR | FAILED;
				throw IOException(strm->lastErrorMessage());
			case InStream::ENDED:
				state |= ENDED;
				break;
			default:
				ASSERT(false);
			}
		}
	}
	return res;
}

/**
 * Skip space characters until finding the end of file ornon-space character.
 * @return	Found character or InStream error code.
 */
int Input::skip() {
	int c = get();
	while(isspace(c))
		c = get();
	return c;
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
 * @fn bool Input::ended() const;
 * Test if the stream is ended. Once ended, any new scan will fail.
 * @return	True if the stream is ended, false else.
 */

/**
 * bool Input::failed() const;
 * Test if the last operation failed. Failed means that there were a format
 * in the last read value.
 * @return	True if the last operation failed.
 */

/**
 * bool Input::error() const;
 * Test if there has been an input error from the underlying stream.
 * @return	True if there has been an input error.
 */

/**
 * bool Input::ok() const;
 * Test if the stream is ok (end not reached, no failed operation, no input
 * error).
 * @return	True if the input is ready to proceed.
 */

/**
 * @fn void Input::resetState();
 * Remove any failure or input error from the state.
 */


/**
 * Read a boolean value, that is, 'true'/'false' or '1'/'0'.
 * @return	Read boolean value.
 */
bool Input::scanBool(void) {
	const char *pattern;
	bool res;

	// Look first character
	int chr = get();
	if (chr == '1') {
		pattern = "1";
		res = true;
	}
	else if (chr == '0') {
		pattern = "0";
		res = false;
	}
	else if(chr == 't') {
		pattern = "true";
		res = true;
	}
	else if(chr == 'f') {
		pattern = "false";
		res = false;
	}
	else {
		pattern = "";
		res = false;
	}

	// Look other characters
	while(*pattern == chr) {
		pattern++;
		if(*pattern == '\0')
			return res;
		chr = get();
	}
	state = InStream::FAILED;
	return false;
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
 * Test if the character is in the base and return the matching digit.
 * @param chr	Character to test.
 * @param base	Base of the read.
 * @return		Matching digit or not (-1).
 */
static inline int test_base(char chr, int base) {
	if(base < 10) {
		if(chr >= '0' && chr < '0' + base)
			return chr - '0';
		else
			return -1;
	}
	else if(chr >= '0' && chr <= '9')
		return chr - '0';
	else if(chr >= 'a' && chr < 'a' + base - 10)
		return chr - 'a' + 10;
	else if(chr >= 'A' && chr < 'A' + base - 10)
		return chr - 'A' + 10;
	else
		return -1;
}


/**
 * Scan a based unsigned long, decimal as a default.
 * Supported base prefixes are '0', '0[xX]' or '0[bB]'.
 * @param base			Base of the number to read (default to 0 to scan prefixes).
 * @return				Integer value.
 * @throw IOException	In case of IO error.
 */
t::uint32 Input::scanULong(int base) {
	bool one = false;
	t::uint32 val = 0;

	// Read the base
	int chr = skip();
	if(base == 0) {
		if(chr == '0')
			switch(chr = get()) {
			case 'x': case 'X':
				base = 16;
				chr = get();
				break;
			case 'b': case 'B':
				base = 2;
				chr = get();
				break;
			default:
				one = true;
				base = 8;
				break;
			}
		else
			base = 10;
	}

	// read the digits
	int digit = test_base(chr, base);
	while(digit >= 0) {
		t::uint32 old = val;
		val = val * base + digit;
		one = true;
		if(val < old) {
			state |= FAILED;
			return 0;
		}
		chr = get();
		digit = test_base(chr, base);
	}
	if(chr >= 0)
		back(chr);
	if(!one)
		state |= FAILED;
	return val;
}


/**
 * Scan a based long, decimal as a default.
 * Supported base prefixes are '0', '0[xX]' or '0[bB]'.
 * @param base			Base of the number to read (default to 0 to scan prefixes).
 * @return				Integer value.
 * @throw IOException	In case of IO or format error.
 */
t::int32 Input::scanLong(int base) {
	t::uint32 val = 0;
	bool neg = false;

	// Read sign
	int chr = skip();
	if(chr == '-')
		neg = true;
	else if(chr != '+') {
		if(chr < 0) {
			state |= FAILED;
			return 0;
		}
		back(chr);
	}

	// get the value
	val = scanULong(base);
	if(val >= (1UL << 31)) {
		state |= FAILED;
		return 0;
	}
	return neg ? -t::int32(val) : val;
}


/**
 * Scan a based unsigned long long, decimal as a default.
 * Supported base prefixes are '0', '0[xX]' or '0[bB]'.
 * @param base			Base of the number to read (default to 0 to scan prefixes).
 * @return				Integer value.
 * @throw IOException	In case of IO or format error.
 */
t::uint64 Input::scanULLong(int base) {
	t::uint64 val = 0;
	bool one = false;

	// Read the base
	int chr = skip();
	if(base == 0) {
		if(chr == '0')
			switch(chr = get()) {
			case 'x': case 'X':
				base = 16;
				chr = get();
				break;
			case 'b': case 'B':
				base = 2;
				chr = get();
				break;
			default:
				base = 8;
				one = true;
				break;
			}
		else
			base = 10;
	}

	// read the digits
	int digit = test_base(chr, base);
	while(digit >= 0) {
		t::uint32 old = val;
		val = val * base + digit;
		one = true;
		if(val < old) {
			state |= FAILED;
			return 0;
		}
		chr = get();
		digit = test_base(chr, base);
	}
	if(chr >= 0)
		back(chr);
	if(!one) {
		state |= FAILED;
		return 0;
	}
	return val;
}


/**
 * Scan a based long long, decimal as a default.
 * Supported base prefixes are '0', '0[xX]' or '0[bB]'.
 * @param base			Base of the number to read (default to 0 to scan prefixes).
 * @return				Integer value.
 * @throw IOException	In case of IO or format error.
 */
t::int64 Input::scanLLong(int base) {
	t::uint64 val = 0;
	bool neg = false;

	// Read sign
	int chr = skip();
	if(chr == '-')
		neg = true;
	else if(chr != '+') {
		if(chr < 0) {
			state |= FAILED;
			return 0;
		}
		back(chr);
	}

	// get the value
	val = scanULLong(base);
	if(val >= (1ULL << 63)) {
		state |= FAILED;
		return 0;
	}
	return neg ? -t::int64(val) : val;
}


/**
 * Scan a floating value.
 * @return	Read value.
 */
double Input::scanDouble(void) {
	double value = 0;
	bool neg = false;
	bool one = false;

	// Read sign
	int chr = skip();
	if(chr == '-') {
		neg = true;
		chr = get();
	}
	else if(chr == '+')
		chr = get();

	// Read integer part
	while(chr >= '0' && chr <= '9') {
		value = value * 10 + (chr - '0');
		one = true;
		chr = get();
	}

	// Read decimal part
	if(chr == '.') {
		chr = get();
		double dec = 0.1;
		while(chr >= '0' && chr <='9') {
			value += (chr - '0') * dec;
			dec = dec / 10;
			one = true;
			chr = get();
		}
	}

	// Read exponent part
	if(!one) {
		state |= FAILED;
		return 0;
	}
	if(chr == 'e' || chr == 'E') {
		int exp = 0;
		chr = get();
		if(chr == '-')
			chr = get();
		else if(chr == '+')
			chr = get();
		one = false;
		while(chr >= '0' && chr <= '9') {
			exp = exp * 10 + (chr - '0');
			one = true;
			chr = get();
		}
		if(!one) {
			state |= FAILED;
			return 0;
		}
		value = value * pow(10, exp);
	}

	// Return result
	if(chr >= 0)
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
	bool one = false;
	int chr = skip();
	while(chr >= 0 && !isspace(chr)) {
		buf << (char)chr;
		one = true;
		chr = get();
	}
	if(chr >= 0)
		back(chr);
	if(!one)
		state |= FAILED;
	return buf.toString();
}


/**
 * Scan a full line. The end is reached when the string
 * is empty.
 * @return	Read line (final \n, if any, is appended).
 */
String Input::scanLine(void) {
	StringBuffer buf;
	int chr = get();
	while(chr >= 0) {
		buf << static_cast<char>(chr);
		if(chr == '\n')
			break;
		chr = get();
	}
	if(chr == InStream::FAILED) {
		state |= IO_ERROR;
		return "";
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


/**
 * @class StringInput
 * Input performed on a string. It makes easy to perform formatted
 * read from a simple string.
 *
 * @code
 *	string s = "666";
 *	StringInput in(s);
 *	int x;
 *	in >> x;
 * @endcode
 *
 * @ingroup ios
 */

/**
 * @fn StringInput::StringInput(const char *str);
 * Perform intput from the given string stored in character array.
 * @param	str		To read.
 */

/**
 * @fn StringInput::StringInput(const cstring& str);
 * Perform intput from the given C string.
 * @param	str		To read.
 */

/**
 * @fn StringInput::StringInput(const string& str);
 * Perform intput from the given ELM string.
 * @param	str		To read.
 */


/**
 * @class FileInput
 * Input from a file. Shortcut to perform formatted read
 * from a buffered opened file.
 * @ingroup ios
 */

/**
 * Build an input by opening the given file path.
 * @param path					Path to the file to open.
 * @throw sys::SystemException	If the file cannot be opened.
 */
FileInput::FileInput(string path): FileInput(sys::Path(path))
{ }

 /**
  * Build an input by opening the given file path.
  * @param path					Path to the file to open.
  * @throw sys::SystemException	If the file cannot be opened.
  */
FileInput::FileInput(const char *path):	FileInput(sys::Path(path))
{ }

/**
 * Build an input by opening the given file path.
 * @param path					Path to the file to open.
 * @throw sys::SystemException	If the file cannot be opened.
 */
FileInput::FileInput(cstring path):	FileInput(sys::Path(path))
{ }


 /**
  * Build an input by opening the given file path.
  * @param path					Path to the file to open.
  * @throw sys::SystemException	If the file cannot be opened.
  */
FileInput::FileInput(sys::Path path) : _in(path.read()) {
	setStream(*_in);
}


/**
 * Transfer an existing file input. After this operation, the argument input
 * stream is no more usable.
 * @param fi	File input to transfer.
 */
FileInput::FileInput(FileInput&& fi): _in(fi._in) {
	fi._in = nullptr;
	setStream(*_in);
}


/**
 */
FileInput::~FileInput(void) {
	if(_in != nullptr)
		delete _in;
}

} // io

/**
 * Formatted input.
 * @ingroup ios
 */
io::Input cin;

} // eml
