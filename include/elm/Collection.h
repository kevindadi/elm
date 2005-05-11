/*
 * $Id$
 * Copyright (c) 2004, IRIT UPS.
 *
 * elm/Collection.h -- Collection and MutableCollection interfaces.
 */
#ifndef ELM_COLLECTION_H
#define ELM_COLLECTION_H

#include <elm/string.h>
#include <elm/utility.h>
#include <elm/Iterator.h>

namespace elm {

// Classes
template <class T> class Collection;
template <class T> class MutableCollection;


// Abstract collection class
template <class T> class Collection {
public:
	
	// Simple access
	virtual int count(void);
	virtual bool isEmpty(void);	
	virtual bool contains(const T value);
	virtual bool containsAll(Collection<T> *values);
	virtual bool equals(Collection<T> *values);	

	// Iteration
	virtual IteratorInst<T> *visit(void) = 0;

	// Building
	virtual MutableCollection<T> *empty(void) = 0;
	virtual MutableCollection<T> *copy(void);
	virtual Collection<T> *merge(Collection<T> *values);
	virtual Collection<T> *retain(Collection<T> *values);
	virtual Collection<T> *meet(Collection<T> *values);
	
	// Operators
	inline operator bool(void);
	inline operator IteratorInst<T> *(void);
	inline Collection<T>& operator+(Collection<T>& values);
	inline Collection<T>& operator-(Collection<T>& values);
	inline Collection<T>& operator*(Collection<T>& values);
	inline bool operator==(Collection<T>& values);
	inline bool operator!=(Collection<T>& values);
	inline bool operator<(Collection<T>& values);
	inline bool operator<=(Collection<T>& values);
	inline bool operator>(Collection<T>& values);
	inline bool operator>=(Collection<T>& values);
	inline bool operator()(T value);
};


// Mutable collection interface
template <class T> class MutableCollection: public Collection<T> {
public:

	// Accessors
	virtual MutableIteratorInst<T> *edit(void) = 0;	
	
	// Modifiers
	virtual void add(const T value) = 0;
	virtual void addAll(Collection<T> *values);
	virtual void remove(const T value) = 0;
	virtual void removeAll(Collection<T> *values);
	virtual void clear(void) = 0;
	
	// Operators
	inline MutableCollection<T>& operator+=(const T value);
	inline MutableCollection<T>& operator+=(Collection<T>& values);
	inline MutableCollection<T>& operator-=(const T value);
	inline MutableCollection<T>& operator-=(Collection<T>& values);
};


// Collection methods
template <class T> bool Collection<T>::isEmpty(void)  {
	return !count();
}

template <class T> bool Collection<T>::containsAll(Collection<T> *values) {
	for(Iterator<T> iter(*this); iter; iter++)
		if(!contains(*iter))
			return false;
	return true;
}

template <class T> bool Collection<T>::equals(Collection<T> *values) {
	return containsAll(values) && values->containsAll(this);
}

template <class T> int Collection<T>::count(void) {
	int cnt = 0;
	for(Iterator<T> iter(*this); iter; iter++)
		cnt++;
	return cnt;
} 

template <class T> bool Collection<T>::contains(const T value) {
	for(Iterator<T> iter(*this); iter; iter++)
		if(*iter == value)
			return true;
	return false;
}

template <class T> Collection<T>::operator IteratorInst<T> *(void) {
	return visit();
}


template <class T>
Collection<T> *Collection<T>::merge(Collection<T> *values) {
	Collection<T> *result = copy();
	copy()->addAll(values);
	return result;
}

template <class T>
Collection<T> *Collection<T>::retain(Collection<T> *values) {
	MutableCollection<T> *result = empty();
	for(Iterator<T> iter(*this); iter; iter++)
		if(!values->contains(*iter))
			result->add(*iter);
	return result;
}

template <class T>
Collection<T> *Collection<T>::meet(Collection<T> *values) {
	MutableCollection<T> *result = empty();
	for(Iterator<T> iter(*this); iter; iter++)
		if(values->contains(*iter))
			result->add(*iter);
	return result;
}

template <class T>
MutableCollection<T> *Collection<T>::copy(void) {
	MutableCollection<T> *result = empty();
	result->addAll(this);
	return result;
}

template <class T>
inline Collection<T>::operator bool(void) {
	return !isEmpty();
}

template <class T>
inline Collection<T>& Collection<T>::operator+(Collection<T>& values) {
	return *merge(&values);
}

template <class T>
inline Collection<T>& Collection<T>::operator-(Collection<T>& values) {
	return *retain(&values);
}

template <class T>
inline Collection<T>& Collection<T>::operator*(Collection<T>& values) {
	return *meet(&values);
}

template <class T>
inline bool Collection<T>::operator==(Collection<T>& values) {
	return equals(&values);
}

template <class T>
inline bool Collection<T>::operator!=(Collection<T>& values) {
	return !equals(&values);
}

template <class T>
inline bool Collection<T>::operator<(Collection<T>& values) {
	return values.containsAll(this) && !equals(&values);
}

template <class T>
inline bool Collection<T>::operator<=(Collection<T>& values) {
	return values.containsAll(&values);
}

template <class T>
inline bool Collection<T>::operator>(Collection<T>& values) {
	return containsAll(&values) && !equals(&values);
}

template <class T>
inline bool Collection<T>::operator>=(Collection<T>& values) {
	return containsAll(&values);
}

template <class T>
inline bool Collection<T>::operator()(const T value) {
	return contains(value);
}


// MutableCollection methods
template <class T>
void MutableCollection<T>::addAll(Collection<T> *values) {
	for(Iterator<T> iter(*this); iter; iter++)
		add(*iter);
}

template <class T>
void MutableCollection<T>::removeAll(Collection<T> *values) {
	for(Iterator<T> iter(*this); iter; iter++)
		remove(*iter);
}

template <class T>
inline MutableCollection<T>& MutableCollection<T>::operator+=(const T value) {
	add(value);
	return *this;
}

template <class T>
inline MutableCollection<T>& MutableCollection<T>::operator+=(Collection<T>& values) {
	addAll(values);
	return *this;
}

template <class T>
inline MutableCollection<T>& MutableCollection<T>::operator-=(const T value) {
	remove(value);
	return *this;
}

template <class T>
inline MutableCollection<T>& MutableCollection<T>::operator-=(Collection<T>& values) {
	removeAll(values);
	return *this;
}

} // elm

#endif	// ELM_COLLECTION_H
