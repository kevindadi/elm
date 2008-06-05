/*
 *	$Id$
 *	Tree class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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
#ifndef ELM_GENSTRUCT_TREE_H
#define ELM_GENSTRUCT_TREE_H

#include <elm/inhstruct/Tree.h>

namespace elm { namespace genstruct {

// Tree class
template <class T>
class Tree: private inhstruct::Tree {
public:
	inline Tree(const T& value): _value(value) { }
	
	// Accessors
	inline Tree *children(void) const
		{ return static_cast<Tree *>(inhstruct::Tree::children()); }
	inline Tree *sibling(void) const
		{ return static_cast<Tree *>(inhstruct::Tree::sibling()); }
	bool hasChild(Tree *tree) const
		{ return inhstruct::Tree::hasChild(tree); }
	inline bool contains(Tree *tree) const { return hasChild(tree); }
	inline int count(void) const
		{ return inhstruct::Tree::count(); }
	inline bool isEmpty(void) const
		{ return inhstruct::Tree::isEmpty(); }
	inline operator bool(void) const
		{ return inhstruct::Tree::isEmpty(); }

	// Iterator class
	class Iterator: public PreIterator<Iterator, T> {
	public:
		inline Iterator(const Iterator& iter): it(iter.it) { }
		inline Iterator(const Tree *tree): it(tree) { }
		inline bool ended (void) const { return it.ended(); }
		inline const T& item(void) const
			{ return static_cast<Tree *>(it.item())->_value; }
		inline void next(void) { it.next(); }
	private:
		inhstruct::Tree::Iterator it;
	};

	// Mutators
	inline void prependChild(Tree *child)
		{ inhstruct::Tree::prependChild(child); }
	inline void appendChild(Tree *child)
		{ inhstruct::Tree::appendChild(child); }
	inline void add(Tree *child)
		{ inhstruct::Tree::add(child); }
	template <class TT> void addAll(const TT& coll)
		{ inhstruct::Tree::addAll(coll); } 
	inline void removeChild(Tree *child)
		{ inhstruct::Tree::removeChild(child); }
	inline void remove(Tree *child)
		{ inhstruct::Tree::remove(child); }
	inline void remove(const Iterator& iter)
		{ removeChild(iter); }
	template <class TT> void removeAll(const TT& coll)
		{ inhstruct::Tree::removeAll(coll); } 
	inline void clear(void)
		{ inhstruct::Tree::clear(); }
	
private:
	T _value;
	

/*public:
	
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
	};*/
};

// Tree inlines
/*template <class T>
inline void Tree<T>::addChild(Tree<T> *tree) {
	assert(!tree->_sibling);
	tree->_sibling = _children;
	_children = tree;
}

template <class T>
inline void Tree<T>::addSibling(Tree<T> *tree) {
	assert(!tree->_sibling);
	tree->_sibling = _sibling;
	_sibling = tree;
}

template <class T>
inline void Tree<T>::removeChild(void) {
	assert(_children);
	Tree<T> *next = _children->_sibling;
	_children->_sibling = 0;
	_children = next;
}

template <class T>
inline void Tree<T>::removeSibling(void) {
	assert(_sibling);
	Tree<T> *next = _sibling->_sibling;
	_sibling->_sibling = 0;
	_sibling = next;
}

template <class T>
inline void Tree<T>::clear(void) {
	while(_children)
		removeChild();
}

template <class T>
void Tree<T>::deleteAll(void) {
	while(_children) {
		Tree<T> *tree = _children;
		removeChild();
		tree->deleteAll();
	}
	delete this;
}*/

} } // elm:genstruct

#endif // ELM_GENSTRUCT_TREE_H
