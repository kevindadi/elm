/*
 *	$Id$
 *	SLList class interface
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
#ifndef ELM_GENSTRUCT_SLLIST_H
#define ELM_GENSTRUCT_SLLIST_H

#include <elm/assert.h>
#include <elm/Iterator.h>
#include <elm/util/Equiv.h>
#include <elm/inhstruct/SLList.h>

namespace elm { namespace genstruct {

// SLList class
template <class T, class E = Equiv<T> >
class SLList {
	inhstruct::SLList list;
	
	// Node class
	class Node: public inhstruct::SLNode {
	public:
		T val;
		inline Node(const T value);
		inline Node *next(void) const;
	};

public:
	inline ~SLList(void);
	
	// Collection concept
	inline int count(void) const;
	inline bool contains (const T &item) const;
	inline bool isEmpty(void) const;
	inline operator bool(void) const { return !isEmpty(); }

	// Iterator class
	class Iterator: public PreIterator<Iterator, T> {
	public:
		inline Iterator(void);
		inline Iterator(const SLList& _list);
		inline Iterator(const Iterator& source);
		
		inline bool ended(void) const;
		inline const T& item(void) const;
		inline void next(void);

	private:
		friend class SLList;
		Node *node, *prev;
	};
	
	// MutableCollection concept
	inline void clear(void);
	inline void add(const T& value) { addFirst(value); }
	template <template<class _> class C>
		inline void addAll (const C<T> &items);
	inline void remove(const T& value);
	template <template<class _> class C>
		inline void removeAll (const C<T> &items);
	inline void remove(const Iterator &iter);
	
	// List concept
	inline const T& first(void) const;
	inline const T& last(void) const;
	inline Iterator find(const T& item) const {
		Iterator iter(*this);
		for(; iter; iter++) if(E::equals(item, iter)) break;
		return iter;
	}
	inline Iterator find(const T& item, const Iterator& iter) const {
		for(iter++; iter; iter++) if(E::equals(item, iter)) break;
		return iter;
	}
	
	// MutableList concept
	inline void addFirst(const T& value);
	inline void addLast(const T& value);
	inline void addAfter(const Iterator& pos, const T& value);
	inline void addBefore(const Iterator& pos, const T& value);
	inline void removeFirst(void);
	inline void removeLast(void);
	inline void set(const Iterator &pos, const T &item);
};


// SLList::Node inlines
template <class T, class E>
SLList<T, E>::Node::Node(const T value): val(value) {
}
template <class T, class E>
inline typename SLList<T, E>::Node *SLList<T>::Node::next(void) const {
	return (Node *)SLNode::next();
}

// SLList class
template <class T, class E>
inline void SLList<T, E>::clear(void) {
	while(!list.isEmpty()) {
		Node *node = (Node *)list.first();
		list.removeFirst();
		delete node;
	}	
}

template <class T, class E>
inline SLList<T, E>::~SLList(void) {
	clear();
}

template <class T, class E> template <template<class _> class C>
inline void SLList<T, E>::addAll(const C<T> &items) {
	for(typename C<T>::Iterator iter; iter; iter++)
		add(iter);
}

template <class T, class E> template <template<class _> class C>
inline void SLList<T, E>::removeAll (const C<T> &items) {
	for(typename C<T>::Iterator iter; iter; iter++)
		remove(iter);	
}

template <class T, class E>
inline const T& SLList<T, E>::first(void) const {
	return ((Node *)list.first())->val;
}

template <class T, class E>
inline const T& SLList<T, E>::last(void) const {
	return ((Node *)list.last())->val;
}

template <class T, class E>
inline int SLList<T, E>::count(void) const {
	return list.count();
}

template <class T, class E>
inline void SLList<T, E>::addFirst(const T &value) {
	list.addFirst(new Node(value));
}

template <class T, class E>
inline void SLList<T, E>::addLast(const T &value) {
	list.addLast(new Node(value));
}

template <class T, class E>
inline void SLList<T, E>::removeFirst(void) {
	Node *node = (Node *)list.first();
	list.removeFirst();
	delete node;
}

template <class T, class E>
inline void SLList<T, E>::removeLast(void) {
	Node *node = (Node *)list.last();
	list.removeLast();
	delete node;
}

template <class T, class E>
inline void SLList<T, E>::remove(const T &value) {
	for(Node *prv = 0, *cur = (Node *)list.first(); cur;
	prv = cur, cur = cur->next())
		if(E::equals(cur->val, value)) {
			if(!prv)
				list.removeFirst();
			else
				prv->removeNext();
		}
}

template <class T, class E>
inline bool SLList<T, E>::isEmpty(void) const {
	return list.isEmpty();
};

template <class T, class E>
inline bool SLList<T, E>::contains (const T &item) const {
	for(Iterator iter(*this); iter; iter++)
		if(E::equals(item, iter))
			return true;
	return false;
}

template <class T, class E>
inline void SLList<T, E>::addAfter(const Iterator& pos, const T& value) {
	ASSERT(pos.node);
	pos.node->insertAfter(new Node(value));
}

template <class T, class E>
inline void SLList<T, E>::addBefore(const Iterator& pos, const T& value) {
	if(!pos.prev)
		addFirst(value);
	else
		pos.prev->insertAfter(new Node(value));
}

template <class T, class E>
inline void SLList<T, E>::set(const Iterator &pos, const T &item) {
	ASSERT(pos.node);
	pos.node->val = item;
}


template <class T, class E>
inline void SLList<T, E>::remove(const Iterator &iter) {
	ASSERT(iter.node);
	if(!iter.prev)
		removeFirst();
	else
		iter.prev->removeNext();
}


// SLList::Iterator class
template <class T, class E>
inline SLList<T, E>::Iterator::Iterator(const SLList& _list)
: node((Node *)_list.list.first()), prev(0) {
}

template <class T, class E>
inline SLList<T, E>::Iterator::Iterator(const Iterator& source)
: node(source.node), prev(source.prev) {
}

template <class T, class E>
inline SLList<T, E>::Iterator::Iterator()
: node(0), prev(0) {
}

template <class T, class E>
inline bool SLList<T, E>::Iterator::ended(void) const {
	return !node;
}

template <class T, class E>
inline const T& SLList<T, E>::Iterator::item(void) const {
	ASSERT(node);
	return node->val;
}

template <class T, class E>
inline void SLList<T, E>::Iterator::next(void) {
	ASSERT(node);
	prev = node;
	node = node->next();
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_SLLIST_H
