/*
 *	$Id$
 *	utility module
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-07, IRIT UPS.
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

#include <elm/util/GenValue.h>
#include <elm/utility.h>

namespace elm {

/**
 * @defgroup utility Utility Classes
 * 
 * This module contains classes providing miscalleneous services.
 * 
 * @li @ref AutoComparator -- implementation of the @ref concept::Comparator
 * using the default "==" and "<" operators.
 * @li @ref BitVector -- compact and fast representation of vector of bits,
 * @li @ref HashKey -- implementation of the @ref concept::Hash concept,
 * @li @ref Initializer -- framework for single-dependency initialization of
 * static objects,
 * @li @ref STRONG_TYPE -- automatic class wrapper around scalar types like
 * enumeration (to avoid ambiguities in C++ type conversion),
 * @li @ref VarArg -- wrapper around the variable arguments of function,
 * @li @ref Version -- unified version representation.
 * 
 * Other classes provides base classes to a unified exception system:
 * @li @ref Exception -- base class of exception,
 * @li @ref MessageException -- exception with built-in string message.
 * 
 * Some classes makes easier the management of structured values:
 * @li @ref Option -- optional value,
 * @li @ref Pair -- pair of values,
 * 
 * Finally, some classes provides facilities to handle references:
 * @li @ref AutoPtr and @ref Lock -- provides an automatic pointer management
 * system,
 * @li @ref Ref -- mutable references.
 */

/**
 * @class Exception
 * The base class of exceptions in Elm.
 * @ingroup utility
 */


/**
 */
Exception::~Exception(void) {
}


/**
 * Return a message describing the exception.
 * @return	Exception message.
 */
String Exception::message(void) {
	//cerr << "elm::Exception::message() = \"\"\n";
	return "";	
}


/**
 * @class AbstractValue
 * Support class for @ref GenValue.
 *
 * @ingroup util
 */


/**
 */
AbstractValue::~AbstractValue(void) {
}


/**
 * @class Value
 * The purpose of this class is to store in safe way a collection of vales
 * of different types. As it inherits from @ref AbstractValue, they can be deleted
 * in a safe way. To use this class, the collection must accept values of type
 * AbstractValue * (that will accept Value * objects) and the collection has to
 * delete its contained item using the delete operator.
 *
 * @code
 *	genstruct::Vector<AbstractValue *> vals;
 *  vals.add(gen_value(666));
 *  vals.add(gen_value(string("ok"));
 *  vals.add(gen_value(111.666);
 *  vals.add(gen_value(MyClass()));
 *
 *  ...
 *
 *  for(int i = 0; i < vals.length(); i++)
 *  	delete vals[i];
 *
 * @endcode
 *
 * @sa gen_value
 * @ingroup util
 */

/**
 * @fn Value<T> *gen_value(const T& v);
 * Shortcut to build a @ref GenValue.
 * @param v		Value to store.
 * @return		GenValue to store the value in.
 */

};
