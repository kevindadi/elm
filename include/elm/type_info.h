/*
 *	$Id$
 *	type_info class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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

#include <float.h>
#include <elm/string.h>

namespace elm {

// type_info trait
template <class T> struct type_info {
	enum { is_type = 0 };
	enum { is_scalar = 0 };
	enum { is_enum = 0 };
	enum { is_class = 1 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
	static inline CString name(void) { return T::_class.name(); }
};
typedef struct type_t {
	enum { is_type = 1 };
	enum { is_scalar = 0 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
} type_t;
typedef struct scalar_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
} scalar_t;
typedef struct ptr_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 1 };
	enum { is_ref = 0 };
} ptr_t;
typedef struct ref_t {
	enum { is_type = 1 };
	enum { is_scalar = 1 };
	enum { is_enum = 0 };
	enum { is_class = 0 };
	enum { is_ptr = 0 };
	enum { is_ref = 1 };
} ref_t;
typedef struct enum_t {
	enum { is_type = 1 };
	enum { is_enum = 1 };
	enum { is_class = 0 };
	enum { is_scalar = 1 };
	enum { is_ptr = 0 };
	enum { is_ref = 0 };
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
struct int_info: public scalar_t {
	static const int size = sizeof(I) * 8;
	static const bool is_signed = I(-1) < I(0);
	static const I min = !is_signed ? 0 : (I(-1) << (size - 1));
	static const I max = (is_signed ? ((I(1) << (size - 1)) - 1) : I(-1));
	static const I null = 0;
};
template <class I> const I int_info<I>::null; 
template <class I> const I int_info<I>::min; 
template <class I> const I int_info<I>::max; 

template <> struct type_info<signed int>: public int_info<signed int>
	{ static inline cstring name(void) { return "<int>"; } };
template <> struct type_info<unsigned int>: public int_info<unsigned int>
	{ static inline cstring name(void) { return "<unsigned>"; } };

template <> struct type_info<char>: public int_info<char>
	{ static inline cstring name(void) { return "<char>"; } };
template <> struct type_info<signed char>: public int_info<signed char>
	{ static inline cstring name(void) { return "<signed char>"; } };
template <> struct type_info<unsigned char>: public int_info<unsigned char>
		{ static inline cstring name(void) { return "<unsigned char>"; } };

template <> struct type_info<signed short>: public int_info<signed short>
	{ static inline cstring name(void) { return "<short>"; } };
template <> struct type_info<unsigned short>: public int_info<unsigned short>
	{ static inline cstring name(void) { return "<unsigned short>"; } };

template <> struct type_info<signed long>: public int_info<signed long>
	{ static inline cstring name(void) { return "<long>"; } };
template <> struct type_info<unsigned long>: public int_info<unsigned long>
	{ static inline cstring name(void) { return "<unsigned long>"; } };

template <> struct type_info<signed long long>: public int_info<signed long long>
	{ static inline cstring name(void) { return "<long long>"; } };
template <> struct type_info<unsigned long long>: public int_info<unsigned long long>
	{ static inline cstring name(void) { return "<unsigned long long>"; } };

	
// float specialization
template <> struct type_info<float>: public scalar_t {
	static const float min = FLT_MIN;
	static const float max = FLT_MAX;
	static const float null = 0;
	static inline cstring name(void) { return "<float>"; }
};
template <> struct type_info<double>: public scalar_t {
	static const float min = DBL_MIN;
	static const float max = DBL_MAX;
	static const double null = 0;
	static inline cstring name(void) { return "<double>"; }
};
template <> struct type_info<long double>: public scalar_t {
	static const float min = LDBL_MIN;
	static const float max = LDBL_MAX;
	static const long double null = 0;
	static inline CString name(void) { return "<long double>"; }
};


// String specialization
template <> struct type_info<cstring>: public type_t {
	static const cstring null;
	static inline cstring name(void) { return "<cstring>"; }
};

template <> struct type_info<String>: public type_t {
	static const string null;
	static inline cstring name(void) { return "<string>"; }
};


// pointer specialization
template <class T> struct type_info<const T *>: public ptr_t {
	typedef T of;
	enum { is_const = 1 };
	static const T * const null;
};
template <class T> const T * const type_info<const T *>::null = 0;


template <class T> struct type_info<T *>: public ptr_t {
	typedef T of;
	enum { is_const = 0 };
	static T * const null;
};
template <class T> T * const type_info<T *>::null = 0;


// reference specialization
template <class T> struct type_info<const T&>: public ref_t {
	typedef T of;
	enum { is_const = 1 };
};

template <class T> struct type_info<T&>: public ref_t {
	typedef T of;
	enum { is_const = 0 };
};

} // elm

#endif /* ELM_TYPE_INFO_H_ */
