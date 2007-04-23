/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <casse@irit.fr>
 *
 * elm/io/BlockInStream.h -- BlockInStream class interface.
 */
#ifndef ELM_IO_BLOCK_IN_STREAM_H
#define ELM_IO_BLOCK_IN_STREAM_H

#include <elm/assert.h>
#include <elm/string.h>
#include <elm/io/InStream.h>

namespace elm { namespace io {

// BlockInStream class
class BlockInStream: public InStream {
	const char *_block;
	int _size, off;
public:

	BlockInStream(const void *block, int size);
	BlockInStream(const char *string);
	BlockInStream(const CString& string);
	BlockInStream(const String& string); 
	inline const void *block(void) const;
	inline int size(void) const;
	inline int mark(void) const;
	inline void move(int mark);
	inline void moveForward(int size);
	inline void moveBackward(int size);
	inline void reset(void);
	
	// InStream overload
	virtual int read(void *buffer, int size);
	virtual int read(void);
};

// Inlines
inline const void *BlockInStream::block(void) const {
	return _block;
}

inline int BlockInStream::size(void) const {
	return _size;
}

inline int BlockInStream::mark(void) const {
	return off;
}

inline void BlockInStream::move(int mark) {
	ASSERT(mark < _size);
	off = mark;
}

inline void BlockInStream::moveForward(int size) {
	ASSERTP(off + size <= _size, "move out of block");
	off += _size;
}

inline void BlockInStream::moveBackward(int size) {
	ASSERTP(off - size >= 0, "move out of block");
	off -= size;
}

inline void BlockInStream::reset(void) {
	off = 0;
}

} } // elm::io

#endif	// ELM_IO_BLOCK_IN_STREAM_H
