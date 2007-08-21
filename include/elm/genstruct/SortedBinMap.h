/*
 *	$Id$
 *	SortedBinMap class interface
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
#ifndef ELM_GENSTRUCT_SORTEDBINMAP_H
#define ELM_GENSTRUCT_SORTEDBINMAP_H

#include <elm/utility.h>
#include <elm/util/Pair.h>
#include <elm/genstruct/SortedBinTree.h>

namespace elm { namespace genstruct {

// SortedBinMap class
template <class K, class T, class C = Comparator<K> >
class SortedBinMap {
public:
	inline SortedBinMap(void) { }
	inline SortedBinMap(const SortedBinMap& map): tree(map.tree) { }
	
	// Accessors
	inline int count(void) const { return tree.count(); }
	inline bool contains(const K &item) const { return tree.contains(item); }
	inline bool isEmpty(void) const { return tree.isEmpty(); }
 	inline operator bool(void) const { return !isEmpty(); }
	
	// Map
	inline Option<const T> get(const K &key) const {
		Option<const T&> res = tree.get(key);
		if(res)
			return res.snd;
		else
			return none;
	}
	
	inline T get(const K &key, const T &def) const {
		Option<const value_t> res = tree.get(key);
		if(res)
			return (*res).snd;
		else
			return def;
	}

	inline void put(const K& key, const T& value) { tree.add(value_t(key, value)); }
	inline void remove(const K& key) { tree.remove(key); }

private:
	typedef Pair<K, T> value_t; 
	typedef struct {
		typedef K t;
		static const K& key(const value_t& v) { return v.fst; }
		static int compare(const K& v1, const K& v2)
			{ return C::compare(v1, v2); }
	} Key;
	genstruct::SortedBinTree<value_t, Key> tree;

public:

	class Iterator: public PreIterator<Iterator, T> {
	public:
		inline Iterator(const SortedBinMap& map): iter(map.tree) { }
		inline Iterator(const Iterator& _): iter(_) { }
		inline bool ended(void) const { return iter.ended(); }
		inline void next(void) { iter.next(); }
		const T &item(void) const { return iter.snd; }
	private:
		typename SortedBinTree<value_t>::Iterator iter;
	};

	class KeyIterator: public PreIterator<KeyIterator, K> {
	public:
		inline KeyIterator(const SortedBinMap& map): iter(map.tree) { }
		inline KeyIterator(const KeyIterator& _): iter(_) { }
		inline bool ended(void) const { return iter.ended(); }
		inline void next(void) { iter.next(); }
		const T &item(void) const { return iter.fst; }
	private:
		typename SortedBinTree<value_t>::Iterator iter;
	};

	class ValueIterator: public SortedBinTree<value_t>::Iterator {
	public:
		inline ValueIterator(const SortedBinMap& map):
			SortedBinTree<value_t>::Iterator(map.tree) { }
		inline ValueIterator(const ValueIterator& iter):
			SortedBinTree<value_t>::Iterator(iter) { }
	};

	// Mutators
	inline void remove(const ValueIterator& iter) { tree.remove(iter.iter); }
};

} } // elm::genstruct

#endif // ELM_GENSTRUCT_SORTEDBINMAP_H
