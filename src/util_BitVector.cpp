/*
 *	BitVector class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
 * 
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software 
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/util/BitVector.h>
#include <elm/int.h>
#include <elm/compare.h>
#include <elm/array.h>
#include <memory.h>

namespace elm {

/**
 * @class BitVector
 * <p>This class provides facilities for managing vector of bits in an optimized
 * way.</p>
 * <p>Notice that vector is represented as a contiguous block of memory. This
 * bit vector representation is clearly not performant for sparse vectors.</p>
 * @ingroup utility
 */


/**
 * @fn BitVector::BitVector(int size, bool set);
 * Build a bit vector of the given size.
 * @param size	Count of bits in the vector.
 * @param set	Initial value of bits (default to 0).
 */
BitVector::BitVector(int size, bool set): _size(size) {
	ASSERTP(size > 0, "size must be positive");
	bits = new word_t[wcount()];
	ASSERT(bits);
	memset(bits, set ? 0xff : 0, wcount() * sizeof(word_t));
}


/**
 * @fn BitVector::BitVector(const BitVector& vec);
 * Build a vector by copying the given one.
 * @param vec	Vector to copy.
 */
BitVector::BitVector(const BitVector& vec): _size(vec.size()) {
	bits = new word_t[wcount()];
	ASSERT(bits);
	memcpy(bits, vec.bits, wcount() * sizeof(word_t));
}


/**
 * Build a vector by extending or reducing the given one.
 * @param vec		Vector to extend or to reduce.
 * @param new_size	Size of the built vector.
 */
BitVector::BitVector(const BitVector& vec, int new_size): _size(new_size) {
	ASSERTP(new_size > 0, "size must be positive");
	bits = new word_t[wcount()];
	if(new_size >= vec._size) {
		memcpy(bits, vec.bits, vec._size);
		memset(bits + vec.wcount(), 0, wcount() - vec.wcount());
	}
	else {
		memcpy(bits, vec.bits, wcount());
		mask();
	}
}


/**
 * Same as copy().
 */
BitVector& BitVector::operator=(const BitVector& vec) {
	if(wcount() && wcount() == vec.wcount())
		copy(vec);
	else {
		if(bits)
			delete bits;
		if(!vec.bits)
			bits = 0;
		else {
			_size = vec._size;
			bits = new word_t[wcount()];
			copy(vec);
		}
	}
	return *this;
}



/**
 * @fn int BitVector::size(void) const;
 * Get the size in bits of the vector.
 * @return	Vector size.
 */


/**
 * @fn bool BitVector::bit(int index) const;
 * Get the value of a bit. It is an error to pass index higher than vector size.
 * @param index	Bit index.
 * @return		Value of the bit.
 */


/**
 * @fn bool BitVector::isEmpty(void) const;
 * Test if the vector is empty.
 * @return	True if no bit is set, false else.
 */


/**
 * Test if the current vector includes the given one.
 * @param vec	Vector to use.
 * @return		True if the inclusion holds, false else.
 */
bool BitVector::includes(const BitVector& vec) const {
	ASSERTP(_size == vec._size, "bit vector must have the same size");
	mask();
	for(int i = 0; i < wcount(); i++)
		if(~bits[i] & vec.bits[i])
			return false;
	return true;
}


/**
 * Test if the current vector includes strictly the given one.
 * @param vec	Vector to use.
 * @return		True if the strict inclusion holds, false else.
 */
bool BitVector::includesStrictly(const BitVector &vec) const {
	ASSERTP(_size == vec._size, "bit vector must have the same size");
	mask();
	bool equal = true;
	for(int i = 0; i < wcount(); i++) {
		if(~bits[i] & vec.bits[i])
			return false;
		if(bits[i] != vec.bits[i])
			equal = false;
	}
	return !equal;
}


/**
 * Test if two vectors are equals.
 * @param vec	Second vector to test with.
 * @return		True if the vectors are equal, false else.
 */
bool BitVector::equals(const BitVector& vec) const {
	ASSERTP(_size == vec._size, "bit vector must have the same size");
	mask();
	for(int i = 0; i < wcount(); i++)
		if(bits[i] != vec.bits[i])
			return false;
	return true;
}


/**
 * @fn void BitVector::set(int index) const;
 * Set to true a bit.
 * @param index	Index of the bit to set. It must be higher or equal to vector
 * size.
 */
void BitVector::set(void) {
	memset(bits, 0xff, wcount() * sizeof(word_t));
	mask();
}


/**
 * @fn void BitVector::set(int index, bool value) const;
 * Set the value of a bit.
 * @param index	Index of the bit to set. It must be higher or equal to vector
 * size.
 * @param value	Value of the bit.
 */


