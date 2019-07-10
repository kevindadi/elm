/*
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

#include <elm/delegate.h>
#include <elm/utility.h>

namespace elm {

/**
 * @defgroup utility Utility Classes
 * 
 * This module contains classes providing miscellaneous services.
 * 
 * @li @ref AutoComparator -- implementation of the @ref concept::Comparator
 * using the default "==" and "<" operators.
 * @li @ref BitVector -- compact and fast representation of vector of bits,
 * @li @ref HashKey -- implementation of the @ref concept::Hash concept,
 * @li @ref Initializer -- framework for single-dependency initialization of
 * static objects,
 * @li @ref STRONG_TYPE -- automatic class wrapper around scalar types like
 * enumeration (to avoid ambiguities in C++ type conversion),
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
 * @li @ref LockPtr and @ref Lock -- provides an automatic pointer management
 * system,
 * @li @ref Ref -- mutable references.
 * @li @ref SharedPtr
 * @li @ref UniquePtr
 * Notice that the set of pointer wrapper classes can be include with "elm/ptr.h".
 *
 * @par deprecated
 * @li @ref VarArg -- wrapper around the variable arguments of function,
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
 * @class KeyException
 * Exception raised when a key is not available in a map.
 */

///
string KeyException::message(void) {
	return "key not available";
}


/**
 * @class UniquePtr
 * Implements a pointer wrapper class ensuring there is only one owner
 * of a pointed object. When a unique pointer is deleted, the pointed
 * object is also deleted while when a unique pointer is assigned
 * to another one, it looses the pointed object that is passed
 * to assigned unique pointer.
 *
 * @param T		Type of pointed objects.
 * @ingroup		utility
 */

/**
 * @fn bool UniquePtr::isNull(void) const;
 * Test if the pointer is null.
 * @return	True if the pointer is null, false else.
 */

/**
 * @fn void UniquePtr::clean(void);
 * Free the pointed memory and set the pointer to null.
 */

/**
 * @fn T *UniquePtr::detach(void);
 * Return the pointer and set it in the object to null (it will no more be
 * automatically fried).
 * @return	Stored pointer.
 */

/**
 * @fn UniquePtr& UniquePtr::operator=(T *ptr);
 * Change the pointer contained in the unique pointer, the old pointer begin
 * fried.
 * Same as set().
 * @param ptr	Pointer to set.
 * @return		Set unique pointer.
 */

/**
 * @fn UniquePtr& UniquePtr::operator=(UniquePtr& ptr);
 * Change the current pointer with the one of the given unique pointer. The old
 * pointer is first fried and the ad pointer is set to null.
 * @param 	ptr	Unique pointer to set the pointer form.
 * @return	Set unique pointer.
 */

/**
 * @fn UniquePtr::operator T *(void) const;
 * Same as get().
 */


/**
 * @fn T *UniquePtr::operator->(void) const;
 * Indirect access to the members of stored pointer.
 * @return	Stored pointer.
 */


/**
 * @fn UniquePtr::operator bool(void) const;
 * Same as !isNull().
 */


/**
 * @class SharedPtr
 * Implements a pointer wrapper class that takes care of the usage of
 * a pointer and that automatically delete a pointed object when it
 * is no more used.
 *
 * Based on reference counting approach, assignment of shared pointer
 * induces the decrementation of the previous pointer and the incrementation
 * of the new pointer.
 *
 * Beware: this also means that pointed objects forming a cycle will not
 * be deleted!
 *
 * @param T		Type of pointed object.
 * @ingroup		utility
 */


/**
 * @class LockPtr
 * Implements a pointer wrapper class that takes care of the usage of
 * a pointer and that automatically delete a pointed object when it
 * is no more used.
 *
 * Based on reference counting approach, assignment of shared pointer
 * induces the decrementation of the previous pointer and the incrementation
 * of the new pointer.  Unlike the @ref SharedPtr, the pointed object must
 * implements the @ref Lock class. This permits to save one extraneous pointer
 * used, in @ref SharedPtr, to link the pointed objects with its counter.
 *
 * Beware: this also means that pointed objects forming a cycle will not
 * be deleted!
 *
 * @param T		Type of pointed object.
 * @ingroup		utility
 */

/**
 * @macro UNUSED
 * Avoid "unused variable" warning when put after the identifier of the variable.
 * Mainly useful when a for(auto x: ...) is used.
 * @ingroup utility
 */

/**
 * @macro ELM_UNUSED
 * See @ref UNUSED.
 * @ingroup utility
 */

/**
 * @class Flags;
 * Small class to manage flags of bit in a safe way.
 *
 * The user has to assign an index to each flag bit and they are stored in
 * this class as an integer of type type T. Then, they may be read, set
 * or cleared safely with function of Flags.
 *
 * Operator (index) and [index] can be used as shortcuts to Flags::bit().
 *
 * A common use of this class with 3 flags, RED, GREEN, BLUE could be:
 * @code
 * const int RED = 0, GREEN = 1, BLUE = 2;
 * Flags<> f;
 * f.set(RED);
 * f.clear(GREEN);
 * if(f(RED))
 *	// do something
 * @endcode
 *
 * @param T	Integer type to store the flag bits (default o t::uint32).
 * @ingroup utility
 */

/**
 * @fn bool Flags::bit(int i) const;
 * Get the value of flag represented by the index.
 * @return	Flag value.
 */

/**
 * @fn void Flags::set(int i);
 * Set to true the flag corresponding to the index.
 * @param i		Index of the flag to set.
 */

/**
 * @fn void Flags::clear(int i);
 * Set to false the flag corresponding to the index.
 * @param i		Index of the flag to clear.
 */

};
