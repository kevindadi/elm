/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * HashKey class interface.
 */
#ifndef ELM_UTIL_HASH_KEY_H
#define ELM_UTIL_HASH_KEY_H

#include <elm/string.h>
#include <elm/util/Option.h>

namespace elm {

// Useful hash functions
unsigned long hash_string(const char *chars, int length);
unsigned long hash_cstring(const char *chars);
unsigned long hash_jenkins(const void *block, int size);

// HashKey class
template <class T> class HashKey {
public:
	static unsigned long hash(const T& key)
		{ return hash_jenkins(&key, sizeof(T)); };
	static inline bool equals(const T& key1, const T& key2)
		{ return key1 == key2; }
};

// Predefined hash keys
template <> class HashKey<int> {
public:
	static inline unsigned long hash(int key) { return (unsigned long)key; }
	static inline bool equals(int key1, int key2) { return key1 == key2; }
};

template <> class HashKey<void *> {
public:
	static inline unsigned long hash(void *key) { return (unsigned long)key; }
	static inline bool equals(void *key1, void *key2) { return key1 == key2; } 
};

template <> class HashKey<const void *> {
public:
	static inline unsigned long hash(const void *key)
		{ return (unsigned long)key; }
	static inline bool equals(const void *key1, const void *key2)
		{ return key1 == key2; }
};

template <> class HashKey<CString> {
public:
	static unsigned long hash(CString key)
		{ return hash_cstring(&key); }
	static inline bool equals(CString key1, CString key2)
		{ return key1 == key2; }
};

template <> class HashKey<String> {
public:
	static unsigned long hash(const String& key)
		{ return hash_string(key.chars(), key.length()); };
	static inline bool equals(const String& key1, const String& key2)
		{ return key1 == key2; };
};

};	// elm

#endif	// ELM_UTIL_HASH_KEY_H
