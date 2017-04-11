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
#include <elm/data/HashTable.h>

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
 * @fn bool HashTable::hasKey(const HashTable::key_t& key);
 * Test if there is an item with the given in the table.
 * @param key	Key to look for.
 * @return		True if the key found, false else.
 */


/**
 * @fn void HashTable::put(const HashTable::data_t& data);
 * Put an item in the table. If there is already an item with the same key,
 * it is replaced by the new item.
 * @param key	Key of the item to put in.
 * @param value	Value of the item to put in.
 */


/**
 * @fn void HashTable::add(const HashTable::data_t& data);
 * Add an item to the table. If an item already exists with the same key, it is
 * only hidden and may appear again if the added item is removed.
 * @param key	Key of the item to add.
 * @param value	Value of the item to add.
 */


/**
 * @class HashTable::Iterator
 * Iterator on the items of an hash table.
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
 * @li memory space: pointer size * S + n * (data size + pointer size)
 *
 * @ingroup data
 */

/**
 * @class HashTable
 * @deprecated	Use @ref HashMap instead.
 */

}	// elm
