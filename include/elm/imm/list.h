/*
 *	imm::List class interface
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
#ifndef ELM_IMM_LIST_H_
#define ELM_IMM_LIST_H_

#include <elm/assert.h>
#include <elm/alloc/DefaultAllocator.h>
#include <elm/alloc/BlockAllocatorWithGC.h>

namespace elm { namespace imm {

template <class T>
class list {
	typedef struct node_t {
		inline node_t(const T& _h, node_t *_t = 0): h(_h), t(_t) { }
		T h;
		list<T *> t;
	} node_t;
	inline list(node_t *n): node(node) { }
	friend class list_man;
	friend class list_gc;
public:
	inline list<T> null(void) { return list<T>(); }
	inline list(void): node(0) { }
	inline list(const list& l): node(l.node) { }
	inline list& operator=(const list& l) { node = l.node; return *this; }

	inline const T& hd(void) const { ASSERT(node); return node->h; }
	inline const T& operator*(void) const { return hd(); }
	inline list<T> *tl(void) const { ASSERT(node); return node->t; }
	inline operator bool(void) const { return node; }

	inline int length(void) const
		{ int c = 0; list<T> n = *this; while(n) { c++; n = n.tl(); } return c; }

private:
	node_t *node;
};

template <class T, class A = DefaultAllocator>
class ListAllocator {
	typedef typename list<T>::node_t node_t;
public:
	inline ListAllocator(A& allocator = A::DEFAULT): alloc(allocator) { }
	inline list<T> cons(const T& h, list<T> tl)
		{ node_t *n = (node_t *)alloc.allocate(sizeof(node_t)); n->h = h; n->t = tl->node; return new list<T>(n); }
	inline void free(list<T> l) { if(l->node) free(l->node); }
	inline void freeAll(list<T> l) { node_t *n = l->node; while(n) { node_t *nn = n->t; free(n); n = nn; } }
private:
	A& alloc;
};

template <class T>
class ListGC: public BlockAllocatorWithGC<typename list<T>::node_t > {
	typedef typename list<T>::node_t node_t;
public:
	inline list<T> cons(const T& h, list<T> tl)
		{ node_t *n = BlockAllocatorWithGC<node_t>::allocate(); n->h = h; n->t = tl->node; return new list<T>(n); }
protected:
	void mark(list<T> l) { node_t *n = l->node; while(n && !mark(n)) n = n->t; }
};

} }	// elm::imm

#endif /* ELM_IMM_LIST_H_ */
