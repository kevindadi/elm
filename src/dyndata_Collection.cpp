/*
 *	SystemException class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
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

 #include <elm/dyndata/Collection.h>
 
namespace elm { namespace dyndata {

/**
 * @defgroup dyndata Dynamic Data
 *
 * In ELM, you can use usual data structure based on the template approach (as in STL)
 * but also data structure that works in the same way as in Java language based on
 * interfaces and virtual function calls. This enables to use data structures
 * implementing the same interface independently of their actual type. However, notice
 * that, if dynamic structure are more flexible than generic data structure, they are also
 * slower.
 *
 * To handle collections, there are 3 classes providing the interface:
 * @li @ref AbstractCollection -- defines the basic virtual functions implementing the
 * 		@ref concept::Collection.
 * @li @ref MutableAbstractCollection -- defines the basic virtual functions implementing the
 * 		@ref concept::MutableCollection.
 * @li @ref AbstractIter -- defines the virtual functions to implement an iterator.
 *
 * Additionally, to support allocated operator easily, the class @ref Iter receives
 * an iterator from @ref AbstractCollection, behave like an iterator wrapped around
 * the @ref AbstractIter and is in charge of deleting it at the end.
 *
 * Dynamic data structure are easily derived from generic data structures using the
 * classes @ref Collection or @ref InstIter. Below is an example of the use of the
 * iterator:
 * @code
 * int count(const AbstractCollection<T>& coll) {
 * 	int c = 0;
 * 	for(Iter i(coll->iterator()); i; i++)
 * 		c++;
 * 	return c;
 * }
 * @endcode
 */


/**
 * @class AbstractCollection
 * Abstract interface implement the @ref concept::Collection concept to use as
 * dynamic data.
 *
 * @param T	Type of values in the collection.
 * @ingroup dyndata
 */

/**
 * @fn int AbstractCollection::count(void);
 * Count the number of values in the collection.
 * @return	Value count.
 */

/**
 * @fn bool AbstractCollection::contains(const T& val);
 * Test if a value is in the collection.
 * @param val	Looked value.
 * @return		True if the value is in the collection, false else.
 */

/**
 * @fn bool AbstractCollection::isEmpty(void) const;
 * Test if the collection is empty.
 * @return	True if the collection is empty, false else.
 */

/**
 * @fn AbstractIter<T> *AbstractCollection::iterator(void) const;
 * Provide an iterator on the values of the collection.
 * @return	Iterator on the collection values.
 */


 /**
  * @class MutableAbstractCollection
  * Provide interface in @ref dyndata module implementing the @ref concept::MutableCollection concept.
  *
  * @param T	Type of values in the collection.
  * @ingroup	dyndata
  */

/**
 * @class void MutableCollection::clear(void);
 * Clear the content of the collection.
 */

/**
 * @fn void MutableCollection::add(const T& val);
 * Add a value to the collection.
 * @param val	Added value.
 */

/**
 * @fn void MutableCollection::addAll(const AbstractCollection<T>& coll);
 * Add the values of the given collection to the current one.
 * @param coll	Added collection.
 */

/**
 * @fn void MutableCollection::remove(const T& val);
 * Remove a value from the collection.
 * @param val	Removed value.
 */

/**
 * @fn void MutableCollection::removeAll(const AbstractCollection<T>& coll);
 * Remove the values of the given collection from the given one.
 * @param coll	Removed collection.
 */

/**
 * @fn void MutableCollection::remove(const AbstractIter<const T&>& iter);
 * Remove a value from the collection using an iterator.
 * @param iter	Iterator on the value to remove.
 */


/**
 * @class AbstractIter
 * Interface class to implements an iterator as defined in @ref concept::Collection concept.
 * @param T		Type of iterated values.
 * @ingroup dyndata
 */


/**
 * @class Iter
 * Wrapper class around @ref AbstractIter to more easily manage the usage and the release.
 * @param T		Type of iterated values.
 * @ingroup	dyndata
 */

/**
 * @fn AbstractIter<T> *Iter::instance(void) const;
 * Get the instance of the @ref AbstractIter used.
 * @return	Abstract iterator instance.
 */


/**
 * @class Collection
 * @ref AbstractCollection implementation from @ref data collection.
 * @param T		Type of collection values.
 * @param C		Type of generic collection (containing values of type T).
 * @ingroup dyndata
 */


/**
 * @class MutableCollection
 * @ref AbstractCollection implementation from @ref data collection.
 * @param T		Type of collection values.
 * @param C		Type of generic collection (containing values of type T).
 * @ingroup dyndata
 */



/**
 * @class IterInst
 * Build a @red dyndata iterator from a generic iterator.
 *
 * @param T		Type of iterated values.
 * @param I		Type of the iterator.
 * @ingroup dyndata
 */


/**
 * @fn IterInst<T, I> *iter(const I& i);
 * Build a @ref dyndata iterator from a generic iterator.
 * @param i		Generic iterator.
 * @param T		Type of iterated values.
 * @param I		Type of the iterator.
 * @ingroup dyndata
 */

} }	// elm::dyndata
 
