/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/Class.h -- Class class interface.
 */
#ifndef ELM_UTIL_CLASS_H
#define ELM_UTIL_CLASS_H

#include <elm/string.h>

namespace elm {

// Class class
class Class {
	CString _name;
	Class *_base;
public:
	inline Class(CString name, Class *base = 0): _name(name), _base(base) { };
	inline CString name(void) const { return _name; };
	inline Class *base(void) const { return _base; };
	virtual void *instantiate(void) = 0;
};

// GenClass class
template <class T>
class GenClass: public Class {
public:
	inline GenClass(CString name, Class *base = 0): Class(name, base) { };
	virtual void *instantiate(void) { return new T; }; 
};

} // elm

#endif	// ELM_UTIL_CLASS_H
