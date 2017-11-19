/*
 *	avl::GenTree class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2013, IRIT UPS.
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

#include <elm/avl/GenTree.h>
#include <elm/avl/Set.h>
#include <elm/avl/Map.h>
#include <elm/data/Vector.h>
#include <elm/compare.h>

namespace elm { namespace avl {

using namespace elm;

/*
 * Let T supporting a partial-order (T, ≤),
 * AVLTree(T) = node(val: T, bal: ℤ, left: AVLTree(T), right: AVLTree(T)) | nil
 *
 * Invariant — let t ∈ AVLTree(T),
 * left_sorted(nil) = ⊤
 * left_sorted(node(x, _, l, r)) =
 * 		(∀ y ∈ values(l) ⇒ y < x) ∧ left_sorted(l) ∧ left_sorted(r)
 * right_sorted(nil) = ⊤
 * right_sorted(node(x, _, l, r)) =
 * 		(∀ y ∈ values(l) ⇒ x < y) ∧ right_sorted(l) ∧ right_sorted(r)
 * balanced(nil) = ⊤
 * balanced(node(_, b, l, r) =
 * 		b = h(r) - h(l) ∧ -1 ≤ b ≤ 1 ∧ balanced(l) ∧ balanced(r)
 * invariant(t) = left_sorted(t) ∧ right_sorted(t) ∧ balanced(t)
 *
 * Reference:
 * http://interactivepython.org/runestone/static/pythonds/Trees/AVLTreeImplementation.html
 */


/**
 * Get the link to the pointer of the top-node corresponding
 * to the followed path (basically used to relink nodes).
 * @param s	Stack to the concerned node.
 */
AbstractTree::Node **AbstractTree::link(const Stack& s) {
	if(s.empty())
		return &_root;
	else if(s.topDir() == LEFT)
		return &s.topNode()->_left;
	else
		return &s.topNode()->_right;
}


/**
 * Exchange two nodes values (does not update the parent link).
 * @param n		First node.
 * @param m		Second node.
 */
void AbstractTree::exchange(Node *n, Node *m) {
	auto nl = n->_left;
	auto nr = n->_right;
	auto nb = n->_bal;
	n->_left = m->_left;
	n->_right = m->_right;
	n->_bal = m->_bal;
	m->_left = nl;
	m->_right = nr;
	m->_bal = nb;

}


/**
 * Perform right-balancing of the node at the top of the stack.
 * @param s		Stack which top-node must be balanced.
 */
void AbstractTree::rotateRight(Stack& s) {
	Node *r = s.topNode();
	s.pop();
	Node *nr = r->_left;

	// relink
	//set(s, nr);
	*link(s) = nr;
	r->_left = nr->_right;
	nr->_right = r;

	// udpate balance
	r->_bal = r->_bal + 1 - min(int(nr->_bal), 0);
	nr->_bal = nr->_bal + 1 + max(int(r->_bal), 0);
}


/**
 * Perform left-balancing of the node at the top of the stack.
 * @param s		Stack which top-node must be balanced.
 */
void AbstractTree::rotateLeft(Stack& s) {
	Node *r = s.topNode();
	s.pop();
	Node *nr = r->_right;

	// relink
	//set(s, nr);
	*link(s) = nr;
	r->_right = nr->_left;
	nr->_left = r;

	// udpate balance
	r->_bal = r->_bal - 1 - max(int(nr->_bal), 0);
	nr->_bal = nr->_bal - 1 + min(int(r->_bal), 0);
}


/**
 * Perform actual insertion and re-balancing of a new value.
 * @param s		Tree traversal stack.
 * @param node	Added node.
 */
void AbstractTree::insert(Stack& s, Node *node) {
	_cnt++;

	// empty tree
	if(_root == nullptr) {
		_root = node;
		return;
	}

	// insert the node
	//set(s, node);
	*link(s) = node;

	// update the balance factor and find the unbalancing point
	while(!s.empty()) {

		// consume current node
		int dir = s.topDir();
		Node *n = s.topNode();

		// fix the balance
		if(dir == LEFT)
			n->_bal -= 1;
		else
			n->_bal += 1;

		// balanced!
		if(n->_bal == 0)
			return;

		// too high on left
		else if(n->_bal < -1) {
			if(n->_left->_bal > 0) {
				s.push(n->_left, LEFT);
				rotateLeft(s);
			}
			rotateRight(s);
			return;
		}

		// too high on right
		else if(+1 < n->_bal) {
			if(n->_right->_bal < 0) {
				s.push(n->_right, RIGHT);
				rotateRight(s);
			}
			rotateLeft(s);
			return;
		}

		// propagate addition
		s.pop();
	}
}


/**
 * Perform removal and rebalance operation.
 * @param s		Stack of parents of removed node.
 * @param n		Replacing node.
 */
