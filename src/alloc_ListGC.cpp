/*
 *	ListGC class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2010, IRIT UPS.
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

#include <elm/alloc/ListGC.h>

namespace elm {

/**
 * @class ListGC
 * A simple garbage collector allocator from the main heap but keep trace of
 * the allocated objects to release them automatically.
 *
 * The GC is automatically triggered when the difference of the  number of
 * allocated object since the last GC cycle is bigger than a configuration
 * limit.
 *
 * @ingroup alloc
 */

class ListGC::block_t {
public:
	static const t::intptr TAG = 1;

	inline static block_t *alloc(t::size s) {
		return reinterpret_cast<block_t *>(new char[s + sizeof(block_t)]);
	}

	inline void free() {
		delete [] reinterpret_cast<char *>(this);
	}

	inline static block_t *block(void *p) {
		return reinterpret_cast<block_t *>(p) - 1;
	}

	inline void *data() { return this + 1; }
	inline void mark() { next = reinterpret_cast<block_t *>(TAG | reinterpret_cast<t::intptr>(next)); }
	inline void unmark() { next = reinterpret_cast<block_t *>(~TAG & reinterpret_cast<t::intptr>(next)); }
	inline bool isMarked() const { return (reinterpret_cast<t::intptr>(next) & TAG) != 0; }
	block_t *next;
};

/**
 * Build a list GC.
 * @param m			Current garbage collection manager.
 * @param limit		Limit triggering garbage collection.
 */
ListGC::ListGC(GCManager& m, int limit):
	AbstractGC(m),
	lcnt(0),
	cnt(0),
	lim(limit),
	head(nullptr),
	dis(false)
{ }

///
ListGC::~ListGC() {
	clean();
}

///
void *ListGC::allocate(t::size size) {
	auto p = block_t::alloc(size);
	p->next = head;
	head = p;
	cnt++;
	if(gcNeeded()) {
		lim *= 2;
		p->mark();
		runGC();
	}
	return p->data();
}

///
void ListGC::runGC() {

	// collect
	manager.collect(*this);

	// free
	auto *q = &head;
	auto p = head;
	while(p != nullptr) {
		if(p->isMarked()) {
			p->unmark();
			q = &p->next;
			p = p->next;
		}
		else {
			*q = p->next;
			manager.clean(p->data());
			p->free();
			p = *q;
			cnt--;
		}
	}

	// re-prepare auto GC
	lcnt = cnt;
}

///
bool ListGC::mark(void *data, t::size size) {
	auto b = block_t::block(data);
	bool r = b->isMarked();
	b->mark();
	return r;
}

///
void ListGC::disable() {
	dis = true;
}

///
void ListGC::enable() {
	dis = false;
	if(gcNeeded())
		runGC();
}

///
void ListGC::clean() {
	auto p = head;
	while(p != nullptr) {
		auto q = p->next;
		manager.clean(p->data());
		p->free();
		p = q;
	}
	head = nullptr;
	cnt = 0;
	lcnt = 0;
}

} // elm
