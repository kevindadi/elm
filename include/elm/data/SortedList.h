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

#include "Adapter.h"
#include "List.h"
#include "Manager.h"
#include "util.h"
#include <elm/util/Option.h>

namespace elm {

// SortedList class
template <class T, class M = CompareManager<T> >
class SortedList {
protected:
	typedef List<T, M> list_t;
public:
	typedef SortedList<T, M> self_t;

	inline SortedList(void): _man(Single<M>::_) { }
	inline SortedList(M& man): _man(man) { }
	SortedList(const SortedList<T, M> &l): list(l.list), _man(l._man) { }

	inline void removeFirst(void) { list.removeFirst(); }
	inline void removeLast(void) { list.removeLast(); }

	// Collection concept
	inline int count (void) const { return list.count(); }

	inline bool contains(const T &item) const { return find(item) != end(); }
	template <class C> bool containsAll(const C& c) const
		{ for(typename C::Iter i(c); i; i++) if(!contains(*i)) return false; return true; }

	inline bool isEmpty(void) const { return list.isEmpty(); }
	inline operator bool(void) const { return !list.isEmpty(); }

	class Iter: public list_t::Iter {
	public:
		inline Iter(void) { }
		inline Iter(const self_t& _list): list_t::Iter(_list.list) { }
	};
	inline Iter items(void) const { return Iter(*this); }
	inline Iter operator*(void) const { return items(); }
	inline operator Iter(void) const { return items(); }
	inline Iter begin(void) const { return items(); }
	inline Iter end(void) const { return Iter(); }

	// MutableCollection concept
	inline void clear(void) { list.clear(); }

	void add(const T &value) {
		for(typename list_t::PrecIter current(list); current; current++)
			if(_man.compare(value,  *current) < 0) {
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
	void remove(const Iter &iter) { list.remove(iter); }

	// List concept
	inline const T& first(void) const { return list.first(); }
	inline const T& last(void) const { return list.last(); }
	inline Iter find(const T& item, const Iter& iter) const {
		Iter i = iter; for(; i; i++) {
			int cmp = _man.compare(item, *i);
			if(cmp > 0) continue; else if(!cmp) return i; else return end();
		}
		return i;
	}
	inline Iter find(const T& item) const
		{ return find(item, begin()); }

protected:
	list_t list;
	M& _man;
};


template <class T, class M = CompareManager<T> >
class ListSet: public SortedList<T, M> {
public:
	inline ListSet(void): SortedList<T, M>() { }
	inline ListSet(M& man): SortedList<T, M>(man) { }
	ListSet(const ListSet &l): SortedList<T, M>(static_cast<SortedList<T,M> >(l)) { }
 
	void add(const T &value) {
		if(SortedList<T, M>::contains(value))
			return;
		SortedList<T, M>::add(value);
	}
	template <template <class _> class CC> inline void addAll (const CC<T> &items)
	{ for(typename CC<T>::Iter item(items); item; item++) add(item); }
	static const ListSet<T, M> null;
};
template <class T, class M> const ListSet<T, M> ListSet<T, M>::null;

#	if 0
template <class K, class T, class M = CompareManager<K> >
class ListMap {
public:
	typedef ListMap<K, T, M> self_t;
private:
	typedef Pair<K, T> pair_t;
	typedef PairAdapter<K, T> adapter_t;
	typedef SortedList<pair_t, M, adapter_t> list_t;

	struct equals {
		const self_t& m;
		const T& v;
		inline equals(const self_t& map, const T& val): m(map), v(val) { }
		inline bool operator()(const T& vp) const { return m.man.isEqual(v, vp); };
	};

public:

	inline ListMap(const M& m = Single<M>::_): man(m) { }
	inline ListMap(const self_t& l, const M& m = Single<M>::_): list(l.list), man(m) { }

	// Collection concept
	class Iter: public PreIterator<Iter, T> {
	public:
		inline Iter(void) { }
		inline Iter(const self_t& l): i(l.list) { }
		inline bool ended(void) const { return i.ended(); }
		inline void next(void) { i++; }
		inline const T& item(void) const { return PairAdapter<K, T>::value(*i); }
	private:
		typename list_t::Iter i;
	};

	inline int count(void) const { return list.count(); }
	inline bool contains(const T& val) const { return elm::exists(*this, equals(*this, val)); }

	// Map concept
	inline void put(const K& key, const T& val) { list.add(pair(key, val)); }

	inline bool contains(const T& val)
		{ for(Iter i(*this); i; i++) if() return true; return false; }

	class KeyIter: public PreIterator<KeyIter, K> {
	public:
		inline KeyIter(const self_t& m): i(m) { }
	private:
		typename base_t::Iter i;
	};

	inline Option<T> get(const K& k)
		{ typename base_t::Iter i = base_t::find(k); if(i) return some(*i); else return none; }
	inline const T& get(const K& k, const T& d)
		{ typename base_t::Iter i = base_t::find(k); if(i) return *i; else return d; }
	inline bool hasKey(const K& k)
		{ typename base_t::Iter i = base_t::find(k); return !i.ended(); }

	inline void put(const K& k, const T& v)
		{ base_t::add(pair(k, v)); }
	inline void remove(const K& k)
		{ typename base_t::Iter i = find(k); if(i) remove(*i); }

private:
	list_t list;
	const M& man;
};
#endif

}	// elm

#endif /* ELM_DATA_SORTEDLIST_H_ */
