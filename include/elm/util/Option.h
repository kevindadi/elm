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
public:
	inline Option(void): one(false) { }
	inline Option(const OptionalNone& none): one(false) { }
	inline Option(const T& value): one(true), val(value) { }
	inline Option(const Option<T> &opt): one(opt.one), val(opt.val) { }
	inline bool isOne(void) const { return one; }
	inline bool isNone(void) const { return !one; }
	inline const T& value(void) const { return val; }
	
	inline operator bool(void) const { return isOne(); }
	inline const T& operator*(void) const { return val; }
	inline operator const T&(void) const { return val; }
	inline Option<T>& operator=(const Option<T>& opt)
		{ one = opt.one; val = opt.val; return *this; }
	inline Option<T>& operator=(const T& value)
		{ one = true; val = value; return *this; }

private:
	bool one;
	T val;
};


// Fast Option building
template <class T>
inline Option<T> some(const T& val) { return Option<T>(val); };

} // elm

#endif /* ELM_UTIL_OPTION_H */
