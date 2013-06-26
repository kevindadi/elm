/*
 *	imm::List class interface
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

#include <elm/imm/list.h>

namespace elm { namespace imm {

/**
 * @defgroup imm	Immutable Data Structure
 *
 * ELM provides a set of immutable data structure like lists and tree.
 * The goal of this module is to allow functional programming style
 * while supporting limited but effective garbage collection.
 * Basically, the immutable nature of the data structure allows (a) to handle more easily the memory management
 * and (b) providing an efficient and compact way of memory use while avoiding a lot of time-costly memory
 * operations.
 *
 * Coming with this immutable nature, an efficient garbage collector is provided.
 * It is quite limited because it has no way to collect the living instances of the data structures items.
 * Therefore, it requires the user to specialize it and to provided a collect() function responsible
 * to supply the list of living data structure items.
 */


/**
 * @class list
 * Implementation of immutable list. To be built, an item of this data structure
 * requires an allocator, @ref ListAllocator, or a garbage collector, @ref ListGC.
 * @param T		Type of items in the list.
 * @ingroup imm
 */


/**
 * @fn list<T> list::null(void);
 * Get the empty list.
 */


/**
 * @fn list::list(void);
 * Build an empty list.
 */


/**
 * @fn list::list(const list& l);
 * Clone a list (no shallow copy).
 */


/**
 * @fn const T& list::hd(void) const;
 * Get the first item of the list.
 * @return		Head item.
 */


/**
 * @fn list<T> *list::tl(void) const;
 * Get the sub-list after the first item in the list.
 * @return		Tail of the list.
 */


/**
 * @fn int list::length(void) const;
 * Compute the length of the list.
 * @return	List length.
 */


/**
 * @class ListAllocator
 * Provide a simple and customized allocator to create lists.
 * @param T		Type of item of the list.
 * @param A		Allocator to use, must implement the @ref Allocator concept (default to @ref DefaultAllocator).
 * @ingroup imm
 */


/**
 * @fn ListAllocator::ListAllocator(A& allocator);
 * @param allocator		Allocator to use (optional).
 */


/**
 * @fn list<T> ListAllocator::cons(const T& h, list<T> tl);
 * Build a list by creating a node and prepending to the given tail list.
 * @param h		Value of the prepended node.
 * @param t		List to prepend the new node to.
 * @return		New list.
 */


/**
 * @fn void ListAllocator::free(list<T> l);
 * Free the first node of the given list.
 * @param l		List to free the first item from.
 */


/**
 * @fn void ListAllocator::freeAll(list<T> l);
 * Free all nodes from the given list.
 * @param l		List to free.
 */

/**
 * @class ListGC
 * Allocator and garbage collector for the @ref list immutable data structure.
 * This object provides a way to allocate nodes of the @ref list data structure
 * but it must be assisted to perform garbage collection by implementing the abstract function
 * @ref collect(). This function is called each time a garbage collection is required in order
 * to collect all the living lists. For each living list, the user must perform
 * a call to @ref mark() function.
 *
 * The example below show an example of use of ListGC to garbage-collect a set of lists contained
 * in a @ref genstruct::Vector.
 * @code
 * using namespace elm;
 * using namespace imm;
 *
 * genstruct::Vector<list<int> > living_lists;
 *
 * class MyGC: public ListGC {
 * protected:
 * 	virtual void collect(void) {
 * 		for(int i = 0; i < libing_lists.count(); i++)
 * 			mark(my_lists[i]);
 * 	}
 * };
 * @endcode
 *
 * @param T		Type of the item in the list.
 * @ingroup imm
 */


/**
 * @fn list<T> ListGC::cons(const T& h, list<T> tl);
 * Build a new list node with h value and prepend it to tl.
 * @param h		Item to store in the new node.
 * @param t		List to preprend to.
 * @return		Created list.
 */


/**
 * @fn void ListGC::mark(list<T> l);
 * when a garbage collection is running, inform the collector that the given list is alive.
 * @param l		List to mark as alive.
 */

} }	// elm::imm
