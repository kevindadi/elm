/*
 *	$Id$
 *	Comparator class interface
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
#ifndef ELM_COMPARATOR_H_
#define ELM_COMPARATOR_H_

#include <elm/string.h>
#include <elm/type_info.h>
#include <elm/util/Pair.h>
#include <elm/util/Equiv.h>

namespace elm {

// PreComparator class
template <class T, class C>
class PreComparator {
public:
	static inline const T& min(const T& v1, const T& v2)
		{ return C::compare(v1, v2) < 0 ? v1 : v2; }
	static inline const T& max(const T& v1, const T& v2)
		{ return C::compare(v1, v2) > 0 ? v1 : v2; }
};


// Comparator class
template <class T>
class Comparator: public PreComparator<T, Comparator<T> > {
public:
	static inline int compare(const T& v1, const T& v2)
		{ if(v1 == v2) return 0; else if(v1 > v2) return 1; else return -1; }
};

// SubstractComparator class
/*template <class T>
class SubstractComparator: public PreComparator<T, SubstractComparator<T> > {
public:
	static inline int compare(const T& v1, const T& v2) { return v1 - v2; }
};
template <> class Comparator<signed char>: public SubstractComparator<signed char> { };
template <> class Comparator<unsigned char>: public SubstractComparator<unsigned char> { };
template <> class Comparator<signed short>: public SubstractComparator<signed short> { };
template <> class Comparator<unsigned short>: public SubstractComparator<unsigned short> { };
template <> class Comparator<signed int>: public SubstractComparator<signed int> { };
template <> class Comparator<unsigned int>: public SubstractComparator<unsigned int> { };
template <> class Comparator<signed long>: public SubstractComparator<signed long> { };
template <> class Comparator<unsigned long>: public SubstractComparator<unsigned long> { };
template <> class Comparator<signed long long>: public SubstractComparator<signed long long> { };
template <> class Comparator<unsigned long long>: public SubstractComparator<unsigned long long> { };*/


// CompareComparator class
template <class T>
class CompareComparator: public PreComparator<T, CompareComparator<T> > {
public:
	static inline int compare(const T& v1, const T& v2) { return v1.compare(v2); }
};
template <> class Comparator<cstring>: public CompareComparator<cstring> { };
template <> class Comparator<string>: public CompareComparator<string> { };


// AssocComparator class
template <class K, class T, class C = Comparator<K> >
class AssocComparator: public PreComparator<Pair<K, T>, AssocComparator<K, T, C> > {
public:
	typedef Pair<K, T> pair_t;
	static inline int compare(const pair_t& v1, const pair_t& v2)
		{ return C::compare(v1.fst, v2. fst); }
};
template <class K, class T> class Comparator<Pair<K, T> >
	: public AssocComparator<K, T> { };


// ReverseComparator class
template <class T, class C>
class ReverseComparator: public PreComparator<T, ReverseComparator<T, C > > {
public:
	static inline int compare(const T& v1, const T& v2)
		{ return -C::compare(v1, v2); }
};


// CompareEquiv class
template <class T, class C = Comparator<T> >
class CompareEquiv {
public:
	static inline bool equals(const T& v1, const T& v2)
		{ return C::compare(v1, v2) == 0; }
};


// Useful inlines
template <class T> inline const T& min(const T& x, const T& y)
	{ return Comparator<T>::min(x, y); }
template <class T> inline const T& max(const T& x, const T y)
	{ return Comparator<T>::max(x, y); }

} // elm

#endif /* ELM_COMPARATOR_H_ */
