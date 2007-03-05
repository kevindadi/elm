/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * src/genstruct_SortedSLList.cpp -- SortedSLList class implementation.
 */

#include <elm/genstruct/SortedSLList.h>

namespace elm { namespace genstruct {


/**
 * @class SortedSLList <elm/genstruct/SortedSLList.h>
 * This class provides a generic implementation of single-link lists.
 * To traverse, you ay use its @ref Iterator and @ref Editor may be used to
 * modify it.
 * @param T	Type of data stored in the list.
 */


/**
 * @fn T SortedSLList::first(void) const;
 * Get the first item of the list.
 * @return	First item.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn T SortedSLList::last(void) const;
 * Get the last item of the list. Remark that this method is really inefficient.
 * Its working time is in O(n), n number of nodes in the list. Use it only with
 * small list or revert to more powerful data structures.
 * @return	Last item.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn int SortedSLList::count(void) const;
 * Count the items in the list.
 * @return	Item count.
 */


/**
 * @fn bool SortedSLList::isEmpty(void) const;
 * Test if the list is empty.
 * @return	True if the list is empty, false else.
 */


/**
 * @fn void SortedSLList::addFirst(const T item);
 * Add the given item at the first position in the list.
 * @param item	Item to add.
 */


/**
 * @fn void SortedSLList::addLast(const T item);
 * Add the given item at the last position in the list. Remark that this method is really inefficient.
 * Its working time is in O(n), n number of nodes in the list. Use it only with
 * small list or revert to more powerful data structures.
 * @param item	Item to add.
 */


/**
 * @fn void SortedSLList::removeFirst(void);
 * Remove the first item from the list.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn void SortedSLList::removeLast(void);
 * Remove the last item from the list. Remark that this method is really inefficient.
 * Its working time is in O(n), n number of nodes in the list. Use it only with
 * small list or revert to more powerful data structures.
 * @warning	It is an error to call this method if the list is empty.
 */


/**
 * @fn void SortedSLList::remove(const T item);
 * Remove the given item from the list or just one if the list contains many
 * items equals to the given one. The item type T must support the equality /
 * inequality operators.
 * @param item	Item to remove.
 */


/**
 * @class SortedSLList::Iterator <elm/genstruct/SortedSLList.h>
 * Iterator for generic single link-list.
 */


/**
 * @fn SortedSLList::Iterator::Iterator(const SortedSLList& list);
 * Build a new iterator.
 * @param list	List to iterate on.
 */


/**
 * @fn bool SortedSLList::Iterator::ended(void) const;
 * Test if the end of the list is reached.
 * @return	True if the end is reached, false.
 */


/**
 * @fn T SortedSLList::Iterator::item(void) const;
 * Get the current item.
 * @return	Current item.
 * @warning It is an error to call this method if the end of the list is
 * reached.
 */


/**
 * @fn void SortedSLList::Iterator::next(void);
 * Go to the next item.
 */


/**
 * @class SortedSLList::Editor <elm/genstruct/SortedSLList.h>
 * Implements an editor for the generic single-link list.
 */


/**
 * @fn SortedSLList::Editor::Editor(SortedSLList& list);
 * Build an editor on the given list.
 * @param list	List to iterate on.
 */


/**
 * @fn void SortedSLList::Editor::addAfter(T item);
 * Add an item after the current one.
 * @param item	Item to add.
 * @warning It is an error to call this method if the end of the list is
 * reached.
 */


/**
 * @fn void SortedSLList::Editor::removeNext(void);
 * Remove the next item from the list.
 * @warning It is an error to call this method if the end of the list is
 * reached.
 */ 

} } // elm::genstruct
