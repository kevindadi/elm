/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS <casse@irit.fr>.
 *
 * elm/util/Option.h -- interface for Option class.
 */
#ifndef ELM_UTIL_OPTION_H
#define ELM_UTIL_OPTION_H

namespace elm {

// OptionalNone value
class OptionalNone {
};
extern const OptionalNone none;


// Optional value
template <class T> class Option {
	bool one;
	T val;
public:
	// Constructors
	inline Option(void);
	inline Option(const OptionalNone& none);
	inline Option(const T& value);
	inline Option(const Option<T> &opt);
	
	// Accessors
	inline bool isOne(void) const;
	inline bool isNone(void) const;
	inline T value(void) const;
	
	// Operators
	inline operator bool(void) const;
	inline T operator*(void) const;
	inline operator T(void) const;
	inline Option<T>& operator=(const Option<T>& opt);
	inline Option<T>& operator=(const T& value);
};


// Fast Option building
template <class T>
inline Option<T> some(const T& val) { return Option<T>(val); };


// Option<T> inlines
template <class T>
inline Option<T>::Option(void): one(false) {
}

template <class T>
inline Option<T>::Option(const OptionalNone& none): one(false) {
}

template <class T>
inline Option<T>::Option(const T& value): one(true), val(value) {
}

template <class T>
inline Option<T>::Option(const Option<T> &opt): one(opt.one), val(opt.val) {
}

template <class T>
inline bool Option<T>::isOne(void) const {
	return one;
}

template <class T>
inline bool Option<T>::isNone(void) const {
	return !one;
}

template <class T>
inline T Option<T>::value(void) const {
	return val;
}

template <class T>
inline Option<T>::operator bool(void) const {
	return one;
}

template <class T>
inline T Option<T>::operator*(void) const {
	return val;
}

template <class T>
inline Option<T>::operator T(void) const {
	return val;
}

template <class T>
inline Option<T>& Option<T>::operator=(const Option<T>& opt) {
	one = opt.one;
	val = opt.val;
}

template <class T>
inline Option<T>& Option<T>::operator=(const T& value) {
	one = true;
	val = value;
}

} // elm

#endif /* ELM_UTIL_OPTION_H */
