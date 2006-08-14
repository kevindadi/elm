/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/Pair.h -- interface of Pair class.
 */

#include <elm/util/Pair.h>

namespace elm {
	
/**
 * @class Pair <elm/util/Pair.h>
 * This template class is mainly useful for returning or passing in parameter
 * a data item composed of a two values.
 * @param T1	First value type.
 * @param T2	Second value type.
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
