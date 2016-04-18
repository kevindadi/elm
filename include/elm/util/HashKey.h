/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * HashKey class interface.
 */
#ifndef ELM_UTIL_HASH_KEY_H
#define ELM_UTIL_HASH_KEY_H

#include <elm/types.h>
#include <elm/string.h>
#include <elm/util/Equiv.h>
#include <elm/util/Option.h>

namespace elm {

namespace t { typedef t::intptr hash; }

// Useful hash functions
t::hash hash_string(const char *chars, int length);
t::hash hash_cstring(const char *chars);
t::hash hash_jenkins(const void *block, int size);
bool hash_equals(const void *p1, const void *p2, int size);

// HashKey class
template <class T> class HashKey {
public:
	static t::hash hash(const T& key) { return hash_jenkins(&key, sizeof(T)); };
	static inline bool equals(const T& key1, const T& key2) { return &key1 == &key2 || Equiv<T>::equals(key1, key2); }
};

template <class T> class HashKey<const T&> {
public:
	static t::hash hash(const T& key) { return hash_jenkins(&key, sizeof(T)); };
	static inline bool equals(const T& key1, const T& key2) { return &key1 == &key2 || Equiv<T>::equals(key1, key2); }
};

template <class T> class HashKey<T&> {
public:
	static t::hash hash(const T& key) { return hash_jenkins(&key, sizeof(T)); };
	static inline bool equals(const T& key1, const T& key2) { return &key1 == &key2 || Equiv<T>::equals(key1, key2); }
};

};	// elm

#endif	// ELM_UTIL_HASH_KEY_H
