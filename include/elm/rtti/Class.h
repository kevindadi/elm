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

#include "type_of.h"

namespace elm { namespace rtti {

class AbstractClass: public rtti::Type {
public:
	AbstractClass(CString name, const AbstractClass& base);
	inline const AbstractClass& base(void) const { return _base; };
	virtual void *instantiate(void) const = 0;
	bool baseOf(const AbstractClass *clazz);
	virtual bool isClass(void) const;
	virtual const AbstractClass& asClass(void) const;
	virtual void *upCast(void *ptr) const;
	inline const void *upCast(const void *ptr) const { return upCast(const_cast<void *>(ptr)); }
	virtual void *downCast(void *ptr) const;
	inline const void *downCast(const void *ptr) const { return downCast(const_cast<void *>(ptr)); }
	virtual void *upCast(void *ptr, const AbstractClass& cls) const;
	inline const void *upCast(const void *ptr, const AbstractClass& cls) const { return upCast(const_cast<void *>(ptr), cls); }
	virtual void *downCast(void *ptr, const AbstractClass& cls) const;
	inline const void *downCast(const void *ptr, const AbstractClass& cls) const { return downCast(const_cast<void *>(ptr), cls); }
private:
	const AbstractClass& _base;
};


template <class T, class B = Object>
class Class: public AbstractClass {
public:
	inline Class(CString name, const AbstractClass& base = type_of<B>()): AbstractClass(name, base) { };
	virtual void *instantiate(void) const { return new T; };
	virtual void *upCast(void *ptr) const { return static_cast<B *>(static_cast<T *>(ptr)); }
	virtual void *downCast(void *ptr) const { return static_cast<T *>(static_cast<B *>(ptr)); }
};

} }	// elm::rtti

#endif /* ELM_RTTI_CLASS_H_ */
