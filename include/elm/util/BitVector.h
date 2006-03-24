/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * elm/util/BitVector.h -- BitVector class interface.
 */
#ifndef ELM_UTIL_BIT_VECTOR_H
#define ELM_UTIL_BIT_VECTOR_H

#include <assert.h>
#include <memory.h>
#include <elm/io.h>
#include <elm/Iterator.h>

namespace elm {

// BitVector class
class BitVector {
	unsigned char *bits;
	int _size;
	inline void mask(void) const;
	inline int bytes(void) const;
	inline int byte_index(int index) const;
	inline int bit_index(int index) const;
public:
	inline BitVector(int size, bool set = false);
	inline BitVector(const BitVector& vec);
	BitVector(const BitVector& vec, int new_size);
	inline ~BitVector(void);
	
	inline int size(void) const;
	inline bool bit(int index) const;
	inline bool isEmpty(void) const;
	inline bool includes(const BitVector& vec) const;
	inline bool includesStrictly(const BitVector &vec) const;
	inline bool equals(const BitVector& vec) const;
	int countBits(void) const;
	
	inline void set(int index) const;
	inline void set(int index, bool value) const;
	inline void clear(int index) const;
	
	inline void copy(const BitVector& bits) const;
	inline void clear(void);
	inline void set(void);

	inline void applyNot(void);	
	inline void applyOr(const BitVector& vec);
	inline void applyAnd(const BitVector& vec);
	inline void applyReset(const BitVector& vec);
	
	inline BitVector makeNot(void) const;
	inline BitVector makeOr(const BitVector& vec) const;
	inline BitVector makeAnd(const BitVector& vec) const;
	inline BitVector makeReset(const BitVector& vec) const;
	
	void print(io::Output& out) const;
	
	// Iterator iter
	class OneIterator: public PreIterator<OneIterator, int> {
		const BitVector& bvec;
		int i;
	public:
		inline OneIterator(const BitVector& bit_vector);
		inline int item(void) const;
		inline bool ended(void) const;
		inline void next(void);		
	};
	
