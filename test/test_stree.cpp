/*
 *	stree module test
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

#include <elm/util/test.h>
#include <elm/stree/MarkerBuilder.h>

using namespace elm;
using namespace elm::stree;

namespace elm { namespace stree {

/*template <class K, class T, class C = Comparator<K> >
class MarkerBuilder {
	typedef typename Tree<K, T, C>::node_t node_t;
public:

	void add(const K& mark, const T& val) {
		marks.put(mark, val);
	}

	void make(stree::Tree<K, T, C>& tree) {

		// allocate the memory
		node_t *nodes = allocate(marks.count());

		// insert the bounds
		int i = 0;
		typename genstruct::AVLMap<K, T, C>::Iterator iter(marks);
		Pair<K, T> l = *iter;
		for(iter++; iter; iter++) {
			Pair<K, T> u = *iter;
			nodes[i] = node_t(l.fst, u.fst);
			nodes[i++].data = l.snd;
			l = u;
		}

		// build the tree
		int root = make(nodes, i, 0, i - 1);

		// perform the transfer
		tree.set(root, nodes);
	}

protected:

	node_t *allocate(t::uint32 n) {
		int s = n + leastUpperPowerOf2(n) - 1;
		return new node_t[s];
	}

	int make(node_t *nodes, int& s, int start, int end) {
		if(start == end)
			return start;
		else {
			int m = (start + end) / 2,
				l = make(nodes, s, start, m),
				u = make(nodes, s, m + 1, end);
			int p = s;
			nodes[s++] = node_t(nodes, l, u);
			return p;
		}
	}

private:
	genstruct::AVLMap<K, T, C> marks;
};*/

} }	// elm::stree

typedef enum {
	ARM = 0,
	THUMB = 1,
	DATA = 2
} area_t;

