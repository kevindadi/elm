/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * HashKey class implementation.
 */

#include <elm/util/HashKey.h>

namespace elm {

/**
 * @page hash Hash Concept
 * The Hash concept has the following signature:
 * @code
 * class Hash {
 * public:
 *		static unsigned long hash(const T& key);
 *		static inline bool equals(const T& key1, const T& key2)
 * };
 * @endcode
 * 
 * The hash function is used to get a 32-bits hash value associated with a key
 * while the equals method performs test for equality.
 * 
 * This concept is used in @ref genstruct::HashTable and
 * @ref datastruct::HashTable.
 */


/**
 * @class HashKey
 * This is the default implementation of the Hash concept in ELM. It provides
 * a generic Jenkins hash function but provides also easier or more adapted
 * hash functions for curren types like integers, void pointer or strings.
 * 
 * Refer to @ref hash concept for more details.
 */ 


/**
 * Perform hashing according Jenkins approach
 * (http://www.burtleburtle.net/bob/hash/doobs.html).
 */
unsigned long hash_jenkins(const void *block, int size) {
	unsigned long hash = 0;
	const unsigned char *p = (const unsigned char *)block;
	for(int i = 0; i < size; i++) {
		hash += p[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}


/**
 * Use a classical compiler string hashing algorithm (see "The Compilers"
 * by Aho, Sethi, Ullman).
 */
unsigned long hash_string(const char *chars, int length) {
	unsigned long h = 0, g;
	for(int i = 0; i < length; i++) {
		h = (h << 4) + chars[i];
		if(g = h & 0xf0000000) {
			h = h ^ (g >> 24);
			h = h ^ g;
		}
	}
	return h;
}


/**
 * Use a classical compiler string hashing algorithm (see "The Compilers"
 * by Aho, Sethi, Ullman).
 */
unsigned long hash_cstring(const char *chars) {
	unsigned long h = 0, g;
	for(; *chars; chars++) {
		h = (h << 4) + *chars;
		if(g = h & 0xf0000000) {
			h = h ^ (g >> 24);
			h = h ^ g;
		}
	}
	return h;
}

};	// elm
