/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/block/DynBlock.h -- interface for DynBlock class.
 */
#ifndef ELM_BLOCK_DYNBLOCK_H
#define ELM_BLOCK_DYNBLOCK_H

namespace elm { namespace block {

// DynBlock class
class DynBlock {
	int _size, cap, inc;
	char *buf;
	void grow(int min);
public:
	inline DynBlock(int capacity = 256, int increment = 64);
	inline ~DynBlock(void);
	void put(const char *block, int size);
	void get(char *block, int size, int pos);
	char *alloc(int size);
	inline int size(void) const;
	inline int capacity(void) const;
	inline int increment(void) const;
	inline void setSize(int new_size);
	inline void reset(void);
	inline const char *base(void) const;
	inline char *detach(void);
};

// Inlines
inline DynBlock::DynBlock(int capacity, int increment)
: _size(0), cap(capacity), inc(increment), buf(new char[capacity]) {
}
inline DynBlock::~DynBlock(void) {
	if(buf)
		delete [] buf;
}
inline int DynBlock::size(void) const {
	return _size;
}
inline int DynBlock::capacity(void) const {
	return cap;
}
inline int DynBlock::increment(void) const {
	return inc;
}
inline void DynBlock::setSize(int new_size) {
	_size = new_size;
}
inline void DynBlock::reset(void) {
	_size = 0;
}
inline char *DynBlock::detach(void) {
	char *result = buf;
	buf = 0;
	return result;
}
inline const char *DynBlock::base(void) const {
	return buf;
}

} } // elm::block

#endif // ELM_BLOCK_DYNBLOCK_H
