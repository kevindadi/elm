/*
 *	Type class interface
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
#ifndef ELM_RTTI_TYPE_H_
#define ELM_RTTI_TYPE_H_

#include <elm/ptr.h>
#include <elm/string.h>
#include <elm/util/Initializer.h>

namespace elm { namespace rtti {

class AbstractClass;
class Enum;

class Type {
public:
	static const Type *get(string name);
	Type(string name = "unknown");
	virtual ~Type(void);
	inline string name(void) const { return _name; }
	const Type *pointer(void) const;
	virtual bool canCast(const Type *t) const;
	virtual bool isBool(void) const;
	virtual bool isInt(void) const;
	virtual bool isFloat(void) const;
	virtual bool isPtr(void) const;
	virtual bool isClass(void) const;
	virtual const AbstractClass *asClass(void) const;
	virtual bool isEnum(void) const;
	virtual const Enum& asEnum(void) const;
	void initialize(void);
private:
	string _name;
	mutable UniquePtr<Type>_pointer;
	static Initializer<Type> _init;
};

} }		// otawa::rtti

#endif /* ELM_RTTI_TYPE_H_ */
