/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * DAGNode.h -- DAG interface.
 */
#ifndef ELM_GENSTRUCT_DAGNODE_H 
#define ELM_GENSTRUCT_DAGNODE_H

#include <elm/assert.h>
#include <elm/Iterator.h>
#include <elm/genstruct/SLList.h>
#include <elm/genstruct/HashTable.h>

namespace elm { namespace genstruct {

// DAGNode class
template <class T> class DAGNode {

	T value;
	SLList<DAGNode*> children; 
	bool deleted;

	
public:

	// Constructors / Destructors
	inline DAGNode(const T& _value);	
	inline ~DAGNode(); 

	// Mutators
	inline void addChild(DAGNode *child);
	inline void removeChild(DAGNode *child);	
	
	// Accessors
	inline T& useValue(void);

	// Iterator class
	class Iterator: public PreIterator<Iterator, DAGNode*> {
		friend class DAGNode;
		
		typename SLList<DAGNode*>::Iterator iter;
		inline void skipDeleted();
	public:
		inline Iterator(const DAGNode& _node);
		inline Iterator(const Iterator& source);
		
		inline void operator=(const Iterator& source);
		inline bool ended(void) const;
		inline DAGNode* item(void) const;
		inline void next(void);
	};


};

template <class T>
inline T& DAGNode<T>::useValue(void) {
	return value;
}

template <class T>
inline DAGNode<T>::DAGNode(const T& _value) : value(_value), deleted(false) {

}

template <class T>
inline DAGNode<T>::~DAGNode() {
}

template <class T>
inline void DAGNode<T>::addChild(DAGNode *child) {
	this->children.addFirst(child);
}

template <class T>
inline void DAGNode<T>::removeChild(DAGNode *child) {
	this->children.remove(child);
}

// DAGNode::Iterator class
template <class T> inline DAGNode<T>::Iterator::Iterator(const DAGNode& _node)
: iter(typename SLList<DAGNode*>::Iterator(_node.children)) {
}

template <class T> inline DAGNode<T>::Iterator::Iterator(const Iterator& source)
: iter(source.iter) {
}

template <class T> inline void DAGNode<T>::Iterator::operator=(const Iterator& source)
{
	iter = source.iter;
}
template <class T> inline bool DAGNode<T>::Iterator::ended(void) const {
	return iter.ended();
}
template <class T> inline DAGNode<T>* DAGNode<T>::Iterator::item(void) const {
	return iter.item();
}
template <class T> inline void DAGNode<T>::Iterator::next(void) {
	iter.next();

}

template <class T> inline void DAGNode<T>::Iterator::skipDeleted(void) {
	while ((!iter.ended()) && (iter.item()->deleted) ) {
		iter.next();
	}
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_DAGNODE_H
