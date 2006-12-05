/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * Type information.
 */
#ifndef ELM_RTTI_H
#define ELM_RTTI_H

#include <elm/string.h>

namespace elm {

// value_t structure
class value_t {
	CString _name;
	int _value;
public:
	inline value_t(CString name, int value): _name(name), _value(value) { }
	inline CString name(void) const { return _name; }
	inline int value(void) const { return _value; }
};
inline value_t value(CString name, int value) {
	return value_t(name, value);
} 


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


// istype trait
template <class T> struct type_info {
	enum { is_type = 0 };
	enum { is_scalar = 0 };
	enum { is_enum = 0 };
	enum { is_class = 1 };
	static inline CString name(void) { return T::_class.name(); }
};
typedef struct type_t {
	enum { is_type = 1 };
	enum { is_scalar = 0 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
} type_t;
typedef struct scalar_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
} scalar_t;
template <> struct type_info<bool>: public scalar_t {
	static inline CString name(void) { return "<bool>"; }		
};
template <> struct type_info<signed int>: public scalar_t {
	static inline CString name(void) { return "int"; }
};
template <> struct type_info<unsigned int>: public scalar_t {
	static inline CString name(void) { return "<unsigned>"; }
};
template <> struct type_info<char>: public scalar_t {
	static inline CString name(void) { return "<char>"; }
};
template <> struct type_info<signed char>: public scalar_t {
	static inline CString name(void) { return "<signed char>"; }
};
template <> struct type_info<unsigned char>: public scalar_t {
	static inline CString name(void) { return "<unsigned char>"; }
};
template <> struct type_info<signed short>: public scalar_t {
	static inline CString name(void) { return "<short>"; }
};
template <> struct type_info<unsigned short>: public scalar_t {
	static inline CString name(void) { return "<unsigned short>"; }
};
template <> struct type_info<signed long>: public scalar_t {
	static inline CString name(void) { return "<long>"; }
};
template <> struct type_info<unsigned long>: public scalar_t {
	static inline CString name(void) { return "<unsigned long>"; }
};
template <> struct type_info<signed long long>: public scalar_t {
	static inline CString name(void) { return "<long long>"; }
};
template <> struct type_info<unsigned long long>: public scalar_t {
	static inline CString name(void) { return "<unsigned long long>"; }
};
template <> struct type_info<float>: public scalar_t {
	static inline CString name(void) { return "<float>"; }
};
template <> struct type_info<double>: public scalar_t {
	static inline CString name(void) { return "<double>"; }
};
template <> struct type_info<long double>: public scalar_t {
	static inline CString name(void) { return "<long double>"; }
};
template <> struct type_info<CString>: public type_t {
	static inline CString name(void) { return "<cstring>"; }
};
template <> struct type_info<String>: public type_t {
	static inline CString name(void) { return "<string>"; }
};


// Enumerations
typedef struct enum_t {
	enum { is_type = 1 };
	enum { is_enum = 1 };
	enum { is_class = 0 };
} enum_t;
#define ELM_ENUM(type) \
	namespace elm { \
		template <> struct type_info<type>: public enum_t { \
			static value_t __vals[]; \
			static inline CString name(void) { return "<enum " #type ">"; } \
			static inline value_t *values(void) { return __vals; } \
		}; \
	}
#define ELM_ENUM_BEGIN(type) \
	namespace elm { \
		struct value_t type_info<type>::__vals[] = {
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


// AbstractClass class
class AbstractClass {
	CString _name;
	AbstractClass *_base;
public:
	inline AbstractClass(CString name, AbstractClass *base = 0)
		: _name(name), _base(base) { };
	inline CString name(void) const { return _name; };
	inline AbstractClass *base(void) const { return _base; };
	virtual void *instantiate(void) = 0;
};


// Class class
template <class T>
class Class: public AbstractClass {
public:
	inline Class(CString name, AbstractClass *base = 0)
		: AbstractClass(name, base) { };
	virtual void *instantiate(void) { return new T; }; 
};


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
