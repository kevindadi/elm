/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test_sorted_bintree.cpp -- unit tests for SortedBinTree class.
 */

#include <elm/util/test.h>
#include <elm/genstruct/SortedBinTree.h>

using namespace elm;


// Visitor class
class MyVisitor: public genstruct::SortedBinTree<int>::Visitor {
public:
	int count;
	bool equal;
	inline MyVisitor(void): count(0), equal(true) {
	};
	virtual int process(int value) {
		equal = equal && (count == value);
		count++;
	};
};


// test routine
void test_sorted_bintree(void) {
	CHECK_BEGIN("SortedBinTree");
	
	// Base test
	{
		genstruct::SortedBinTree<int> tree;
		tree.insert(5);
		tree.insert(0);
		tree.insert(1);
		tree.insert(2);
		tree.insert(4);
		tree.insert(3);
		CHECK(!tree.contains(10));
		CHECK(tree.contains(0));
		CHECK(tree.contains(1));
		CHECK(tree.contains(2));
		CHECK(tree.contains(3));
		CHECK(tree.contains(4));
		CHECK(tree.contains(5));
		MyVisitor visitor;
		tree.visit(&visitor);
		CHECK(visitor.count <= 6);
		CHECK(visitor.equal);
	}
	
	CHECK_END;
}
