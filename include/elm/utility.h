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

namespace elm {

// Exception class
class Exception {
public:
	virtual ~Exception(void) { };
	virtual String message(void) = 0;
};


// Error class
class Error: public Exception {
};


// HashKey class
template <class T> class HashKey {
public:
	static HashKey<T>& def;
	virtual unsigned long hash(T key) = 0;
	virtual bool equals(T key1, T key2) = 0;
};


// Comparator class
template <class T> class Comparator {
public:
	static Comparator<T>& def;
	virtual int compare(T v1, T v2) = 0;
};

};	// elm

#endif	// ELM_UTILITY_H
