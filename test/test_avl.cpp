/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * test/test_avl.cpp -- AVLTree class test.
 */

#define ELM_DEBUG_AVL

#include <elm/util/test.h>
#include <elm/genstruct/Vector.h>
#include <elm/avl/Set.h>
#include <elm/avl/Map.h>
#include <elm/genstruct/HashTable.h>
#include <elm/system/System.h>
#include <elm/io.h>
 
using namespace elm;
using namespace elm::avl;

#ifdef ELM_DEBUG_AVL
#	define LOG(cmd)	// cmd
#endif

static const int maxv = 1000;
static const int count = 1000;

// Entry point
TEST_BEGIN(avl)
	
	// unit test
	{
		Set<int> tree;
		CHECK(tree.isEmpty());
		tree.add(100);
		CHECK(!tree.isEmpty());
		CHECK(tree.contains(100));
		CHECK(!tree.contains(0));
	}

	// check AVLTree
	{
		genstruct::Vector<int> ints;
		Set<int> tree;
		bool intensive = true;
		
		for(int i = 0; intensive && i < count; i++) {
			LOG(tree.dump(cerr); cerr << io::endl;)
			int a = system::System::random(maxv * 3);

			// remove
			if(a < 2 * maxv && ints.count()) {
				int n = ints[a % ints.count()];
				LOG(cerr << "removing " << ints[a % ints.count()] << io::endl;)
				ints.remove(n);
				tree.remove(n);
				intensive = !tree.contains(n);
			}

			// insert
			else if(a < maxv) {
				int n = a % maxv;
				LOG(cerr << "adding " << n << io::endl;)
				if(!ints.contains(n))
					ints.add(n);
				tree.add(n);
				intensive = tree.contains(n);
			}

			// check
			else {
				bool ok = true;
				for(int i = 0; i < ints.count(); i++)
					if(!tree.contains(ints[i]))
						ok = false;
				intensive = ok;
			}
		}
		CHECK(intensive);
	}
	
	// AVLMap
	{
		Map<string, int> map;
		Option<int> r = map.get("ok");
		CHECK(!r);

		genstruct::HashTable<string, int> htab;

		bool map_intensive = true;
		for(int i = 0; map_intensive && i < count; i++) {
			int a = system::System::random(maxv * 4);

			// remove
			if(a < 2 * maxv && !htab.isEmpty()) {
				int n = a % htab.count();
				string kk;
				for(genstruct::HashTable<string, int>::KeyIterator k(htab); n >= 0; k++, n--)
					kk = k;
				map.remove(kk);
				htab.remove(kk);
				map_intensive = !map.hasKey(kk);
			}

			// insert
			else if(a < maxv) {
				int n = a % maxv;
				string k = _ << n;
				htab.put(k, n);
				map.put(k, n);
				map_intensive = map.get(k) == n;
			}

			// contains
			else if(a < 2 * maxv) {
				int n = a % maxv;
				string k = _ << n;
				map_intensive = htab.get(k, -1) == map.get(k, -1);
			}

			// check
			else {
				bool ok = true;
				for(genstruct::HashTable<string, int>::KeyIterator k(htab); k; k++)
					if(htab.get(k, -1) != map.get(k, -1)) {
						ok = false;
						break;
					}
				map_intensive = ok;
			}
		}
		CHECK(map_intensive);
	}

TEST_END

