/*
 *	$Id$
 *	types module
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
#ifndef ELM_TYPES_H
#define ELM_TYPES_H

#include <elm/string.h>

namespace elm {

// type_info trait
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
	static const int max = 0x7fffffff;
	static const int min = -0x80000000;
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
	static const unsigned long max = 0xffffffff;
	static const unsigned long min = 0;
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

// Useful inlines
inline int max(int x, int y) { return (x > y) ? x : y; }
inline int min(int x, int y) { return (x < y) ? x : y; }

} // elm

#endif // ELM_TYPES_H
