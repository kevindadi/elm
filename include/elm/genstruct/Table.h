/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/genstruct/Table.h -- Table and AllocatedTable class implementation.
 */
#ifndef ELM_GENSTRUCT_TABLE_H
#define ELM_GENSTRUCT_TABLE_H

#include <assert.h>

namespace elm { namespace genstruct {

// Table class
template <class T>
class Table {
protected:
	T *tab;
	int cnt;
public:
	static Table<T> EMPTY;

	inline Table(void);
	inline Table(T *table, int count);
	inline Table(const Table<T>& table);
	
	// Accessors
	inline int count(void) const;
	inline const T *table(void) const;
	inline T *table(void);
	inline const T& get(int index) const;
	inline T& get(int index);
	inline void set(int index, const T& value);
	inline bool isEmpty(void) const;
	
	// Mutators
	inline void copy(const Table<T>& table);
	
	// Operators
	inline const T& operator[](int index) const;
	inline T& operator[](int index);
	inline Table<T>& operator=(const Table& table);
	inline operator bool(void) const;
};


// AllocatedTable class
template <class T>
class AllocatedTable: public Table<T> {
public:
	inline AllocatedTable(void);
	inline AllocatedTable(int count);
	inline AllocatedTable(const Table<T>& table);
	inline ~AllocatedTable(void);
	inline void allocate(int count);
	inline void free(void);
	inline AllocatedTable<T>& operator=(const Table<T>& table);
};


// Table inlines
template <class T>
Table<T> Table<T>::EMPTY;

template <class T>
inline Table<T>::Table(void): tab(0), cnt(0) {
}

template <class T>
inline Table<T>::Table(T *table, int count): tab(table), cnt(count) {
	assert(count == 0 || (count > 0 && table));
}


template <class T>
inline Table<T>::Table(const Table<T>& table): tab(table.tab), cnt(table.cnt) {
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
inline const T& Table<T>::get(int index) const {
	assert(index >= 0 && index < cnt);
	return tab[index];
}

template <class T>
inline T& Table<T>::get(int index) {
	assert(index >= 0 && index < cnt);
	return tab[index];
}

template <class T>
inline void Table<T>::set(int index, const T& value) {
	assert(index >= 0 && index < cnt);
	tab[index] = value;
}

template <class T>
inline bool Table<T>::isEmpty(void) const {
	return cnt == 0;
}

template <class T>	
inline const T& Table<T>::operator[](int index) const {
	return get(index);
}

template <class T>
inline T& Table<T>::operator[](int index) {
	return get(index);
}

template <class T>
inline void Table<T>::copy(const Table<T>& table) {
	tab = table.tab;
	cnt = table.cnt;
}

template <class T>
inline Table<T>& Table<T>::operator=(const Table& table) {
	copy(table);
}

template <class T>
inline Table<T>::operator bool(void) const {
	return !isEmpty();
}


// Allocated table inlines
template <class T>
inline AllocatedTable<T>::AllocatedTable(void) {
}

template <class T>
inline AllocatedTable<T>::AllocatedTable(int count)
: Table<T>(new T[count], count) {
}

template <class T>
inline AllocatedTable<T>::AllocatedTable(const Table<T>& table)
: Table<T>(new T[table.count()], table.count()) {
	for(int i = 0; i < Table<T>::cnt; i++)
		Table<T>::tab[i] = table[i];
}

template <class T>
inline AllocatedTable<T>::~AllocatedTable(void) {
	free();	
}

template <class T>
inline void AllocatedTable<T>::allocate(int count) {
	free();
	Table<T>::cnt = count;
	Table<T>::tab = new T[count];
}

template <class T>
inline void AllocatedTable<T>::free(void) {
	if(Table<T>::tab)
		delete [] Table<T>::tab;
	Table<T>::tab = 0;
	Table<T>::cnt = 0;
}

template <class T>
inline AllocatedTable<T>& AllocatedTable<T>::operator=(const Table<T>& table) {
	copy(table);
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_TABLE_H
