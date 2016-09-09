/*
 *	SortedList class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2012, IRIT UPS.
 *
 *	ELM is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	ELM is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with ELM; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef ELM_DATA_SORTEDLIST_H_
#define ELM_DATA_SORTEDLIST_H_

#include <elm/genstruct/SLList.h>
#include <elm/compare.h>
#include <elm/adapter.h>

namespace elm {

// SortedList class
template <class T, class C = Comparator<T>, class A = IdAdapter<T> >
class SortedList {
	typedef genstruct::SLList<T, CompareEquiv<T, C> > list_t;
public:
	typedef typename A::key_t key_t;
	typedef typename A::val_t val_t;

	inline SortedList(void) { }
	inline SortedList(const C& c): _c(c) { }
	SortedList(const SortedList & source): list(source.list) { }

	inline void removeFirst(void) { list.removeFirst(); }
	inline void removeLast(void) { list.removeLast(); }

	// Collection concept
	inline int count (void) const { return list.count(); }

	bool contains(const key_t &item) const {
		for (Iterator current(*this); current; current++) {
			int cmp = _c.doCompare(item,  A::key(*current));
			if(cmp > 0) continue; else if(!cmp) return true; else break;
		}
		return false;
	}

	inline bool isEmpty(void) const { return list.isEmpty(); }
	inline operator bool(void) const { return !list.isEmpty(); }

	class Iterator: public list_t::Iterator {
	public:
		inline Iterator(void) { }
		inline Iterator(const SortedList& _list): list_t::Iterator(_list.list) { }
	private:
		friend class SortedList;
		inline Iterator(const typename list_t::Iterator& iter)
			: list_t::Iterator(iter) { }
	};

	// MutableCollection concept
	inline void clear(void) { list.clear(); }

	void add (const T &value) {
		for(Iterator current(*this); current; current++)
			if(_c.doCompare(A::key(value),  A::key(*current)) < 0) {
				list.addBefore(current, value);
				return;
			}
		list.addLast(value);
	}

	template <template <class _> class CC> inline void addAll (const CC<T> &items)
		{ for(typename CC<T>::Iterator item(items); item; item++) add(item); }
	inline void remove(const T &item) { list.remove(item); }
	template <template <class _> class CC> inline void removeAll(const CC<T> &items)
		{ list.removeAll(items); }
	void remove(const Iterator &iter) { list.remove(iter); }

	// List concept
	inline const T& first(void) const { return list.first(); }
	inline const T& last(void) const { return list.last(); }
	inline Iterator find(const T& item) const
		{ return Iterator(list.find(item)); }
	inline Iterator find(const T& item, const Iterator& iter) const
		{ return list.find(item, iter); }

private:
	list_t list;
	C _c;
};

}	// elm

#endif /* ELM_DATA_SORTEDLIST_H_ */
