/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * test/test_avl.cpp -- AVLTree class test.
 */

#include <elm/util/test.h>
#include <elm/genstruct/Vector.h>
#include <elm/genstruct/AVLTree.h>
#include <elm/genstruct/AVLMap.h>
#include <elm/genstruct/HashTable.h>
#include <elm/system/System.h>
#include <elm/io.h>
 
using namespace elm;

static const int maxv = 1000;
static const int count = 1000;

// Entry point
void test_avl(void) {
	CHECK_BEGIN("avltree");
	
	// check AVLTree
	{
		genstruct::Vector<int> ints;
		genstruct::AVLTree<int> tree;
		
		for(int i = 0; i < count; i++) {
			int a = system::System::random(maxv * 3);

			// remove
			if(a < 2 * maxv && ints.count()) {
				int n = ints[a % ints.count()];
				ints.remove(n);
				tree.remove(n);
				CHECK(!tree.contains(n));
			}

			// insert
			else if(a < maxv) {
				int n = a % maxv;
				if(!ints.contains(n))
					ints.add(n);
				tree.add(n);
				CHECK(tree.contains(n));
			}

			// check
			else {
				bool ok = true;
				for(int i = 0; i < ints.count(); i++)
					if(!tree.contains(ints[i])) {
						ok = false;
					}
				CHECK(ok);
			}
		}
	}
	
	// AVLMap
	{
		genstruct::AVLMap<string, int> map;
		genstruct::HashTable<string, int> htab;
		for(int i = 0; i < count; i++) {
			int a = system::System::random(maxv * 4);

			// remove
			if(a < 2 * maxv && !htab.isEmpty()) {
				int n = a % htab.count();
				string kk;
				for(genstruct::HashTable<string, int>::KeyIterator k(htab); n >= 0; k++, n--)
					kk = k;
				map.remove(kk);
				htab.remove(kk);
				CHECK(!map.hasKey(kk));
			}

			// insert
			else if(a < maxv) {
				int n = a % maxv;
				string k = _ << n;
				htab.put(k, n);
				map.put(k, n);
				CHECK(map.get(k) == n);
			}

			// contains
			else if(a < 2 * maxv) {
				int n = a % maxv;
				string k = _ << n;
				CHECK(htab.get(k, -1) == map.get(k, -1));
			}

			// check
			else {
				bool ok = true;
				for(genstruct::HashTable<string, int>::KeyIterator k(htab); k; k++)
					if(htab.get(k, -1) != map.get(k, -1)) {
						ok = false;
						break;
					}
				CHECK(ok);
			}
		}
	}

	CHECK_END;
}
