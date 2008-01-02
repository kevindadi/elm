/*
 *	$Id$
 *	SLList class interface
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
#ifndef ELM_GENSTRUCT_SLLIST_H
#define ELM_GENSTRUCT_SLLIST_H

#include <elm/assert.h>
#include <elm/Iterator.h>

#include <elm/inhstruct/SLList.h>
namespace elm { namespace genstruct {

// SLList class
template <class T> class SLList {
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
		inline T item(void) const;
		inline void next(void);

		// Deprecated
		//inline void operator=(const Iterator& source);	// !!TODO!!

	private:
		friend class SLList;
		Node *node;
	};
	
	// Mutable collection
	inline void clear(void);
	inline void add(const T& value) { addFirst(value); }
	template <template<class _> class C>
		inline void addAll (const C<T> &items);
	inline void remove(const T& value);
	template <template<class _> class C>
		inline void removeAll (const C<T> &items);
	inline void remove(const Iterator &iter) { remove(iter); }
	
	// Specific
	inline T first(void) const;
	inline T last(void) const;
	inline void addFirst(const T& value);
	inline void addLast(const T& value);
	inline void addAfter(const Iterator& pos, const T& value);
	inline void removeFirst(void);
	inline void removeLast(void);
	inline void removeNext(const Iterator& pos);
};


// SLList::Node inlines
template <class T> SLList<T>::Node::Node(const T value): val(value) {
}
template <class T> inline typename SLList<T>::Node *SLList<T>::Node::next(void) const {
	return (Node *)SLNode::next();
}

// SLList class
template <class T>
inline void SLList<T>::clear(void) {
	while(!list.isEmpty()) {
		Node *node = (Node *)list.first();
		list.removeFirst();
		delete node;
	}	
}

template <class T> inline SLList<T>::~SLList(void) {
	clear();
}

template <class T> template <template<class _> class C>
inline void SLList<T>::addAll(const C<T> &items) {
	for(typename C<T>::Iterator iter; iter; iter++)
		add(iter);
}

template <class T> template <template<class _> class C>
inline void SLList<T>::removeAll (const C<T> &items) {
	for(typename C<T>::Iterator iter; iter; iter++)
		remove(iter);	
}

template <class T> inline T SLList<T>::first(void) const {
	return ((Node *)list.first())->val;
}
template <class T> inline T SLList<T>::last(void) const {
	return ((Node *)list.last())->val;
}
template <class T> inline int SLList<T>::count(void) const {
	return list.count();
}
template <class T> inline void SLList<T>::addFirst(const T &value) {
	list.addFirst(new Node(value));
}
template <class T> inline void SLList<T>::addLast(const T &value) {
	list.addLast(new Node(value));
}
template <class T> inline void SLList<T>::removeFirst(void) {
	Node *node = (Node *)list.first();
	list.removeFirst();
	delete node;
}
template <class T> inline void SLList<T>::removeLast(void) {
	Node *node = (Node *)list.last();
	list.removeLast();
	delete node;
}
template <class T> inline void SLList<T>::remove(const T &value) {
	for(Node *prv = 0, *cur = (Node *)list.first(); cur;
	prv = cur, cur = cur->next())
		if(cur->val == value) {
			if(!prv)
				list.removeFirst();
			else
				prv->removeNext();
		}
}
template <class T> inline bool SLList<T>::isEmpty(void) const {
	return list.isEmpty();
};

template <class T>
inline bool SLList<T>::contains (const T &item) const {
	for(Iterator iter(*this); iter; iter++)
		if(item == iter)
			return true;
	return false;
}


// SLList::Iterator class
template <class T> inline SLList<T>::Iterator::Iterator(const SLList& _list)
: node((Node *)_list.list.first()) {
}

template <class T> inline SLList<T>::Iterator::Iterator(const Iterator& source)
: node(source.node) {
}
template <class T> inline SLList<T>::Iterator::Iterator()
: node(0) {
}
/*template <class T> inline void SLList<T>::Iterator::operator=(const Iterator& source)
{
	node = source.node;
}*/
template <class T> inline bool SLList<T>::Iterator::ended(void) const {
	return !node;
}
template <class T> inline T SLList<T>::Iterator::item(void) const {
	ASSERT(node);
	return node->val;
}
template <class T> inline void SLList<T>::Iterator::next(void) {
	ASSERT(node);
	node = node->next();
}


template <class T> inline void SLList<T>::addAfter(const Iterator& pos, const T& value) {
	ASSERT(pos.node);
	pos.node->insertAfter(new Node(value));
}
template <class T> inline void SLList<T>::removeNext(const Iterator& pos) {
	ASSERT(pos->node);
	pos->node->removeNext();
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_SLLIST_H
