/*
 *	FixedStack class implementaion
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2019, IRIT UPS.
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

#include <elm/data/FixedStack.h>

namespace elm {

/**
 * @class FixedStack;
 * This class implements a lightweight stack  with a fixed size that is
 * allocated in the stack.
 *
 * @param T		Type of stack element.
 * @param S		Size of the stack (fixed).
 * @param E		Equivalence relationship for T elements (default to Equiv).
 */

/**
 * @fn bool FixedStack::isEmpty() const;
 * Test if the stack is empty.
 * @return	True if the stack is empty, false else.
 */

/**
 * @fn bool FixedStack::isFull() const;
 * Test if the stack is full.
 * @return	True if the stack is full, fase else.
 */

/**
 * @fn const T& FixedStack::top() const;
 * Get the top item of the stack.
 * The stack must not be empty!
 * @return	Top item.
 */

/**
 * @fn void FixedStack::reset();
 * Empty the stack.
 */

/**
 * @fn T FixedStack::pop();
 * Remove the top item of the stack and return it.
 * @return	Stack top element.
 */

/**
 * @fn void FixedStack::push(const T& x);
 * Add an element at the top of stack.
 * @param x		Added element.
 */

} // elm
