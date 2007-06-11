/*
 * $Id$
 * Copyright (c) 2007, IRIT-UPS <casse@irit.fr>
 *
 * AutoComparator and AutoPartialComparator classes
 */
#ifndef ELM_UTIL_AUTO_COMPARATOR_H
#define ELM_UTIL_AITO_COMPARATOR_H

#include <elm/assert.h>

namespace elm {

// AutoComparator template
template <class T>
class AutoComparator {
public:
	inline int _compare(const T& v) const { return ((T*)this)->compare(v); }
	inline bool operator==(const T& v) const { return _compare(v) == 0; }
	inline bool operator!=(const T& v) const { return _compare(v) != 0; }
	inline bool operator<(const T& v) const { return _compare(v) < 0; }
	inline bool operator<=(const T& v) const { return _compare(v) <= 0; }
	inline bool operator>(const T& v) const { return _compare(v) > 0; }
	inline bool operator>=(const T& v) const { return _compare(v) >= 0; }
};

// AutoComparator template
template <class T>
class AutoPartialComparator {
public:
	inline int _compare(const T& v) const { return ((T*)this)->compare(v); }
	inline int _equals(const T& v) const { return ((T*)this)->equals(v); }
	inline bool operator==(const T& v) const { return _equals(v); }
	inline bool operator!=(const T& v) const { return !_equals(v); }
	inline bool operator<(const T& v) const { return _compare(v) < 0; }
	inline bool operator<=(const T& v) const { return _compare(v) <= 0; }
	inline bool operator>(const T& v) const { return _compare(v) > 0; }
	inline bool operator>=(const T& v) const { return _compare(v) >= 0; }
};
} // elm

#endif // ELM_UTIL_AUTO_COMPARATOR_H