void AbstractTree::remove(Stack& s, Node *n) {

	// relink
	_cnt--;
	*link(s) = n;

	// propagate the balance update
	while(!s.empty()) {

		// propagate modificiation
		Node *n = s.topNode();
		dir_t d = s.topDir();
		s.pop();
		if(d == LEFT)
			n->_bal++;
		else
			n->_bal--;

		// left unbalanced?
		if(n->_bal < -1) {
			return;
		}

		// right unbalanced?
		else if(n->_bal > +1) {
			return;
		}

	}
}


/**
 * @fn int AbstractTree::count(void) const;
 * Count the number of nodes.
 * @return	Number of nodes.
 */


/**
 * @class GenTree
 * This class implements an AVL tree collection based on C++ templates as provided by:
 * Ben Pfaff, "An Introduction to
 * Binary Search Trees and Balanced Trees",
 * Libavl Binary Search Tree Library, Volume 1: Source Code, Version 2.0.2.
 * @par
 * This class is rarely used as is but used as a base class for @ref elm::avl::Set or @ref elm::avl::Map.
 * 
 * @param T		Type of contained items.
 * @param C		Comparator for T items (default to @ref elm::Comparator<T>).
 * @see			@ref elm::avl::Set, @ref elm::avl::Map
 * 
 * @par Implemented concepts
 * @li @ref elm::concept::Collection<T>
 * @li @ref elm::concept::MutableCollection<T>
 */

/**
 * @fn int GenTree::count(void) const;
 * Get the count of items in the tree.
 * @return	Item count.
 * @notice	This function call is fast as the item count is maintained
 *			during each insertion and removal.
 */

/**
 * @fn bool GenTree::contains(const T& item) const;
 * Test if the tree contains the given item.
 * @param item	Item to look for.
 * @return		True if it is contained, false else.
 * @notice		Access time in log2(item number).
 */

/**
 * @fn bool GenTree::containsAll(const Co<T>& coll) const;
 * Test if the given collection is contained in the current one.
 * @param coll	Collection to test.
 * @return		True if the collection is containted, false else.
 * @param C		Type of the collection.
 */

/**
 * @fn bool GenTree::isEmpty(void) const;
 * Test if the tree is empty.
 * @return	True if the tree is empty, false else.
 */

/**
 * @class GenTree::Iterator
 * Iterator on items of the tree. No assumption may be made on the order of traversal
 * of the items of the tree.
 */

/**
 * @fn void GenTree::clear(void);
 * Remove all items from the tree and let it cleared.
 */

/**
 * @fn void GenTree::add(const T& item);
 * Add an item to the tree. Note that the item is still added even if it is already
 * contained in the tree, leading to duplicates.
 * @param item	Item to add.
 */

/**
 * @fn void GenTree::addAll(const Co<T>& coll);
 * Add a collection to this tree.
 * @param coll	Collection to add.
 * @param C		Type of the collection.
 */

/**
 * @fn void GenTree::remove(const T& item);
 * Remove an item from a tree. Notice that if the tree contains duplicates of the item,
 * only the first duplicate is removed.
 * @param item	Item to remove.
 * @warning	Attempting to remove an item not contained in the tree is an error.
 */

/**
 * @fn void GenTree::removeAll(const Co<T>& coll);
 * Remove a collection from this tree.
 * @param coll	Collection to remove.
 * @param C		Type of the collection.
 */

/**
 * @fn void GenTree::remove(const Iterator& iter);
 * Remove the item pointed by the iterator.
 * @param	Iterator pointing to the item to remove.
 */


/**
 * @class Set
 * Implements a set collection based on an AVL tree, that is, supporting access and modifications
 * with a O(log n) complexity.
 * @par Implemented concepts
 * @li @ref elm::concept::Collection<T>
 * @li @ref elm::concept::MutableCollection<T>
 * @li @ref elm::concept::Set<T>
 *
 * @param T		Type of stored items.
 * @param C		Comparator used to sort the items (must implements the @ref elm::concept::Comparator<T> concept,
 * 				as a default @ref elm::Comparator<T>).
 * @see			@ref elm::avl::GenTree
 */


/**
 * @class Map
 * Implements a map based on AVL tree, that is, a map supporting O(log n) accesses.
 * @par Implemented concepts
 * @li @ref elm::concept::Collection<T>
 * @li @ref elm::concept::Map<K, T>
 *
 * @param K		Type of keys of the map.
 * @param T		Type of stored items.
 * @param C		Comparator used to sort the items (must implements the @ref elm::concept::Comparator<K> concept,
 * 				as a default @ref elm::Comparator<K>).
 * @see			@ref elm::avl::GenTree
 */

}	// avl

namespace genstruct {

/**
 * @class AbstractAVLTree
 * @deprecated	Only for compilation compatibility. Use @ref elm::avl::AbstractTree.
 */

/**
 * @class GenAVLTree
 * @deprecated	Only for compilation compatibility. Use @ref elm::avl::GenTree.
 */

/**
 * @class AVLTree
 * @deprecated	Only for compilation compatibility. Use @ref elm::avl::Set.
 */

} }	// elm::genstruct
