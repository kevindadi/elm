/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * utility.h -- useful classes interfaces.
 */
#ifndef ELM_UTILITY_H
#define ELM_UTILITY_H

#include <assert.h>
#include <elm/string.h>
#include <elm/util/Option.h>
#include <elm/util/Pair.h>
#include <elm/util/MessageException.h>
//#include <elm/util/HashKey.h>

namespace elm {

// Comparator class
template <class T> class Comparator {
public:
	static Comparator<T>& def;
	virtual int compare(T v1, T v2) = 0;
};

};	// elm

#endif	// ELM_UTILITY_H
