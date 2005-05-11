/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * sllist.h -- single link list interface.
 */
#ifndef ELM_GENSTRUCT_SLLIST_H
#define ELM_GENSTRUCT_SLLIST_H

#include <assert.h>
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
	inline T first(void) const;
	inline T last(void) const;
	inline int count(void) const;
	inline bool isEmpty(void) const;

	inline void addFirst(const T value);
	inline void addLast(const T value);
	inline void removeFirst(void);
	inline void removeLast(void);
	inline void remove(const T value);

	// Iterator class
	class Iterator {
		const SLList& list;
		const Node *node;
	public:
		inline Iterator(const SLList& _list);
		inline bool ended(void) const;
		inline T item(void) const;
		inline void next(void);
		inline operator bool(void) const;
		inline Iterator& operator++(int);
		inline operator T(void) const;
		inline T operator*(void) const;
		inline T *operator->(void) const;
	};

	// Editor class
	class Editor: public Iterator {
		inline SLList& list(void);
	public:
		inline Editor(SLList& list);
		inline void addAfter(T value);
		inline void removeNext(void);
	};
};


// SLList::Node inlines
template <class T> SLList<T>::Node::Node(const T value): val(value) {
}
template <class T> inline typename SLList<T>::Node *SLList<T>::Node::next(void) const {
	return (Node *)SLNode::next();
}

// SLList class
template <class T> inline T SLList<T>::first(void) const {
	return ((Node *)list.first())->val;
}
template <class T> inline T SLList<T>::last(void) const {
	return ((Node *)list.last())->val;
}
template <class T> inline int SLList<T>::count(void) const {
	return list.count();
}
template <class T> inline void SLList<T>::addFirst(const T value) {
	list.addFirst(new Node(value));
}
template <class T> inline void SLList<T>::addLast(const T value) {
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
template <class T> inline void SLList<T>::remove(const T value) {
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
: list(_list), node((Node *)list.list.first()) {
}
template <class T> inline bool SLList<T>::Iterator::ended(void) const {
	return !node;
}
template <class T> inline T SLList<T>::Iterator::item(void) const {
	assert(node);
	return node->val;
}
template <class T> inline void SLList<T>::Iterator::next(void) {
	assert(node);
	node = node->next();
}
template <class T> inline SLList<T>::Iterator::operator bool(void) const {
	return !ended();
}
template <class T>
inline typename SLList<T>::Iterator& SLList<T>::Iterator::operator++(int) {
	next(); return *this;
}
template <class T> inline SLList<T>::Iterator::operator T(void) const {
	return item();
}
template <class T> inline T SLList<T>::Iterator::operator*(void) const {
	return item();
}
template <class T> inline T *SLList<T>::Iterator::operator->(void) const {
	return &item();
};

} } // elm::genstruct

#endif // ELM_GENSTRUCT_SLLIST_H
