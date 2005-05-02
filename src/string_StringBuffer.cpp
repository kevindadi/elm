/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * src/StringBuffer.cpp -- implementation for StringBuffer class.
 */

#include <stdio.h>
#include <elm/string/StringBuffer.h>

namespace elm {

/**
 * @class StringBuffer
 * As the ELM @ref String class is immutable, the big building of strings
 * may have a prohibitive cost. Instead, this class provides an economic way
 * of concatenating strings.
 */


/**
 * @fn StringBuffer::StringBuffer(int capacity, int increment);
 * Build a new string buffer.
 * @param capacity		Initial capacity of the buffer.
 * @param increment	Incrementation size when buffer is enlarged.
 */

	
/**
 * @fn String StringBuffer::toString(void);
 * Convert the buffer to a string. The string buffer must no more be used after this call.
 * @return String contained in the buffer.
 */
	
	
/**
 * @fn void StringBuffer::put(char chr);
 * Put a single character in the buffer.
 * @param chr	Character to put in the buffer.
 */


/**
 * @fn void StringBuffer::put(const char *block, int size);
 * Put a block a memory in the buffer.
 * @param block	Address of memory block to put.
 * @param size	Size of memory block.
 */


/**
 * @fn void StringBuffer::put(const char *cstring);
 * Put a C string in the buffer.
 * @param cstring	C string to put in the buffer.
 */


/**
 * @fn void StringBuffer::put(const CString str);
 * Put a CString object in the buffer.
 * @param str	CString to put in the buffer.
 */


/**
 * @fn void StringBuffer::put(const String& str);
 * Put a string in the buffer.
 * @param str	Strint to put in the buffer.
 */


/**
 * Put a formatted string in the buffer.
 * @param fmt		Format string as passed to vsprintf().
 * @param args	Arguments as passed to vsprintf().
 */
void StringBuffer::print(const char *fmt, va_list args) {
	
	// Allocate remaining memory
	int rem = buf.capacity() - buf.size();
	char *mem = buf.alloc(rem);
	int size = vsnprintf(mem, rem - 1, fmt, args);
	
	// Ok, fix the used size.
	if(size < rem)
		buf.setSize(buf.size() - (rem - size));
	
	// Else restart with enough place
	else {
		buf.setSize(buf.size() - rem);
		mem = buf.alloc(size + 1);
		vsnprintf(mem, size, fmt, args);
		buf.setSize(buf.size() - 1);
	}
}


/**
 * @fn void StringBuffer::print(const char *fmt, ...);
 * Print a formatted string as does the printf() from C standard IO.
 * @param fmt	Format string (see printf() manual).
 * @param ...	Argument for format string.
 */


/**
 * @fn int StringBuffer::length(void) const;
 * Get the length of the string stored in the buffer.
 * @return	String length.
 */


/**
 * @fn void StringBuffer::reset(void);
 * Remove all characters from the string buffer.
 */

} // elm
