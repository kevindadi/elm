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
template <class K, class T>
class HashTable: public Map<K, T> {

	// KeyIterator class
	class KeyIterator: public IteratorInst<K> {
		typename genstruct::HashTable<K, T>::KeyIterator iter;
	public:
		inline KeyIterator(const HashTable<K, T>& htab): iter(htab.htab) { };
		virtual bool ended(void) const { return iter.ended(); };
		virtual K item(void) const { return iter.item(); };
		virtual void next(void) { iter.next(); };
	};
	
	// ItemIterator class
	class ItemIterator: public IteratorInst<T> {
		typename genstruct::HashTable<K, T>::ItemIterator iter;
	public:
		inline ItemIterator(const HashTable<K, T>& htab): iter(htab.htab) { };
		virtual bool ended(void) const { return iter.ended(); };
		virtual T item(void) const { return iter.item(); };
		virtual void next(void) { iter.next(); };
	};
	
	// KeyCollection class
	class KeyCollection: public Collection<K> {
		const HashTable<K, T>& htab;
	public:
		inline KeyCollection(const HashTable<K, T>& _htab);
		virtual IteratorInst<K> *visit(void) const;
		virtual MutableCollection<K> *empty(void) const;
	};
	
	// ValueCollection class
	class ItemCollection: public Collection<T> {
		const HashTable<K, T>& htab;
	public:
		inline ItemCollection(const HashTable<K, T>& _htab);
		virtual IteratorInst<T> *visit(void) const;
		virtual MutableCollection<T> *empty(void) const;
	};
		
	genstruct::HashTable<K, T> htab;
	KeyCollection keycol;
	ItemCollection itemcol;
public:
	inline HashTable(HashKey<K>& hkey = HashKey<K>::def, int size = 211);

	// Map overload
	virtual void put(const K key, const T value);
	virtual const Option<T> get(const K key);
	virtual const T get(const K key, const T def);
	virtual void remove(const K key);
	virtual const Collection<K>& keys(void);
	virtual const Collection<T>& items(void);
};


// Methods
template <class K, class T>
HashTable<K, T>::HashTable(HashKey<K>& hkey, int size)
: htab(hkey, size), keycol(*this), itemcol(*this) {
}

template <class K, class T>
void HashTable<K, T>::put(const K key, const T value) {
	htab.put(key, value);
}

template <class K, class T> 
const Option<T> HashTable<K, T>::get(const K key) {
	return htab.get(key);
}

template <class K, class T>
const T HashTable<K, T>::get(const K key, const T def) {
	return htab.get(key, def);
}

template <class K, class T>
void HashTable<K, T>::remove(const K key) {
	htab.remove(key);
}

template <class K, class T>
const Collection<K>& HashTable<K, T>::keys(void) {
	return keycol;
}

template <class K, class T>
const Collection<T>& HashTable<K, T>::items(void) {
	return itemcol;
}


// HashTable<K, T>::KeyCollection methods
template <class K, class T>
HashTable<K, T>::KeyCollection::KeyCollection(const HashTable<K, T>& _htab)
: htab(_htab) {
}

template <class K, class T>
IteratorInst<K> *HashTable<K, T>::KeyCollection::visit(void) const {
	return new KeyIterator(htab);
}

template <class K, class T>
MutableCollection<K> *HashTable<K, T>::KeyCollection::empty(void) const {
	return new Vector<K>();
}


// HashTable<K, T>::ItemCollection methods
template <class K, class T>
HashTable<K, T>::ItemCollection::ItemCollection(const HashTable<K, T>& _htab)
: htab(_htab) {
}

template <class K, class T>
IteratorInst<T> *HashTable<K, T>::ItemCollection::visit(void) const {
	return new ItemIterator(htab);
}

template <class K, class T>
MutableCollection<T> *HashTable<K, T>::ItemCollection::empty(void) const {
	return new Vector<T>();
}

} } // elm::datastruct

#endif	// ELM_DATASTRUCT_HASHTABLE_H
