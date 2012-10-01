/*
 *	$Id$
 *	type_info class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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

#include <elm/type_info.h>
#include <elm/rtti.h>

namespace elm {

/**
 * @defgroup types Type Support
 *
 * ELM provides several facilities to handle type and parametric types.
 *
 * @par Basic Types
 *
 * @code
 * #include <elm/types.h>
 * using namespace elm;
 * @encode
 *
 * This include provides alternative non-ambiguous names for integer types:
 * @li t::int8
 * @li t::uint8
 * @li t::int16
 * @li t::uint16
 * @li t::int32
 * @li t::uint32
 * @li t::int64
 * @li t::uint64
 *
 * In addition, some useful types are provided:
 * @li t::size -- size in memory
 * @li t::offset -- offset in memory
 * @li t::uint -- short notation for unsigned int.
 *
 *
 * @par Type Information
 *
 * @code
 * #include <elm/type_info.h>
 * using namespace elm;
 * @endcode
 *
 * Class @ref elm::type_info<T> allows to get from type passed as the parametric argument.
 * This may be useful for templates using static evaluation. The common fields includes:
 * @li is_type -- true if T is not a class
 * @li is_scalar -- true if T is a simple type (neither a structure, nor union, nor class)
 * @li is_enum -- true if T is an enumerated type
 * @li is_class -- true if T is a class
 * @li is_ptr -- true if T is a pointer
 * @li is_ref -- true if T is a reference
 * @li is_deep -- true if T requires deep copy (that is, requires copy using operator = instead of
 * system fast byte-per-byte copy mechanism)
 * @li is_virtual -- true if T contains virtual functions
 *
 * @par Array Copying
 *
 * The include file <otawa/util/array.h> provides functions to handling arrays:
 * @li @ref array::copy() -- copy without overlapping
 * @li @ref array::move() -- copy with overlapping
 * @li @ref array::clear() -- set to initial value
 * @li @ref array::set() -- set all items to a specific values
 *
 * According to the type of the type of the items, these functions may invokes
 * specific system functions to make faster this operation. Usually, only types
 * without pointers can only be processed in this way (scalar data) but you can
 * informs that your own class can be shallowly copied by specializing the @ref type_info
 * class:
 * @code
 * class MyClass {
 * 	...
 * };
 *
 * template <>
 * class type_info<MyClass>: public class_t<T> { enum { is_deep = 1 }; };
 *
 * @endcode
 */

/**
 * @class type_info
 * This class can not be instantiated. It provides only static information
 * about the types used in a program. Although a partial type_info instantiation
 * is provided for usual types of C++, the type_info may be specialized
 * for user types in order to let ELM classes -- like containers -- to adapt
 * to the custom types.
 * 
 * According the type T, one of the following information may also be available:
 * @li const T null: null value for the types supporting one.
 * @li const T min: minimum value for the types supporting a total order.
 * @li const T max: maximum value for the types supporting a total order.
 *
 * @param T		Type to get information for.
 *
 * @ingroup types
 */


/**
 * @var type_info<T>::is_type
 * True if T is a simple type (not a class).
 */


/**
 * @var type_info<T>::is_class
 * True if T is a class type.
 */


/**
 * @var type_info<T>::is_scalar
 * True if T is a scalar type (integer, float, boolean, etc).
 */


/**
 * @var type_info<T>::is_enum
 * True if T is an enumerated type.
 */


/**
 * @var type_info<T>::is_deep
 * Does not support byte-to-byte copy.
 */


/**
 * @var type_info<T>::is_virtual
 * Contains virtual functions.
 */

/**
 * @var type_info<T>::null
 * Null value for the current type.
 */


/**
 * @fn cstring type_info<T>::name(void);
 * Get the name of the type.
 * @return	Type name.
 */

// Statics
const cstring type_info<cstring>::null = "";
const string type_info<string>::null = "";


/**
 * Test if the current class is base class of the given one.
 * Notice that this class is a base class of clazz even if this
 * class equals the class clazz.
 * @param clazz		Class to test.
 * @return			True if this class is a base class, false else.
 */
bool AbstractClass::baseOf(AbstractClass *clazz) {
	while(clazz) {
		if(clazz == this)
			return true;
		clazz = clazz->base();
	}
	return false;
}


// type_info<float>
const float type_info<float>::min = -FLT_MAX;
const float type_info<float>::max = FLT_MAX;

// type_info<double>
const double type_info<double>::min = -DBL_MAX;
const double type_info<double>::max = DBL_MAX;

// type_info<long double>
const long double type_info<long double>::min = -LDBL_MAX;
const long double type_info<long double>::max = LDBL_MAX;

}  // elm

