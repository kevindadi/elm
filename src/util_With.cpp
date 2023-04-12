/*
 *	With and WithPtr class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2023, IRIT UPS.
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

#include <elm/util/With.h>

namespace elm {

/**
 * @class With
 *
 * Class mimicking Python's with command. At creation time, enter() function of
 * passed object is called. At deleation time (when the context is left), the
 * leave() function is called. This is specially useful when exception are used
 * to clean up context in case of exception throw.
 * @see with()
 * @ingroup util
 */

/**
 * @fn With<T> with(T& p);
 * Help function making easier the use of @ref With class. It may be used as
 * below:
 * ```
 *	class Hello {
 *	public:
 * 		void enter() { cout << "Hellow, "; }
 * 		void leave() { cout << " World!" << io::endl; }
 *	};
 *
 *	Hello hello;
 *
 * 	{
 * 		auto hello = with(hello);
 *		work();		// that may raise exception
 *	}
 *  ```
 */

/**
 * @class WithPtr
 * As @ref With class but takes in charge the use of allocated pointer:
 * ensures that the pointer is deleted when the context is left.
 *
 * @see with_ptr
 * @ingroup util
 */

/**
 * @fn WithPtr<T> with_ptr(T *p);
 * Ensures that the pointer is deleted when the context is left, specially in
 * case of exception throw.
 *
 * Use it as below:
 * ```
 *	{
 *		auto p = with_ptr(new int);
 *
 * 		work_with(*i);	// that may throw an exception
 *	}
 * ```
 */

}	// elm
