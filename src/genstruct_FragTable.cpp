/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * src/genstruct_FragTable.cpp -- implementation FragTable class.
 */

#include <elm/genstruct/FragTable.h>

namespace elm { namespace genstruct {

/**
 * @class FragTable
 * This container class allows indexed access to its data. It is implemented
 * as expandable fragmented table using a two-level table traversal. The first
 * level table selects a sub-table that contains the actual stored items.
 * @par
 * Consequently, the access table is longer than a classic table but small and
 * constant. Yet, the table may be expanded without inducing a copy of already
 * stored content. According the granularity / size of the sub-tables, the 
 * place / item count ratio overhead is pretty small : this class is a good
 * candidate for big tables requiring dynamic expansion.
 * 
 * @param T	Type of stored items.
 */


/**
 * @fn FragTable::FragTable(int chunk_size = 256);
 * The constructor of a fragmented table.
 * @param chunk_size	2^chunk_size is the size of sub-tables (default to 256).
 */


/**
 * @fn bool FragTable::isEmpty(void) const;
 * Test if the fragmented table is empty.
 * @return	True if it is empty, false else.
 */


/**
 * @fn int FragTable::length(void) const;
 * Get the length / item count of the table.
 * @return	Table length.
 */


/**
 * @fn const T& FragTable::get(int index) const;
 * Get the item at the given index.
 * @warning It is an error to pass an index greater or equal to the table length.
 * @param index	Index of the looked item.
 * @return		Item matching the given index.
 */
 
 
/**
 * @fn T& FragTable::get(int index);
 * Same as @ref FragTable::get() const but return a mutable reference.
 * @param index	Index of the looked item.
 * @return		Reference on the matching item.
 */


/**
 * @fn void FragTable::set(int index, const T& value) const;
 * Change the value of an item in the table.
 * @warn It is an error to pass an index greater or equal to the table length.
 * @param index	Index of the item to set.
 * @param value	Value to set.
 */


/**
 * @fn void FragTable::add(T value);
 * Add an item to the table.
 * @param value	Value of the item to add.
 */


/*
 * @fn const T& FragTable::operator[](int index) const;
 * Operator implementing @ref FragTable::get().
 */


/**
 * @fn T& FragTable::operator[](int index);
 * Operator implementing @ref FragTable::get().
 */


/**
 * @fn FragTable<T>& FragTable::operator+=(T value);
 * Operator implementing @ref FragTable::add().
 */


/**
 * @fn FragTable::operator bool(void) const;
 * Evaluates to the true if the table is not empty.
 * @return	False if the table is empty, false else.
 */


/**
 * @class FragTable::Iterator
 * Iterator on the content of @ref FragTable.
 */


/**
 * @fn FragTable::Iterator::Iterator(const FragTable<T>& table);
 * Iterator constructor.
 * @param table	Fragmented table to traverse.
 */


/**
 * @fn void FragTable::Iterator::next(void);
 * Go to the next item.
 */


/**
 * @fn const T& FragTable::Iterator::item(void) const;
 * Get the current item.
 * @return	Current item.
 */


/**
 * @fn bool FragTable::Iterator::ended(void) const;
 * Evaluates to true if the traversal is ended.
 * @return	True if the traversal is ended, false else.
 */


/**
 * @class MutableIterator
 * Implements a mutable iterator on the items of a @ref FragTable.
 */


/**
 * @fn FragTable::MutableIterator::MutableIterator(FragTable<T>& table);
 * Constructor.
 * @param table	Table to traverse.
 */


/**
 * @fn void FragTable::MutableIterator::set(const T& value);
 * Change the value of the curren item.
 * @param	New value of the current item.
 */


/**
 * @fn T& FragTable::MutableIterator::item(void);
 * Get a reference on the curren item.
 * @return	Current item reference.
 */


/**
 * @fn MutableIterator& FragTable::MutableIterator::operator=(const T& value);
 * Operator shortcut to @ref set().
 */
	
} } // elm::genstruct
