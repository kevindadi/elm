/*
 *	BinomialQeue test
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2021, IRIT UPS.
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

#include <elm/io.h>
#include <elm/data/Array.h>
#include <elm/data/quicksort.h>
#include <elm/test.h>

#define TEST_BINOMIAL_QUEUE
#include <elm/data/BinomialQueue.h>

using namespace elm;

template <class T, class C, class A>
void BinomialQueue<T, C, A>::dump(io::Output& out) {
	out << "digraph BinomialQueu {" << io::endl;
	if(_min != nullptr)
		out << "node \"" << _min->x << "\" [shape=doublecircle];" << io::endl;
	dump_rec(out, _head);
	out << "}" << io::endl;
}

template <class T, class C, class A>
void BinomialQueue<T, C, A>::dump_rec(io::Output& out, Node *node) {
	if(node->child != nullptr) {
		out << '"' << node->x << "\" -> \"" << node->child->x << "\";" << io::endl;
		dump_rec(out, node->child);
	}
	if(node->next != nullptr) {
		out << '"' << node->x << "\" -> \"" << node->next->x << "\" [style=dashed];" << io::endl;
		dump_rec(out, node->next);
	}
}


// Entry point
TEST_BEGIN(binomial_queue)

	{
		int T[] = {
			24,		16,		9,		7,
			25,		13,		5,		6,
			26,		21,		117,	102,
			108,	125,	107,	118,
			111,	115,	120,	121,
			109,	105,	123,	110,
			114,	101,	106,	18,
			14
		};
		int N = sizeof(T) / sizeof(int);
		Array<int> A(N, T);
		BinomialQueue<int> q;
		CHECK(q.isEmpty());

		for(int i = 0; i < N; i++)
			q.put(T[i]);
		CHECK(!q.isEmpty());

		quicksort(A);
		bool ok = true;
		for(int i = 0; i < N && ok; i++)
			ok = !q.isEmpty() || T[i] != q.get();
		CHECK(ok);
	}

{
	int T[] = {
		113,	124,	112,	103,
		104,	122,	119,	2,
		20,		12,		10,		3,
		17,		23,		19,		0,
		22,		4,		1,		8,
		15,		11,		100,	116
	};
	int N = sizeof(T) / sizeof(int);
	Array<int> A(N, T);
	BinomialQueue<int> q;
	CHECK(q.isEmpty());

	for(int i = 0; i < N; i++)
		q.put(T[i]);
	CHECK(!q.isEmpty());

	quicksort(A);
	bool ok = true;
	for(int i = 0; i < N && ok; i++)
		ok = !q.isEmpty() || T[i] != q.get();
	CHECK(ok);
}

TEST_END
