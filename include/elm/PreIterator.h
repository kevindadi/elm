/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * PreIterator template class
 */
#ifndef ELM_PREITERATOR_H
#define ELM_PREITERATOR_H

namespace elm {

// PreIterator class
template <class I, class T>
class PreIterator {
public:
	inline operator bool(void) const
		{ return !((I *)this)->ended(); }
	inline operator T(void) const
		{ return ((I *)this)->item(); }
	inline I& operator++(void)
		{ ((I *)this)->next(); return *(I *)this; }
	inline I& operator++(int)
		{ ((I *)this)->next(); return *(I *)this; }
	inline T operator*(void) const
		{ return ((I *)this)->item(); }
	inline T operator->(void) const
		{ return ((I *)this)->item(); }
};

} // elm

#endif	// ELM_PREITERATOR_H
