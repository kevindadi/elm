/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * SortedSet.h -- interface implementing sorted sets.
 */
#ifndef ELM_DATASTRUCT_SORTEDSET_H
#define ELM_DATASTRUCT_SORTEDSET_H

#include <elm/datastruct/Collection.h>

namespace elm { namespace datastruct {

// SortedSet class
template <class T> class SortedSet {
public:
	virtual bool isEmpty(void) const = 0;
	virtual int count(void) const = 0;
	virtual bool contains(const T value) const = 0;

	virtual void insert(const T value) = 0;
	virtual void remove(const T value) = 0;

	virtual IteratorInst<T> *items() const = 0;
	virtual Collection<T>& toColl(void) const = 0;
	inline operator Collection<T>&(void) const = 0;
};

} }	// elm::datastruct

#endif	// ELM_DATASTRUCT_SORTEDSET_H
