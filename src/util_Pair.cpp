/*
 *	$Id$
 *	Pair class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
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

#include <elm/util/Pair.h>

namespace elm {
	
/**
 * @class Pair <elm/util/Pair.h>
 * This template class is mainly useful for returning or passing in parameter
 * a data item composed of a two values.
 * @param T1	First value type.
 * @param T2	Second value type.
 * @ingroup utility
 */


/**
 * @var Pair::fst;
 * The first value of the pair : may be read or written.
 */


/**
 * @var Pair::snd;
 * The second value of the pair : may be read or written.
 */


/**
 * @fn Pair::Pair(void);
 * Build a pair with uninitialized content.
 */ 


/**
 * @fn Pair::Pair(const T1& _fst, const T2& _snd);
 * Build a pair from two values.
 * @param _fst	First value.
 * @param _snd	Second value.
 */


/**
 * @fn Pair::Pair(const Pair<T1, T2>& pair);
 * Build a pair by copying another pair.
 * @param pair	Pair to copy.
 */


/**
 * @fn Pair<T1, T2>& Pair::operator=(const Pair<T1, T2>& pair);
 * Assignment overload for pairs.
 * @param pair	Pair to assign.
 * @return		Current pair.
 */

} // elm
