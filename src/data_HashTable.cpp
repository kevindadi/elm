/*
 *	HashTable class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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

#include <elm/data/HashMap.h>
#include <elm/data/HashSet.h>

namespace elm {

/**
 * @class HashTable
 * This class provides an hashing table implementation as an array of linked
 * list. A small caching feature put to the head of the linked list last
 * accessed items.
 *
 * This class is the basic implementation of hash table.
 * To use it as a map, refer to @ref HashMap. To use it as a set, refer
 * to @ref HashSet.
 *
 * @param T	Type of stored data.
 * @param A	Adapter to access key information (must implement @ref concept::Adapter).
 * @param M	Manager of the hash table providing hashing and allocation services.
 * @ingroup data
 */

/**
 * @fn HashTable::HashTable(int size);
 * Build an hash table with the given size. Improved efficiency is obtained with prime
 * number as sizes.
 * @param size	Table size (default to 211).
 */

/**
 * @fn HashTable::HashTable(M& man, int _size);
 * Build an hash table with given hash manager and size. Improved efficiency is obtained with prime
 * number as sizes.
 * @param man	Hash manager to use.
 * @param size	Table size (default to 211).
 */

/**
 * HashTable::HashTable(const self_t& h);
 * Clone constructor.
 * @param h	Hash table to clone.
 */

/**
 * @fn bool HashTable::isEmpty(void) const;
 * Test if the table is empty.
 * @return	True if the table is empty, false else.
 */

/**
 * @fn int HashTable::count(void) const;
 * Count the number of items in the table.
 * @return	Count of items.
 */

/**
 * @fn const data_t *HashTable::get(const key_t& key) const;
 * Get a table item by its key.
 * @param key	Looked key.
 * @return		Pointer on item if found, null pointer else.
 */

/**
 * @fn bool HashTable::hasKey(const key_t& key) const;
 * Test if a key is in the table.
 * @param key	Tested key.
 * @return		True if there is an item in the table with the given key, false else.
 */

/**
 * @fn bool HashTable::exists(const key_t& key) const;
 * Same as @ref hasKey().
 */

/**
 * @fn void HashTable::put(const data_t& data);
 * Add a data in the table ensuring there is only one data with the corresponding key.
 * @param data	Added data.
 */

/**
 * @fn void HashTable::putAll(const self_t& m);
 * Add the items of the given table to the current one.
 * @param m		Added table.
 */

/**
 * @fn void HashTable::remove(const key_t& key);
 * Remove the item corresponding to the given key.
 * @param key	Key of the item to remove.
 */

/**
 * @fn void HashTable::clear(void);
 * Remove all items of the table.
 */

/**
 * @class HashTable::Iter;
 * Iterator on the items of the table.
 */

/**
 * @fn const key_t& HashTable::Iter::key(void) const;
 * Get the key of the current item.
 * @return	Current item key.
 */


/**
 * @class HashMap
 * Map implemented using an hash table.
 *
 * @par Implemented Concepts
 * @li @ref Collection
 * @li @ref Map
 * @li @ref MutableMap
 *
 * @par Characteristics
 * S is the size of the table.
 * @li average access time: O(n / S)
 * @li average add time: O(n / S)
 * @li average remove time: O(n / S)
 * @li memory space: pointer size * S + n * (key size + value size + pointer size)
 *
 * @param K		Type of the key.
 * @param T		Type of values.
 * @param M		Used manager (default to @ref HashManager).
 * @ingroup data
 */

/**
 * @fn HashMap::HashMap(int size);
 * Build an hash map with the given size. Improved efficiency is obtained with prime
 * number as sizes.
 * @param size	Table size (default to 211).
 */

/**
 * @fn HashMap::HashMap(M& man, int _size);
 * Build an hash map with given hash manager and size. Improved efficiency is obtained with prime
 * number as sizes.
 * @param man	Hash manager to use.
 * @param size	Table size (default to 211).
 */

/**
 * @fn bool HashMap::isEmpty(void) const;
 * Test if the map is empty.
 * @return	True if the map is empty, false else.
 */

/**
 * @fn int HashMap::count(void) const;
 * Count the number of items in the map.
 * @return	Count of items.
 */

/**
 * @fn Option<T> HashMap::get(const K& key) const;
 * Get an item by its key.
 * @param key	Looked key.
 * @return		The matching value if the key is in the map, none else.
 */

/**
 * @fn const T& HashMap::get(const K& key, const T& def) const;
 * Get an item by its key.
 * @param key	Looked key.
 * @param def	Default value.
 * @return		The matching value if the key is in the map, the default value else.
 */

