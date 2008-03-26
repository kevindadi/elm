/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * obj/dllist.h -- vector object structure interface.
 */
#ifndef ELM_DATASTRUCT_DLLIST_H
#define ELM_DATASTRUCT_DLLIST_H

#include <elm/Iterator.h>
#include <elm/Collection.h>
#include <elm/genstruct/DLList.h>

namespace elm { namespace datastruct {

// DLList class
template <class T>
class DLList: public Collection<T> {
	genstruct::DLList<T> list;
public:
	virtual ~DLList(void) { }

	// Accessors
	inline T first(void) const;
	inline T last(void) const;

	// Mutators
	inline void remove(const T value);
	inline void addFirst(const T value);
	inline void addLast(const T value);
	inline void removeFirst(void);
	inline void removeLast(void);
	inline void clear(void);
	
	// Collection overload
	virtual int count(void);
	virtual bool isEmpty(void);	
	virtual bool contains(const T value);
	virtual IteratorInst<T> *visit(void);
	virtual MutableCollection<T> *empty(void);
	
	// Iterator class
	class Iterator: public genstruct::DLList<T>::Iterator {
		friend class DLList<T>;
		inline Iterator(const typename genstruct::DLList<T>::Iterator& iter);
	public:
		inline Iterator(const DLList<T>& list);
		inline Iterator(const Iterator& iter);
	};
	
	// Iterator methods
	Iterator fromFirst(void) const { return list.fromFirst(); }
	Iterator fromLast(void) const { return list.fromLast(); }
};

// DLList<T>::Iterator class
template <class T>
inline DLList<T>::Iterator::Iterator(const DLList<T>& list)
: genstruct::DLList<T>::Iterator(list.list) {
}

template <class T>
inline DLList<T>::Iterator::Iterator(const DLList<T>::Iterator::Iterator& iter)
: genstruct::DLList<T>::Iterator(iter) {
}

template <class T>
inline DLList<T>::Iterator::Iterator(const typename genstruct::DLList<T>::Iterator& iter)
: genstruct::DLList<T>::Iterator(iter) {
}


// DLList methods
template <class T> inline T DLList<T>::first(void) const {
	return list.first();
}

template <class T> inline T DLList<T>::last(void) const {
	return list.last();
}

template <class T> inline void DLList<T>::remove(const T value) {
	list.remove(value);
}

template <class T> inline void DLList<T>::addFirst(const T value) {
	list.addFirst(value);
}

template <class T> inline void DLList<T>::addLast(const T value) {
	list.addLast(value);
}

template <class T> inline void DLList<T>::removeFirst(void) {
	list.removeFirst();
}

template <class T> inline void DLList<T>::removeLast(void) {
	list.removeLast();
}

template <class T> inline void DLList<T>::clear(void) {
	list.clear();
}

template <class T> int DLList<T>::count(void) {
	return list.count();
}

template <class T> bool DLList<T>::isEmpty(void) {
	return list.isEmpty();
}

template <class T> bool DLList<T>::contains(const T value) {
	return list.contains(value);
}

template <class T> IteratorInst<T> *DLList<T>::visit(void) {
	Iterator iter(*this);
	return new IteratorObject<Iterator, T>(iter);
}

template <class T> MutableCollection<T> *DLList<T>::empty(void) {
	return 0 /*new DLList<T>*/;
}

} }	// elm::datastruct

#endif	// ELM_OBJ_DLLIST_H
