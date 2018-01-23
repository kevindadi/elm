/*
 *	StaticStack class
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2013, IRIT UPS.
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

#include <elm/data/StaticStack.h>

namespace elm {

/**
 * @class StaticStack
 * Implements a stack locally allocated, that is, whose stack data structure is allocated
 * in system stack if the object is local, in the static memory is the object is a global
 * variable or wherever the object is embedded. To sum up, no heap allocation is performed.
 * This is why its size is fixed.
 *
 * Implemented concepts:
 * * @ref elm::concept::Stack
 * * @ref elm::concept::Collection
 *
 * Performances:
 * * push -- O(1) (~ value copy)
 * * pop -- O(1) (~ value copy)
 *
 * @param T		Type of values stored in the stack.
 * @param N		Size of the stack.
 *
 * @ingroup data
 */

/**
 * @fn StaticStack::StaticStack(void);
 * Build an empty stack.
 */

/**
 * @fn StaticStack::StaticStack(const StaticStack<T, N>& s);
 * Build a stack by copy.
 * @param s		Copied stack.
 */

/**
 * @fn void StaticStack::copy(const StaticStack<T, N>& s);
 * Copy the given stack.
 * @param s	Copied stack.
 */

}	// elm

