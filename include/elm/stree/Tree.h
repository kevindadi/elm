/*
 *	stree::Tree class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2013, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef ELM_STREE_TREE_H_
#define ELM_STREE_TREE_H_

#include <elm/util/Comparator.h>
#include <elm/PreIterator.h>
#include <elm/genstruct/AVLTree.h>

namespace elm { namespace stree {

/*template <class T>
class AsIs {
public:
	typedef T item_t;
	typedef T store_t;
	void add(const store_t& store, const item_t& item) { store = item; }
};*/

// Tree class
template <class K, class T, class C = Comparator<K> >
class Tree {
	static const int null = -1;

public:
	typedef struct node_t {
		inline node_t(void) { }
		inline node_t(struct node_t s[], int _ll, int _rl)
			: lb(s[_ll].lb), ub(s[_rl].ub), ll(_ll), rl(_rl) { }
		inline node_t(const K& _lb, const K& _ub)
			: lb(_lb), ub(_ub), ll(null), rl(null) { }
		inline bool isLeaf(void) const { return ll == null; }
		inline int left(void) const { return ll; }
		inline int right(void) const { return rl; }
		inline const K& lowerBound(void) const { return lb; }
		inline const K& upperBound(void) const { return ub; }
		K lb, ub;
		int ll, rl;
		T data;
	} node_t;

	inline Tree(void): root(-1), nodes(0) { }
	inline Tree(int _root, node_t *_nodes): root(_root), nodes(_nodes) { }
	inline void set(int _root, node_t *_nodes) { root = _root; nodes = _nodes; }

		/*genstruct::AVLTree<K, C> tree;

		// build the bounds
		for(segment_list_t item = list; item; item = item->next) {
			tree.add(item->lb);
			tree.add(item->ub);
		}

		// allocate the memory
		t::uint32 n = tree.count();
		int s = n + leastUpperPowerOf2(n) - 1;
		nodes = new node_t[s];

		// insert the bounds
		int i = 0;
		typename genstruct::AVLTree<K, C>::Iterator iter(tree);
		K l = *iter;
		for(iter++; iter; iter++) {
			K u = *iter;
			nodes[i++] = node_t(l, u);
			l = u;
		}
		root = make(i, 0, i - 1);

		// insert the segments
		for(segment_list_t item = list; item; item = item->next)
			insert(root, item->lb, item->ub, item->val);
	}*/

	~Tree(void) {
		delete [] nodes;
	}

	T& find(const K& key) const {
		int i = root;
		while(!nodes[i].isLeaf()) {
			if(C::compare(key, nodes[nodes[i].right()].lowerBound()) < 0)
				i = nodes[i].left();
			else
				i = nodes[i].right();
		}
		return nodes[i].data;
	}

private:

	/*int make(int& s, int start, int end) {
		if(start == end)
			return start;
		else {
			int m = (start + end) / 2,
				l = make(s, start, m),
				u = make(s, m + 1, end);
			int p = s;
			nodes[s++] = node_t(nodes[start].lb, nodes[end].ub, l, u);
			return p;
		}
	}

	void insert(int c, const K& l, const K& u, const typename T::t& v) {
		if(nodes[c].isLeaf())
			T::set(nodes[c].data, v);
		else {
		}
	}*/

	int root;
	node_t *nodes;
};

// SegmentTreeBuilder class
/*template <class K, class T, class C = Comparator<K> >
class SegmentTreeBuilder {
public:
protected:
};*/

} }	// elm::stree

#endif /* ELM_STREE_TREE_H_ */
