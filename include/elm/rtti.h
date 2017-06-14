/*
 *	$Id$
 *	RTTI module
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
#ifndef ELM_RTTI_H
#define ELM_RTTI_H

#include <elm/ptr.h>
#include <elm/rtti/Class.h>
#include <elm/rtti/Enum.h>
#include <elm/string.h>
#include <elm/types.h>

namespace elm {

namespace rtti {
extern const Type &int8_type, &uint8_type, &int16_type, &uint16_type, &int32_type, &uint32_type, &int64_type, &uint64_type;
extern const Type &float_type, &double_type, &long_double_type;
extern const Type &bool_type, &string_type, &cstring_type;

// type determination
template <class T> struct _type
	{ static inline const Type& _(void) { return T::__type; } };
template <> inline const Type& _type<t::int8>::_(void) { return int8_type; }
template <> inline const Type& _type<t::int16>::_(void) { return int16_type; }
template <> inline const Type& _type<t::int32>::_(void) { return int32_type; }
template <> inline const Type& _type<t::int64>::_(void) { return int64_type; }
template <> inline const Type& _type<t::uint8>::_(void) { return uint8_type; }
template <> inline const Type& _type<t::uint16>::_(void) { return uint16_type; }
template <> inline const Type& _type<t::uint32>::_(void) { return uint32_type; }
template <> inline const Type& _type<t::uint64>::_(void) { return uint64_type; }
template <> inline const Type& _type<float>::_(void) { return float_type; }
template <> inline const Type& _type<double>::_(void) { return double_type; }
template <> inline const Type& _type<long double>::_(void) { return long_double_type; }
template <> inline const Type& _type<bool>::_(void) { return bool_type; }
template <> inline const Type& _type<cstring>::_(void) { return cstring_type; }
template <> inline const Type& _type<string>::_(void) { return string_type; }

template <class T> struct _type<T *>
	{ static inline const Type& _(void) { return _type<T>::_().pointer(); } };

} // rtti

template <class T> inline const rtti::Type& type_of(void) { return rtti::_type<T>::_(); }

inline rtti::Enum::Value value(cstring name, int value) {
	return rtti::Enum::Value(name, value);
}

// New support for enumeration
#define ELM_DECLARE_ENUM(name) \
	namespace elm { namespace rtti { template <> const Type& _type<name>::_(void); } } \
	elm::io::Output& operator<<(io::Output& out, name value) { out << elm::type_of<name>().asEnum().nameFor(value); return out; }

#define ELM_DEFINE_ENUM(type, desc) \
		namespace elm { namespace rtti { template <> const Type& _type<type>::_(void) { return desc; } } }

#ifndef ELM_NO_SHORTCUT
#	define DECLARE_ENUM(name) 		ELM_DECLARE_ENUM(name)
#	define DEFINE_ENUM(type, desc)	ELM_DEFINE_ENUM	(type, desc)
#endif


// Field class
template <class V>
class Field {
	CString _name;
	V& _value;
public:
	inline Field(CString name, V& value): _name(name), _value(value) { }
	inline CString name(void) const { return _name; };
	inline V& value(void) const { return _value; };
};
template <class T>
inline Field<T> field(CString name, T& value) {
	return Field<T>(name, value);
}


// DefaultField class
template <class T>
class DefaultField: public Field<T> {
	const T& def;
public:
	inline DefaultField(CString name, T& value, const T& _default)
		: Field<T>(name, value), def(_default) { }
	inline const T& defaultValue(void) const { return def; }
};
template <class T>
inline DefaultField<T> field(CString name, T& value, const T& def) {
	return DefaultField<T>(name, value, def);
}


// Enumerations
#define ELM_ENUM(type) \
	namespace elm { \
		template <> struct type_info<type>: public enum_t { \
			static elm::rtti::Enum::Value __vals[]; \
			static inline CString name(void) { return "<enum " #type ">"; } \
			static inline elm::rtti::Enum::Value *values(void) { return __vals; } \
		}; \
		namespace rtti { template <> inline const Type& _type<type>::_(void); } \
		elm::io::Output& operator<<(io::Output& out, type value) { out << elm::type_of<type>().asEnum().nameFor(value); return out; } \
	}
#define ELM_ENUM_BEGIN(type) \
	namespace elm { \
		namespace rtti { template <> inline const Type& _type<type>::_(void) { static Enum _("", elm::type_info<type>::__vals); return _; };  } \
		elm::rtti::Enum::Value type_info<type>::__vals[] = {
#define ELM_ENUM_END \
			, value("", 0) \
		}; \
	}
#define ELM_VALUE(name) elm::value(elm::_unqualify(#name), name)

#ifndef ELM_NO_SHORTCUT
#	define ENUM(type) ELM_ENUM(type)
#	define VALUE(name) ELM_VALUE(name)
#	define ENUM_BEGIN(type) ELM_ENUM_BEGIN(type)
#	define ENUM_END ELM_ENUM_END
#endif


// _unqualify function
inline CString _unqualify(CString name) {
	int pos = name.lastIndexOf(':');
	if(pos < 0)
		return name;
	else
		return name.substring(pos + 1);
}

} // elm

#endif // ELM_RTTI_H
