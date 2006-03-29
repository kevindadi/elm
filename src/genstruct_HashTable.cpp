/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * src/genstruct_HashTable.cpp -- HashTable class implementation.
 */

#include <elm/genstruct/HashTable.h>

namespace elm { namespace genstruct {

/**
 * @class HashTable
 * This class provides an hashing table implementation as an array of linked
 * list. A small caching feature put to the head of the linked list last
 * accessed items.
 */


/**
 * @fn bool HashTable::hasKey(const K& key);
 * Test if there is an item with the given in the table.
 * @param key	Key to look for.
 * @return		True if the key found, false else.
 */


/**
 * @fn void HashTable::put(const K& key, const T& value);
 * Put an item in the table. If there is already an item with the same key,
 * it is replaced by the new item.
 * @param key	Key of the item to put in.
 * @param value	Value of the item to put in.
 */


/**
 * @fn void HashTable::add(const K& key, const T& value);
 * Add an item to the table. If an item already exists with the same key, it is
 * only hidden and may appear again if the added item is removed.
 * @param key	Key of the item to add.
 * @param value	Value of the item to add.
 */


/**
 * @class HashTable::ItemIterator
 * Iterator on the items of an hash table.
 */


/**
 * @fn HashTable::ItemIterator::ItemIterator(const HashTable<K, T>& htab);
 * Build the iterator on the given table.
 * @param htab	Hashing table to work on.
 */


/**
 * @fn T HashTable::ItemIterator::item(void) const;
 * Get the current item.
 * @return	Current item.
 */


/**
 * @fn const K& HashTable::ItemIterator::key(void) const;
 * Get the key of the current item.
 * @return	Current item key.
 */

} } // elm::genstruct
