/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <casse@irit.fr>
 *
 * src/BlockOutStream.cpp -- BlockOutStream class implementation.
 */

#include <elm/assert.h>
#include <string.h>
#include <elm/io/BlockOutStream.h>

namespace elm { namespace io {

/**
 * @class BlockOutStream
 * This class provides an out stream stocking output bytes in memory
 * in a continuous blocks.
 */


/**
 * @fn BlockOutStream::BlockOutStream(int size, int inc);
 * Build a new block output stream.
 * @param size	Initial size of the block.
 * @param inc	Value of the increment for enlarging the block.
 */


/**
 * @fn char *BlockOutStream::block(void) const;
 * Get a pointer on the start of the storage block. This pointer remains
 * only valid until an output is performed on the stream.
 * @return	Current storage memory block.
 */


/**
 * @fn int BlockOutStream::size(void) const;
 * Get the current size of stored bytes in this stream.
 */


/**
 * @fn char *BlockOutStream::detach(void);
 * Detach the block from the stream. After this call, the stream will
 * perform no management on the memory block and the caller is responsible
 * for deleting it.
 * It is an error to perform more output after this call unless
 * @ref restart() is called.
 * @return	Base of the block.
 */


/**
 * @fn void BlockOutStream::clear(void);
 * Clear the block receiving bytes from output.
 */


/**
 * @fn void BlockOutStream::setSize(int size);
 * Change the size of the current block.
 * @param size	New size occupied by the block.
 */


/**
 */	
int BlockOutStream::write(const char *buffer, int size) {
	_block.put(buffer, size);
	return 0;
}


/**
 */
int BlockOutStream::write(char byte) {
	_block.put(&byte, 1);
	return 0;
}


/**
 */
int BlockOutStream::flush(void) {
	return 0;
}


/**
 * Convert the buffer to a CString object.
 * (this object must not be used after this call and the caller is reponsible
 * for freeing the C string buffer).
 * @return	Buffer converted to C string.
 */
CString BlockOutStream::toCString(void) {
	write('\0');
	return CString(detach());
}


/**
 * Convert the buffer to a String object.
 * @return	String object.
 */
String BlockOutStream::toString(void) {
	return String(_block.base(), _block.size());
}

} }	// elm::io
