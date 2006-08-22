/*
 * $Id$
 * Copyright (c) 2003, Alfheim Corporation.
 *
 * string.cc -- string classes implementation.
 */

 #include <elm/string.h>
 
 namespace elm {
 
 
/**
 * @class String
 * An immutable implementation of the string data type. Refer to
 * @ref StringBuffer for long concatenation string building.
 */

 /* Empty buffer */
 String::buffer_t String::empty_buf = { 1, 0 };
 
 /**
  * Make a string by copying the given character array.
  * @param str	Character array address.
  * @param _len	Character array length.
  */
 void String::copy(const char *str, int _len) {
 	
 	// empty string?
 	if(!_len) {
 		buf = (char *)&empty_buf;
 		off =zero_off;
 		len = 0;
 		lock();
 	}
 	
 	// Create the buffer
 	else {
		buf = new char[sizeof(buffer_t) + _len]; 
		buffer_t *desc = (buffer_t *)buf;
		desc->use = 1;
		memcpy(desc->buf, str, _len);
		desc->buf[_len] = '\0';
		off = zero_off;
		len = _len; 
 	}
 }

/**
 * Build a new string by concatenation of two character arrays.
 * @param s1	First character array address.
 * @param l1	First character array length.
 * @param s2	Second character array address.
 * @param l2	Second character array length.
 */
String String::concat(const char *s1, int l1, const char *s2, int l2) {
	buffer_t *sbuf = (buffer_t *)new char[sizeof(String::buffer_t) + l1 + l2];
	sbuf->use = 0;
	memcpy(sbuf->buf, s1, l1);
	memcpy(sbuf->buf + l1, s2, l2);
	sbuf->buf[l1 + l2] = '\0';
	return String((char *)sbuf, zero_off, l1 + l2);
}


/**
 * Transform the buffer such that a '\0' character is found at end of the
 * current string. If the buffer is only owned by the current string, the '\0'
 * is simply added. Else a new buffer is created.
 */
void String::toc(void) {
	
	// Only one owner
	buffer_t *sbuf = (buffer_t *)buf;
	if(sbuf->use <= 1)
		sbuf->buf[len] = '\0';
	
	// Build a new buffer
	else {
		char *nbuf = new char[sizeof(buffer_t) + len]; 
		buffer_t *nsbuf = (buffer_t *)nbuf;
		nsbuf->use = 1;
		memcpy(nsbuf->buf, sbuf->buf, len);
		unlock();
		nsbuf->buf[len] = '\0';
		off = zero_off;
	}
}


/**
 * @fn String::String(void)
 * Build an empty string.
 */


/**
 * @fn String::String(const char *str, int _len)
 * Build a string from a character array.
 * @param str	Character array base.
 * @param _len	Character array length.
 */


/**
 * @fn String::String(const char *str);
 * Build an ELM string from a C string.
 * @param str	C string.
 */


/**
 * @fn String::String(const CString str);
 * Build a string from a @ref CString.
 * @param str	CString object to use.
 */


/**
 * @fn String::String(const String& str);
 * Clone an existing string.
 * @param str	String to clone.
 */


/**
 * @fn String& String::operator=(const String& str);
 * Assign a string to the current one.
 * @param str	String to assign.
 * @return		Current string.
 */


/**
 * @fn String& String::operator=(const CString str);
 * Assign a CString object to the current string.
 * @param str	CString object to assign.
 * @return		Current string.
 */
 
 
/**
 * @fn String& String::operator=(const char *str)
 * Assign a C string to the current string.
 * @param str	C string to assign.
 * @return		Current string.
 */


/**
 * @fn int String::length(void) const;
 * Get the length of the string.
 * @return	String length.
 */


/**
 * @fn const char *String::chars(void) const;
 * Get access to internal representation of the string. Use it with caution and
 * recall that the got buffer may be shared by many different strings.
 * @return	Raw access to character buffer.
 */

 
/**
 * @fn int String::compare(const String& str) const;
 * Compare two strings with ASCII order.
 * @param str	String to compare with.
 * @return		0 for equality, <0 if the current string is less than given one,
 * 				>0 if the current string is greater than given one.
 */


/**
 * @fn int String::compare(const CString str) const;
 * Compare this string with a CString object using ASCII order.
 * @param str	String to compare with.
 * @return		0 for equality, <0 if the current string is less than given one,
 * 				>0 if the current string is greater than given one.
 */


/**
 * @fn bool String::isEmpty(void) const;
 * Test if string is empty.
 * @return	True if the string is empty, false else.
 */


/**
 * @fn String::operator bool(void) const;
 * Same as isEmpty().
 */


/**
 * @fn CString String::toCString(void);
 * Convert the current string to a CString object.
 * @return	Matching CString object.
 * @warning The returned CString contains a pointer to a buffer owned by the
 * current string. This buffer is only valid while the current is living.
 */


/**
 * @fn const char *String::operator&(void);
 * Convert to C string.
 * @return	Matching C string.
 */

		
/**
 * @fn char String::charAt(int index) const;
 * Get a character at some position in the string. 
 * @param index Index of the character to get (It is an error to give
 * a negative index or an index greater or equal to the string length).
 * @return Matching character.
 */


/**
 * @fn char String::operator[](int index) const;
 * Same as @ref charAt().
 */


/**
 * @fn String String::substring(int _off);
 * Get a substring starting at the given offset to the
 * end of the string.
 * @param _off	Offset to start from (It is an error to give
 * a negative index or an index greater than the string length).
 * @return		Matching substring.
 */


/**
 * @fn String String::substring(int _off, int _len);
 * Get a substring starting at the given offset and continuing to the given
 * length.
 * @param _off	Offset to start from (It is an error to give
 * a negative index or an index greater than the string length).
 * @param _len	Length of the substring (it is an error to have a length
 * out of the current string).
 * @return		Matching substring.
 */


/**
 * @fn String String::concat(const CString str) const;
 * Concatenate a string with a C string.
 * @param str	C string to concatenate after.
 * @return		Result of concatenation.
 */


/**
 * @fn String String::concat(const String& str) const;
 * Concatenate two strings.
 * @param str	String to concatenate after.
 * @return		Result of concatenation.
 */


/**
 * @fn int String::indexOf(char chr) const;
 * Get the first index of a character in the string.
 * @param chr	Character to look for.
 * @param index	Index of the character in the string or -1 if not
 * found.
 */


/**
 * @fn int String::indexOf(char chr, int pos) const;
 * Get the first index of a character in the string from the given position.
 * @param chr	Character to look for.
 * @param pos	Position to start to look for (it is an error to pass a negative
 * position or a position greater or equal to the string length).
 * @param index	Index of the character in the string or -1 if not
 * found.
 */


/**
 * @fn int String::lastIndexOf(char chr) const;
 * Get the last index of a character in the string.
 * @param chr	Character to look for.
 * @param index	Index of the character in the string or -1 if not
 * found.
 */


/**
 * @fn int String::lastIndexOf(char chr, int pos) const;
 * Get the last index of a character in the string from the given position.
 * @param chr	Character to look for.
 * @param pos	Position to start to look for (it is an error to pass a negative
 * or null position or a position greater to the string length).
 * @param index	Index of the character in the string or -1 if not
 * found.
 */


/**
 * @fn bool String::startsWith(const char *str) const;
 * Test if the string starts with the given C string.
 * @param str	C string to compare.
 * @return		True if the string starts with, false else.
 */
 

/**
 * @fn bool String::startsWith(const CString str) const;
 * Test if the string starts with the given C string.
 * @param str	C string to compare.
 * @return		True if the string starts with, false else.
 */


/**
 * @fn bool String::startsWith(const String& str) const;
 * Test if the string starts with the given string.
 * @param str	String to compare.
 * @return		True if the string starts with, false else.
 */


/**
 * @fn bool String::endsWith(const char *str) const;
 * Test if the string ends with the given C string.
 * @param str	C string to compare.
 * @return		True if the string ends with, false else.
 */


/**
 * @fn bool String::endsWith(const CString str) const;
 * Test if the string ends with the given string.
 * @param str	String to compare.
 * @return		True if the string ends with, false else.
 */


/**
 * @fn bool String::endsWith(const String& str) const;
 * Test if the string ends with the given string.
 * @param str	String to compare.
 * @return		True if the string ends with, false else.
 */

}	// elm
