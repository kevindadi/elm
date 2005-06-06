/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * dllist.h -- double link list classes interface.
 */
#ifndef ELM_GENSTRUCT_DLLIST_H
#define ELM_GENSTRUCT_DLLIST_H

#include <elm/Iterator.h>
#include <elm/inhstruct/DLList.h>

namespace elm { namespace genstruct {

// DLList<T> class
template <class T>
class DLList {
	
	// DLNode class
	class DLNode: public inhstruct::DLNode {
		T val;
	public:
		inline DLNode(const T value);
		inline T value(void) const;
	};
	
	inhstruct::DLList list;
public:
	inline T first(void) const;
	inline T last(void) const;
	inline bool isEmpty(void) const;
	inline int count(void) const;
	inline bool contains(const T value) const;

	inline void remove(const T value);
	inline void addFirst(const T value);
	inline void addLast(const T value);
	inline void removeFirst(void);
	inline void removeLast(void);
	inline void clear(void);
	
	// Iterator class
	class Iterator: public PreIterator<Iterator, T> {
	protected:
		const inhstruct::DLList& list;
		DLNode *cur;
	public:
		inline Iterator(const DLList& _list);
		inline Iterator(const Iterator& iter);
		inline bool ended(void) const;
		inline T item(void) const;
		inline void next(void);
		inline bool begining(void) const;
		inline void previous(void);
		inline void first(void);
		inline void last(void);	
	};
	
	// Editor class
	class Editor: public Iterator {
		inline inhstruct::DLList& elist(void) const;
	public:
		inline Editor(DLList& list);
		inline T& item(void) const;
		inline T& operator*(void) const;		
		inline void remove(void);
		inline void removeNext(void);
		inline void removePrevious(void);
		inline void insertAfter(const T value);
		inline void insertBefore(const T value);
	};
};


// DLList<T>::DLNode methods
template <class T> DLList<T>::DLNode::DLNode(const T value): val(value) {
}
template <class T> T DLList<T>::DLNode::value(void) const {
	return val;
}


// DLList<T> methods
template <class T> T DLList<T>::first(void) const {
	return ((DLNode *)list.first())->value();
}
template <class T> T DLList<T>::last(void) const {
	return ((DLNode *)list.last())->value();
}
template <class T> bool DLList<T>::isEmpty(void) const {
	return list.isEmpty();
}
template <class T> int DLList<T>::count(void) const {
	return list.count();
}
template <class T> void DLList<T>::addFirst(const T value) {
	list.addFirst(new DLNode(value));
}
template <class T> void DLList<T>::addLast(const T value) {
	list.addLast(new DLNode(value));
}
template <class T> void DLList<T>::removeFirst(void) {
	list.removeFirst();
}
template <class T> void DLList<T>::removeLast(void) {
	list.removeLast();
}
template <class T> void DLList<T>::remove(const T value) {
	for(DLNode *cur = (DLNode *)list.first(); !cur->atEnd(); cur = (DLNode *)cur->next())
		if(cur->value() == value) {
			cur->remove();
			break;
		}
}
template <class T> bool DLList<T>::contains(const T value) const {
	for(DLNode *cur = (DLNode *)list.first(); !cur->atEnd(); cur = (DLNode *)cur->next())
		if(cur->value() == value)
			return true;
	return false;
}
template <class T> void DLList<T>::clear(void) {
	DLNode *node;
	while(node = (DLNode *)list.first()) {
		list.removeFirst();
		delete node;
	}
}


// DList<T>::Iterator methods
template <class T> DLList<T>::Iterator::Iterator(const DLList<T>& _list)
: list(_list.list) {
	cur = (DLNode *)list.first();
}

template <class T>
inline DLList<T>::Iterator::Iterator(const DLList<T>::Iterator& iter)
: list(iter.list), cur(iter.cur) {
}

template <class T> bool DLList<T>::Iterator::ended(void) const {
	return cur->atEnd();
}
template <class T> T DLList<T>::Iterator::item(void) const {
	return cur->value();
}
template <class T> void DLList<T>::Iterator::next(void) {
	cur = (DLNode *)cur->next();
}
template <class T> bool DLList<T>::Iterator::begining(void) const {
	return cur == list.first();
}
template <class T> void DLList<T>::Iterator::previous(void) {
	cur = (DLNode *)cur->previous();
}
template <class T> void DLList<T>::Iterator::first(void) {
	cur = (DLNode *)list.first();
}
template <class T> void DLList<T>::Iterator::last(void) {
	cur = (DLNode *)list.last();
}


// DLList<T>::Editor methods
template <class T> inhstruct::DLList& DLList<T>::Editor::elist(void) const {
	return (DLList<T>&)list;
}
template <class T> DLList<T>::Editor::Editor(DLList& list): Iterator(list) {
};
template <class T> T& DLList<T>::Editor::item(void) const {
	return this->cur->value();
}
template <class T> T& DLList<T>::Editor::operator*(void) const {
	return item();
}
template <class T> void DLList<T>::Editor::remove(void) {
	DLNode *to_remove = this->cur;
	DLList<T>::Iterator::next();
	to_remove->remove();
}
template <class T> void DLList<T>::Editor::removeNext(void) {
	this->cur->removeNext();
}
template <class T> void DLList<T>::Editor::removePrevious(void) {
	this->cur->removePrevious();
}
template <class T> void DLList<T>::Editor::insertAfter(const T value) {
	this->cur->insertAfter(new DLNode(value));
}
template <class T> void DLList<T>::Editor::insertBefore(const T value) {
	this->cur->insertBefore(new DLNode(value));
}


} }	// elm::genstruct


#endif	// ELM_GENSTRUCT_DLLIST_H
