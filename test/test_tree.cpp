#include <elm/inhstruct/Tree.h>
#include <elm/util/test.h>

using namespace elm;
using namespace elm::inhstruct;

int main(void) {
	CHECK_BEGIN("inhstruct_Tree")
	
	cerr << "INFO: sizeof(Tree<>) = " << sizeof(Tree<>) << io::endl;
	cerr << "INFO: sizeof(Tree<BackTreeFeature>) = " << sizeof(Tree<BackTreeFeature>) << io::endl;
	
	// simple tree
	{
		Tree<> *t1 = new Tree<>;
		Tree<> *t2 = new Tree<>;
		Tree<> *t3 = new Tree<>;
		t1->add(t2);
		t1->add(t3);
		CHECK(!t1->isEmpty());
		Tree<>::Iterator child(t1);
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

	// back tree
	{
		typedef Tree<BackTreeFeature> t;
		t *t1 = new t();
		t *t2 = new t();
		t *t3 = new t();
		t1->add(t2);
		t2->add(t3);
		CHECK(t1->parent() == 0);
		CHECK(t2->parent() == t1);
		CHECK(t3->parent() == t2);
	}
	
	CHECK_END
}
