/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * test/test_avl.cpp -- AVLTree class test.
 */

#include <elm/util/test.h>
#include <elm/inhstruct/AVLTree.h>
#include <elm/genstruct/AVLTree.h>
#include <elm/io.h>
 #include <stdlib.h>
 
using namespace elm::inhstruct;
using namespace elm;

#define VAL_MAX		1000
#define TEST_CNT	1000

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
	int i;
	TestCase& __case;
public:
	MyVisitor(TestCase& test): i(0), __case(test) {
	}
	virtual int process(BinTree::Node *node) {
		MyNode *mynode = (MyNode *)node;
		cout << "===> " << mynode->v << '\n';
		CHECK(mynode->v == i);
		i++;
		return 1;
	};
	int count(void) const { return i; };
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


// Dump the tree
void dump(MyNode *node, int tab = 0) {
	if(!node)
		return;
	for(int i = 0; i < tab; i++)
		cout << "  ";
	cout << node->v << io::endl;
	dump((MyNode *)node->left(), tab + 1);
	dump((MyNode *)node->right(), tab + 1);
}


// genstruct::AVLTree<int>::Visitor
class GenVisitor: public genstruct::AVLTree<int>::Visitor {
	TestCase& __case;
	int i;
public:
	GenVisitor(TestCase& test): i(0), __case(test) {
	}
	virtual int process(int value) {
		cout << value << '\n';
		CHECK(value == i);
		i++;
		return 1;
	};
	inline int count(void) const { return i; };
};

// Entry point
void test_avl(void) {
	CHECK_BEGIN("avltree");
	
	//************* inhstruct test *****************
	{
		MyTree tree;
		MyVisitor visitor(__case);
		MyNode *nodes[10];
	
		// Simple test
		CHECK(tree.isEmpty());
		for(int i = 0; i < 10; i++) {
			nodes[i] = new MyNode(i);
			tree.insert(/*nodes[i]*/new MyNode(i));
		}
		CHECK(!tree.isEmpty());
		for(int i = 0; i < 10; i++)
			CHECK(tree.contains(nodes[i]));
		
		// Visit tree
		CHECK(visitor.count() == 0);
		tree.visit(&visitor);
		CHECK(visitor.count() == 10);
		#ifdef ELM_DEBUG_AVLTREE
			tree.dump();
		#endif
	
		// Remove some nodes
		int removes[3] = { 9, 8, 5 };
		//dump((MyNode *)tree.root());
		for(int i = 0; i < 3; i++) {
			cout << "BEFORE\n";
			dump((MyNode *)tree.root());
			cout << "REMOVE " << removes[i] << io::endl;
			tree.remove(nodes[removes[i]]);
			cout << "AFTER\n";
			dump((MyNode *)tree.root());
			CHECK(!tree.contains(nodes[removes[i]]));
			#ifdef ELM_DEBUG_AVLTREE
				tree.dump();
			#endif
			nodes[removes[i]] = 0;
			for(int j = 0; j < 10; j++) {
				if(nodes[j])
					CHECK(tree.contains(nodes[j]));
			}	
		}
		#ifdef ELM_DEBUG_AVLTREE
			tree.dump();
		#endif
	
		// Cleanup
		tree.clean();
	}
	
	//**************** genstruct test ********************
	{
		genstruct::AVLTree<int> tree;
		GenVisitor visitor(__case);
		
		// Fill the tree
		CHECK(tree.isEmpty());
		for(int i = 0; i < 10; i++)
			tree.insert(i);
		CHECK(!tree.isEmpty());
			
		// Visit the tree
		CHECK(visitor.count() == 0);
		tree.visit(&visitor);
		CHECK(visitor.count() == 10);
		
		// Remove some nodes
		tree.remove(9);
		tree.remove(8);
		tree.remove(5);
		
		// Clean up
		tree.clean();
	}
	
	// Robustness test
	{
		bool failed = false;
		genstruct::AVLTree<int> tree;
		int t[VAL_MAX];
		for(int i = 0; i < VAL_MAX; i++)
			t[i] = 0;
		for(int cnt = 0; !failed && cnt < TEST_CNT; cnt++) {
			
			// Do operation
			int op = rand();
			int idx = int(double(op >> 1) * VAL_MAX / RAND_MAX);
			if(op % 2 == 0) {
				cout << cnt << ". add " << idx << io::endl;
				tree.insert(idx);
				t[idx] = 1;	
			}			
			else {
				if(!t[idx]) {
					int base = idx++;
					while(!t[idx] && idx != base)
						idx = (idx + 1) % VAL_MAX;
					if(idx == base)
						continue;
				}
				cout << cnt << ". remove " << idx << io::endl;
				tree.remove(idx);
				t[idx] = 0;
			}
			
			// Check the content
			for(int i = 0; i < VAL_MAX; i++) {
				if(t[i] && !tree.contains(i)) {
					failed = true;
					cerr << "ERROR:" << i << " not in the tree !\n";
					break;
				}
				if(!t[i] && tree.contains(i)) {
					failed = true;
					cerr << "ERROR:" << i << " in the tree !\n";
					break;
				}
			}
		}
		CHECK(!failed); 
	}
	
	CHECK_END;
}
