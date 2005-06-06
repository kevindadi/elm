/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <casse@irit.fr>
 *
 * elm/io/BlockOutStream.h -- BlockOutStream class interface.
 */
#ifndef ELM_IO_BLOCK_OUT_STREAM_H
#define ELM_IO_BLOCK_OUT_STREAM_H

#include <elm/io/OutStream.h>

namespace elm { namespace io {

// BlockOutStream class
class BlockOutStream: public OutStream {
	char *_block;
	int _size, max;
	void enlarge(int min_size);
public:
	BlockOutStream(int size = 4096);
	virtual ~BlockOutStream(void);
	inline char *block(void) const;
	inline int size(void) const;
	void detach(void);
	void clear(void);
	void restart(void);
	
	// OutStream overload
	virtual int write(const char *buffer, int size);
	virtual int write(char byte);
	virtual int flush(void);
};



// Inlines
inline char *BlockOutStream::block(void) const {
	return _block;
}
inline int BlockOutStream::size(void) const {
	return _size;
}

} } // elm::io

#endif	// ELM_IO_BLOCK_OUT_STREAM_H
