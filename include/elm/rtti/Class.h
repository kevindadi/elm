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


template <class T, class B = void>
class Class: public AbstractClass {
public:
	inline Class(CString name, const AbstractClass& base = type_of<B>().asClass()): AbstractClass(name, base) { };
	virtual void *instantiate(void) const { return new T; };
	virtual void *upCast(void *ptr) const { return static_cast<B *>(static_cast<T *>(ptr)); }
	virtual void *downCast(void *ptr) const { return static_cast<T *>(static_cast<B *>(ptr)); }

	inline void *upCast(void *ptr, const AbstractClass& cls) const { return AbstractClass::upCast(const_cast<void *>(ptr), cls); }
	inline void *downCast(void *ptr, const AbstractClass& cls) const { return AbstractClass::downCast(const_cast<void *>(ptr), cls); }
	inline const void *upCast(const void *ptr) const { return AbstractClass::upCast(ptr); }
	inline const void *downCast(const void *ptr) const { return AbstractClass::downCast(ptr); }
	inline const void *upCast(const void *ptr, const AbstractClass& cls) const { return AbstractClass::upCast(ptr, cls); }
	inline const void *downCast(const void *ptr, const AbstractClass& cls) const { return AbstractClass::downCast(ptr, cls); }
};

#define ELM_IS_CLASS_EXTEND(name, base) \
	public: \
		typedef base __base; \
		static elm::rtti::Class<name, base> __type; \
	private:

#define ELM_CLASS_EXTEND(name, base) \
	class name: public base { \
	ELM_IS_CLASS_EXTEND(name, base)

#define ELM_IS_CLASS(name) \
	public: \
		typedef void __base; \
		static elm::rtti::Class<name, void> __type; \
	private:

#define ELM_CLASS(name) \
	class name { \
	ELM_IS_CLASS(name)

#define ELM_END_CLASS	};

#define ELM_IMPLEMENT(name) \
	elm::rtti::Class<name, typename name::__base> name::__type(#name)

#ifndef ELM_NO_SHORTCUT
#	define IS_CLASS_EXTEND(name, base)	ELM_IS_CLASS_EXTEND(name, base)
#	define CLASS_EXTEND(name, base)		ELM_CLASS_EXTEND(name, base)
#	define IS_CLASS(name)				ELM_IS_CLASS(name)
#	define CLASS(name)					ELM_CLASS(name)
#	define END_CLASS					ELM_END_CLASS
#	define IMPLEMENT(name)				ELM_IMPLEMENT(name)
#endif

} }	// elm::rtti

#endif /* ELM_RTTI_CLASS_H_ */
