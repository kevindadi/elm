/*
 *	Data Manager classes
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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
#ifndef ELM_DATA_MANAGER_H_
#define ELM_DATA_MANAGER_H_

#include <elm/compare.h>
#include <elm/util/Equiv.h>
#include <elm/alloc/DefaultAllocator.h>

namespace elm {

// EquivManager class
template <class T, class E = Equiv<T>, class A = DefaultAllocator>
class EquivManager {
public:
	inline EquivManager(void): alloc(DefaultAllocator::DEFAULT) { }
	E eq;
	A& alloc;
	static EquivManager def;
};
template <class T, class E, class A> EquivManager<T, E, A> EquivManager<T, E, A>::def;

// CompareManager class
template <class T, class C = Comparator<T>, class A = DefaultAllocator>
class CompareManager {
public:
	inline CompareManager(void): alloc(DefaultAllocator::DEFAULT) { }
	C cmp;
	A& alloc;
	static CompareManager def;
};
template <class T, class C, class A> CompareManager<T, C, A> CompareManager<T, C, A>::def;

}	// elm

#endif /* ELM_DATA_MANAGER_H_ */
