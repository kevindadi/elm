/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <casse@irit.fr>
 *
 * src/BlockInStream.cpp -- BlockInStream class implementation.
 */

#include <string.h>
#include <elm/io/BlockInStream.h>

namespace elm { namespace io {

/**
 * @class BlockInStream
 * Input stream from a memory block.
 */


/**
 * Build a new memory block input stream.
 * @param block	Block to read from.
 * @param size	Block size.
 */ 
BlockInStream::BlockInStream(char *block, int size)
: _block(block), _size(size), off(0) {
}
	

/**
 * @fn char *BlockInStream::block(void) const;
 * Get the current memory block.
 * @return	Memory block.
 */


/**
 * @fn int BlockInStream::size(void) const;
 * Get the size of the current memory block.
 * @return	Memory block size.
 */


/**
 * @fn int BlockInStream::mark(void) const;
 * Get the current offset in the memory block.
 * @return	Current offset.
 */


/**
 * @fn void BlockInStream::move(int mark);
 * Move the read position to the given mark.
 * @param mark	Position mark to move to.
 */
 
/**
 * @fn void BlockInStream::moveForward(int size);
 * Move forward in the stream.
 * @param size	Count of bytes to move forward to.
 */


/**
 * @fn void BlockInStream::moveBackward(int size);
 * Move backward in the stream.
 * @param size Count of bytes to move backward to.
 */


/**
 * @fn void BlockInStream::reset(void);
 * Reset the stream to the start.
 */


/**
 */	
int BlockInStream::read(char *buffer, int size) {
	
	// Check size
	if(off + size > _size)
		size = _size - off;
	
	// Perform the copy
	memcpy(buffer, _block + off, size);
	off += size;
	return size;
}


/**
 */
int BlockInStream::read(void) {
	if(off >= _size)
		return ENDED;
	else
		return (unsigned char)_block[off++];
}

} } // elm::io

