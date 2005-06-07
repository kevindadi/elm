/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * test_dllist.cpp -- unit tests for DLList class.
 */

#include <elm/util/test.h>
#include <elm/datastruct/DLList.h>

using namespace elm;

// MyDLNode class
class MyDLNode: public inhstruct::DLNode {
public:
	int v;
	inline MyDLNode(int _v): v(_v) {
	};
};



// Test
void test_dllist(void) {
	CHECK_BEGIN("elm::datastruct::DLList");
	
	// Base tests
	{
		datastruct::DLList<int> l;
		CHECK(l.isEmpty());
		l.addLast(666);
		CHECK(!l.isEmpty());
		CHECK(l.count() == 1);
		CHECK(l.contains(666));
		CHECK(!l.contains(111));
		l.addLast(111);
		CHECK(!l.isEmpty());
		CHECK(l.count() == 2);
		CHECK(l.contains(666));
		CHECK(l.contains(111));
	}
	
	// Removal tests
	{
		datastruct::DLList<int> l;
		l.addLast(0);
		l.addLast(1);
		l.addLast(2);
		CHECK(l.count() == 3);
		l.remove(1);
		CHECK(l.count() == 2);
		CHECK(l.contains(0));
		CHECK(!l.contains(1));
		CHECK(l.contains(2));
		l.remove(2);
		CHECK(l.count() == 1);
		CHECK(l.contains(0));
		CHECK(!l.contains(1));
		CHECK(!l.contains(2));
		l.remove(0);
		CHECK(l.count() == 0);
		CHECK(!l.contains(0));
		CHECK(!l.contains(1));
		CHECK(!l.contains(2));
	}
	
	// Iterator test
	{
		datastruct::DLList<int> l;
		l.addLast(0);
		l.addLast(1);
		l.addLast(2);
		l.addLast(3);
		l.addLast(4);
		CHECK(l.count() == 5);
		int i = 0;
		for(Iterator<int> iter(l); iter; iter++, i++)
			CHECK(*iter == i);
	}
	
	// Bi-directionnal walk test
	{
		inhstruct::DLList list;
		list.addLast(new MyDLNode(0));
		list.addLast(new MyDLNode(1));
		list.addLast(new MyDLNode(2));
		CHECK(list.count() == 3);
		int cnt = 0;
		for(MyDLNode *node = (MyDLNode *)list.first(); !node->atEnd();
		node = (MyDLNode *)node->next(), cnt++)
			CHECK(node->v == cnt);
		CHECK(cnt == 3);
		cnt--;
		for(MyDLNode *node = (MyDLNode *)list.last(); !node->atBegin();
		node = (MyDLNode *)node->previous(), cnt--)
			CHECK(node->v == cnt);
		CHECK(cnt == -1);
	}
	
	// Insert before and efter tests
	{
		inhstruct::DLList list;
		list.addLast(new MyDLNode(0));
		list.addLast(new MyDLNode(2));
		list.addLast(new MyDLNode(4));
		inhstruct::DLNode *node = list.first();
		CHECK(!node->atEnd());
		node = node->next();
		CHECK(!node->atEnd());
		node->insertBefore(new MyDLNode(1));
		node->insertAfter(new MyDLNode(3));
		int cnt = 0;
		for(MyDLNode *node = (MyDLNode *)list.first(); !node->atEnd();
		node = (MyDLNode *)node->next(), cnt++)
			CHECK(node->v == cnt);
		CHECK(cnt == 5);
		cnt--;
		for(MyDLNode *node = (MyDLNode *)list.last(); !node->atBegin();
		node = (MyDLNode *)node->previous(), cnt--)
			CHECK(node->v == cnt);
		CHECK(cnt == -1);		
	}
	
	CHECK_END;
}


