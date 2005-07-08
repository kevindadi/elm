/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS <caasse@irit.fr>
 *
 * elm/genstruct/AVLTree.h -- AVL binary tree interface.
 */
#ifndef ELM_GENSTRUCT_AVLTREE_H
#define ELM_GENSTRUCT_AVLTREE_H

#include <elm/utility.h>
#include <elm/inhstruct/AVLTree.h>

namespace elm { namespace genstruct {

// Generic AVLTree
template <class T>
class AVLTree: private inhstruct::AVLTree {

	// Node class
	class Node: public inhstruct::AVLTree::Node {
	public:
		T val;
		inline Node(const T value);
		#ifdef ELM_DEBUG_AVLTREE
			virtual void dump(void)  { };
		#endif
	};
	
	Comparator<T>& comp;
protected:
	virtual int compare(inhstruct::AVLTree::Node *node1,
		inhstruct::AVLTree::Node *node2);
public:

	// Visitor class
	class Visitor: private inhstruct::AVLTree::Visitor {
		friend class AVLTree<T>;
		virtual int process(inhstruct::BinTree::Node *node);
	public:
		virtual int process(T value) = 0;
	};

	// Constructors
	inline AVLTree(void);
	inline AVLTree(Comparator<T>& comp);
	
	// Accessors
	inline int count(void);
	inline bool isEmpty(void);
	inline bool contains(const T value);
	inline Option<T> get(const T value);
	void visit(Visitor *visitor);
	
	// Mutators
	void insert(const T value);
	void remove(const T value);
	void clean(void);
};

// AVLTree<T>::Node methods
template <class T> inline AVLTree<T>::Node::Node(const T value): val(value) {
}


// AVLTree<T>::Visitor methods
template <class T> int AVLTree<T>::Visitor::process(inhstruct::BinTree::Node *node) {
	return process(((Node *)node)->val);
}


// AVLTree<T> methods
template <class T>
inline AVLTree<T>::AVLTree(void): comp(Comparator<T>::def) {
}

template <class T>
inline AVLTree<T>::AVLTree(Comparator<T>& comparator)
: comp(comparator) {
}

template <class T>
inline bool AVLTree<T>::isEmpty(void) {
	return inhstruct::AVLTree::isEmpty();
}

template <class T>
inline int AVLTree<T>::count(void) {
	return inhstruct::AVLTree::count();
}

template <class T>
inline bool AVLTree<T>::contains(const T value) {
	Node test_node(value);
	Node *found_node = (Node *)inhstruct::AVLTree::get(&test_node);
	return found_node != 0;
}

template <class T>
inline Option<T> AVLTree<T>::get(const T value) {
	Node test_node(value);
	Node *found_node = get(&test_node);
	if(found_node)
		return Option<T>(found_node.val);
	else
		return Option<T>();
}

template <class T>
void AVLTree<T>::insert(const T value) {
	Node *new_node = new Node(value);
	inhstruct::AVLTree::insert(new_node);
}

template <class T>
void AVLTree<T>::remove(const T value) {
	Node test_node(value);
	inhstruct::AVLTree::remove(&test_node);
}

template <class T>
void AVLTree<T>::visit(AVLTree<T>::Visitor *visitor) {
	BinTree::visit(visitor);
}

template <class T>
int AVLTree<T>::compare(inhstruct::AVLTree::Node *node1,
inhstruct::AVLTree::Node *node2) {
	return comp.compare(((Node *)node1)->val, ((Node *)node2)->val);
}

template <class T>
void AVLTree<T>::clean(void) {
	inhstruct::AVLTree::clean();
}

} }	// elm::genstruct

#endif	// ELM_AVLTREE_AVLTREE_H
