/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/genstruct/SortedBinTree.h -- binary tree interface.
 */
#ifndef ELM_GENSTRUCT_SORTEDBINTREE_H
#define ELM_GENSTRUCT_SORTEDBINTREE_H

#include <elm/utility.h>
#include <elm/inhstruct/SortedBinTree.h>

namespace elm { namespace genstruct {

template <class T> class SortedBinTree: private inhstruct::SortedBinTree {

	// Node class
	class Node: public inhstruct::SortedBinTree::Node {
	public:
		T val;
		inline Node(const T value);
	};
	
	Comparator<T>& comp;
protected:
	virtual int compare(inhstruct::SortedBinTree::Node *node1,
		inhstruct::SortedBinTree::Node *node2);
public:
	
	// Visitor class
	class Visitor: private inhstruct::SortedBinTree::Visitor {
		friend class SortedBinTree<T>;
		virtual int process(inhstruct::BinTree::Node *node);
	public:
		virtual int process(T value) = 0;
	};

	// Methods
	inline SortedBinTree(void);
	inline SortedBinTree(Comparator<T>& comp);
	inline bool isEmpty(void);
	inline int count(void);
	inline Option<T> get(const T value);
	inline bool contains(const T value);
	void insert(const T value);
	void remove(const T value);
	void visit(Visitor *visitor);
};
	
// BinTree<T>::Node methods
template <class T> inline SortedBinTree<T>::Node::Node(const T value): val(value) {
}


// BinTree<T>::Visitor methods
template <class T> int SortedBinTree<T>::Visitor::process(inhstruct::BinTree::Node *node) {
	return process(((Node *)node)->val);
}


// SortedBinTree<T> methods
template <class T>
inline SortedBinTree<T>::SortedBinTree(void): comp(Comparator<T>::def) {
}

template <class T>
inline SortedBinTree<T>::SortedBinTree(Comparator<T>& comparator)
: comp(comparator) {
}

template <class T>
inline bool SortedBinTree<T>::isEmpty(void) {
	return inhstruct::SortedBinTree::isEmpty();
}

template <class T>
inline int SortedBinTree<T>::count(void) {
	return inhstruct::SortedBinTree::count();
}

template <class T>
inline bool SortedBinTree<T>::contains(const T value) {
	Node test_node(value);
	Node *found_node = (Node *)inhstruct::SortedBinTree::get(&test_node);
	return found_node != 0;
}

template <class T>
inline Option<T> SortedBinTree<T>::get(const T value) {
	Node test_node(value);
	Node *found_node = get(&test_node);
	if(found_node)
		return Option<T>(found_node.val);
	else
		return Option<T>();
}

template <class T>
void SortedBinTree<T>::insert(const T value) {
	Node *new_node = new Node(value);
	inhstruct::SortedBinTree::insert(new_node);
}

template <class T>
void SortedBinTree<T>::remove(const T value) {
	Node test_node(value);
	remove(&test_node);
}

template <class T>
void SortedBinTree<T>::visit(SortedBinTree<T>::Visitor *visitor) {
	BinTree::visit(visitor);
}

template <class T>
int SortedBinTree<T>::compare(inhstruct::SortedBinTree::Node *node1,
inhstruct::SortedBinTree::Node *node2) {
	return comp.compare(((Node *)node1)->val, ((Node *)node2)->val);
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_SORTEDBINTREE_H
