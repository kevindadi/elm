/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * src/genstruct_SLList.cpp -- SLList class implementation.
 */

#include <elm/genstruct/SLList.h>

namespace elm { namespace genstruct {


/**
 * @class SLList <elm/genstruct/SLList.h>
 * This class provides a generic implementation of single-link lists.
 * To traverse, you ay use its @ref Iterator and @ref Editor may be used to
 * modify it.
 * @param T	Type of data stored in the list.
 */


/**
 * @fn T SLList::first(void) const;
 * Get the first item of the list.
 * @return	First item.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn T SLList::last(void) const;
 * Get the last item of the list. Remark that this method is really inefficient.
 * Its working time is in O(n), n number of nodes in the list. Use it only with
 * small list or revert to more powerful data structures.
 * @return	Last item.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn int SLList::count(void) const;
 * Count the items in the list.
 * @return	Item count.
 */


/**
 * @fn bool SLList::isEmpty(void) const;
 * Test if the list is empty.
 * @return	True if the list is empty, false else.
 */


/**
 * @fn void SLList::addFirst(const T item);
 * Add the given item at the first position in the list.
 * @param item	Item to add.
 */


/**
 * @fn void SLList::addLast(const T item);
 * Add the given item at the last position in the list. Remark that this method is really inefficient.
 * Its working time is in O(n), n number of nodes in the list. Use it only with
 * small list or revert to more powerful data structures.
 * @param item	Item to add.
 */


/**
 * @fn void SLList::removeFirst(void);
 * Remove the first item from the list.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn void SLList::removeLast(void);
 * Remove the last item from the list. Remark that this method is really inefficient.
 * Its working time is in O(n), n number of nodes in the list. Use it only with
 * small list or revert to more powerful data structures.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn void SLList::remove(const T item);
 * Remove the given item from the list or just one if the list contains many
 * items equals to the given one. The item type T must support the equality /
 * inequality operators.
 * @param item	Item to remove.
 */


/**
 * @class SLList::Iterator <elm/genstruct/SLList.h>
 * Iterator for generic single link-list.
 */


/**
 * @fn SLList::Iterator::Iterator(const SLList& list);
 * Build a new iterator.
 * @param list	List to iterate on.
 */


/**
 * @fn bool SLList::Iterator::ended(void) const;
 * Test if the end of the list is reached.
 * @return	True if the end is reached, false.
 */


/**
 * @fn T SLList::Iterator::item(void) const;
 * Get the current item.
 * @return	Current item.
 * @warning It is an error to call this method if the end of the list is
 * reached.
 */


/**
 * @fn void SLList::Iterator::next(void);
 * Go to the next item.
 */


/**
 * @class SLList::Editor <elm/genstruct/SLList.h>
 * Implements an editor for the generic single-link list.
 */


/**
 * @fn SLList::Editor::Editor(SLList& list);
 * Build an editor on the given list.
 * @param list	List to iterate on.
 */


/**
 * @fn void SLList::Editor::addAfter(T item);
 * Add an item after the current one.
 * @param item	Item to add.
 * @warning It is an error to call this method if the end of the list is
 * reached.
 */


/**
 * @fn void SLList::Editor::removeNext(void);
 * Remove the next item from the list.
 * @warning It is an error to call this method if the end of the list is
 * reached.
 */ 

} } // elm::genstruct
