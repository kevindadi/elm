/*
 *	BinomialQueue class
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

#include <elm/data/BinomialQueue.h>

namespace elm {

/**
 * @class BinomialQueue
 *
 * Implements the binomial priority queue.
 *
 * The performance of the queue are:
 * * pick - O(1)
 * * take - O(log n)
 * * put - O(1) (amortized)
 * * memory - for each element, 2 pointers and 1 integer are required.
 *
 * @param T		Type of elements in the queue.
 * @param C		Comparator type (default to elm::Comparator).
 * @param A		Allocator type (default to elm::DefaultAllocatorDelegate).
 *
 * @ingroup data
 */

/**
 * @fn BinomialQueue::BinomialQueue(const C& c, const A& a);
 * Build a binomial queue.
 * @param c		Comparator instance to use.
 * @param a		Allocator delegate instance.
 */

}	// elm
