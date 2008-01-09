/*
 *	$Id$
 *	SortedSLList class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-08, IRIT UPS.
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
#ifndef ELM_GENSTRUCT_SORTEDSLLIST_H
#define ELM_GENSTRUCT_SORTEDSLLIST_H

#include <elm/genstruct/SLList.h>
#include <elm/util/Comparator.h>

namespace elm { namespace genstruct {

// SortedSLList class
template <class T, class R = Comparator<T> >
class SortedSLList {
public:
	inline SortedSLList(void) { }
	SortedSLList(SortedSLList & source): list(source.list) { }

	inline void removeFirst(void) { list.removeFirst(); }
	inline void removeLast(void) { list.removeLast(); }

	// Collection concept
	inline int count (void) const { return list.count(); }
	bool contains (const T &item);
	inline bool isEmpty(void) const { return list.isEmpty(); }
	inline operator bool(void) const { return !list.isEmpty(); }

	class Iterator: public genstruct::SLList<T>::Iterator {
	public:
		inline Iterator(void) { }
		inline Iterator(const SortedSLList& _list)
			: genstruct::SLList<T>::Iterator(_list.list) { }
		inline Iterator(const Iterator& source)
			: genstruct::SLList<T>::Iterator(source) { }
	};
	
	// MutableCollection concept
	inline void clear(void) { list.clear(); }
	void add (const T &item);
	template <template <class _> class C> inline void addAll (const C<T> &items)
		{ for(typename C<T>::Iterator item(items); item; item++)
			add(item); }
	inline void remove(const T &item) { list.remove(item); }
	template <template <class _> class C> inline void removeAll(const C<T> &items)
		{ list.removeAll(items); }
	void remove(const Iterator &iter) { list.remove(iter); }

	// List concept
	inline const T& first(void) const { return list.first(); }
	inline const T& last(void) const { return list.last(); }
	
private:
	genstruct::SLList<T> list;
	//inline typename genstruct::SLList<T>::Iterator elements(void) const;
};


/*template <class T, class R> inline SortedSLList<T,R>::Iterator::Iterator(const SortedSLList<T,R> &_list)
:genstruct::SLList<T>::Iterator(_list.elements()) {
	
}
template <class T, class R> inline SortedSLList<T,R>::Iterator::Iterator(const Iterator &source)
:genstruct::SLList<T>::Iterator(source) {
	
}
template <class T, class R> inline SortedSLList<T,R>::Iterator::Iterator()
:genstruct::SLList<T>::Iterator() {
	
}*/

/*template <class T, class R> inline T SortedSLList<T,R>::first(void) const {
	return list.first();
}*/

/*template <class T, class R> inline T SortedSLList<T,R>::last(void) const {
	return list.last();
}
template <class T, class R> inline int SortedSLList<T,R>::count(void) const {
	return list.count();
}
template <class T, class R> inline bool SortedSLList<T,R>::isEmpty(void) const {
	return list.isEmpty();
}
template <class T, class R> inline typename genstruct::SLList<T>::Iterator SortedSLList<T,R>::elements(void) const {
	return typename genstruct::SLList<T>::Iterator(list);
}*/


/*template <class T, class R> inline void SortedSLList<T,R>::removeFirst(void) {
	list.removeFirst();
}
template <class T, class R> inline void SortedSLList<T,R>::removeLast(void) {
	list.removeLast();
}
template <class T, class R> inline void SortedSLList<T,R>::removeNext(const typename genstruct::SortedSLList<T,R>::Iterator& pos) {
	list.removeNext(pos);
}*/
/*template <class T, class R> inline void SortedSLList<T,R>::remove(const T& value) {
	list.remove(value);

}*/

template <class T, class R>
void SortedSLList<T,R>::add(const T& value) {
	for(Iterator current(*this); current; current++)					
		if(R::compare(value,  *current) < 0) {
			list.addBefore(current, value); 
			return;
		}
	list.addLast(value);
}

template <class T, class R>
bool SortedSLList<T, R>::contains (const T &item) {
	for (Iterator current(*this); current; current++) {
		int cmp = R::compare(item,  *current);
		if(cmp > 0)
			continue;
		else if(!cmp)
			return true;
		else
			break;
	}
	return false;
}

} } // elm::genstruct

#endif
