/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/genstruct/FragArray.h -- interface for FragArray class.
 */
#ifndef ELM_GENSTRUCT_FRAGARRAY_H
#define ELM_GENSTRUCT_FRAGARRAY_H

#include <assert.h>

namespace elm { namespace genstruct {

// FragArray class
template <class T> class FragArray {
	T **tab;
	int mused, msize;
	int sused, ssize;
	int shf, msk;
public:
	inline FragArray(int main_size = 16, int sub_size = 4);
	inline ~FragArray(void);
	
	// Methods
	inline bool isEmpty(void) const;
	inline int count(void) const;
	inline const T& get(int index) const;
	inline void set(int index, const T& value) const;
	inline T& ref(int index);
	inline void add(T value);
	
	// Operators
	inline T& operator[](int index);
	inline T operator[](int index);
	inline FragArray<T>& operator+=(T value);
	inline operator bool(void) const;
	
	// Iterator
	class Iterator {
		FragArray<T>& arr;
		int i;
	public:
	
		// Methods
		inline Iterator(FragArray<T>& array);
		inline void next(void);
		inline const T& item(void) const;
		inline void set(const T& value);
		inline T& ref(void);
		inline bool atEnd(void) const;
		
		// Operators
		inline Iterator& operator++(void);
		inline const T& operator->(void) const;
		inline const T& operator*(void) const;
		inline operator bool(void);
		inline Iterator& operator=(const T& value);
	};
};


// Fragarray<T> Inlines
template <class T>
inline FragArray<T>::FragArray(int main_size, int sub_size)
: msize(main_size), shf(sub_size), mused(0) {
	assert(main_size > 0);
	assert(sub_size > 0);
	tab = new T*[main_size];
	ssize = 1 << shf;
	mask = ssize - 1;
	sused = ssize;
}

template <class T>
inline FragArray<T>::~FragArray(void) {
	for(int i = 0; i < mused; i++)
		delete [] tab[i];
	delete [] tab;
}

template <class T>	
inline bool FragArray<T>::isEmpty(void) const {
	return !mused;
}

template <class T>
inline int FragArray<T>::count(void) const {
	return (mused - 1) * ssize + sused;
}

template <class T>
inline const T& FragArray<T>::get(int index) const {
	assert(index >= 0 && index < count());
	return tab[index >> shf][index & msk];
}

template <class T>
inline void FragArray<T>::set(int index, const T& value) const {
	assert(index >= 0 && index < count());
	tab[index >> shf][index & msk] = value;
}

template <class T>
inline T& FragArray<T>::ref(int index) {
	assert(index >= 0 && index < count());
	return tab[index >> shf][index & msk];
}

template <class T>	
inline void FragArray<T>::add(T value) {
	if(sused >= ssize) {
		if(mused >= msize) {
			msize *= 2;
			T **ntab = new T*[msize];
			for(int i = 0; i < mused; i++)
				mtab[i] = tab[i];
			delete [] tab;
			tab = mtab;
		}
		tab[mused++] = new T[ssize];
	}
	tab[mused - 1][sused++] = value;
}

template <class T>
inline T& FragArray<T>::operator[](int index) {
	return ref(index);
}

template <class T>
inline T FragArray<T>::operator[](int index) {
	return get(index);
}

template <class T>
inline FragArray<T>& FragArray<T>::operator+=(T value) {
	add(value);
	return *this;
}

template <class T>
inline FragArray<T>::operator bool(void) const {
	return !isEmpty();
}


// FragArray<T>::Iterator inlines
template <class T>
inline FragArray<T>::Iterator::Iterator(FragArray<T>& array)
: arr(array), i(0) {
}

template <class T>
inline void FragArray<T>::Iterator::next(void) {
	assert(i < arr.count());
	i++;
}

template <class T>
inline const T& FragArray<T>::Iterator::item(void) const {
	return arr.get(i);
}

template <class T>
inline void FragArray<T>::Iterator::set(const T& value) {
	arr.set(i, value);
}

template <class T>	
inline T& FragArray<T>::Iterator::ref(void) {
	return arr.ref(i);
}

template <class T>
inline bool FragArray<T>::Iterator::atEnd(void) const {
	return i >= arr.count();
}

template <class T>		
inline typename FragArray<T>::Iterator& FragArray<T>::Iterator::operator++(void)
{
	next;
	return *this;
}

template <class T>
inline const T& FragArray<T>::Iterator::operator->(void) const {
	return arr.ref(i);
}

template <class T>
inline const T& FragArray<T>::Iterator::operator*(void) const {
	return arr.get(i);
}

template <class T>
inline FragArray<T>::Iterator::operator bool(void) {
	return !atEnd();
}

template <class T>
inline typename FragArray<T>::Iterator&
FragArray<T>::Iterator::operator=(const T& value) {
	arr.set(i, value);
}

} } // elm::genstruct

#endif	// ELM_GENSTRUCT_FRAGARRAY_H
