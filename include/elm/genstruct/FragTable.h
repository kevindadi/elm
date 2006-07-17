/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/genstruct/FragTable.h -- interface for FragTable class.
 */
#ifndef ELM_GENSTRUCT_FRAGTABLE_H
#define ELM_GENSTRUCT_FRAGTABLE_H

#include <assert.h>
#include <elm/genstruct/Vector.h>

namespace elm { namespace genstruct {

// FragTable class
template <class T> class FragTable {
	genstruct::Vector<T *> tab;
	int cused, csize, msk, shf;
public:
	inline FragTable(int chunk_size = 256);
	inline ~FragTable(void);
	
	// Methods
	inline bool isEmpty(void) const;
	inline int length(void) const;
	inline const T& get(int index) const;
	inline T& get(int index);
	inline void set(int index, const T& value) const;
	inline void add(T value);
	inline void clean(void);
	
	// Operators
	inline const T& operator[](int index) const;
	inline T& operator[](int index);
	inline FragTable<T>& operator+=(T value);
	inline operator bool(void) const;
	
	// Iterator
	class Iterator: public PreIterator<Iterator, T> {
	protected:
		const FragTable<T>& arr;
		int i, len;
	public:
		inline Iterator(const FragTable<T>& array);
		inline void next(void);
		inline const T& item(void) const;
		inline bool ended(void) const;
	};
	
	// MutableIterator class
	class MutableIterator: public Iterator {
		FragTable<T>& mtab;
	public:
		inline MutableIterator(FragTable<T>& table);
		inline void set(const T& value);
		inline T& item(void);
		inline MutableIterator& operator=(const T& value);
	};
};


// FragTable<T> Inlines
template <class T>
inline FragTable<T>::FragTable(int chunk_size): cused(0),
csize(1 << chunk_size), msk(csize - 1), shf(chunk_size) {
	assert(chunk_size > 0);
	tab.add(new T[csize]);
}

template <class T>
inline FragTable<T>::~FragTable(void) {
	for(int i = 0; i < tab.length(); i++)
		delete [] tab[i];
}

template <class T>
inline void FragTable<T>::clean(void) {
	for(int i = 1; i < tab.length(); i++)
		delete [] tab[i];
	tab.setLength(1);
	cused = 0;
}

template <class T>	
inline bool FragTable<T>::isEmpty(void) const {
	return tab.length() == 1 && cused == 0;
}

template <class T>
inline int FragTable<T>::length(void) const {
	return ((tab.length() - 1) << shf) + cused;
}

template <class T>
inline const T& FragTable<T>::get(int index) const {
	assert(index >= 0 && index < length());
	return tab[index >> shf][index & msk];
}

template <class T>
inline T& FragTable<T>::get(int index) {
	assert(index >= 0 && index < length());
	return tab[index >> shf][index & msk];
}

template <class T>
inline void FragTable<T>::set(int index, const T& value) const {
	assert(index >= 0 && index < length());
	tab[index >> shf][index & msk] = value;
}

template <class T>	
inline void FragTable<T>::add(T value) {
	if(cused >= csize) {
		tab.add(new T[csize]);
		cused = 0;
	}
	tab[tab.length() - 1][cused++] = value;
}

template <class T>
inline const T& FragTable<T>::operator[](int index) const {
	return get(index);
}

template <class T>
inline T& FragTable<T>::operator[](int index) {
	return get(index);
}

template <class T>
inline FragTable<T>& FragTable<T>::operator+=(T value) {
	add(value);
	return *this;
}

template <class T>
inline FragTable<T>::operator bool(void) const {
	return !isEmpty();
}


// FragTable<T>::Iterator inlines
template <class T>
inline FragTable<T>::Iterator::Iterator(const FragTable<T>& array)
: arr(array), i(0), len(array.length()) {
}

template <class T>
inline void FragTable<T>::Iterator::next(void) {
	assert(i < arr.length());
	i++;
}

template <class T>
inline const T& FragTable<T>::Iterator::item(void) const {
	return arr.get(i);
}

template <class T>
inline bool FragTable<T>::Iterator::ended(void) const {
	return i >= len;
}


// FragTable<T>::MutableIterator inlines
template <class T>
inline FragTable<T>::MutableIterator::MutableIterator(FragTable<T>& table)
: Iterator(table), mtab(table) {
}


template <class T>
inline T& FragTable<T>::MutableIterator::item(void) {
	return mtab.get(Iterator::i);
}

template <class T>
inline void FragTable<T>::MutableIterator::set(const T& value) {
	mtab.set(Iterator::i, value);
}

template <class T>
inline typename FragTable<T>::MutableIterator&
FragTable<T>::MutableIterator::operator=(const T& value) {
	mtab.set(Iterator::i, value);
}

} } // elm::genstruct

#endif	// ELM_GENSTRUCT_FRAGTABLE_H
