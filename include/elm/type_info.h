/*
 *	type_info class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008-13, IRIT UPS.
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
#ifndef ELM_TYPE_INFO_H_
#define ELM_TYPE_INFO_H_

#include <elm/string.h>

namespace elm {

// type_info trait
template <class T>
class class_t {
public:
	enum { is_type = 0 };
	enum { is_scalar = 0 };
	enum { is_enum = 0 };
	enum { is_class = 1 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
	enum { is_deep = 1 };
	enum { is_virtual = 1 };
	static inline CString name(void) { return T::_class.name(); }
};
template <class T> class type_info: public class_t<T> {
	static cstring name(void) { return T::__type_name(); }
};
typedef struct type_t {
	enum { is_type = 1 };
	enum { is_scalar = 0 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
	enum { is_deep = 1 };
	enum { is_virtual = 0 };
} type_t;
typedef struct scalar_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
	enum { is_deep = 0 };
	enum { is_virtual = 0 };
} scalar_t;
typedef struct ptr_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 1 };
	enum { is_ref = 0 };
	enum { is_deep = 1 };
	enum { is_virtual = 0 };
} ptr_t;
typedef struct ref_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 0 };
	enum { is_ref = 1 };
	enum { is_deep = 1 };
	enum { is_virtual = 0 };
} ref_t;
typedef struct enum_t {
	enum { is_type = 1 };
	enum { is_enum = 1 };
	enum { is_class = 0 };
	enum { is_scalar = 1 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
	enum { is_deep = 0 };
	enum { is_virtual = 0 };
} enum_t;


// bool specialization
template <> struct type_info<bool>: public scalar_t {
	static const bool min = false;
	static const bool max = true;
	static const bool null = false;
	static inline CString name(void) { return "<bool>"; }	
};


// integer specialization
template <class I>
struct signed_info: public scalar_t {
	static const int size = sizeof(I) * 8;
	static const bool is_signed = true;
	static const I min = I(-1) << (size - 1);
	static const I max = I(1) << (size - 1);
	static const I null = 0;
};
template <class I> const I signed_info<I>::null;
template <class I> const I signed_info<I>::min;
template <class I> const I signed_info<I>::max;
template <class I>
struct unsigned_info: public scalar_t {
	static const int size = sizeof(I) * 8;
	static const bool is_signed = false;
	static const I min = 0;
	static const I max = I(-1);
	static const I null = 0;
};
template <class I> const I unsigned_info<I>::null;
template <class I> const I unsigned_info<I>::min;
template <class I> const I unsigned_info<I>::max;

template <> struct type_info<signed int>: public signed_info<signed int> { static cstring name(void); };
template <> struct type_info<unsigned int>: public unsigned_info<unsigned int> { static cstring name(void); };
template <> struct type_info<char>: public signed_info<char> { static cstring name(void); };
template <> struct type_info<signed char>: public signed_info<signed char> { static cstring name(void); };
template <> struct type_info<unsigned char>: public unsigned_info<unsigned char>  { static cstring name(void); };
template <> struct type_info<signed short>: public signed_info<signed short> { static cstring name(void); };
template <> struct type_info<unsigned short>: public unsigned_info<unsigned short> { static cstring name(void); };
template <> struct type_info<signed long>: public signed_info<signed long> { static cstring name(void); };
template <> struct type_info<unsigned long>: public unsigned_info<unsigned long> { static cstring name(void); };
template <> struct type_info<signed long long>: public signed_info<signed long long> { static cstring name(void); };
template <> struct type_info<unsigned long long>: public unsigned_info<unsigned long long> { static cstring name(void); };

	
// float specialization
template <> struct type_info<float>: public scalar_t {
	static const float min;
	static const float max;
	static const float null = 0;
	static cstring name(void);
};
template <> struct type_info<double>: public scalar_t {
	static const double min;
	static const double max;
	static const double null = 0;
	static cstring name(void);
};
template <> struct type_info<long double>: public scalar_t {
	static const long double min;
	static const long double max;
	static const long double null = 0;
	static cstring name(void);
};


// String specialization
template <> struct type_info<cstring>: public type_t {
	static const cstring null;
	static cstring name(void);
};

template <> struct type_info<String>: public type_t {
	static const string null;
	static cstring name(void);
};


// pointer specialization
template <class T> struct type_info<const T *>: public ptr_t {
	typedef T of;
	enum { is_const = 1 };
	static const T * const null;
	static string name(void) { return _ << "const " + type_info<T>::name() << " *"; }
};
template <class T> const T * const type_info<const T *>::null = 0;


template <class T> struct type_info<T *>: public ptr_t {
	typedef T of;
	enum { is_const = 0 };
	static T * const null;
	static string name(void) { return _ << type_info<T>::name() << " *"; }
};
template <class T> T * const type_info<T *>::null = 0;


// reference specialization
template <class T> struct type_info<const T&>: public ref_t {
	typedef T of;
	enum { is_const = 1 };
	static string name(void) { return _ << "const " + type_info<T>::name() << "& "; }
};

template <class T> struct type_info<T&>: public ref_t {
	typedef T of;
	enum { is_const = 0 };
	static string name(void) { return _ << type_info<T>::name() << "& "; }
};

} // elm

#endif /* ELM_TYPE_INFO_H_ */
