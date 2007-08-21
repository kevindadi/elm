/*
 *	$Id$
 *	Tree class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
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

#include <elm/genstruct/Tree.h>

namespace elm { namespace genstruct {

/**
 * @class Tree
 * This class implements a minimal tree whose children are linked with
 * a simple link list. It provides facilities to store a value on the tree
 * and to access either children, or closer sibling.
 * 
 * @param T	Type of stored values.
 * @ingroup gen_datastruct
 */

/**
 * @fn Tree::Tree(const T& value);
 * Build a new empty tree storing the given value.
 * @param value	Value to store in the tree.
 */

/**
 * @fn const T& Tree::value(void) const;
 * Get the value stored in the tree.
 * @return	Stored value.
 */

/**
 * @fn T& Tree::value(void);
 * Get assignable reference on the value stored in the tree.
 * @return	Stored value reference.
 */

/**
 * @fn const Tree<T> *Tree::children(void) const;
 * Get list of children of the tree, that is, the first child.
 * @return	First children.
 */

/**
 * @fn Tree<T> *Tree::children(void)
 * Get list of children of the tree, that is, the first child.
 * @return	First children.
 */

/**
 * @fn const Tree<T> *Tree::sibling(void) const;
 * Get the next sibling of the current tree.
 * @return	Next sibling.
 */

/**
 * @fn Tree<T> *Tree::sibling(void)
 * Get the next sibling of the current tree.
 * @return	Next sibling.
 */
	
	// Mutators
/*	inline void addChild(Tree<T> *tree);
	inline void addSibling(Tree<T> *tree);
	inline void removeChild(void);
	inline void removeSibling(void);
	inline void clear(void);
	inline void deleteAll(void);
	
	// Operators
	inline operator bool(void) const { return _children; }
	inline operator const T&(void) const { return value(); }
	inline operator T&(void) { return value(); }
	inline Tree<T>& operator=(const T& value) { _value = value; }
	inline const T& operator*(void) const { return value(); }
	inline T& operator*(void) { return value(); }
	inline Tree<T>& operator+=(Tree<T> *tree);
	inline Tree<T>& operator+=(Tree<T>& tree);
	
	// Iterator class
	class Iterator: public PreIterator<Iterator, T> {
		const Tree<T> *cur;
	public:
		inline Iterator(const Tree<T> *tree): cur(tree->children()) { }
		inline const T& item(void) const { return cur->value(); }
		inline bool ended(void) const { return cur; }
		inline void next(void) { cur = cur->sibling(); }
	};
};*/

} } // elm:genstruct
