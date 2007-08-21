/*
 *	$Id$
 *	Vector class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-07, IRIT UPS.
 * 
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software 
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef ELM_GENSTRUCT_VECTOR_H
#define ELM_GENSTRUCT_VECTOR_H

#include <elm/assert.h>
#include <elm/genstruct/Table.h>
#include <elm/Iterator.h>

namespace elm { namespace genstruct {


// EmbedVector class
template <class T>
class Vector {
	T *tab;
	unsigned short cap, cnt;
public:
	inline Vector(int _cap = 8);
	inline Vector(const Vector<T>& vec);
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
	inline void add(void);
	inline void add(const T value);
	void removeAt(int index);
	inline void remove(const T value);
	void insert(int index, const T value);
	inline void clear(void);
	void grow(int new_cap);
	void setLength(int new_length);
	inline Table<T> detach(void);
	inline void copy(const Vector& vec);
	inline Vector<T>& operator=(const Vector& vec) { copy(vec); };

	// Stack processing
	inline void push(const T& value);
	inline const T pop(void);
	inline const T& top(void) const;
	
	// Iterator
	class Iterator: public PreIterator<Iterator, T> {
		const Vector<T>& _vec;
		int i;
	public:
		inline Iterator(const Vector& vec);
		inline Iterator(const Iterator& iter);
		inline bool ended(void) const;
		inline T item(void) const;
		inline void next(void);
	};
};


// EmbedVector methods
template <class T> Vector<T>::Vector(int _cap)
: tab(new T[_cap]), cap(_cap), cnt(0) {
}


template <class T> inline Vector<T>::Vector(const Vector<T>& vec)
: tab(0), cap(0), cnt(0) {
	copy(vec);
}


template <class T> Vector<T>::~Vector(void) {
	if(tab)
		delete [] tab;
}

template <class T>
inline Table<T> Vector<T>::detach(void) {
	T *dtab = tab;
	tab = 0;
	return Table<T>(dtab, cnt);
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
	ASSERTP(index < cnt, "index out of bounds");
	return tab[index];
}
template <class T> T Vector<T>::get(int index) const {
	ASSERTP(index < cnt, "index out of bounds");
	return tab[index];
}
template <class T> void Vector<T>::set(int index, const T value) {
	ASSERTP(index < cnt, "index out of bounds");
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
	ASSERTP(start <= cnt, "index out of bounds");
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

template <class T>
inline void Vector<T>::add(void) {
	if(cnt >= cap)
		grow(cap * 2);
	cnt++;	
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
	ASSERTP(index <= cnt, "index out of bounds");
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
	ASSERTP(new_cap > 0 && new_cap < 65536, "new capacity out of [1, 65535]");
	ASSERTP(new_cap >= cap, "new capacity must be bigger than old one");
	cap = new_cap;
	T *new_tab = new T[cap];
	for(int i =0; i < cnt; i++)
		new_tab[i] = tab[i];
	delete [] tab;
	tab = new_tab;
}
template <class T> void Vector<T>::setLength(int new_length) {
	ASSERTP(new_length >= 0 && new_length <= cnt, "new length must be in [0, current length]");
	cnt = new_length;
}

template <class T> inline void Vector<T>::copy(const Vector& vec) {
	if(!tab || vec.cnt > cap) {
		if(tab)
			delete [] tab;
		cap = vec.cap;
		tab = new T[vec.cap];
	}
	cnt = vec.cnt;
	for(int i = 0; i < cnt; i++)
		tab[i] = vec.tab[i];
}

template <class T> inline void Vector<T>::push(const T& value) {
	add(value);
}

template <class T> inline const T Vector<T>::pop(void) {
	ASSERTP(cnt > 0, "no more data to pop");
	return tab[--cnt];
}

template <class T> inline const T& Vector<T>::top(void) const {
	ASSERTP(cnt > 0, "no more data in the stack");
	return tab[cnt - 1];
}


// Vector<T>::Iterator class
template <class T>
inline Vector<T>::Iterator::Iterator(const Vector& vec): _vec(vec), i(0) {
}
template <class T>
inline Vector<T>::Iterator::Iterator(const Vector<T>::Iterator& iter)
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
