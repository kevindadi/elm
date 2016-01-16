/*
 *	List class interface
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
#ifndef ELM_DATA_LIST_H
#define ELM_DATA_LIST_H

#include <elm/assert.h>
#include <elm/PreIterator.h>
#include <elm/util/Equiv.h>
#include <elm/inhstruct/SLList.h>

namespace elm {

// SLList class
template <class T, class E = Equiv<T> >
class List {

	// Node class
	class Node: public inhstruct::SLNode {
	public:
		T val;
		inline Node(const T value): val(value) { }
		inline Node *next(void) const { return nextNode(); }
		inline Node *nextNode(void) const { return static_cast<Node *>(SLNode::next()); }
		inline void removeNext(void) { Node *n = nextNode(); SLNode::removeNext(); delete n; }
	};

public:
	inline List(void) { }
	inline List(const List& list) { copy(list); }
	inline ~List(void) { clear(); }

	void copy(const List<T>& list) {
		clear(); iter item(list); if(!item) return; addFirst(*item); Node *cur = firstNode();
		for(item++; item; item++) { cur->insertAfter(new Node(*item)); cur = cur->next(); }
	}

	// iter class
	class iter: public PreIterator<iter, const T&> {
	public:
		inline iter(void): node(0) { }
		inline iter(const List& _list): node(_list.firstNode()) { }
		inline bool operator==(const iter& i) { return node == i.node; }
		inline bool operator!=(const iter& i) { return node != i.node; }

		inline bool ended(void) const { return !node; }
		inline const T& item(void) const { ASSERT(node); return node->val; }
		inline void next(void) { ASSERT(node); node = node->next(); }

	private:
		friend class List;
		friend class prec_iter;
		Node *node;
	};
	inline iter begin(void) const { return iter(*this); }
	inline iter end(void) const { return iter(); }

	// prec_iter class
	class prec_iter: public PreIterator<prec_iter, const T&> {
	public:
		inline prec_iter(void): node(0), prev(0) { }
		inline prec_iter(const List& _list): node(_list.firstNode()), prev(0) { }
		inline operator iter(void) const { iter i; i.node = node; return i; }
		inline bool operator==(const prec_iter& i) { return node == i.node; }
		inline bool operator!=(const prec_iter& i) { return node != i.node; }

		inline bool ended(void) const { return !node; }
		inline const T& item(void) const { ASSERT(node); return node->val; }
		inline void next(void) { ASSERT(node); prev = node; node = node->next(); }

		void remove(void) { node = node->next(); prev->removeNext(); }

	private:
		friend class List;
		Node *node, *prev;
	};

	// mutable_iter class
	class mutable_iter: public PreIterator<mutable_iter, T&> {
	public:
		inline mutable_iter(void): node(0) { }
		inline mutable_iter(List& _list): node(_list.firstNode()) { }
		inline bool operator==(const mutable_iter& i) { return node == i.node; }
		inline bool operator!=(const mutable_iter& i) { return node != i.node; }

		inline bool ended(void) const { return !node; }
		inline T& item(void) const { ASSERT(node); return node->val; }
		inline void next(void) { ASSERT(node); node = node->next(); }
	private:
		friend class List;
		Node *node;
	};
	inline mutable_iter mutable_begin(void) { return mutable_iter(*this); }
	inline mutable_iter mutable_end(void) { mutable_iter i(*this); while(i) i++; return i;}

	// sub_iter class
	class sub_iter: public PreIterator<sub_iter, T> {
	public:
		inline sub_iter(void) { }
		inline sub_iter(iter begin, iter end): c(begin), e(end) { }

		inline bool ended(void) const { return c == e; }
		inline const T& item(void) const { return *c; }
		inline void next(void) { c++; }
	private:
		iter c, e;
	};

	// Collection concept
	static List<T, E> null;
	inline int count(void) const { return _list.count(); }
	inline bool contains (const T &item) const
		{ for(iter iter(*this); iter; iter++) if(E::equals(item, iter)) return true; return false; }
	inline bool isEmpty(void) const { return _list.isEmpty(); };
	inline operator bool(void) const { return !isEmpty(); }
	bool equals(const List<T>& l) const
		{ iter i1(*this), i2(l); while(i1 && i2) { if(!E::equals(*i1, *i2)) return false; i1++; i2++; } return !i1 && !i2; }
	bool includes(const List<T>& l) const
		{ iter i1(*this), i2(l); while(i1 && i2) { if(E::equals(*i1, *i2)) i2++; i1++; } ; return !i2; }

	// MutableCollection concept
	inline void clear(void)
		{ while(!_list.isEmpty()) { Node *node = firstNode(); _list.removeFirst(); delete node; } }
	inline void add(const T& value) { addFirst(value); }
	template <class C> inline void addAll(const C& items)
		{ for(typename C::iter iter(items); iter; iter++) add(iter); }
	template <class C> inline void removeAll(const C& items)
		{ for(typename C::iter iter(items); iter; iter++) remove(iter);	}

	void remove(const T& value) {
		if(first() && E::equals(first(), value)) removeFirst(); else
		for(Node *prev = firstNode(), *cur = prev->nextNode(); cur; prev = cur, cur = cur->nextNode())
		if(E::equals(cur->val, value)) { prev->removeNext(); return; }
	}

	inline void remove(prec_iter &iter) { remove(iter.prev, iter.node); }

	// List concept
	inline T& first(void) { return firstNode()->val; }
	inline const T& first(void) const { return firstNode()->val; }
	inline T& last(void) { return lastNode()->val; }
	inline const T& last(void) const { return lastNode()->val; }
	inline T& nth(int n) { mutable_iter i(*this); while(n) { ASSERT(i); i++; n--; } ASSERT(i); return *i; };
	inline const T& nth(int n) const { iter i(*this); while(n) { ASSERT(i); i++; n--; } ASSERT(i); return *i; };
	prec_iter find(const T& item) const
		{ prec_iter iter(*this); for(; iter; iter++) if(E::equals(item, iter)) break; return iter;  }
	prec_iter find(const T& item, const prec_iter& pos) const
		{ prec_iter iter(pos); for(iter++; iter; iter++) if(E::equals(item, iter)) break; return iter; }
	iter find(const T& item, const iter& pos) const
		{ iter iter(pos); for(iter++; iter; iter++) if(E::equals(item, iter)) break; return iter; }

	// MutableList concept
	inline void addFirst(const T& value) { _list.addFirst(new Node(value)); }
	inline void addLast(const T& value) { _list.addLast(new Node(value)); }
	inline void addAfter(const iter& pos, const T& value)
		{ ASSERT(pos.node); pos.node->insertAfter(new Node(value)); }
	inline void addBefore(const prec_iter& pos, const T& value)
		{ if(!pos.prev) addFirst(value); else pos.prev->insertAfter(new Node(value)); }
	inline void removeFirst(void) { Node *node = firstNode(); _list.removeFirst(); delete node; }
	inline void removeLast(void) { Node *node = lastNode(); _list.removeLast(); delete node; }
	inline void set(const iter &pos, const T &item) { ASSERT(pos.node); pos.node->val = item; }

	// Stack concept
	inline const T& top(void) const { return first(); }
	inline T pop(void) { T r = first(); removeFirst(); return r; }
	inline void push(const T& i) { addFirst(i); }
	inline void reset(void) { clear(); }

	// operators
	inline List& operator=(const List& list) { copy(list); return *this; }
	inline bool operator&(const T& e) const { return contains(e); }
	inline T& operator[](int k) { return nth(k); }
	inline const T& operator[](int k) const { return nth(k); }
	inline bool operator==(const List<T>& l) const { return equals(l); }
	inline bool operator!=(const List<T>& l) const { return !equals(l); }
	inline bool operator>=(const List<T>& l) const { return includes(l); }
	inline bool operator>(const List<T>& l) const { return includes(l) && !equals(l); }
	inline bool operator<=(const List<T>& l) const { return l.includes(*this); }
	inline bool operator<(const List<T>& l) const { return l.includes(*this) && !equals(l); }
	inline List<T>& operator+=(const T& h) { add(h); return *this; }
	inline List<T>& operator+=(const List<T>& l) { addAll(l); return *this; }
	inline List<T>& operator-=(const T& h) { remove(h); return *this; }
	inline List<T>& operator-=(const List<T>& l) { removeAll(l); return *this; }

private:
	inhstruct::SLList _list;

	inline Node *firstNode(void) const { return static_cast<Node *>(_list.first()); }
	inline Node *lastNode(void) const { return static_cast<Node *>(_list.last()); }
	void remove(Node* prev, Node*& cur) {
		ASSERT(cur);
		if(!prev) { removeFirst(); cur = firstNode(); }
		else { prev->removeNext(); cur = prev->next(); }
	}
};

template <class T, class E> List<T, E> List<T, E>::null;

} // elm::genstruct

#endif // ELM_DATA_SLLIST_H
