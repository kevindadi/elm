/*
 *	BiDiList class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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
#ifndef INCLUDE_ELM_DATA_BIDILIST_H_
#define INCLUDE_ELM_DATA_BIDILIST_H_

#include <elm/assert.h>
#include <elm/inhstruct/DLList.h>
#include <elm/PreIterator.h>
#include <elm/data/Manager.h>
#include "custom.h"

namespace elm {

template <class T, class E = Equiv<T>, class A =  DefaultAlloc>
class BiDiList: public E, public A {

	class Node: public inhstruct::DLNode {
	public:
		T val;
		inline Node(const T& v): val(v) { }
		inline static void *operator new(size_t s, BiDiList<T, E, A> *l) { return l->A::allocate(s); }
		inline void free(BiDiList<T, E, A> *l) { this->~Node(); l->A::free(this); }
	private:
		inline ~Node(void) { }
	};

public:

	inline BiDiList(void) { }
	inline BiDiList(const BiDiList<T>& list) { copy(list); }
	inline ~BiDiList(void) { clear(); }

	class BackIter;
	class Iter: public InplacePreIterator<Iter, T> {
		friend class BiDiList;
	public:
		inline Iter(void): n(_(null._list.first())) { }
		inline Iter(const BiDiList& l): n(_(l._list.first())) { }
		inline Iter(const BackIter& i) { if(i) n = i; else n = i.n->next(); }
		inline Iter(const BiDiList& l, bool end): n(static_cast<const Node *>(end ? l._list.tail() : l._list.first())) { }
		inline bool ended(void) const { return n->atEnd(); }
		inline const T& item(void) const { return n->val; }
		inline void next(void) { n = _(n->next()); }
		inline bool equals(const Iter& i) const { return i.n == n; }
	private:
		const Node *n;
	};

	class BackIter: public InplacePreIterator<BackIter, T> {
		friend class BiDiList;
	public:
		inline BackIter(const BiDiList& l): n(_(l._list.last())) { }
		inline BackIter(const Iter& i) { if(i) n = i.n; else n = _(i.n->previous()); }
		inline bool ended(void) const { return n->atBegin()(); }
		inline const T& item(void) const { return n->val; }
		inline void next(void) { n = _(n->previous()); }
	private:
		Node *n;
	};
	inline Iter reversedItems(void) const { return BackIter(*this); }

	// Collection concept
	static const BiDiList<T, E, A> null;
	inline int count(void) const { return _list.count(); }
	inline bool contains (const T &item) const
		{ for(Iter iter(*this); iter(); iter++) if(E::isEqual(item, *iter)) return true; return false; }
	inline bool isEmpty(void) const { return _list.isEmpty(); };
	inline operator bool(void) const { return !isEmpty(); }
	bool equals(const BiDiList<T>& l) const
		{ Iter i1(*this), i2(l); while(i1() && i2()) { if(!E::isEqual(*i1, *i2)) return false; i1++; i2++; } return !i1 && !i2; }
	bool includes(const BiDiList<T>& l) const
		{ Iter i1(*this), i2(l); while(i1() && i2()) { if(E::isEqual(*i1, *i2)) i2++; i1++; } ; return !i2; }
	inline Iter begin(void) const { return Iter(*this); }
	inline Iter end(void) const { return Iter(*this, true); }
	inline Iter operator*(void) const { return begin(); }
	inline operator Iter(void) const { return begin(); }

	// MutableCollection concept
	void copy(const BiDiList<T>& l) { clear(); for(Iter i(l); i(); i++) addLast(*i); }
	inline void clear(void)
		{ while(!_list.isEmpty()) { Node *node = _(_list.first()); _list.removeFirst(); node->free(this); } }
	inline void add(const T& value) { addFirst(value); }
	template <class C> inline void addAll(const C& items)
		{ for(typename C::Iter iter(items); iter; iter++) add(iter); }
	template <class C> inline void removeAll(const C& items)
		{ for(typename C::Iter iter(items); iter; iter++) remove(iter);	}
	inline void remove(const T& v) { Iter i = find(v); if(i()) remove(i); }
	inline void remove(Iter &i) { ASSERT(i); const Node *n = _(i.n->next()); ((Node *)i.n)->remove(); i.n = n; }

	// List concept
	inline T& first(void) { return _(_list.first())->val; }
	inline const T& first(void) const { return _(_list.first())->val; }
	inline T& last(void) { return _(_list.first())->val; }
	inline const T& last(void) const { return _(_list.first())->val; }
	inline Iter nth(int n) { Iter i(*this); while(n) { ASSERT(i); i++; n--; } ASSERT(i); return i; };
	Iter find(const T& item) const
		{ Iter i; for(i = begin(); i(); i++) if(E::isEqual(item, *i)) break; return i; }
	Iter find(const T& item, const Iter& pos) const
		{ Iter i = pos; for(i++; i; i++) if(E::isEqual(item, i)) break; return i; }

	// MutableList concept
	inline void addFirst(const T& v) { _list.addFirst(new(this) Node(v)); }
	inline void addLast(const T& v) { _list.addLast(new(this) Node(v)); }
	inline void addAfter(const Iter& i, const T& value) { ASSERT(i); i.n->insertAfter(new(this) Node(value)); }
	inline void addBefore(const Iter& i, const T& v) { ASSERT(i); i.n->addBefore(new(this) Node(v)); }
	inline void removeFirst(void) { Node *node = _(_list.first()); _list.removeFirst(); node->free(this); }
	inline void removeLast(void) { Node *node = _(_list.last()); _list.removeLast(); delete node; }
	inline void set(const Iter &i, const T &v) { ASSERT(i); i.n->val = v; }

	// Stack concept
	inline const T& top(void) const { return first(); }
	inline T pop(void) { T r = first(); removeFirst(); return r; }
	inline void push(const T& i) { addFirst(i); }
	inline void reset(void) { clear(); }

	// Queue concept
	inline const T &head(void) const { return first(); }
	const T& get(void) { ASSERT(!isEmpty()); T r = first(); removeFirst(); return r; }
	void put(const T &v) { addLast(v); }

	// operators
	inline BiDiList& operator=(const BiDiList& list) { copy(list); return *this; }
	inline bool operator&(const T& e) const { return contains(e); }
	inline T& operator[](int k) { return nth(k); }
	inline const T& operator[](int k) const { return *nth(k); }
	inline bool operator==(const BiDiList<T>& l) const { return equals(l); }
	inline bool operator!=(const BiDiList<T>& l) const { return !equals(l); }
	inline bool operator>=(const BiDiList<T>& l) const { return includes(l); }
	inline bool operator>(const BiDiList<T>& l) const { return includes(l) && !equals(l); }
	inline bool operator<=(const BiDiList<T>& l) const { return l.includes(*this); }
	inline bool operator<(const BiDiList<T>& l) const { return l.includes(*this) && !equals(l); }
	inline BiDiList<T>& operator+=(const T& h) { add(h); return *this; }
	inline BiDiList<T>& operator+=(const BiDiList<T>& l) { addAll(l); return *this; }
	inline BiDiList<T>& operator-=(const T& h) { remove(h); return *this; }
	inline BiDiList<T>& operator-=(const BiDiList<T>& l) { removeAll(l); return *this; }

private:
	inhstruct::DLList _list;
	static inline Node *_(inhstruct::DLNode *n) { return static_cast<Node *>(n); }
};

template <class T, class E, class A> const BiDiList<T, E, A> BiDiList<T, E, A>::null;

}	// elm

#endif /* INCLUDE_ELM_DATA_BIDILIST_H_ */
