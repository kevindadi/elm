/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/genstruct/Table.h -- Table and AllocatedTable class implementation.
 */
#ifndef ELM_GENSTRUCT_TABLE_H
#define ELM_GENSTRUCT_TABLE_H

#include <elm/assert.h>
#include <elm/deprecated.h>

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

	// Deprecated
	inline const T *table(void) const;
	inline T *table(void);
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
	inline AllocatedTable<T>& operator=(const AllocatedTable<T>& table) {
		*this = (const Table<T>&)table;
		return *this;
	}
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
	ASSERTP(count == 0 || (count > 0 && table), "null pointer for table");
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
	ELM_DEPRECATED
	return tab;
}

template <class T>
inline T *Table<T>::table(void) {
	ELM_DEPRECATED
	return tab;
}

template <class T>
inline const T& Table<T>::get(int index) const {
	ASSERTP(index >= 0 && index < cnt, "index out of bounds");
	return tab[index];
}

template <class T>
inline T& Table<T>::get(int index) {
	ASSERTP(index >= 0 && index < cnt, "index out of bounds");
	return tab[index];
}

template <class T>
inline void Table<T>::set(int index, const T& value) {
	ASSERTP(index >= 0 && index < cnt, "index out of bounds");
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
	//cout << "Table::operator=(" << this << ", " << &table << ")\n";
}

template <class T>
inline Table<T>::operator bool(void) const {
	return !isEmpty();
}


// Allocated table inlines
template <class T>
inline AllocatedTable<T>::AllocatedTable(void) {
	//cout << "new AllocatedTable() = " << this << io::endl;
}

template <class T>
inline AllocatedTable<T>::AllocatedTable(int count)
: Table<T>(new T[count], count) {
	//cout << "new AllocatedTable() = " << this << io::endl;
}

template <class T>
inline AllocatedTable<T>::AllocatedTable(const Table<T>& table)
: Table<T>(new T[table.count()], table.count()) {
	for(int i = 0; i < Table<T>::cnt; i++)
		Table<T>::tab[i] = table[i];
	//cout << "new AllocatedTable() = " << this << io::endl;
}

template <class T>
inline AllocatedTable<T>::~AllocatedTable(void) {
	free();	
	//cout << "deleting AllocatedTable = " << this << io::endl;
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
	//cout << "AllocatedTable::operator=(" << this << ", " << &table << ")\n";
	if(Table<T>::tab)
		delete [] Table<T>::tab;
	Table<T>::cnt = table.count();
	Table<T>::tab = new T[table.count()];
	for(int i = 0; i < table.count(); i++)
		(*this)[i] = table[i];
	return *this;
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_TABLE_H
