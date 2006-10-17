/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * src/genstruct_DLList.cpp -- DLList class implementation.
 */

#include <elm/genstruct/DLList.h>

namespace elm { namespace genstruct {

/**
 * @class DLList <elm/genstruct/DLList.cpp>
 * A generic implementation of a double-link list. It may be traversed using
 * the @ref Iterator class or modified using @ref Editor class.
 * @param T	Type of items stored in the list.
 */


/**
 * @fn Iterator DLList::fromFirst(void) const;
 * Get an iterator on the first item of the list.
 * @return	Iterator on the first item.
 */


/**
 * @fn Iterator DLList::fromLast(void) const;
 * Get an iterator on the last item of the last.
 * @return	Iterator on the last item.
 */


/**
 * @fn T DLList::first(void) const;
 * Get the first item of the list.
 * @return	First item.
 * @warning It is an error to call this method on empty list.
 */


/**
 * @fn T DLList::last(void) const;
 * Get the last item of the list.
 * @return	Last item.
 * @warning It is an error to call this method on empty list.
 */


/**
 * @fn bool DLList::isEmpty(void) const;
 * Test if the list is empty.
 * @return	True if the list is empty, false else.
 */


/**
 * @fn int DLList::count(void) const;
 * Count the items in the list.
 * @return	Item count.
 */


/**
 * @fn bool DLList::contains(const T item) const;
 * Test if the given item is in the list. Notice that the T item type must
 * implement the equality / inequality operators.
 * @param	Item to look for.
 * @return	True if the item is found, false else.
 */


/**
 * @fn void DLList::remove(const T item);
 * Remove the given item from the list, or one the item if the list contains
 * this item many times. Notice that the T item type must
 * implement the equality / inequality operators.
 * @param	Item to remove.
 */


/**
 * @fn void DLList::addFirst(const T item);
 * Add an item at the first position.
 * @param item	Item to add.
 */


/**
 * @fn void DLList::addLast(const T item);
 * Add an item at the last position.
 * @param item	Item to add.
 */


/**
 * @fn void DLList::removeFirst(void);
 * Remove the first item from the list.
 * @warning It is an error to call this method on empty list.
 */


/**
 * @fn void DLList::removeLast(void);
 * Remove the last item from the list.
 * @warning It is an error to call this method on empty list.
 */


/**
 * @fn void DLList::removeAll(const T& item);
 * Remove all items matching the given one. Notice that the T item type must
 * implement the equality / inequality operators.
 * @param item	Item to remove.
 */


/**
 * @fn void DLList::clear(void);
 * Remove all items from the list.
 */


/**
 * @class DLList::Iterator <elm/genstruct/DLList.h>
 * Bidirectionnal iterator on the list @ref DLList.
 */


/**
 * @fn DLList::Iterator::Iterator(const DLList& list);
 * Build an iterator on the given list.
 * @param list	List to iterate on.
 */


/**
 * @fn DLList::Iterator::Iterator(const Iterator& iter);
 * Build an iterator by cloning the given one.
 * @param iter	Iterator to clone.
 */


/**
 * @fn bool DLList::Iterator::ended(void) const;
 * Test if the end or the begin is reached.
 * @return	True if the end is reached, false else.
 */


/**
 * @fn inline T DLList::Iterator::item(void) const;
 * Get the current item.
 * @return	Current item.
 */


/**
 * @fn void DLList::Iterator::next(void);
 * Go to the next item.
 */


/**
 * @fn void DLList::Iterator::previous(void);
 * Go to the previous item.
 */


/**
 * @fn void DLList::Iterator::first(void);
 * Go to the first item of the list.
 */


/**
 * @fn void DLList::Iterator::last(void);
 * Go to the last item of the list.
 */


/**
 * @class DLList::Editor <elm/genstruct/DLList.h>
 * Bidirectionnal editor on a @ref DLList list.
 */


/**
 * @fn DLList::Editor::Editor(DLList& list);
 * Build an editor on the given list.
 * @param list	List to edit.
 */


/**
 * @fn DLList::Editor::Editor(const Editor& editor);
 * Build an editor by cloning an existing one.
 * @param editor	Editor to clone.
 */


/**
 * @fn T& DLList::Editor::item(void) const;
 * Get a reference on the current item to allow assignment.
 * @return	Current item reference.
 */


/**
 * @fn T& DLList::Editor::operator*(void) const;
 * Same as @ref item().
 */


/**
 * @fn void DLList::Editor::remove(void);
 * Remove the current item from the list (go to the next item).
 * @warning It is an error to call this method when no more item is selected.
 */


/**
 * @fn void DLList::Editor::removeNext(void);
 * Remove the next item from the list.
 * @warning It is an error to call this method when no more item is selected.
 */


/**
 * @fn void DLList::Editor::removePrevious(void);
 * Remove the previous item from the list.
 * @warning It is an error to call this method when no more item is selected.
 */


/**
 * @fn void DLList::Editor::insertAfter(const T item);
 * Insert an item after the current one.
 * @param item	Item to insert.
 * @warning It is an error to call this method when no more item is selected.
 */


/**
 * @fn void DLList::Editor::insertBefore(const T item);
 * Insert an item before the current one.
 * @param item	Item to insert.
 * @warning It is an error to call this method when no more item is selected.
 */

} } // elm::genstruct
