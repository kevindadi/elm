/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * src/util_BitVector.cpp -- BitVector class implementation.
 */

#include <elm/util/BitVector.h>

namespace elm {

/**
 * @class BitVector
 * <p>This class provides facilities for managing vector of bits in an optimized
 * way.</p>
 * <p>Notice that vector is represented as a contiguous block of memory. This
 * bit vector representation is clearly not performant for sparse vectors.</p>
 */


/**
 * @fn BitVector::BitVector(int size);
 * Build a bit vector of the given size.
 * @param size	Count of bits in the vector.
 */


/**
 * @fn BitVector::BitVector(const BitVector& vec);
 * Build a vector by copying the given one.
 * @param vec	Vector to copy.
 */


/**
 * Build a vector by extending or reducing the given one.
 * @param vec		Vector to extend or to reduce.
 * @param new_size	Size of the built vector.
 */
BitVector::BitVector(const BitVector& vec, int new_size): _size(new_size) {
	assert(new_size > 0);
	bits = new unsigned char[bytes()];
	if(new_size >= vec._size) {
		memcpy(bits, vec.bits, vec._size);
		memset(bits + vec.bytes(), 0, bytes() - vec.bytes());
	}
	else {
		memcpy(bits, vec.bits, bytes());
		mask();
	}
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
 * @fn bool BitVector::includes(const BitVector& vec) const;
 * Test if the current vector includes the given one.
 * @param vec	Vector to use.
 * @return		True if the inclusion holds, false else.
 */


/**
 * @fn bool BitVector::includesStrictly(const BitVector &vec) const;
 * Test if the current vector includes strictly the given one.
 * @param vec	Vector to use.
 * @return		True if the strict inclusion holds, false else.
 */


/**
 * @fn bool BitVector::equals(const BitVector& vec) const;
 * Test if two vectors are equals.
 * @param vec	Second vector to test with.
 * @return		True if the vectors are equal, false else.
 */


/**
 * @fn void BitVector::set(int index) const;
 * Set to true a bit.
 * @param index	Index of the bit to set. It must be higher or equal to vector
 * size.
 */


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
 * @fn void BitVector::copy(const BitVector& vec) const;
 * Copy the giuven vector in the current vector.
 * @param vec	Vector to copy from.
 */


/**
 * @fn void BitVector::clear(void);
 * Set to false all bits in the vector.
 */


/**
 * @fn void BitVector::applyNot(void);	
 * Apply NOT-operator on the current vector.
 */


/**
 * @fn void BitVector::applyOr(const BitVector& vec);
 * Apply the OR-operation on this vector with given one.
 * @param vec	Vector to process with.
 */


/**
 * @fn void BitVector::applyAnd(const BitVector& vec);
 * Apply the AND-operation on this vector with given one.
 * @param vec	Vector to process with.
 */

 
/**
 * @fn void BitVector::applyReset(const BitVector& vec);
 * Apply the RESET-operation (current & ~vec) on this vector with given one.
 * @param vec	Vector to process with.
 */
 

/**
 * @fn BitVector BitVector::makeNot(void) const;
 * Build a new vector as the result of operation NOT of the current vector.
 * @return	Result of NOT on current vector.
 */


/**
 * @fn BitVector BitVector::makeOr(const BitVector& vec) const;
 * Build a new vector as the result of operation OR on the current vector and
 * the given one.
 * @param vec	Second vector of operation.
 * @return		Result of OR operation.
 */


/**
 * @fn BitVector BitVector::makeAnd(const BitVector& vec) const;
 * Build a new vector as the result of operation AND on the current vector and
 * the given one.
 * @param vec	Second vector of operation.
 * @return		Result of AND operation.
 */


/**
 * @fn BitVector BitVector::makeReset(const BitVector& vec) const;
 * Build a new vector as the result of operation RESET on the current vector and
 * the given one.
 * @param vec	Second vector of operation.
 * @return		Result of RESET operation.
 */


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
 * @fn BitVector& BitVector::operator=(const BitVector& vec);
 * Same as copy().
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

} // elm
