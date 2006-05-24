/*
 * $Id$
 * Copyright (c) 2004, IRIT UPS.
 *
 * elm/genstruct/Vector.h -- Vector class interface.
 */
#ifndef ELM_GENSTRUCT_VECTOR_H
#define ELM_GENSTRUCT_VECTOR_H

#include <assert.h>
#include <elm/Iterator.h>

namespace elm { namespace genstruct {


// EmbedVector class
template <class T>
class Vector {
	T *tab;
	unsigned short cap, cnt;
public:
	inline Vector(int _cap = 8);
	inline ~Vector(void);
	
	// Accessors
	inline int capacity(void) const;
	inline int length(void) const;
	inline bool isEmpty(void) const;	
	inline T get(int index) const;
	inline T& item(int index);
	inline void set(int index, const T value);
	inline T& operator[](int index);
	inline T operator[](int index) const;
	bool contains(const T value) const;
	int indexOf(const T value, int start = 0) const;
	int lastIndexOf(const T value, int start = -1) const;
	inline operator bool(void) const;
	
	// Mutators
	inline void add(const T value);
	void removeAt(int index);
	inline void remove(const T value);
	void insert(int index, const T value);
	inline void clear(void);
	void grow(int new_cap);
	void setLength(int new_length);
	
	// Stack processing
	inline void push(const T& value);
	inline const T pop(void);
	inline const T top(void);
	
	// Iterator
	class Iterator: public PreIterator<Iterator, T> {
		const Vector<T>& _vec;
		int i;
	public:
		inline Iterator(const Vector& vec);
		inline Iterator(Iterator& iter);
		inline bool ended(void) const;
		inline T item(void) const;
		inline void next(void);
	};
};


// EmbedVector methods
template <class T> Vector<T>::Vector(int _cap)
: tab(new T[_cap]), cap(_cap), cnt(0) {
}
template <class T> Vector<T>::~Vector(void) {
	delete [] tab;
}
template <class T> int Vector<T>::capacity(void) const {
	return cap;
}
template <class T> int Vector<T>::length(void) const {
	return cnt;
}
template <class T> bool Vector<T>::isEmpty(void) const {
	return cnt == 0;
}
template <class T> T& Vector<T>::item(int index) {
	assert(index < cnt);
	return tab[index];
}
template <class T> T Vector<T>::get(int index) const {
	assert(index < cnt);
	return tab[index];
}
template <class T> void Vector<T>::set(int index, const T value) {
	assert(index < cnt);
	tab[index] = value;
}
template <class T> T& Vector<T>::operator[](int index) {
	return item(index);
}
template <class T> T Vector<T>::operator[](int index) const {
	return get(index);
}
template <class T> bool Vector<T>::contains(const T value) const {
	for(int i = 0; i < cnt; i++)
		if(value == tab[i])
			return true;
	return false;
}
template <class T> int Vector<T>::indexOf(const T value, int start) const {
	for(int i = start; i < cnt; i++)
		if(value == tab[i])
			return i;
	return -1;
}
template <class T> int Vector<T>::lastIndexOf(const T value, int start) const {
	assert(start <= cnt);
	for(int i = (start < 0 ? cnt : start) - 1; i >= 0; i--)
		if(value == tab[i])
			return i;
	return -1;
}
template <class T> Vector<T>::operator bool(void) const {
	return cnt != 0;
}

template <class T> void Vector<T>::add(const T value) {
	if(cnt >= cap)
		grow(cap * 2);
	tab[cnt++] = value;
}
template <class T> void Vector<T>::removeAt(int index) {
	for(int i = index + 1; i < cnt; i++)
		tab[i - 1] = tab[i];
	cnt--;
}
template <class T> void Vector<T>::remove(const T value) {
	int i = indexOf(value);
	if(i >= 0) removeAt(i);
}
template <class T> void Vector<T>::insert(int index, const T value) {
	assert(index <= cnt);
	if(cnt >= cap)
		grow(cap * 2);
	for(int i = cnt; i > index; i--)
		tab[i] = tab[i - 1];
	tab[index] = value;
	cnt++;
}
template <class T> void Vector<T>::clear(void) {
	cnt = 0;
}
template <class T> void Vector<T>::grow(int new_cap) {
	assert(new_cap > 0);
	assert(new_cap < 65536);
	assert(new_cap >= cap);
	cap = new_cap;
	T *new_tab = new T[cap];
	for(int i =0; i < cnt; i++)
		new_tab[i] = tab[i];
	delete [] tab;
	tab = new_tab;
}
template <class T> void Vector<T>::setLength(int new_length) {
	assert(new_length >= 0);
	assert(new_length <= cnt);
	cnt = new_length;
}

template <class T> inline void Vector<T>::push(const T& value) {
	add(value);
}

template <class T> inline const T Vector<T>::pop(void) {
	assert(cnt > 0);
	return tab[--cnt];
}

template <class T> inline const T Vector<T>::top(void) {
	assert(cnt > 0);
	return tab[cnt - 1];
}


// Vector<T>::Iterator class
template <class T>
inline Vector<T>::Iterator::Iterator(const Vector& vec): _vec(vec), i(0) {
}
template <class T>
inline Vector<T>::Iterator::Iterator(Vector<T>::Iterator& iter)
: _vec(iter._vec), i(iter.i) {
}
template <class T>
inline bool Vector<T>::Iterator::ended(void) const {
	return i >= _vec.length();
}
template <class T>
inline T Vector<T>::Iterator::item(void) const {
	return _vec[i];
}
template <class T>
inline void Vector<T>::Iterator::next(void) {
	i++;
}

} }		// elm::genstruct

#endif	// ELM_GENSTRUCT_VECTOR_H
