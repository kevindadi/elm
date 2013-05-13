/*
 *	$Id$
 *	Table and AllocatedTable class interfaces
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-08, IRIT UPS.
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
#ifndef ELM_GENSTRUCT_TABLE_H
#define ELM_GENSTRUCT_TABLE_H

#include <elm/assert.h>
#include <elm/deprecated.h>
#include <elm/util/IndexedIterator.h>

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
	inline int size(void) const { return cnt; }
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

	// Iterator class
	class Iterator: public IndexedIterator<Iterator, T, Table<T> > {
	public:
		inline Iterator(const Table<T>& table): IndexedIterator<Iterator, T, Table<T> >(table) { }
		inline Iterator(const Iterator &iter): IndexedIterator<Iterator, T, Table<T> >(iter) { }
	};

	// Deprecated
	inline int count(void) const { return cnt; }
	inline const T *table(void) const;
	inline T *table(void);
};


// AllocatedTable class
template <class T>
class AllocatedTable: public Table<T> {
public:
	inline AllocatedTable(void) { }
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
	return *this;
}

template <class T>
inline Table<T>::operator bool(void) const {
	return !isEmpty();
}


template <class T>
inline AllocatedTable<T>::AllocatedTable(int count)
: Table<T>(new T[count], count) {
	//cout << "new AllocatedTable() = " << this << io::endl;
}

template <class T>
inline AllocatedTable<T>::AllocatedTable(const Table<T>& table)
: Table<T>(table ? new T[table.count()] : 0, table.count()) {
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
