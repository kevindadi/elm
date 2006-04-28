/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/genstruct/Table.h -- Table class implementation.
 */
#ifndef ELM_GENSTRUCT_TABLE_H
#define ELM_GENSTRUCT_TABLE_H

#include <assert.h>

namespace elm { namespace genstruct {

// Table class
template <class T>
class Table {
	T *tab;
	int cnt;
public:
	inline Table(T *table, int count);
	
	// Accessors
	inline int count(void) const;
	inline const T *table(void) const;
	inline T *table(void);
	inline T get(int index) const;
	inline T& get(int index);
	inline void set(int index, const T& value);
	
	// Operators
	inline T operator[](int index) const;
	inline T& operator[](int index);
	inline Table<T>& operator=(const Table& table);
};

// Table inlines
template <class T>
inline Table<T>::Table(T *table, int count): tab(table), cnt(count) {
	assert(count == 0 || (count > 0 && table));
}

template <class T>
inline int Table<T>::count(void) const {
	return cnt;
};

template <class T>
inline const T *Table<T>::table(void) const {
	return tab;
}

template <class T>
inline T *Table<T>::table(void) {
	return tab;
}

template <class T>
inline T Table<T>::get(int index) const {
	assert(index < cnt);
	return tab[index];
}

template <class T>
inline T& Table<T>::get(int index) {
	assert(index < cnt);
	return tab[index];
}

template <class T>
inline void Table<T>::set(int index, const T& value) {
	assert(index < cnt);
	tab[index] = value;
}

template <class T>	
inline T Table<T>::operator[](int index) const {
	return get(index);
}

template <class T>
inline T& Table<T>::operator[](int index) {
	return get(index);
}

template <class T>
inline Table<T>& Table<T>::operator=(const Table& table) {
	tab = table.tab;
	cnt = table.cnt;
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_TABLE_H
