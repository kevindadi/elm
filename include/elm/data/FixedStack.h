/*
 *	FixedStack class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2019, IRIT UPS.
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
#ifndef ELM_DATA_FIXEDSTACK_H_
#define ELM_DATA_FIXEDSTACK_H_

#include <elm/assert.h>
#include <elm/equiv.h>

namespace elm {

template <class T, int S, class E = Equiv<T> >
class FixedStack {
public:
	inline FixedStack(): t(0) { }

	inline bool isEmpty() const { return t == 0; }
	inline bool isFull() const { return t == S; }
	inline const T& top() const { ASSERT(t > 0); return s[t - 1]; }

	inline void reset() { t = 0; }
	inline T pop() { ASSERT(t > 0); t--; return s[t]; }
	inline void push(const T& x) { ASSERT(t < S); s[t] = x; }

private:
	int t;
	T s[S];
};

}	// elm

#endif /* INCLUDE_ELM_DATA_FIXEDSTACK_H_ */
