/*
 *	SubCollection class
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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
#ifndef ELM_DATA_SUBCOLLECTION_H_
#define ELM_DATA_SUBCOLLECTION_H_

#include <elm/util/Equiv.h>

namespace elm {

template <class I>
class SubCollection {
public:
	typedef typename I::t t;

	inline SubCollection(const I& begin, const I& end)
		: _begin(begin), _end(end) { }

	class Iter: public PreIterator<I, t> {
	public:
		typedef SubCollection collec_t;
		inline Iter(const SubCollection& collection)
			: c(collection), i(c._begin) { }
		inline bool ended(void) const { return i == c._end; }
		inline t item(void) const { return *i; }
		inline void next(void) const { i.next(); }
	private:
		const SubCollection& c;
		I i;
	};

	inline bool isEmpty(void) const { return _begin == _end; }
	inline int count(void) const
		{ int c = 0; for(Iter i(*this); i; i++) c++; return c; }
	inline operator bool(void) const { return !isEmpty(); }
	inline bool contains(const t& v)
		{ for(Iter i(*this); i; i++) if(Equiv<t>::equals(*i, v)) return true; return false; }
	template <class C> inline bool containsAll(const C& c)
	 	 { for(typename C::Iter i(c); i; i++) if(!contains(*i)) return false; return true; }

private:
	I _begin, _end;
};

template <class I>
SubCollection<I> sub_coll(const I& begin, const I& end) { return SubCollection<I>(begin, end); }

}	// elm


#endif /* ELM_DATA_SUBCOLLECTION_H_ */
