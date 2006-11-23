/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * Interface for Tree class.
 */
#ifndef ELM_GENSTRUCT_TREE_H
#define ELM_GENSTRUCT_TREE_H

#include <elm/Iterator.h>

namespace elm { namespace genstruct {

// TreeFacility class
class TreeFacility {
public:
};


// Tree class
template <class T, class F = TreeFacility >
class Tree: public F {
	Tree<T> *_children, *_sibling;
	T _value;
public:
	inline Tree(const T& value);
	
	// Accessors
	inline const T& value(void) const { return _value; }
	inline T& value(void) { return _value; }
	inline const Tree<T> *children(void) const { return _children; }
	inline Tree<T> *children(void) { return _children; }
	inline const Tree<T> *sibling(void) const { return _sibling; }
	inline Tree<T> *sibling(void) { return _sibling; }
	
	// Mutators
	inline void addChild(Tree<T> *tree);
	inline void addSibling(Tree<T> *tree);
	inline void removeChild(void);
	inline void removeSibling(void);
	inline void clear(void);
	void deleteAll(void);
	
	// Operators
	inline operator bool(void) const { return _children; }
	inline operator const T&(void) const { return value(); }
	inline operator T&(void) { return value(); }
	inline Tree<T>& operator=(const T& value) { _value = value; }
	inline const T& operator*(void) const { return value(); }
	inline T& operator*(void) { return value(); }
	inline Tree<T>& operator+=(Tree<T> *tree) { addChild(tree); return *this; }
	
	// Iterator class
	class Iterator: public PreIterator<Iterator, T> {
		const Tree<T> *cur;
	public:
		inline Iterator(const Tree<T> *tree): cur(tree->children()) { }
		inline const T& item(void) const { return cur->value(); }
		inline bool ended(void) const { return cur; }
		inline void next(void) { cur = cur->sibling(); }
	};
};

// Tree inlines
template <class T, class F>
inline Tree<T, F>::Tree(const T& value)
: _children(0), _sibling(0), _value(value) {
}

template <class T, class F>
inline void Tree<T, F>::addChild(Tree<T> *tree) {
	assert(!tree->_sibling);
	tree->_sibling = _children;
	_children = tree;
}

template <class T, class F>
inline void Tree<T, F>::addSibling(Tree<T> *tree) {
	assert(!tree->_sibling);
	tree->_sibling = _sibling;
	_sibling = tree;
}

template <class T, class F>
inline void Tree<T, F>::removeChild(void) {
	assert(_children);
	Tree<T> *next = _children->_sibling;
	_children->_sibling = 0;
	_children = next;
}

template <class T, class F>
inline void Tree<T, F>::removeSibling(void) {
	assert(_sibling);
	Tree<T> *next = _sibling->_sibling;
	_sibling->_sibling = 0;
	_sibling = next;
}

template <class T, class F>
inline void Tree<T, F>::clear(void) {
	while(_children)
		removeChild();
}

template <class T, class F>
void Tree<T, F>::deleteAll(void) {
	while(_children) {
		Tree<T> *tree = _children;
		removeChild();
		tree->deleteAll();
	}
	delete this;
}

} } // elm:genstruct

#endif // ELM_GENSTRUCT_TREE_H
