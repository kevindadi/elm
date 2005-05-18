/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * obj/vector.h -- vector object structure interface.
 */
#ifndef ELM_DATASTRUCT_VECTOR_H
#define ELM_DATASTRUCT_VECTOR_H

#include <elm/Collection.h>
#include <elm/datastruct/Indexed.h>
#include <elm/genstruct/Vector.h>


namespace elm { namespace datastruct {


// Vector class
template <class T>
class Vector: public Indexed<T>, public MutableCollection<T> {

	// Iterator class
	class Iterator: public IteratorInst<T> {
		const Vector<T> vec;
		int i;
	public:
		inline Iterator(const Vector<T>& vec);
		
		// IteratorInst overload
		virtual bool ended(void) const;
		virtual T item(void) const;
		virtual void next(void);		
	};
	
	// Editor class
	class MutableIterator: public MutableIteratorInst<T> {
		Vector<T> vec;
		int i;
	public:
		inline MutableIterator(Vector<T>& _vec); 
		
		// Editor overload
		virtual bool ended(void) const;
		virtual T& item(void);
		virtual void next(void);
		virtual void remove(void);
	};

	genstruct::Vector<T> vec;
public:
	inline Vector(int _cap = 8);

	// Vector methods	
	inline int capacity(void) const;
	void removeAt(int index);
	void insert(int index, const T value);
	void grow(int new_cap);
	void setLength(int new_length);

	// Array overload
	virtual int length(void) const;
	virtual T get(int index) const;
	virtual void set(int index, const T value);
	virtual T& item(int index);

	// Collection overload
	virtual IteratorInst<T> *visit(void);
	virtual MutableIteratorInst<T> *edit(void);
	inline operator IteratorInst<T> *(void) { return visit(); };
	inline operator MutableIteratorInst<T> *(void) { return edit(); };
	virtual int count(void);
	virtual bool isEmpty(void);	
	virtual void add(const T value);
	virtual void remove(const T value);
	virtual void clear(void);
	virtual MutableCollection<T> *empty(void);
};


// Vector<T>::Iterator methods
template <class T> Vector<T>::Iterator::Iterator(const Vector<T>& _vec)
: vec(_vec), i(0) {
}
template <class T> bool Vector<T>::Iterator::ended(void) const {
	return i >= vec.length();
}
template <class T> T Vector<T>::Iterator::item(void) const {
	return vec[i];
}
template <class T> void Vector<T>::Iterator::next(void) {
	i++;
}


// Vector<T>::Editor class
template <class T> Vector<T>::MutableIterator::MutableIterator(Vector<T>& _vec)
: vec(_vec), i(0) {
}
template <class T> bool Vector<T>::MutableIterator::ended(void) const {
	return i >= vec.length();
}
template <class T> T& Vector<T>::MutableIterator::item(void) {
	return vec.item(i);
}
template <class T> void Vector<T>::MutableIterator::next(void) {
	i++;
}
template <class T> void Vector<T>::MutableIterator::remove(void) {
	vec.removeAt(i);
}


// Vector<T> methods
template <class T> Vector<T>::Vector(int _cap): vec(_cap) {
}
template <class T> int Vector<T>::capacity(void) const {
	return vec.capacity();
}
template <class T> void Vector<T>::removeAt(int index) {
	vec.removeAt(index);
}
template <class T> void Vector<T>::insert(int index, const T value) {
	vec.insert(index, value);
}
template <class T> void Vector<T>::grow(int new_cap) {
	vec.grow(new_cap);
}
template <class T> void Vector<T>::setLength(int new_length) {
	vec.setLength(new_length);
}

// Vector<T> Array overload
template <class T> int Vector<T>::length(void) const {
	return vec.length();
}
template <class T> T Vector<T>::get(int index) const {
	return vec.get(index);
}
template <class T> void Vector<T>::set(int index, const T value) {
	vec.set(index, value);
}
template <class T> T& Vector<T>::item(int index) {
	return vec.item(index);
}

// Vector<T> Collection overload
template <class T> IteratorInst<T> *Vector<T>::visit(void) {
	return new Iterator(*this);
}
template <class T> MutableIteratorInst<T> *Vector<T>::edit(void) {
	return new MutableIterator(*this);
}
template <class T> int Vector<T>::count(void) {
	return vec.length();
}
template <class T> bool Vector<T>::isEmpty(void) {
	return vec.isEmpty();
}
template <class T> void Vector<T>::add(const T value) {
	vec.add(value);
}
template <class T> void Vector<T>::remove(const T value) {
	vec.remove(value);
}
template <class T> void Vector<T>::clear(void) {
	vec.clear();
}
template <class T> MutableCollection<T> *Vector<T>::empty(void) {
	return new Vector<T>(vec.capacity());
}

} };		// elm::datastruct

#endif	// ELM_DATASTRUCT_VECTOR_H