/**
 * @fn void BitVector::clear(int index) const;
 * Set a bit to false.
 * @param index Index of the bit to set. It must be higher or equal to vector
 * size.
 */


/**
 * Copy the giuven vector in the current vector.
 * @param vec	Vector to copy from.
 */
void BitVector::copy(const BitVector& vec) const {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	memcpy(bits, vec.bits, wcount() * sizeof(word_t));
}


/**
 * Set to false all bits in the vector.
 */
void BitVector::clear(void) {
	memset(bits, 0, wcount() * sizeof(word_t));
}


/**
 * @fn void BitVector::applyNot(void);	
 * Apply NOT-operator on the current vector.
 */
void BitVector::applyNot(void) {
	for(int i = 0; i < wcount(); i++)
		bits[i] = ~bits[i];
}



/**
 * @fn void BitVector::applyOr(const BitVector& vec);
 * Apply the OR-operation on this vector with given one.
 * @param vec	Vector to process with.
 */
void BitVector::applyOr(const BitVector& vec) {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	for(int i = 0; i < wcount(); i++)
		bits[i] |= vec.bits[i];
}


/**
 * @fn void BitVector::applyAnd(const BitVector& vec);
 * Apply the AND-operation on this vector with given one.
 * @param vec	Vector to process with.
 */
void BitVector::applyAnd(const BitVector& vec) {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	for(int i = 0; i < wcount(); i++)
		bits[i] &= vec.bits[i];
}


 
/**
 * @fn void BitVector::applyReset(const BitVector& vec);
 * Apply the RESET-operation (current & ~vec) on this vector with given one.
 * @param vec	Vector to process with.
 */
void BitVector::applyReset(const BitVector& vec) {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	for(int i = 0; i < wcount(); i++)
		bits[i] &= ~vec.bits[i];
	mask();
}


 
/**
 * Build a new vector as the result of operation NOT of the current vector.
 * @return	Result of NOT on current vector.
 */
BitVector BitVector::makeNot(void) const {
	BitVector vec(_size);
	for(int i = 0; i < wcount(); i++)
		vec.bits[i] = ~ bits[i];
	return vec;
}

/**
 * Build a new vector as the result of operation OR on the current vector and
 * the given one.
 * @param vec	Second vector of operation.
 * @return		Result of OR operation.
 */
BitVector BitVector::makeOr(const BitVector& vec) const {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	BitVector res(_size);
	for(int i = 0; i < wcount(); i++)
		res.bits[i] = bits[i] | vec.bits[i];
	return res;
}

/**
 * Build a new vector as the result of operation AND on the current vector and
 * the given one.
 * @param vec	Second vector of operation.
 * @return		Result of AND operation.
 */

BitVector BitVector::makeAnd(const BitVector& vec) const {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	BitVector res(_size);
	for(int i = 0; i < wcount(); i++)
		res.bits[i] = bits[i] & vec.bits[i];
	return res;
}


/**
 * Build a new vector as the result of operation RESET on the current vector and
 * the given one.
 * @param vec	Second vector of operation.
 * @return		Result of RESET operation.
 */
BitVector BitVector::makeReset(const BitVector& vec) const {
	ASSERTP(_size == vec._size, "bit vectors must have the same size");
	BitVector res(_size);
	for(int i = 0; i < wcount(); i++)
		res.bits[i] = bits[i] & ~vec.bits[i];
	return res;
}


/**
 * @fn BitVector::operator bool(void) const;
 * Same as NOT isEmpty().
 */


/**
 * @fn bool BitVector::operator[](int index) const;
 * Same as bit().
 */


/**
 * @fn BitVector BitVector::operator~(void) const;
 * Same as makeNot().
 */


/**
 * @fn BitVector BitVector::operator|(const BitVector& vec) const;
 * Same as makeOr().
 */


/**
 * @fn BitVector BitVector::operator&(const BitVector& vec) const;
 * Same as makeAnd().
 */


/**
 * @fn BitVector BitVector::operator+(const BitVector& vec) const;
 * Same makeOr().
 */


/**
 * @fn BitVector BitVector::operator-(const BitVector& vec) const;
 * Same as makeReset().
 */


/**
 * @fn BitVector& BitVector::operator|=(const BitVector& vec);
 * Same as applyOr().
 */


/**
 * @fn BitVector& BitVector::operator&=(const BitVector& vec);
 * Same as applyAnd().
 */


/**
 * @fn BitVector& BitVector::operator+=(const BitVector& vec);
 * Same as applyOr().
 */


