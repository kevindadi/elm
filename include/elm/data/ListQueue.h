/*
 *	ListQueue class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2015, IRIT UPS.
 *
 *	ELM is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	ELM is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with ELM; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#ifndef ELM_DATA_LISTQUEUE_H_
#define ELM_DATA_LISTQUEUE_H_

#include <elm/assert.h>
#include <elm/compare.h>
#include <elm/inhstruct/SLList.h>

namespace elm {

template <class T, class E = Equiv<T> >
class ListQueue {

	typedef struct node_t  {
		inline node_t(const T& v, node_t *n = 0): next(n), val(v) { }
		node_t *next;
		T val;
	} node_t;

public:
	inline ListQueue(void): h(0), t(0) { }
	inline ~ListQueue(void) { reset(); }

	inline bool isEmpty(void) const { return !h; }
	inline const T &head(void) const { ASSERTP(h, "empty queue"); return h->val; }
	inline T get(void)
		{ ASSERTP(h, "empty queue"); T r = h->val; node_t *n = h; h = h->next; if(!h) t = 0; delete n; return r; }

	inline void put(const T &item)
		{ node_t *n = new node_t(item); (h ? t->next : h) = n; t = n; }
	inline void reset(void)
		{ for(node_t *n = h, *nn; n; n = nn) { nn = n->next; delete n; } }

	inline operator bool(void) const { return !isEmpty(); }
	inline ListQueue& operator<<(const T& v) { put(v); return *this; }
	inline ListQueue& operator>>(T& v) { v = get(); return *this; }

private:
	node_t *h, *t;
};

}	// elm

#endif /* ELM_DATA_LISTQUEUE_H_ */
