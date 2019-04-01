/*
 *	$Id$
 *	 class implementation
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

#include <elm/util/strong_type.h>

namespace elm {
	
/**
 * @def STRONG_TYPE(N, T)
 * As type defined with "typedef" command just create aliases to types, they
 * cannot be used to resolve overloading. To circumvent this problem, this macro
 * provide a wrapper around the defined type that is usable as the original type
 * and that provide overload facilities.
 * 
 * This class is usually replaced this kind of declaration:
 * @code
 * typedef type_exp type_name;
 * @endcode
 * by :
 * @code
 * typedef StrongType<type_exp> type_name;
 * @endcode
 * 
 * @param N	Name of the new type.
 * @param T	Encapsulated type.
 * @ingroup utility
 *
 * @deprecated
 */

/**
 * @class StrongType
 * Type definition based on scalar types (bool, int, char, etc) are really just
 * type aliases that does not support type identification in function overloading
 * resolution.
 *
 * For instance, the standard int displayed will be called instead of the specialized
 * displayer:
 * <code c++>
 * 	typedef int index_t;
 * 	io::Output& operator<<(index_t i) { ... }
 *
 * 	index_t i;
 * 	cout << i;
 * </code>
 *
 * To prevent this, one can use the class to make index_t a strong type but index_t
 * can still be used as a normal integer:
 * <code c++>
 * 	typedef StrongType<int> index_t;
 *	io::Output& operator<<(index_t i) { ... }
 *
 * 	index_t i;
 * 	cout << i;
 * </code>
 *
 * @param T	Embedded type.
 * @seealso SolidType
 * @ingroup utility
 */

/**
 * @class SolidType
 * This class targets the same goal as StrongType but in a stricter way. The embedded
 * scalar type needs to use "*" operator to be accessed: no automatic conversion
 * is available to protect even further the values against user mistakes.
 *
 * @param T	Embedded type.
 * @seealso SolidType
 * @ingroup utility
 */
} // elm

