/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * collection.h -- collection classes interfaces.
 */
#ifndef ELM_DATASTRUCT_COLLECTION_H
#define ELM_DATASTRUCT_COLLECTION_H

#include <elm/string.h>
#include <elm/utility.h>
#include <elm/Iterator.h>

namespace elm { namespace datastruct {

	
// Classes
template <class T> class Collection;
template <class T> class MutableCollection;


// Abstract collection class
template <class T> class Collection {
public:
	
	// Simple access
	virtual int count(void) const;
	virtual bool isEmpty(void) const;	
	virtual bool contains(const T value) const;
	virtual bool containsAll(const Collection<T> *values) const;
	virtual bool equals(const Collection<T> *values) const;	

	// Iteration
	virtual IteratorInst<T> *visit(void) const = 0;
	inline operator IteratorInst<T> *(void) const;

	// Building
	virtual MutableCollection<T> *empty(void) const = 0;
	virtual MutableCollection<T> *copy(void) const;
	virtual Collection<T> *merge(const Collection<T> *values) const;
	virtual Collection<T> *retain(const Collection<T> *values) const;
	virtual Collection<T> *meet(const Collection<T> *values) const;
	
	// Operators
	inline operator bool(void);
};


// Mutable collection interface
template <class T> class MutableCollection: public Collection<T> {
public:
	virtual MutableIteratorInst<T> *edit(void) = 0;	
	virtual void add(const T value) = 0;
	virtual void addAll(const Collection<T> *values);
	virtual void remove(const T value) = 0;
	virtual void removeAll(const Collection<T> *values);
	virtual void clear(void) = 0;
};


// Collection methods
template <class T> bool Collection<T>::isEmpty(void) const  {
	return !count();
}

template <class T> bool Collection<T>::containsAll(const Collection<T> *values) const {
	for(Iterator<T> iter(*this); iter; iter++)
		if(!contains(*iter))
			return false;
	return true;
}

template <class T> bool Collection<T>::equals(const Collection<T> *values) const {
	return containsAll(values) && values->containsAll(this);
}

template <class T> int Collection<T>::count(void) const {
	int cnt = 0;
	for(Iterator<T> iter(*this); iter; iter++)
		cnt++;
	return cnt;
} 

template <class T> bool Collection<T>::contains(const T value) const {
	for(Iterator<T> iter(*this); iter; iter++)
		if(*iter == value)
			return true;
	return false;
}

template <class T> Collection<T>::operator IteratorInst<T> *(void) const {
	return visit();
}


template <class T>
Collection<T> *Collection<T>::merge(const Collection<T> *values) const {
	Collection<T> *result = copy();
	copy()->addAll(values);
	return result;
}

template <class T>
Collection<T> *Collection<T>::retain(const Collection<T> *values) const {
	MutableCollection<T> *result = empty();
	for(Iterator<T> iter(*this); iter; iter++)
		if(!values->contains(*iter))
			result->add(*iter);
	return result;
}

template <class T>
Collection<T> *Collection<T>::meet(const Collection<T> *values) const {
	MutableCollection<T> *result = empty();
	for(Iterator<T> iter(*this); iter; iter++)
		if(values->contains(*iter))
			result->add(*iter);
	return result;
}

template <class T>
MutableCollection<T> *Collection<T>::copy(void) const {
	MutableCollection<T> *result = empty();
	result->addAll(this);
	return result;
}

template <class T>
inline Collection<T>::operator bool(void) {
	return !isEmpty();
}


// MutableCollection methods
template <class T>
void MutableCollection<T>::addAll(const Collection<T> *values) {
	for(Iterator<T> iter(*this); iter; iter++)
		add(*iter);
}

template <class T>
void MutableCollection<T>::removeAll(const Collection<T> *values) {
	for(Iterator<T> iter(*this); iter; iter++)
		remove(*iter);
}


} } // namespace elm::datastruct

#endif	// ELM_DATASTRUCT_COLLECTION_H
