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
 *
 * And some optimized functions of not-builtin functions:
 * @li msb32 -- most-left bit to one
 */

/**
 * Compute the position of the left-most bit to one.
 * @param i		Integer to test.
 * @return		Position of left-most bit to one or -1 if the integer is 0.
 * @ingroup int
 */
int msb32(t::uint32 i) {
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

}	// elm
