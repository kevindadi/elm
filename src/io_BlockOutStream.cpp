/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <casse@irit.fr>
 *
 * src/BlockOutStream.cpp -- BlockOutStream class implementation.
 */

#include <assert.h>
#include <string.h>
#include <elm/io/BlockOutStream.h>

namespace elm { namespace io {

/**
 * @class BlockOutStream
 * This class provides an out stream stocking output bytes in memory
 * in a continuous blocks.
 */


/**
 * Build a new block output stream.
 * @param size	Initial size of the block.
 */
BlockOutStream::BlockOutStream(int size): _size(0), max(size) {
	assert(size > 0);
	_block = new char[size];
	assert(_block);
};


/**
 */
BlockOutStream::~BlockOutStream(void) {
	if(_block)
		delete [] _block;
}


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
 * Detach the block from the stream. After this call, the stream will
 * perform no management on the memory block and the caller is responsible
 * for deleting it.
 * It is an error to perform more output after this call unless
 * @ref restart() is called.
 */
void BlockOutStream::detach(void) {
	_block = 0;
	_size = 0;
}


/**
 * Clear the block receiving bytes from output.
 */
void BlockOutStream::clear(void) {
	_size = 0;
}


/**
 * Build a new block where output bytes will be stored.
 * This call must only be done after a @ref detach() call.
 */
void BlockOutStream::restart(void) {
	assert(!_block);
	_block = new char[max];
	assert(_block);
}


/**
 */	
int BlockOutStream::write(const char *buffer, int size) {
	if(size + _size > max)
		enlarge(size + _size - max);
	memcpy(_block + _size, buffer, size);
	_size += size;
}


/**
 */
int BlockOutStream::write(char byte) {
	if(_size + 1 > max)
		enlarge(1);
	_block[_size] = byte;
	_size++;
}


/**
 */
int BlockOutStream::flush(void) {
}


/**
 * Enlarge the current block.
 * @param min_size	Minimum required size.
 */
void BlockOutStream::enlarge(int min_size) {
	
	// Compute the new size
	min_size += _size;
	while(max < min_size)
		max *= 2;
	
	// Reallocate a block
	char *old_block = _block;
	_block = new char[max];
	memcpy(_block, old_block, _size);
}

} }	// elm::io
