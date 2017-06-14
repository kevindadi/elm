/*
 *	rtti module implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2017, IRIT UPS.
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

#include <elm/data/HashMap.h>
#include <elm/rtti.h>

/**
 * @defgroup rtti  Run-Time Type Information
 *
 * This module provides information for type at run-time.
 * It may be used for very different purposes as:
 * * automatic serialization / deserialization,
 * * automatic interface generation,
 * * automatic display of instances,
 * * run-time typed and generic storage.
 *
 * For each type, it can provide a @ref Type descriptor that
 * includes:
 * * name as a string,
 * * parent for classes,
 * * casting information,
 * * list of attributes,
 * * list of methods and constructors.
 */

namespace elm { namespace rtti {


/**
 * Map of available types.
 */
static HashMap<string, const Type *> type_map;

/**
 */
class PointerType: public Type {
public:
	PointerType(const Type *t): Type(t->name() + "*") { }
	virtual bool isPointer(void) const { return true; }
};

/**
 * @class Type
 * Materialize the concept of type. Used for serialization or
 * with classes like variant.
 * @ingroup rtti
 */

/**
 * Initializer to avoid the initialization issue of C++.
 */
Initializer<Type> Type::_init(false);

/**
 */
Type::Type(string name): _name(name) {
	_init.record(this);
}

/**
 * For internal use only. Do not call it.
 */
void Type::initialize(void) {
	type_map.put(name(), this);
}

/**
 * Get a type by its name.
 * @param name	Name of looked type.
 * @return		Found type or null.
 */
const Type *Type::get(string name) {
	_init.startup();
	return type_map.get(name, 0);
}

/**
 */
Type::~Type(void) { }

/**
 * Obtain pointer type on the current type.
 * @return	Corresponding pointer type.
 */
const Type *Type::pointer(void) const {
	if(!_pointer)
		_pointer = new PointerType(this);
	return _pointer;
}

/**
 * @fn string Type::name(void) const;
 * Get the name of the type.
 */

/**
 * Test if the type can be casted to the given type.
 * @param t		Type to cast to.
 * @return		True if the type can be casted to the given type, false else.
 */
bool Type::canCast(const Type *t) const {
	return t == this;
}

/**
 * Test if the type is a boolean.
 * @return	True if the type is boolean, false else.
 */
bool Type::isBool(void) const {
	return false;
}

/**
 * Test if the type is a integer.
 * @return	True if the type is boolean, false else.
 */
bool Type::isInt(void) const {
	return false;
}

/**
 * Test if the type is a floating-point real.
 * @return	True if the type is boolean, false else.
 */
bool Type::isFloat(void) const {
	return false;
}

/**
 * Test if the type is a pointer.
 * @return	True if the type is boolean, false else.
 */
bool Type::isPtr(void) const {
	return false;
}

/**
 * Test if the type is a class. Default implementation
 * return false.
 * @return	True if the type is a class, false else.
 */
bool Type::isClass(void) const {
	return false;
}

/**
 * Get the class description corresponding to this type.
 * If the type is not a class, an assertion failure is raised.
 * @return	Corresponding class instance.
 */
const AbstractClass *Type::asClass(void) const {
	ASSERTP(false, "type " << name() << " is not a class!");
	return 0;
}

/**
 * Test if the type is enumerated. Default implementation
 * return false.
 * @return	True if the type is a class, false else.
 */
bool Type::isEnum(void) const {
	return false;
}

/**
 * Get the enumeration description corresponding to this type.
 * If the type is not enumerated, an assertion failure is raised.
 * @return	Corresponding class instance.
 */
const Enum& Type::asEnum(void) const {
	ASSERTP(false, "type " << name() << " is not enumerated!");
	return *null<Enum>();
}


/**
 */
template <class T>
class IntType: public Type {
public:
	IntType(void): Type(type_info<T>::name()) { }
	virtual bool isInt(void) const { return true; }
	virtual bool canCast(const Type *t) const { return t->isBool() || t->isInt() || t->isFloat(); }
};

/**
 * Type for signed 8-bit integer.
 * @ingroup rtti
 */
const Type& int8_type = Single<IntType<t::int8> >::_;

/**
 * Type for unsigned 8-bit integer.
 * @ingroup rtti
 */
const Type& uint8_type = Single<IntType<t::uint8> >::_;

/**
 * Type for signed 16-bit integer.
 * @ingroup rtti
 */
const Type& int16_type = Single<IntType<t::int16> >::_;

/**
 * Type for unsigned 8-bit integer.
 * @ingroup rtti
 */
const Type& uint16_type = Single<IntType<t::uint16> >::_;

/**
 * Type for signed 32-bit integer.
 * @ingroup rtti
 */
const Type& int32_type = Single<IntType<t::int32> >::_;

/**
 * Type for unsigned 32-bit integer.
 * @ingroup rtti
 */
const Type& uint32_type = Single<IntType<t::uint32> >::_;

/**
 * Type for signed 64-bit integer.
 * @ingroup rtti
 */
const Type& int64_type = Single<IntType<t::int64> >::_;

/**
 * Type for unsigned 64-bit integer.
 * @ingroup rtti
 */
const Type& uint64_type = Single<IntType<t::uint64> >::_;


/**
 * Type class for floating-point reals.
 */
template <class T>
class FloatType: public Type {
public:
	FloatType(void): Type(type_info<T>::name()) { }
	virtual bool isFloat(void) const { return true; }
	virtual bool canCast(const Type *t) const { return t->isBool() || t->isInt() || t->isFloat(); }
};

/**
 * Type for single-precision floating-point real.
 * @ingroup rtti
 */
const Type& float_type = Single<FloatType<float> >::_;

/**
 * Type for double-precision floating-point real.
 * @ingroup rtti
 */
const Type& double_type = Single<FloatType<double> >::_;

/**
 * Type for quadruple-precision floating-point real.
 * @ingroup rtti
 */
const Type& long_double_type = Single<FloatType<long double> >::_;

/**
 */
class BoolType: public Type {
public:
	BoolType(void): Type("boo") { }
	virtual bool canCast(const Type *t) const { return t == this || t->isInt(); }
	virtual bool isBool(void) const { return true; }
};

/**
 * Type for booleans.
 * @ingroup rtti
 */
const Type& bool_type = Single<BoolType>::_;

/**
 */
class StringType: public Type {
public:
	StringType(void): Type("string") { }
};

/**
 * Type for strings.
 * @ingroup rtti
 */
const Type& string_type = Single<StringType>::_;

/**
 */
class CStringType: public Type {
public:
	CStringType(void): Type("cstring") { }
};

/**
 * Type for C strings.
 * @ingroup rtti
 */
const Type& cstring_type = Single<CStringType>::_;


/**
 * @class AbstractClass
 *
 * Abstract class to represent classes in RTTI. It is mainly used
 * for serialization / deserialization.
 *
 * @ingroup rtti
 */

/**
 * Build the abstract class.
 * @param name	Class named (fully qualified).
 * @param base	Base class (default none).
 */
AbstractClass::AbstractClass(CString name, AbstractClass *base): rtti::Type(name), _base(base) {
}

/**
 * @fn AbstractClass *AbstractClass::base(void) const;
 * Get the parent class.
 * @return	Parent class.
 */

/**
 * @fn void *AbstractClass::instantiate(void);
 * Call this function to get a new allocated fresh object of the corresponding class.
 * This function must be overridden to perform the actual allocation
 * and the class must support constructor without any argument.
 * @return	Allocated instance of class.
 */

/**
 * Test if the current class is base class of the given one.
 * Notice that this class is a base class of clazz even if this
 * class equals the class clazz.
 * @param clazz		Class to test.
 * @return			True if this class is a base class, false else.
 */
bool AbstractClass::baseOf(AbstractClass *clazz) {
	while(clazz) {
		if(clazz == this)
			return true;
		clazz = clazz->base();
	}
	return false;
}

/**
 */
bool AbstractClass::isClass(void) const {
	return true;
}

/**
 */
const AbstractClass *AbstractClass::asClass(void) const {
	return this;
}


/**
 * @class Class
 * @ref Type building for a class.
 * @param T		C++ type of the class this descriptor is used for.
 * @ingroup rtti
 */


/**
 * @class Enum
 * Type for an enumerated type. Recording an enumration in the RTTI system
 * requires several actions:
 * * defining an Enum descriptor,
 * * link the Enum descriptor with the type itself,
 * * providing support for other facilities (input/output, etc).
 *
 * To help providing this stuff, two macros are provided, @ref DECLARE_ENUM
 * is used in the header file and @ref DEFINE_ENUM in the source file.
 *
 * The code below represents an heade file where an enumerated type is
 * provided:
 * @code
 *	#include <elm/rtti.h>
 *
 *	typedef enum my_enum {
 *		A,
 *		B,
 *		C
 *	} my_enum;
 *	DECLARE_ENUM(my_enum);
 * @endcode
 *
 * The code below shows the source corresponding part:
 * @code
 *	elm::rtti::Enum my_enum_type(elm::rtti::make("my_enum")
 *		.value("A", A)
 *		.value("B", B)
 *		.value("C", C));
 *	DEFINE_ENUM(my_enum, my_enum_type);
 * @endcode
 *
 * @ingroup rtti
 */

/**
 * @class Enum::value
 * Class representing a value of an enumerated type.
 */

/**
 * @fn Enum::value::value(cstring name, int value);
 * Build a value.
 * @param name	Value name.
 * @param value	Value.
 */

/**
 * @fn cstring Enum::value::name(void) const;
 * Get the value name.
 * @return	Value name.
 */

/**
 * @fn int Enum::value::value(void) const;
 * Get the value.
 * @return	Value.
 */

/**
 * @class Enum::make
 * Maker to build an enumerated value @ref Enum.
 */

/**
 * @fn make& Enum::make::value(cstring name, int value);
 * Add a value.
 * @param name	Value name.
 * @param value	Value itself.
 */

/**
 * @fn make& Enum::make::alias(cstring name, int value);
 * @param name	Alias name.
 * @param value	Value itself.
 */

/**
 *
 */
Enum::Enum(const make& make): Type(make._name), _values(make._values) {
	_map.addAll(make._values);
	_map.addAll(make._aliases);
}

/**
 * Old-style enumerated type builder.
 * @param name		Full-qualified enumerated name.
 * @param values	Values of the enumerated type.
 */
Enum::Enum(cstring name, const Value values[]): Type(name) {
	for(int i = 0; values[i].name(); i++) {
		_values.add(values[i]);
		_map.add(values[i]);
	}
}

/**
 * Get the value for a text.
 * @param text	Text of the value for.
 * @return		Found value or -1 if not found.
 */
int Enum::valueFor(cstring text) const {
	for(Vector<Value>::Iter i = _map; i; i++)
		if((*i).name() == text)
			return (*i).value();
	return -1;
}

/**
 * Find the name corresponding to the gi en enumerated
 * value.
 * @param value	Value to look text for.
 * @return		If found, corresponding name or empty string.
 */
cstring Enum::nameFor(int value) const {
	for(Iter i = values(); i; i++)
		if((*i).value() == value)
			return (*i).name();
	return "";
}


/**
 * @fn Enum::Iter Enum::values(void) const;
 * Get the list of values.
 * @return	List of values.
 */

/**
 */
bool Enum::canCast(const Type *t) const {
	return t == this || t->isInt();
}

/**
 */
bool Enum::isEnum(void) const {
	return true;
}

/**
 */
const Enum& Enum::asEnum(void) const {
	return *this;
}

} }	// elm::rtti
