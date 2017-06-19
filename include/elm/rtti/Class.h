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
	virtual void *downCast(void *ptr) const;

	void *upCast(void *ptr, const AbstractClass& cls) const;
	void *downCast(void *ptr, const AbstractClass& cls) const;

	inline const void *upCast(const void *ptr) const { return upCast(const_cast<void *>(ptr)); }
	inline const void *downCast(const void *ptr) const { return downCast(const_cast<void *>(ptr)); }
	inline const void *upCast(const void *ptr, const AbstractClass& cls) const { return upCast(const_cast<void *>(ptr), cls); }
	inline const void *downCast(const void *ptr, const AbstractClass& cls) const { return downCast(const_cast<void *>(ptr), cls); }
private:
	const AbstractClass& _base;
};


class ObjectType: public AbstractClass {
public:
	typedef void *ptr_t;
	typedef const void *const_ptr_t;
	ObjectType(void);
	virtual bool isClass(void) const;
	virtual const AbstractClass& asClass(void) const;
	virtual void *instantiate(void) const;
};
extern ObjectType& object_type;
template <> inline const Type& _type<Object>::_(void) { return object_type; }

template <class T> struct is_object { enum { _ = 0 }; };
template <> struct is_object<Object> { enum { _ = 1 }; };

template <class T, class B = Object>
class Class: public AbstractClass {
	typedef typename _if<is_object<B>::_, void, B>::_ base_t;
public:
	inline Class(CString name, const AbstractClass& base = type_of<B>().asClass()): AbstractClass(name, base) { };
	virtual void *instantiate(void) const { return new T; };
	virtual void *upCast(void *ptr) const { return static_cast<base_t *>(static_cast<T *>(ptr)); }
	virtual void *downCast(void *ptr) const { return static_cast<T *>(static_cast<base_t *>(ptr)); }

	inline void *upCast(void *ptr, const AbstractClass& cls) const { return AbstractClass::upCast(const_cast<void *>(ptr), cls); }
	inline void *downCast(void *ptr, const AbstractClass& cls) const { return AbstractClass::downCast(const_cast<void *>(ptr), cls); }
	inline const void *upCast(const void *ptr) const { return AbstractClass::upCast(ptr); }
	inline const void *downCast(const void *ptr) const { return AbstractClass::downCast(ptr); }
	inline const void *upCast(const void *ptr, const AbstractClass& cls) const { return AbstractClass::upCast(ptr, cls); }
	inline const void *downCast(const void *ptr, const AbstractClass& cls) const { return AbstractClass::downCast(ptr, cls); }
};

} }	// elm::rtti

#endif /* ELM_RTTI_CLASS_H_ */