/**
 * @fn bool HashMap::hasKey(const key_t& key) const;
 * Test if a key is in the map.
 * @param key	Tested key.
 * @return		True if there is an item in the map with the given key, false else.
 */

/**
 * @fn bool HashMap::exists(const key_t& key) const;
 * Same as @ref hasKey().
 */

/**
 * @fn void HashMap::put(const K& key, const T& val);
 * Put a new item in the map matching the given key.
 * @param key	Key of added item.
 * @param val	Added item.
 */

/**
 * @fn void HashMap::remove(const K& key);
 * Remove an item by its key.
 * @param key	Key of the removed item.
 */

/**
 * @fn void HashMap::clear(void);
 * Remove all items of the map.
 */

/**
 * @class HashMap::Iter;
 * Iterator on the items of the map.
 */

/**
 * @fn const K& HashMap::Iter::key(void) const;
 * Get the key of the current item.
 * @return	Current item key.
 */

/**
 * @class HashMap::KeyIter;
 * Iterator on the keys of the map.
 */

/**
 * @class HashMap::PairIter;
 * Iterator on the pairs formed of(key, value) of each item of the map.
 */

/**
 * @class bool HashMap::contains(const T& item);
 * Test if the given item is in the map.
 * @warning: this function is particularly inefficient (complexity of O(n)).
 * @param item	Looked item.
 * @return		True if the item is in the map, false else.
 */

/**
 * @fn bool HashMap::containsAll(const C& c);
 * Test if all items of collection c are in the map.
 * @param c		Collection to test.
 * @return		True if all collection items are in the map, false else.
 */

/**
 * @fn void HashMap::remove(Iter& i) const;
 * Remove the item corresponding to the iterator.
 * @warning The iterator is pushed forward.
 */


/**
 * @class HashSet
 * Set implemented using an hash table.
 *
 * @par Implemented Concepts
 * @li @ref Collection
 * @li @ref MutableCollection
 * @li @ref Set
 *
 * @par Characteristics
 * S is the size of the table.
 * @li average access time: O(n / S)
 * @li average add time: O(n / S)
 * @li average remove time: O(n / S)
 * @li memory space: pointer size * S + n * (data size + pointer size)
 *
 * @param T		Type of set elements.
 * @param M		Type of used manager (default to @ref HashManager).
 * @ingroup data
 */

/**
 * @fn HashSet::HashSet(int size);
 * Build an hash set with the given size. Improved efficiency is obtained with prime
 * number as sizes.
 * @param size	Table size (default to 211).
 */

/**
 * @fn HashSet::HashSet(M& man, int _size);
 * Build an hash set with given hash manager and size. Improved efficiency is obtained with prime
 * number as sizes.
 * @param man	Hash manager to use.
 * @param size	Table size (default to 211).
 */

/**
 * @class HashSet::Iter;
 * Iterator on the items of the set.
 */

/**
 * @fn int HashSet::count(void) const;
 * Count the number of items in the set.
 * @return	Count of items.
 */

/**
 * @class bool HashSet::contains(const T& item);
 * Test if the given item is in the set.
 * @param item	Looked item.
 * @return		True if the item is in the set, false else.
 */

/**
 * @fn bool HashSet::containsAll(const C& c);
 * Test if all items of collection c are in the set.
 * @param c		Collection to test.
 * @return		True if all collection items are in the set, false else.
 */

/**
 * @fn bool HashSet::isEmpty(void) const;
 * Test if the set is empty.
 * @return	True if the set is empty, false else.
 */

/**
 * @fn Iter HashSet::items(void) const;
 * Get an iterator on the items of the set.
 * @return	Iterator on the set.
 */

/**
 * @fn void HashSet::clear(void);
 * Remove all items of the set.
 */

/**
 * @fn void HashSet::add(const T& val);
 * Add an item to the set.
 * @param val	Added item.
 */

/**
 * @fn void HashSet::addAll(const C& coll);
 * Add the given collection of items to the set.
 * @param coll	Added collection of items.
 */

/**
 * @fn void HashSet::remove(const T& val);
 * Remove the given item from the set.
 * @param val	Removed item.
 */

/**
 * @fn void HashSet::removeAll(const C& coll);
 * Remove a collection of items from the set.
 * @param coll	Collection of items to remove.
 */

/**
 * @fn void HashSet::remove(const Iter& i);
 * Remove the item matching the iterator.
 * @warning	The iterator is pushed to the next item.
 * @param i	Iterator on the item to remove.
 */

/**
 * @fn void HashSet::insert(const T& val);
 * Same add @ref add().
 */


/**
 * @class HashTable
 * @deprecated	Use @ref HashMap instead.
 */

}	// elm
