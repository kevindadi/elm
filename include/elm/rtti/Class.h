/*
 *	AbstractClass and Class classes interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2007, IRIT UPS.
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
#ifndef ELM_RTTI_CLASS_H_
#define ELM_RTTI_CLASS_H_

#include "Type.h"

namespace elm { namespace rtti {

// AbstractClass class
class AbstractClass: public rtti::Type {
public:
	AbstractClass(CString name, AbstractClass *base);
	inline AbstractClass *base(void) const { return _base; };
	virtual void *instantiate(void) = 0;
	bool baseOf(AbstractClass *clazz);
	virtual bool isClass(void) const;
	virtual const AbstractClass *asClass(void) const;
private:
	AbstractClass *_base;
};


// Class class
template <class T>
class Class: public AbstractClass {
public:
	inline Class(CString name, AbstractClass *base = 0)
		: AbstractClass(name, base) { };
	virtual void *instantiate(void) { return new T; };
};

} }	// elm::rtti

#endif /* ELM_RTTI_CLASS_H_ */
