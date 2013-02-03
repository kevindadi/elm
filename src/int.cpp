/*
 *	$Id$
 *	int module implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2011, IRIT UPS.
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

#include <elm/int.h>

namespace elm {

/**
 * @defgroup int	Integer Operation
 *
 * This module provides several facilities to work with integers.
 *
 * First, types to ensure typing model without ambiguities:
 * @li t::int8 / t::uint8 -- signed / unsigned 8-bits integers
 * @li t::int16 / t::uint16 -- signed / unsigned 16-bits integers
 * @li t::int32 / t::uint32 -- signed / unsigned 32-bits integers
 * @li t::int64 / t::uint64 -- signed / unsigned 64-bits integers
 * @li t::size -- memory size type (according to the system configuration)
 * @li t::offset -- memory offset type (according to the system configuration)
 * @li t::uint -- short to unsigned int
 * @li t::intptr -- integer sufficiently big to store a pointer (according to the system configuration)
 *
 * And some optimized functions of not-builtin functions:
 * @li msb32 -- most-left bit to one
 * @li roundup -- round upto upper multiple integer
 * @li rounddown -- round downto lower multiple integer
 */


/**
 * @fn t::uint32 roundup(t::uint32 v, t::uint32 m);
 * Round upto upper multiple integer
 * @param v		Value to round.
 * @param m		Multiple to round with.
 * @return		Value round upto the upper multiple integer.
 * @ingroup int
 */


/**
 * @fn t::uint32 rounddown(t::uint32 v, t::uint32 m);
 * Round upto upper multiple integer
 * @param v		Value to round.
 * @param m		Multiple to round with.
 * @return		Value round upto the upper multiple integer.
 * @ingroup int
 */

/**
 * Compute the position of the left-most bit to one.
 * @param i		Integer to test.
 * @return		Position of left-most bit to one or -1 if the integer is 0.
 * @ingroup int
 */
int msb(t::uint32 i) {
	#define LT(n) n, n, n, n, n, n, n, n, n, n, n, n, n, n, n, n
	static const char tab[256] = {
		-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
		LT(4), LT(5), LT(5), LT(6), LT(6), LT(6), LT(6),
		LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7), LT(7)
	};

	t::uint32 m = i >> 16;
	if(m) {
		t::uint32 n = m >> 8;
		if(n)	return tab[n] + 24;
		else	return tab[m] + 16;
	}
	else {
		t::uint32 n = i >> 8;
		if(n)	return tab[n] + 8;
		else	return tab[i];
	}
}


/**
 * Compute the position of the left-most bit to one.
 * @param i		Integer to test.
 * @return		Position of left-most bit to one or -1 if the integer is 0.
 * @ingroup int
 */
int msb(t::uint64 i) {
	t::uint32 uw = (i >> 32);
	if(uw)
		return msb(uw) + 32;
	else
		return msb(t::uint32(i));
}


/**
 * Count the number of ones in the given byte.
 * @param i		Byte to count ones in.
 * @return		Number of ones in the byte.
 */
int ones(t::uint8 i) {
	static int t[] = {
		0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8
	};
	return t[i];
}


/**
 * @fn int ones(t::uint16 i);
 * Count the number of ones in the given half-word.
 * @param i		Half-word to count ones in.
 * @return		Number of ones in the half-word.
 */

/**
 * @fn int ones(t::uint32 i);
 * Count the number of ones in the given word.
 * @param i		Word to count ones in.
 * @return		Number of ones in the word.
 */

/**
 * @fn int ones(t::uint64 i);
 * Count the number of ones in the given double-word.
 * @param i		Double-word to count ones in.
 * @return		Number of ones in the double-word.
 */


/**
 * Get the least upper power of 2 for the given value.
 * If the value is a power of two, return it else compute
 * the least greater power.
 * @param v		Value to process.
 * @return		Least upper power of two.
 */
t::uint32 leastUpperPowerOf2(t::uint32 v) {
	int m = msb(v);
	if(m < 0)
		return 0;
	else if(v == (1 << m))
		return v;
	else
		return 1 << (m + 1);
}

/**
 * Get the least upper power of 2 for the given value.
 * If the value is a power of two, return it else compute
 * the least greater power.
 * @param v		Value to process.
 * @return		Least upper power of two.
 */
t::uint64 leastUpperPowerOf2(t::uint64 v) {
	int m = msb(v);
	if(m < 0)
		return 0;
	else if(v == (1 << m))
		return v;
	else
		return 1 << (m + 1);
}

}	// elm
