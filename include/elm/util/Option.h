/*
 *	Option class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006, IRIT UPS.
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
#ifndef ELM_UTIL_OPTION_H
#define ELM_UTIL_OPTION_H

#include <elm/assert.h>
#include <elm/type_info.h>

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
	inline Option(T value): one(true) { type_info<T>::put(val, value); }
	inline Option(const Option<T> &opt): one(opt.one), val(opt.val) { }
	inline bool isOne(void) const { return one; }
	inline bool isNone(void) const { return !one; }
	inline T value(void) const
		{ ASSERTP(one, "no value in option"); return type_info<T>::get(val); }
	
	inline operator bool(void) const { return isOne(); }
	inline T operator*(void) const { return value(); }
	inline operator T(void) const { return value(); }
	inline Option<T>& operator=(const Option<T>& opt)
		{ one = opt.one; if(one) val = opt.val; return *this; }
	inline Option<T>& operator=(T value)
		{ one = true; type_info<T>::put(val, value); return *this; }
	inline bool equals(const OptionalNone& none) const { return isNone(); }
	inline bool equals(const Option<T> &opt) const
		{ return (this->isNone() && opt.isNone()) || (this->isOne() && opt.isOne() && val == opt.val); }

	template <class F> const Option<T>& if_one(const F& f) { if(one) f(val); return *this; }
	template <class F> const Option<T>& if_else(const F& f) { if(!one) f(val); return *this; }

	inline bool operator==(const OptionalNone& _) const { return isNone(); }
	inline bool operator!=(const OptionalNone& _) const { return !isNone(); }
	inline bool operator==(const Option<T>& o) const { return !isNone() && !o.isNone() && val == o.val; }
	inline bool operator!=(const Option<T>& o) const { return !operator==(o); }

private:
	bool one;
	typename type_info<T>::embed_t val;
};


// Fast Option building
template <class T>
inline Option<T> some(T val) { return Option<T>(val); };

} // elm

#endif /* ELM_UTIL_OPTION_H */
