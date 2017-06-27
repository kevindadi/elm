#include <elm/inhstruct/Tree.h>
#include <elm/data/Tree.h>
#include "../include/elm/test.h"

using namespace elm;

	// simple tree
TEST_BEGIN(tree)
	{
		inhstruct::Tree *t1 = new inhstruct::Tree;
		inhstruct::Tree *t2 = new inhstruct::Tree;
		inhstruct::Tree *t3 = new inhstruct::Tree;
		t1->add(t2);
		t1->add(t3);
		CHECK(!t1->isEmpty());
		inhstruct::Tree::Iterator child(t1);
		CHECK(child == true); 
		CHECK(child == t3);
		child++;
		CHECK(child == true); 
		CHECK(child == t2);
		child++;	
		CHECK(child == false); 
		t1->remove(t3);
		t1->remove(t2);
		CHECK(t1->isEmpty());
	}

	// generic tree
	{
		typedef elm::Tree<string> tree_t;
		tree_t *t1 = new tree_t("1");
		tree_t *t2 = new tree_t("2");
		tree_t *t3 = new tree_t("3");
		t1->add(t2);
		t1->add(t3);
		CHECK(!t1->isEmpty());
		tree_t::Iterator child(t1);
		CHECK(child == true); 
		CHECK(child == "3");
		child++;
		CHECK(child == true); 
		CHECK(child == "2");
		child++;	
		CHECK(child == false); 
		t1->remove(t3);
		t1->remove(t2);
		CHECK(t1->isEmpty());
	}

TEST_END
