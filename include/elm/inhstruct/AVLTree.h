/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/inhstruct/AVLTree.h -- AVLTree interface.
 */
#ifndef ELM_INHSTRUCT_AVLTREE_H
#define ELM_INHSTRUCT_AVLTREE_H

#include <elm/inhstruct/BinTree.h>

namespace elm { namespace inhstruct {

// AVLTree class
class AVLTree: protected BinTree {
public:
	
	// AVLNode class
	class Node: public BinTree::Node {
		friend class AVLTree;
		int h;
		inline Node *_left(void) const { return (Node *)left(); };
		inline Node *_right(void) const { return (Node *)right(); };
		#ifdef ELM_DEBUG_AVLTREE
			virtual void dump(void) = 0;
		#endif
	};

private:
	Node *insert(Node *cur, Node *node);
	Node *remove(Node *cur, Node *node);
	Node *rotateSingleLeft(Node *node);
	Node *rotateDoubleLeft(Node *node);
	Node *rotateSingleRight(Node *node);
	Node *rotateDoubleRight(Node *node);
	Node *remap(Node *left, Node *right);
	void clean(Node *node);
	inline Node *_root(void) const { return (Node *)root(); };
	inline int height(Node *node) const { return node ? node->h : 0; };
	inline void computeHeight(Node *node);
	
protected:
	virtual int compare(Node *node1, Node *node2) = 0;
	virtual void free(Node *node);

public:

	// Accessors
	inline bool isEmpty(void);
	inline int count(void);
	Node *get(Node *node);
	inline bool contains(Node *node);
	inline void visit(Visitor *visitor);
	inline void search(Visitor *visitor);
	
	// Modifiers
	void insert(Node *node);
	void remove(Node *node);
	inline void clean(void);
	
	// Debug
	#ifdef ELM_DEBUG_AVLTREE
		void dump(Node *node = 0, int level = 0);
	#endif
};


// SortedBinTree inlines
inline bool AVLTree::isEmpty(void) {
	return BinTree::isEmpty();
}

inline int AVLTree::count(void) {
	return BinTree::count();
}

inline bool AVLTree::contains(Node *node) {
	return get(node) != 0;
}

inline void AVLTree::visit(Visitor *visitor) {
	return BinTree::visit(visitor);
}
	
inline void AVLTree::search(Visitor *visitor) {
	BinTree::search(visitor);
}

inline void AVLTree::computeHeight(Node *node) {
	int hleft = height(node->_left()), hright = height(node->_right());
	if(hleft > hright)
		node->h = hleft + 1;
	else
		node->h = hright + 1;
}

inline void AVLTree::clean(void) {
	clean(_root());
}

} } // elm::inhstruct

#endif // ELM_INHSTRUCT_AVLTREE_H
