/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/StrongType.h -- interface of StrongType class.
 */
#ifndef ELM_UTIL_STRONG_TYPE_H
#define ELM_UTIL_STRONG_TYPE_H

namespace elm {

// StrongType template
template <class T>
class StrongType {
public:
	T v;
	inline StrongType(T _v = 0): v(_v) { };
	inline operator const T&(void) const { return v; };
	inline operator T&(void) { return v; };
	inline StrongType<T>& operator=(T _v) { v = _v; return *this; };
};

} // elm

#endif // ELM_UTIL_STRONG_TYPE_H

