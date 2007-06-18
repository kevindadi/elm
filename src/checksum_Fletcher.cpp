/*
 * $Id$
 * Copyright (c) 2007 IRIT-UPS <casse@irit.fr>
 * 
 * checksum::Fletcher class implementation
 */ 

#include <elm/checksum/Fletcher.h>
#include <elm/util/MessageException.h>
#include <elm/io/BlockInStream.h>

namespace elm { namespace checksum {

/**
 * @class Fletcher
 * Apply the Fletcher algorithm (http://en.wikipedia.org/wiki/Fletcher%27s_checksum)
 * to compute a checksum.
 * 
 * Data are checksummed calling any one of the @ref put() methods.
 * When all data has been checksummed, the checksum value is returned by
 * @ref sum. 
 */


/**
 * Build a new Fletcher checksum builder.
 */
Fletcher::Fletcher(void)
:	len(0),
	sum1(0xffff),
	sum2(0xffff),
	size(0)
{
}


/**
 */
void Fletcher::shuffle(void) {
	sum1 = (sum1 & 0xffff) + (sum1 >> 16);
	sum2 = (sum2 & 0xffff) + (sum2 >> 16);
	len = 0;
}


/**
 */
void Fletcher::add(void) {
	sum1 += *(unsigned short *)half;
	sum2 += sum1;
	len += 2;
	if(len == 360)
		shuffle();
}


/**
 * Checksum the given stream.
 * @param in		Stream to checksum.
 */
void Fletcher::put(io::InStream& in) {
	while(true) {
		int result = in.read(half + size, 2 - size);
		if(result < 0)
			throw MessageException("elm::checksum::Fletcher: error during stream read");
		size += result;
		if(size != 2)
			break;
		size = 0;
		add();
	}
}


/**
 * Return the checksum.
 * @param checksum	Current checksum.
 */
unsigned long Fletcher::sum(void) {
	if(size == 1) {
		half[1] = 0;
		add();
	}
	shuffle();
	return (sum2 << 16) | sum1;
}


/**
 * Put a data block in the checksum.
 * @param block		Block address.
 * @param length	Block length.
 */
void Fletcher::put(const void *block, int length) {
	io::BlockInStream stream(block, length);
	put(stream);
}


/**
 * Put a C string in the checksum.
 * @param str	C string to put in.
 */
void Fletcher::put(const CString& str) {
	io::BlockInStream stream(str);
	put(stream);
}


/**
 * Put a string in the checksum.
 * @param str	String to put in.
 */
void Fletcher::put(const String& str) {
	io::BlockInStream stream(str);
	put(stream);	
}

} } // elm::checksum
