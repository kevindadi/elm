/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * test/test_avl.cpp -- AVLTree class test.
 */

#include <elm/inhstruct/AVLTree.h>
#include <elm/io.h>

using namespace elm::inhstruct;
using namespace elm;

/* My node */
class MyNode: public AVLTree::Node {
public:
	int v;
	MyNode(int _v): v(_v) { };
	#ifdef ELM_DEBUG_AVLTREE
		virtual void dump(void) {
			cout << v;
		}
	#endif
};

/* Visitor */
class MyVisitor: public BinTree::Visitor {
public:
	virtual int process(BinTree::Node *node) {
		MyNode *mynode = (MyNode *)node;
		cout << mynode->v << '\n';
		return 1;
	};
};

/* My Tree */
class MyTree: public AVLTree {
protected:
	virtual int compare(Node *node1, Node *node2) {
		return ((MyNode *)node1)->v - ((MyNode *)node2)->v;
	}
	virtual void free(Node *node)  {
		MyNode *mynode = (MyNode *)node;
		cout << "Freeing " << mynode->v << '\n';
		delete mynode;
	}
};

int main(void) {
	MyTree tree;
	MyVisitor visitor;
	MyNode *nodes[10];
	
	// Simple test
	for(int i = 0; i < 10; i++) {
		nodes[i] = new MyNode(i);
		tree.insert(nodes[i]);
		cout << "=> " << i << '\n';
	}
	
	// Visit tree
	tree.visit(&visitor);
	#ifdef ELM_DEBUG_AVLTREE
		tree.dump();
	#endif
	
	// Remove some nodes
	tree.remove(nodes[9]);
	tree.remove(nodes[8]);
	tree.remove(nodes[5]);
	#ifdef ELM_DEBUG_AVLTREE
		tree.dump();
	#endif
	
	// Cleanup
	tree.clean();
	return 0;
}