TEST_BEGIN(stree)

	MarkerBuilder<t::uint32, area_t> builder;
	Tree<t::uint32, area_t> tree;

	// store the values
	Pair<t::uint32, area_t> marks[] = {
		pair(0U, ARM),
		pair(0x00008000U, ARM),
		pair(0x0000a910U, ARM),
		pair(0x00008020U, ARM),
		pair(0x000080a8U, ARM),
		pair(0x0000a91cU, ARM),
		pair(0x00008104U, ARM),
		pair(0x0000800cU, ARM),
		pair(0x0000a8c0U, ARM),
		pair(0x0000a8f4U, ARM),
		pair(0x00008010U, ARM),
		pair(0x00008014U, ARM),
		pair(0x0000a920U, ARM),
		pair(0x0000810cU, ARM),
		pair(0x00008218U, ARM),
		pair(0x000085c8U, ARM),
		pair(0x000085dcU, ARM),
		pair(0x00008610U, ARM),
		pair(0x00008650U, ARM),
		pair(0x000086ccU, ARM),
		pair(0x000087bcU, ARM),
		pair(0x00008864U, ARM),
		pair(0x00008910U, ARM),
		pair(0x000089d0U, ARM),
		pair(0x00008accU, ARM),
		pair(0x00008ba8U, ARM),
		pair(0x00008c78U, ARM),
		pair(0x00008d24U, ARM),
		pair(0x00008d70U, ARM),
		pair(0x00008d94U, ARM),
		pair(0x00008df0U, ARM),
		pair(0x00009094U, ARM),
		pair(0x00009180U, ARM),
		pair(0x000092f0U, ARM),
		pair(0x00009300U, ARM),
		pair(0x0000931cU, ARM),
		pair(0x00009394U, ARM),
		pair(0x000093e8U, ARM),
		pair(0x00009458U, ARM),
		pair(0x00009570U, ARM),
		pair(0x00009598U, ARM),
		pair(0x000095b0U, ARM),
		pair(0x000096b4U, ARM),
		pair(0x00009dd0U, ARM),
		pair(0x00009dd8U, ARM),
		pair(0x00009e10U, ARM),
		pair(0x00009ed4U, ARM),
		pair(0x00009f34U, ARM),
		pair(0x00009f74U, ARM),
		pair(0x00009facU, ARM),
		pair(0x0000a0b4U, ARM),
		pair(0x0000a350U, ARM),
		pair(0x0000a448U, ARM),
		pair(0x0000a6a8U, ARM),
		pair(0x0000a6e8U, ARM),
		pair(0x0000a728U, ARM),
		pair(0x0000a84cU, ARM),
		pair(0x0000a8fcU, ARM),
		pair(0x0000a90cU, ARM),
		pair(0x0000000cU, DATA),
		pair(0x00012950U, DATA),
		pair(0x0001293cU, DATA),
		pair(0x00012944U, DATA),
		pair(0x00008090U, DATA),
		pair(0x000080f0U, DATA),
		pair(0x000133b4U, DATA),
		pair(0x000133b0U, DATA),
		pair(0x00012940U, DATA),
		pair(0x00012948U, DATA),
		pair(0x0000a938U, DATA),
		pair(0x0001294cU, DATA),
		pair(0x0000a8f0U, DATA),
		pair(0x00000354U, DATA),
		pair(0x00008200U, DATA),
		pair(0x00012968U, DATA),
		pair(0x00000034U, DATA),
		pair(0x00012a68U, DATA),
		pair(0x0000838cU, DATA),
		pair(0x000085b4U, DATA),
		pair(0x000133d4U, DATA),
		pair(0x00012b68U, DATA),
		pair(0x00000010U, DATA),
		pair(0x0000860cU, DATA),
		pair(0x00000030U, DATA),
		pair(0x00008648U, DATA),
		pair(0x00000058U, DATA),
		pair(0x0000a92cU, DATA),
		pair(0x00012b78U, DATA),
		pair(0x0000a930U, DATA),
		pair(0x000086bcU, DATA),
		pair(0x00000084U, DATA),
		pair(0x000000b0U, DATA),
		pair(0x0000885cU, DATA),
		pair(0x00008908U, DATA),
		pair(0x000089c8U, DATA),
		pair(0x00008ac4U, DATA),
		pair(0x00008ba0U, DATA),
		pair(0x00008c70U, DATA),
		pair(0x00008d1cU, DATA),
		pair(0x00008d68U, DATA),
		pair(0x00008d90U, DATA),
		pair(0x00008de8U, DATA),
		pair(0x0000a934U, DATA),
		pair(0x000136d8U, DATA),
		pair(0x000000d8U, DATA),
		pair(0x00009178U, DATA),
		pair(0x000003ccU, DATA),
		pair(0x000092e8U, DATA),
		pair(0x00000400U, DATA),
		pair(0x000092fcU, DATA),
		pair(0x00000438U, DATA),
		pair(0x00009318U, DATA),
		pair(0x00009384U, DATA),
		pair(0x000093e4U, DATA),
		pair(0x00009454U, DATA),
		pair(0x0000956cU, DATA),
		pair(0x00009590U, DATA),
		pair(0x000095a8U, DATA),
		pair(0x00000458U, DATA),
		pair(0x00000574U, DATA),
		pair(0x00009dc4U, DATA),
		pair(0x00012fa0U, DATA),
		pair(0x00013788U, DATA),
		pair(0x000005c8U, DATA),
		pair(0x00000600U, DATA),
		pair(0x00009e0cU, DATA),
		pair(0x00000630U, DATA),
		pair(0x0000065cU, DATA),
		pair(0x000006dcU, DATA),
		pair(0x00009f70U, DATA),
		pair(0x000006fcU, DATA),
		pair(0x00009fa8U, DATA),
		pair(0x00000728U, DATA),
		pair(0x0000a0b0U, DATA),
		pair(0x00000754U, DATA),
		pair(0x0000a344U, DATA),
		pair(0x00000790U, DATA),
		pair(0x0000a43cU, DATA),
		pair(0x0000a694U, DATA),
		pair(0x000007d0U, DATA),
		pair(0x0000a6e4U, DATA),
		pair(0x00000820U, DATA),
		pair(0x0000a724U, DATA),
		pair(0x0000084cU, DATA),
		pair(0x0000a848U, DATA),
		pair(0x0000a8bcU, DATA),
		pair(0x00000878U, DATA),
		pair(0x0000a904U, DATA),
		pair(0x00008390U, THUMB),
		pair(0x0000a908U, THUMB),
		pair(0xffffffff, ARM)
	};
	int marks_count = sizeof(marks) / sizeof(Pair<t::uint32, area_t>);
	for(int i = 0; i < marks_count; i++)
		builder.add(marks[i].fst, marks[i].snd);
	builder.make(tree);

	// test start of content
	for(int i = 0; i < marks_count - 1; i++)
		CHECK_EQUAL(tree.find(marks[i].fst), marks[i].snd);

	// test middle of the content
	for(int i = 0; i < marks_count - 1; i++)
		CHECK_EQUAL(tree.find(marks[i].fst + 1), marks[i].snd);

TEST_END