/**
 * @fn BitVector& BitVector::operator-=(const BitVector& vec);
 * Same makeReset().
 */


/**
 * @fn bool BitVector::operator==(const BitVector& vec) const;
 * Same as equals().
 */


/**
 * @fn bool BitVector::operator!=(const BitVector& vec) const;
 * Same as NOT equals().
 */


/**
 * @fn bool BitVector::operator<(const BitVector& vec) const;
 * Same as includesStrictly().
 */


/**
 * @fn bool BitVector::operator<=(const BitVector& vec) const;
 * Same as includes().
 */


/**
 * @fn bool BitVector::operator>(const BitVector& vec) const;
 * Reverse form of includesStricly().
 */


/**
 * @fn bool BitVector::operator>=(const BitVector& vec) const;
 * Reverse form of includes().
 */


/**
 * Print the bit vector in a binary form.
 * @param out	Output to use.
 */
void BitVector::print(io::Output& out) const {
	for(int i = size() - 1; i >= 0; i--) {
		out << (bit(i) ? '1' : '0');
		if(!(i & 0x7))
			out << ' ';
	}
}


/**
 * Count the number of bits whose value is 1.
 */
int BitVector::countBits(void) const {
	int result = 0;
	for(int i = 0; i < wcount(); i++)
		result += elm::ones(bits[i]);
	return result;
}


/**
 * Test if vectors have some bit to 1 in common.
 * @param bv	Bit vector to compare with.
 * @return		True if there is something common, false else.
 */
bool BitVector::meets(const BitVector& bv) {
	int s = min(wcount(), bv.wcount());
	for(int i = 0; i < s; i++)
		if(bits[i] & bv.bits[i])
			return true;
	return false;
}



/**
 * @class Iterator::OneIterator
 * This class represents an iterator on the bits containing a one in a bit
 * vector. As a value, it returns the bit vector positions containing a 1.
 * @note May be fully improved by benefiting from the test a full byte
 * for presence of at least a one inside.
 */


/**
 * @fn BitVector::OneIterator::OneIterator(const BitVector& bit_vector);
 * Build a new bit-to-one iterator.
 * @param bit_vector	Bit vector to iterate on.
 */


/**
 * @fn int BitVector::countOnes(void) const;
 * Count the number of ones in the vector.
 * @return	Number of ones.
 */
int BitVector::countOnes(void) const {
	int cnt = 0;
	for(int i = 0; i < wcount(); i++)
		cnt += ones(bits[i]);
	return cnt;
}


/**
 * @fn int BitVector::countZeroes(void) const;
 * Count the number of zeroes in the vector.
 * @return	Number of zeroes.
 */


/**
 * Resize the vector.
 * @param new_size	New size (in bits).
 */
void BitVector::resize(int new_size) {
	int new_wcount = inWords(new_size);
	if(wcount() != new_wcount) {
		word_t *new_bits = new word_t[new_wcount];
		if(bits != nullptr) {
			array::copy(new_bits, bits,min(wcount(),new_wcount) );
			delete [] bits;
		}
		bits = new_bits;
	}
	_size = new_size;
}


#ifdef EXPERIMENTAL
/**
 * @fn void BitVector::shiftLeft(int n);
 * Shift the vector for n positions to the left.
 * @param n	Shift positions (default to 1).
 */


/**
 * @fn BitVector BitVector::makeShiftLeft(int n = 1) const;
 * Build a new vector from the current one shifted n bits to left.
 * @param n	Shift.
 * @return	Built vectior.
 */

/**
 * Actual implementation of shift left.
 * @param n		Number of bits to shift.
 * @param tbits	Storage for results.
 */
void BitVector::doShiftLeft(int n, word_t *tbits) const {
	ASSERT(n >= 0);
	if(n == 0)
		return;
	int B = wcount();
	int bs = bindex(n);
	int Bs = windex(n);
	for(int i = B - 1; i > Bs; i--)
		tbits[i] = (bits[i - Bs] << bs) | (bits[i - Bs - 1] >> (wsize() - bs));
	tbits[Bs] = bits[0] << bs;
	for(int i = 0; i < Bs; i++)
		tbits[i] = 0;
	mask(tbits);
}

/**
 * @fn void BitVector::shiftRight(int n);
 * Shift the vector for n positions to the right.
 * @param n	Shift positions (default to 1).
 */

/**
 * Actual implementation of shift right.
 * @param n		Number of bits to shift.
 * @param tbits	Storage for results.
 */
