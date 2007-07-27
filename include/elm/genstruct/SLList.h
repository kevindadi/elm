/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * sllist.h -- single link list interface.
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

	// Iterator class
	class Iterator: public PreIterator<Iterator, T> {
		friend class SLList;
		Node *node;
	public:

		inline Iterator();
		inline Iterator(const SLList& _list);
		inline Iterator(const Iterator& source);
		
		inline void operator=(const Iterator& source);
		inline bool ended(void) const;
		inline T item(void) const;
		inline void next(void);
	};

	// Accessors
	inline T first(void) const;
	inline T last(void) const;
	inline int count(void) const;
	inline bool isEmpty(void) const;

	// Mutators
	inline void addFirst(const T& value);
	inline void addLast(const T& value);
	inline void addAfter(const Iterator& pos, const T& value);
	inline void removeFirst(void);
	inline void removeLast(void);
	inline void removeNext(const Iterator& pos);
	inline void remove(const T& value);
};


// SLList::Node inlines
template <class T> SLList<T>::Node::Node(const T value): val(value) {
}
template <class T> inline typename SLList<T>::Node *SLList<T>::Node::next(void) const {
	return (Node *)SLNode::next();
}

// SLList class

template <class T> inline SLList<T>::~SLList(void) {
	while(!list.isEmpty()) {
		Node *node = (Node *)list.first();
		list.removeFirst();
		delete node;
	}
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
template <class T> inline void SLList<T>::Iterator::operator=(const Iterator& source)
{
	node = source.node;
}
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
