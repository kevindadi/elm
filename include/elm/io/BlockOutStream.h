/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <casse@irit.fr>
 *
 * elm/io/BlockOutStream.h -- BlockOutStream class interface.
 */
#ifndef ELM_IO_BLOCK_OUT_STREAM_H
#define ELM_IO_BLOCK_OUT_STREAM_H

#include <elm/io/OutStream.h>
#include <elm/block/DynBlock.h>

namespace elm { namespace io {

// BlockOutStream class
class BlockOutStream: public OutStream {
	block::DynBlock _block;
public:
	inline BlockOutStream(int size = 4096, int inc = 256);
	inline const char *block(void) const;
	inline int size(void) const;
	inline char *detach(void);
	inline void clear(void);
	inline void setSize(int size);
	
	// OutStream overload
	virtual int write(const char *buffer, int size);
	virtual int write(char byte);
	virtual int flush(void);
};



// Inlines
inline BlockOutStream::BlockOutStream(int size, int inc): _block(size, inc) {
}
inline const char *BlockOutStream::block(void) const {
	return _block.base();
}
inline int BlockOutStream::size(void) const {
	return _block.size();
}
inline char *BlockOutStream::detach(void) {
	return _block.detach();
}
inline void BlockOutStream::clear(void) {
	_block.reset();
}
inline void BlockOutStream::setSize(int size) {
	_block.setSize(size);
}

} } // elm::io

#endif	// ELM_IO_BLOCK_OUT_STREAM_H
