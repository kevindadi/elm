/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * src/inhstruct_AVLTree.cpp -- AVLTree implementation.
 */

#include <elm/assert.h>
#include <elm/inhstruct/AVLTree.h>
#include <elm/io.h>

namespace elm { namespace inhstruct {

// Private
static inline int max(int x, int y) {
	if(x > y)
		return x;
	else
		return y;
}
static int inline abs(int x) {
	if(x >= 0)
		return x;
	else
		return -x;
}

/**
 * @class AVLTree::AVLNode
 * AVL tree requires a special kind of nodes implemenetd by this class.
 * For using inherited AVL trees, the tree ndoe must inherit this class.
 */


/**
 * @class AVLTree
 * Implementation of the Adelson-Velskii and Landis (AVL) tree algorithm.
 * In order to use this class, you must make a class inheriting this class
 * and overload the compare() protected method. Nodes inserted in the tree
 * must also inherit from the AVLTree::AVLNode class.
 * 
 * Performances:
 * - depth: O(Log n)
 * - find: O(n/2)
 */

/**
 * @fn int AVLTree::compare(Node *node1, Node *node2);
 * This method is called for comparing nodes. It must be overloaded for getting
 * an actual implementation of AVL tree.
 * @param node1	First node to compare.
 * @param node2	Second node to compare.
 * @return		0 for equality, <0 if node1 < node2, >0 else.
 */


/**
 * @fn bool AVLTree::isEmpty(void);
 * Test if the tree is empty.
 * @return	True if the tree is empty, false else.
 */


/**
 * @fn int AVLTree::count(void);
 * count the number of nodes in the tree.
 * @return	Node count.
 */


/**
 * Get a tree node equal to the given one.
 * @param node	Node to test for equality.
 */
AVLTree::Node *AVLTree::get(Node *node) {
	ASSERTP(node, "null node");
	Node *cur = _root();
	while(cur) {
		int result = compare(node, cur);
		if(!result)
			break;
		else if(result < 0)
			cur = cur->_left();
		else
			cur = cur->_right();
	}
	return cur;
}


/**
 * @fn bool AVLTree::contains(Node *node);
 * Test if the given node value is contained in the tree.
 * @return	True if the node is contained, false else.
 */


/**
 * @fn void AVLTree::visit(Visitor *visitor);
 * Visit the node of the tree.
 * @param visitor	The method process() of this object is called with each
 * tree node.
 */


/**
 * @fn void AVLTree::search(Visitor *visitor);
 * Look for a special node in the given tree.For each node, the process() method
 * of the visitor is called. If it returns 0, search stops. If it returns,
 * <0 traversal continue with left child else with the right child.
 * @param visitor	Visitor to use.
 */


/**
 * Insert a new node in the tree.
 * @param node	Node to insert.
 */
void AVLTree::insert(Node *node) {
	setRoot(insert(_root(), node));
}


/**
 * Remove a node from the tree.
 * @param node	Node to remove.
 */
void AVLTree::remove(Node *node) {
	setRoot(remove(_root(), node));
}


// Private
AVLTree::Node *AVLTree::insert(Node *cur, Node *node) {
	ASSERTP(node, "null node");
	if(!cur) {
		node->h = 1;
		return node;
	}
	else {
		int res = compare(cur, node);
		
		// Insert to left
		if(res > 0 ) {
            cur->insertLeft(insert(cur->_left(), node));
            if(height(cur->_left()) - height(cur->_right()) >= 2) {
				if(compare(cur->_left(), node) > 0)
					cur = rotateSingleLeft(cur);
				else
					cur = rotateDoubleLeft(cur);
            }
		}

		// Insert to right
		else if(res < 0 ) {
            cur->insertRight(insert(cur->_right(), node));
            if(height(cur->_right()) - height(cur->_left()) >= 2) {
				if(compare(cur->_right(), node) < 0)
					cur = rotateSingleRight(cur);
				else
					cur = rotateDoubleRight(cur);
            }
		}

		// Nothing to do
		else
			return cur;
		
		// Recompute max
		computeHeight(cur);
		ASSERT(abs(height(cur->_left()) - height(cur->_right())) < 2);
		return cur;
	}
}

// Private
AVLTree::Node *AVLTree::rotateSingleLeft(Node *root) {
	ASSERTP(root, "null root");
	Node *new_root = root->_left();
	root->insertLeft(new_root->_right());
	new_root->insertRight(root);
	computeHeight(root);
	computeHeight(new_root);
	return new_root;
}

// Private
AVLTree::Node *AVLTree::rotateSingleRight(Node *root) {
	ASSERTP(root, "null root");
	Node *new_root = root->_right();
	root->insertRight(new_root->_left());
	new_root->insertLeft(root);
	computeHeight(root);
	computeHeight(new_root);
	return new_root;
}

// Private
AVLTree::Node *AVLTree::rotateDoubleLeft(Node *root) {
	root->insertLeft(rotateSingleRight(root->_left()));
	return rotateSingleLeft(root);
}

// Private
AVLTree::Node *AVLTree::rotateDoubleRight(Node *root) {
	root->insertRight(rotateSingleLeft(root->_right()));
	return rotateSingleRight(root);
}

// Private
AVLTree::Node *AVLTree::remove(Node *cur, Node *node) {
	ASSERTP(node, "null removed node");
	
	// Compare node
	if(!cur)
		return cur;
	int cmp = compare(cur, node);
	
	// To left
	if(cmp > 0) {
		cur->insertLeft(remove(cur->_left(), node));
		if(height(cur->_right()) - height(cur->_left()) > 1)
			cur = rotateSingleRight(cur);
		computeHeight(cur);
	}
	
	// To right
	else if(cmp < 0) {
		cur->insertRight(remove(cur->_right(), node));
		if(height(cur->_left()) - height(cur->_right()) > 1)
			cur = rotateSingleLeft(cur);
		computeHeight(cur);
	}
	
	// Found !
	else {
		Node *old_cur = cur;
		cur = remap(cur->_left(), cur->_right());
		delete old_cur;
	}
	
	ASSERT(!cur || abs(height(cur->_left()) - height(cur->_right())) < 2);
	return cur;
}

// Private
AVLTree::Node *AVLTree::remap(Node *left, Node *right) {
	
	/* Trivial case */
	if(!left)
		return right;
	if(!right)
		return left;
	
	/* Remap with left down */
	if(left->h < right->h) {
		if(!right->_left()) {
			right->insertLeft(left);
			computeHeight(right);
			return right;
		}
		else {
			Node *root = right->_left();
			right->insertLeft(remap(root->_left(), root->_right()));
			computeHeight(right);
			root->insertLeft(left);
			root->insertRight(right);
			computeHeight(root);
			return root;
		}
		return right;
	}
	
	/* Remap with right down */
	else {
		if(!left->_right()) {
			left->insertRight(right);
			computeHeight(left);
			return left;
		}
		else {
			Node *root = left->_right();
			left->insertRight(remap(root->_left(), root->_right()));
			computeHeight(left);
			root->insertLeft(left);
			root->insertRight(right);
			computeHeight(root);
			return root;
		}
		return right;
	}
}


/**
 * Dump the content of tree. For debugging purpose, only.
 */
#ifdef ELM_DEBUG_AVLTREE
void AVLTree::dump(Node *node, int level) {
	if(!node)
		dump(_root(), 0);
	else {
		for(int i = 0; i < level; i++)
			cout << "| ";
		cout << "+-";
		node->dump();
		cout << '\n';
		if(node->_left())
			dump(node->_left(), level + 1);
		if(node->_right())
			dump(node->_right(), level + 1);
	}
}
#endif


/**
 * this method is called for freeing a node in the tree. This method may be
 * overloaded for providing special freeing method. Not overloaded, do nothing.
 * @param node	Node to free.
 */
void AVLTree::free(Node *node) {
}


// Private
void AVLTree::clean(Node *node) {
	if(!node)
		return;
	else {
		clean(node->_left());
		clean(node->_right());
		free(node);
	}
}


/**
 * @fn void AVLTree::clean(void)
 * Remove all nodes from the tree.
 */

} } // elm::inhstruct

