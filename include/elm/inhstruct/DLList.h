/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * dllist.h -- double link list classes interface.
 */
#ifndef ELM_INHSTRUCT_DLLIST_H
#define ELM_INHSTRUCT_DLLIST_H

#include <assert.h>

namespace elm { namespace inhstruct {

// DLList class
class DLList;
class DLNode {
	friend class DLList;
	DLNode *nxt, *prv;
public:
	inline DLNode *next(void) const;
	inline DLNode *previous(void) const;
	inline bool atBegin(void) const;
	inline bool atEnd(void) const;
	
	inline void replace(DLNode *node);
	inline void insertAfter(DLNode *node);
	inline void insertBefore(DLNode *node);
	inline void remove(void);
	inline void removeNext(void);
	inline void removePrevious(void);
};


// DLList class
class DLList {
	DLNode hd, tl;
public:
	inline DLList(void);

	inline DLNode *first(void) const;
	inline DLNode *last(void) const;
	inline bool isEmpty(void) const;
	inline int count(void) const;

	inline void addFirst(DLNode *node);
	inline void addLast(DLNode *node);
	inline void removeFirst(void);
	inline void removeLast(void);
};


// DLNode methods
DLNode *DLNode::next(void) const {
	return nxt;
}
DLNode *DLNode::previous(void) const {
	return prv;
}
void DLNode::replace(DLNode *node) {
	assert(node);
	nxt->prv = node;
	node->nxt = nxt;
	prv->nxt = node;
	node->prv = prv;
}
void DLNode::insertAfter(DLNode *node) {
	assert(node);
	nxt->prv = node;
	node->nxt = nxt;
	nxt = node;
	node->prv = this;
}
void DLNode::insertBefore(DLNode *node) {
	assert(node);
	prv->nxt = node;
	node->prv = prv;
	prv = node;
	node->nxt = this;
}
void DLNode::remove(void) {
	prv->nxt = nxt;
	nxt->prv = prv;
}
void DLNode::removeNext(void) {
	assert(!nxt->atEnd());
	nxt->remove();
}
void DLNode::removePrevious(void) {
	assert(!prv->atBegin());
	prv->remove();
}
bool DLNode::atBegin(void) const {
	return prv == 0;
}
bool DLNode::atEnd(void) const {
	return nxt == 0;
}


// DLList methods
DLList::DLList(void) {
	hd.nxt = &tl;
	hd.prv = 0;
	tl.prv = &hd;
	tl.nxt = 0;
}
DLNode *DLList::first(void) const {
	return hd.nxt;
}
DLNode *DLList::last(void) const {
	return tl.prv;
}
bool DLList::isEmpty(void) const {
	return hd.nxt == &tl;
}
int DLList::count(void) const {
	int cnt = 0;
	for(DLNode *cur = hd.nxt; cur != &tl; cur =cur->nxt)
		cnt++;
	return cnt;
}
void DLList::addFirst(DLNode *node) {
	assert(node);
	hd.insertAfter(node);
}
void DLList::addLast(DLNode *node) {
	assert(node);
	tl.insertBefore(node);
}
void DLList::removeFirst(void) {
	assert(!isEmpty());
	hd.removeNext();
}
void DLList::removeLast(void) {
	assert(!isEmpty());
	tl.removePrevious();
}


} } // elm::inhstruct

#endif	// ELM_INHSTRUCT_DLLIST_H
