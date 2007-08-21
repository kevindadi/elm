/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * utility.h -- useful classes interfaces.
 */
#ifndef ELM_UTILITY_H
#define ELM_UTILITY_H

#include <elm/string.h>
#include <elm/util/Option.h>
#include <elm/util/Pair.h>
#include <elm/util/MessageException.h>
//#include <elm/util/HashKey.h>

namespace elm {

// Comparator class
template <class T>
class Comparator {
public:
	static int compare(const T& v1, const T& v2);
};

// Specific comparator implementation
template <>
class Comparator<int> {
public:
	static int compare(int v1, int v2) { return v1 - v2; }
};

};	// elm

#endif	// ELM_UTILITY_H