void BitVector::doShiftRight(int n, word_t *tbits) const {
	ASSERT(n >= 0);
	if(n == 0)
		return;
	int B = wcount();
	int bs = bindex(n);
	int Bs = windex(n);
	for(int i = 0; i < B - Bs - 1; i++)
		tbits[i] = (bits[i + Bs] >> bs) | (bits[i + Bs + 1] << (wsize() - bs));
	tbits[B - Bs - 1] = bits[B - 1] >> bs;
	for(int i = B - 1; i > B - Bs - 1; i--)
		tbits[i] = 0;
}

/**
 * Actual implementation of left rotation.
 * @param n		Number of rotation bits.
 * @param tbits	Target bits.
 */
void BitVector::doRotateLeft(int n, word_t *tbits) const {
	ASSERT(n >= 0);
	if(n > _size)
		n = n % _size;
	if(n == 0)
		return;

	/*
	 *	Operation: v <<< k
	 *
	 *	 B-1                            Bs    BS-1   0
	 *	+-----+-----+-----+-----+-----+-----+-----+-----+
	 *	|     |     |     |     |     |     |     |     |
	 *	+-----+-----+-----+-----+-----+-----+-----+-----+
	 *	  ^							  |  ^              ^
	 *	  | eb                        |  |----- k ------|
	 *	                              ^  ^   ^          ^
	 *	                              |rs|bs-|--- Bs ---|
	 */

	int B = wcount();
	int bs = bindex(n);
	int Bs = windex(n);
	int eb = bindex(_size);
	int rs = wsize() - bs;		// bs + rs == wsize
	word_t S[Bs + 1];


	// build the word at vector limit
	if(eb == 0)				// end of word aligned
		S[Bs] = (bits[B - 1] << bs) | (bits[0] >> rs);
	else if(bs <= eb)		// enough shift in last
		S[Bs] = (bits[0] << bs) | (bits[B - 1] >> (eb - bs));
	else					// not enough shift in last word ==> aggregate last two words end
		S[Bs] = (bits[0] << bs) | (bits[B - 1] << (bs - eb)) | (bits[B - 2] >> (wsize() - (bs - eb)));

	// CHECK the following

	// build other overlapping words
	for(int i = 0; i < Bs; i++)
		S[i] = (bits[B - Bs + i - 1] << bs) | (bits[B - i - 1] >> (wsize() - bs));

	// shift the bits
	for(int i = B - 1; i > Bs; i--)
		tbits[i] = (bits[i - Bs] << bs) | (bits[i - Bs - 1] >> (wsize() - bs));
	mask();

	// copy the headers
	for(int i = 0; i <= Bs; i++)
		tbits[i] = S[i];
	if(eb != 0)
		tbits[Bs] = S[Bs];
}


/**
 * Actual implementation of right rotation.
 * @param n		Number of rotation bits.
 * @param tbits	Target bits.
 */
void BitVector::doRotateRight(int n, word_t *tbits) const {
	ASSERT(n >= 0);
	if(n > _size)
		n = n % _size;
	if(n == 0)
		return;
	int B = wcount();
	int bs = bindex(n);
	int Bs = windex(n);
	int eb = bindex(_size);

	// shift bits
	word_t first = bits[0];
	for(int i = 0; i < B - 1; i++)
		tbits[i] = (bits[i] >> bs) | (bits[i + 1] << (wsize() - bs));
	if(bs < eb)
		tbits[B - 1] = (bits[B - 1] >> bs) | (first << (eb - bs));
	else {
		tbits[B - 2] |= first << (B - (bs - eb));
		tbits[B - 1] = first >> (bs - eb);
	}
	mask();

	// shift words
	if(Bs) {
		array::reverse(tbits, B);
		array::reverse(tbits, B - Bs);
		array::reverse(tbits + B - Bs, Bs);
	}
}

/**
 * @fn void BitVector::rotateLeft(int n = 1);
 * Rotate the bits of the current vector n positions to left (increasing indexes-wise).
 * @param n		Rotated positions (default to 1).
 */

/**
 * @fn void BitVector::rotateRight(int n = 1);
 * Rotate the bits of the current vector n positions to right (decreasing indexes-wise).
 * @param n		Rotated positions (default to 1).
 */

/**
 * @fn BitVector BitVector::makeRotateLeft(int n = 1) const;
 * Build a new bit vector by rotating the bits of the current vector n position to the left
 * (increasing indexes-wise).
 * @param n	Rotated positions (default to 1).
 * @return	Rotated vector.
 */

/**
 * @fn BitVector BitVector::makeRotateRight(int n = 1) const;
 * Build a new bit vector by rotating the bits of the current vector n position to the right
 * (decreasing indexes-wise).
 * @param n	Rotated positions (default to 1).
 * @return	Rotated vector.
 */
#endif

} // elm
