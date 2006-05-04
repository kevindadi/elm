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
 * @fn int StringBuffer::length(void) const;
 * Get the length of the string stored in the buffer.
 * @return	String length.
 */


/**
 * @fn void StringBuffer::reset(void);
 * Remove all characters from the string buffer.
 */


/**
 * @fn io::OutStream& StringBuffer::stream(void);
 * Get the an output stream to write to the string buffer.
 * @return	Stream to the string buffer.
 */

} // elm
