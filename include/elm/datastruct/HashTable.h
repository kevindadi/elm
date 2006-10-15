/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/datastruct/HashTable.h -- hashing table.
 */
#ifndef ELM_DATASTRUCT_HASHTABLE_H
#define ELM_DATASTRUCT_HASHTABLE_H

#include <elm/datastruct/Vector.h>
#include <elm/datastruct/Map.h>
#include <elm/genstruct/HashTable.h>

namespace elm { namespace datastruct {

// HashTable class
template <class K, class T, class H = HashKey<K> >
class HashTable: public Map<K, T> {

	// KeyCollection class
	class KeyCollection: public Collection<K> {
		const HashTable<K, T, H>& htab;
	public:
		inline KeyCollection(const HashTable<K, T, H>& _htab);
		virtual IteratorInst<K> *visit(void);
		virtual MutableCollection<K> *empty(void);
	};
	
	// ValueCollection class
	class ItemCollection: public Collection<T> {
		const HashTable<K, T, H>& htab;
	public:
		inline ItemCollection(const HashTable<K, T, H>& _htab);
		virtual IteratorInst<T> *visit(void);
		virtual MutableCollection<T> *empty(void);
	};
		
	genstruct::HashTable<K, T, H> htab;
	KeyCollection keycol;
	ItemCollection itemcol;
public:
	inline HashTable(int size = 211);

	// Map overload
	virtual void put(const K key, const T value);
	virtual const Option<T> get(const K key);
	virtual const T get(const K key, const T def);
	virtual void remove(const K key);
	virtual Collection<K>& keys(void);
	virtual Collection<T>& items(void);
};


// Methods
template <class K, class T, class H>
HashTable<K, T, H>::HashTable(int size)
: htab(size), keycol(*this), itemcol(*this) {
}

template <class K, class T, class H>
void HashTable<K, T, H>::put(const K key, const T value) {
	htab.put(key, value);
}

template <class K, class T, class H> 
const Option<T> HashTable<K, T, H>::get(const K key) {
	return htab.get(key);
}

template <class K, class T, class H>
const T HashTable<K, T, H>::get(const K key, const T def) {
	return htab.get(key, def);
}

template <class K, class T, class H>
void HashTable<K, T, H>::remove(const K key) {
	htab.remove(key);
}

template <class K, class T, class H>
Collection<K>& HashTable<K, T, H>::keys(void) {
	return keycol;
}

template <class K, class T, class H>
Collection<T>& HashTable<K, T, H>::items(void) {
	return itemcol;
}


// HashTable<K, T, H>::KeyCollection methods
template <class K, class T, class H>
HashTable<K, T, H>::KeyCollection::KeyCollection(const HashTable<K, T, H>& _htab)
: htab(_htab) {
}

template <class K, class T, class H>
IteratorInst<K> *HashTable<K, T, H>::KeyCollection::visit(void) {
	typename genstruct::HashTable<K, T, H>::KeyIterator iter(htab.htab);
	return new IteratorObject<typename genstruct::HashTable<K, T, H>::KeyIterator, K>(iter);
}

template <class K, class T, class H>
MutableCollection<K> *HashTable<K, T, H>::KeyCollection::empty(void) {
	return new Vector<K>();
}


// HashTable<K, T>::ItemCollection methods
template <class K, class T, class H>
HashTable<K, T, H>::ItemCollection::ItemCollection(const HashTable<K, T, H>& _htab)
: htab(_htab) {
}

template <class K, class T, class H>
IteratorInst<T> *HashTable<K, T, H>::ItemCollection::visit(void) {
	typename genstruct::HashTable<K, T, H>::ItemIterator iter(htab.htab);
	return new IteratorObject<typename genstruct::HashTable<K, T, H>::ItemIterator, T>(iter);
}

template <class K, class T, class H>
MutableCollection<T> *HashTable<K, T, H>::ItemCollection::empty(void) {
	return new Vector<T>();
}

} } // elm::datastruct

#endif	// ELM_DATASTRUCT_HASHTABLE_H
