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
 *
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
 * @fn cstring type_info<T>::name(void);
 * Get the name of the type.
 * @return	Type name.
 */

// Statics
const cstring type_info<cstring>::null = "";
const string type_info<string>::null = "";

}  // elm

