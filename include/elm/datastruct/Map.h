/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * map.h -- map class interface.
 */
#ifndef ELM_DATASTRUCT_MAP_H
#define ELM_DATASTRUCT_MAP_H

#include <elm/datastruct/Collection.h>

namespace elm { namespace datastruct {

// Map class
template <class K, class T> class Map {
public:
	virtual void put(const K key, const T value) = 0;
	virtual const Option<T> get(const K key) = 0;
	virtual const T get(const K key, const T def) = 0;
	virtual void remove(const K key) = 0;
	virtual Collection<K>& keys(void) = 0;
	virtual Collection<T>& items(void) = 0;
};

} }	// elm::datastruct

#endif	// ELM_DATASTRUCT_MAP_H
