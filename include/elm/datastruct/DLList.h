/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * obj/dllist.h -- vector object structure interface.
 */
#ifndef ELM_OBJ_DLLIST_H
#define ELM_OBJ_DLLIST_H

#include <assert.h>
#include <elm/sequence.h>
#include <elm/data/dllist.h>

namespace elm { namespace obj {

// DLList class
template <class T>
class DLList: public MutableCollection<T>, public data::DLList<T> {
public:

	// Collection overload
	virtual int count(void);
	virtual bool isEmpty(void);	
	virtual IteratorInst<T> *visit(void);
	virtual EditorInst<T> *edit(void);
	virtual bool contains(const T value) const;	
	virtual void add(const T value);
	virtual void remove(const T value);
	virtual void clear(void);
	virtual Collection<T> *empty(void);
	
	// Iterator class
	class Iterator: public IteratorInst<T> {
		typename data::DLList<T>::Iterator iter;
	public:
		inline Iterator(const DLList<T>& list): iter(list) {
		};
		inline Iterator(const DLList<T> *list): iter(*list) {
		};
		virtual bool ended(void) const { return iter.ended(); };
		virtual T item(void) const { return iter.item(); };
		virtual void next(void) { iter.next(); };		
	};
};


// DLList methods
template <class T> int DLList<T>::count(void) {
	return data::DLList<T>::count();
}
template <class T> bool DLList<T>::isEmpty(void) {
	return data::DLList<T>::isEmpty();
}
template <class T> IteratorInst<T> *DLList<T>::visit(void) {
	return new Iterator(this);
}
template <class T> EditorInst<T> *DLList<T>::edit(void) {
	assert(false);	// !!TODO!!
}
template <class T> bool DLList<T>::contains(const T value) {
	return data::DLList<T>::contains(value);
}
template <class T> void DLList<T>::add(const T value) {
	data::DLList<T>::addLast(value);
}
template <class T> void DLList<T>::remove(const T value) {
	data::DLList<T>::remove(value);
}
template <class T> void DLList<T>::clear(void) {
	data::DLList<T>::clear();
}
template <class T> Collection<T> *DLList<T>::empty(void) {
	return new DLList<T>();
}

} }	// elm::obj

#endif	// ELM_OBJ_DLLIST_H