	// Operators
	inline operator bool(void) const;
	inline bool operator[](int index) const;
	inline BitVector operator~(void) const;
	inline BitVector operator|(const BitVector& vec) const;
	inline BitVector operator&(const BitVector& vec) const;
	inline BitVector operator+(const BitVector& vec) const;
	inline BitVector operator-(const BitVector& vec) const;
	inline BitVector& operator=(const BitVector& vec);
	inline BitVector& operator|=(const BitVector& vec);
	inline BitVector& operator&=(const BitVector& vec);
	inline BitVector& operator+=(const BitVector& vec);
	inline BitVector& operator-=(const BitVector& vec);
	inline bool operator==(const BitVector& vec) const;
	inline bool operator!=(const BitVector& vec) const;
	inline bool operator<(const BitVector& vec) const;
	inline bool operator<=(const BitVector& vec) const;
	inline bool operator>(const BitVector& vec) const;
	inline bool operator>=(const BitVector& vec) const;
};


// IO functions
inline io::Output& operator<<(io::Output& out, const BitVector& bvec) {
	bvec.print(out);
	return out;
}

// Inlines
inline int BitVector::bytes(void) const {
	return (_size + 7) / 8;
}

inline void BitVector::mask(void) const {
	unsigned char mask = 0xff >> (8 - (_size % 8));
	if(mask)
		bits[bytes() - 1] &= mask;
}

inline int BitVector::byte_index(int index) const {
	return index / 8;
}
inline int BitVector::bit_index(int index) const {
	return index % 8;
}

inline BitVector::BitVector(int size, bool set): _size(size) {
	assert(size > 0);
	bits = new unsigned char[bytes()];
	assert(bits);
	memset(bits, set ? 0xff : 0, bytes());
}

inline BitVector::BitVector(const BitVector& vec): _size(vec.size()) {
	bits = new unsigned char[bytes()];
	assert(bits);
	memcpy(bits, vec.bits, bytes());
}

inline BitVector::~BitVector(void) {
	delete [] bits;
}

inline int BitVector::size(void) const {
	return _size;
}

inline bool BitVector::bit(int index) const {
	assert(index < _size);
	return (bits[byte_index(index)] & (1 << bit_index(index))) != 0;
}

inline bool BitVector::isEmpty(void) const {
	mask();
	for(int i = 0; i < bytes(); i++)
		if(bits[i])
			return false;
	return true;
}

inline bool BitVector::includes(const BitVector& vec) const {
	assert(_size == vec._size);
	mask();
	for(int i = 0; i < bytes(); i++)
		if(~bits[i] & vec.bits[i])
			return false;
	return true;
}

inline bool BitVector::includesStrictly(const BitVector &vec) const {
	assert(_size == vec._size);
	mask();
	bool equal = true;
	for(int i = 0; i < bytes(); i++) {
		if(~bits[i] & vec.bits[i])
			return false;
		if(bits[i] != vec.bits[i])
			equal = false;
	}
	return !equal;
}

inline bool BitVector::equals(const BitVector& vec) const {
	assert(_size == vec._size);
	mask();
	for(int i = 0; i < bytes(); i++)
		if(bits[i] != vec.bits[i])
			return false;
	return true;
}

inline void BitVector::set(int index) const {
	assert(index < _size);
	bits[byte_index(index)] |= 1 << bit_index(index);
}

inline void BitVector::set(int index, bool value) const {
	assert(index < _size);
	if(value)
		set(index);
	else
		clear(index);	
}

inline void BitVector::clear(int index) const {
	assert(index < _size);
	bits[byte_index(index)] &= ~(1 << bit_index(index));
}

inline void BitVector::copy(const BitVector& vec) const {
	assert(_size == vec._size);
	memcpy(bits, vec.bits, bytes());
}

inline void BitVector::clear(void) {
	memset(bits, 0, bytes());
}

inline void BitVector::set(void) {
	memset(bits, 0xff, bytes());
}

inline void BitVector::applyNot(void) {
	for(int i = 0; i < bytes(); i++)
		bits[i] = ~bits[i];
}

inline void BitVector::applyOr(const BitVector& vec) {
	assert(_size == vec._size);
	for(int i = 0; i < bytes(); i++)
		bits[i] |= vec.bits[i];
}

inline void BitVector::applyAnd(const BitVector& vec) {
	assert(_size == vec._size);
	for(int i = 0; i < bytes(); i++)
		bits[i] &= vec.bits[i];
}

inline void BitVector::applyReset(const BitVector& vec) {
	assert(_size == vec._size);
	for(int i = 0; i < bytes(); i++)
		bits[i] &= ~vec.bits[i];
	mask();
}

inline BitVector BitVector::makeNot(void) const {
	BitVector vec(_size);
	for(int i = 0; i < bytes(); i++)
		vec.bits[i] = ~ bits[i];
	return vec;
}

inline BitVector BitVector::makeOr(const BitVector& vec) const {
	assert(_size == vec._size);
	BitVector res(_size);
	for(int i = 0; i < bytes(); i++)
		res.bits[i] = bits[i] | vec.bits[i];
	return res;
}

inline BitVector BitVector::makeAnd(const BitVector& vec) const {
	assert(_size == vec._size);
	BitVector res(_size);
	for(int i = 0; i < bytes(); i++)
		res.bits[i] = bits[i] & vec.bits[i];
	return res;
}

inline BitVector BitVector::makeReset(const BitVector& vec) const {
	assert(_size == vec._size);
	BitVector res(_size);
	for(int i = 0; i < bytes(); i++)
		res.bits[i] = bits[i] & ~vec.bits[i];
	return res;
}

inline BitVector::operator bool(void) const {
	return !isEmpty();
}

inline bool BitVector::operator[](int index) const {
	return bit(index);
}

inline BitVector BitVector::operator~(void) const {
	return makeNot();
}

inline BitVector BitVector::operator|(const BitVector& vec) const {
	return makeOr(vec);
}

inline BitVector BitVector::operator&(const BitVector& vec) const {
	return makeAnd(vec);
}

inline BitVector BitVector::operator+(const BitVector& vec) const {
	return makeOr(vec);
}

inline BitVector BitVector::operator-(const BitVector& vec) const {
	return makeReset(vec);
}

inline BitVector& BitVector::operator=(const BitVector& vec) {
	copy(vec);
	return *this;
}

inline BitVector& BitVector::operator|=(const BitVector& vec) {
	applyOr(vec);
	return *this;
}

inline BitVector& BitVector::operator&=(const BitVector& vec) {
	applyAnd(vec);
	return *this;
}

inline BitVector& BitVector::operator+=(const BitVector& vec) {
	applyOr(vec);
	return *this;
}

inline BitVector& BitVector::operator-=(const BitVector& vec) {
	applyReset(vec);
	return *this;
}

inline bool BitVector::operator==(const BitVector& vec) const {
	return equals(vec);
}

inline bool BitVector::operator!=(const BitVector& vec) const {
	return !equals(vec);
}

inline bool BitVector::operator<(const BitVector& vec) const {
	return vec.includesStrictly(*this);
}

inline bool BitVector::operator<=(const BitVector& vec) const {
	return vec.includes(*this);
}

inline bool BitVector::operator>(const BitVector& vec) const {
	return includesStrictly(vec);
}

inline bool BitVector::operator>=(const BitVector& vec) const {
	return includes(vec);
}


// BitVector::OneIterator inlines
inline BitVector::OneIterator::OneIterator(const BitVector& bit_vector)
: bvec(bit_vector), i(-1) {
	next();
}

inline int BitVector::OneIterator::item(void) const {
	return i;
}

inline bool BitVector::OneIterator::ended(void) const {
	return i >= bvec.size();
}

inline void BitVector::OneIterator::next(void) {
	do
		i++;
	while(i < bvec.size() && !bvec.bit(i));
}

} // elm

#endif	// ELM_UTIL_BIT_VECTOR_H
