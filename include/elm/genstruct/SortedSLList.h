/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * SortedSLList.h -- sorted single link list interface.
 */
#ifndef ELM_GENSTRUCT_SORTEDSLLIST_H
#define ELM_GENSTRUCT_SORTEDSLLIST_H

#include <elm/genstruct/SLList.h>

namespace elm { namespace genstruct {
	
template <class T, class R> class SortedSLList {
	
		R *order;
		genstruct::SLList<T> list;
		
		inline typename genstruct::SLList<T>::Iterator elements(void) const;
		public:
		
		class Iterator: public genstruct::SLList<T>::Iterator {
			public:
			inline Iterator();
			inline Iterator(const SortedSLList& _list);
			inline Iterator(const Iterator& source);
		};
		
		// Constructors
		SortedSLList(R& _rel);
		SortedSLList(SortedSLList & source);
		
		// Accessors
		inline T first(void) const;
		inline T last(void) const;
		inline int count(void) const;
		inline bool isEmpty(void) const;


		// Mutators

		inline void removeFirst(void);
		inline void removeLast(void);
		inline void removeNext(const typename genstruct::SortedSLList<T,R>::Iterator& pos);
		inline void remove(const T& value);	
		void add(T valuebb);
};

template <class T, class R> inline SortedSLList<T,R>::Iterator::Iterator(const SortedSLList<T,R> &_list)
:genstruct::SLList<T>::Iterator(_list.elements()) {
	
}
template <class T, class R> inline SortedSLList<T,R>::Iterator::Iterator(const Iterator &source)
:genstruct::SLList<T>::Iterator(source) {
	
}
template <class T, class R> inline SortedSLList<T,R>::Iterator::Iterator()
:genstruct::SLList<T>::Iterator() {
	
}
template <class T, class R> SortedSLList<T,R>::SortedSLList(SortedSLList<T,R> &source)
: order(source.order), list(source.list)
{

}

template <class T, class R> SortedSLList<T,R>::SortedSLList(R& _order)
: order(&_order) {

}
 
 
template <class T, class R> inline T SortedSLList<T,R>::first(void) const {
	return list.first();
}

template <class T, class R> inline T SortedSLList<T,R>::last(void) const {
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
}


template <class T, class R> inline void SortedSLList<T,R>::removeFirst(void) {
	list.removeFirst();
}
template <class T, class R> inline void SortedSLList<T,R>::removeLast(void) {
	list.removeLast();
}
template <class T, class R> inline void SortedSLList<T,R>::removeNext(const typename genstruct::SortedSLList<T,R>::Iterator& pos) {
	list.removeNext(pos);
}
template <class T, class R> inline void SortedSLList<T,R>::remove(const T& value) {
	list.remove(value);

}

template <class T, class R> void SortedSLList<T,R>::add(T value) {

		for (typename genstruct::SLList<T>::Iterator current(list), previous; current; previous = current, current++) {						
			if (order->greaterThan(value,  *current)) {
				if (previous.ended()) {
					list.addFirst(value);
				} else {
					list.addAfter(previous, value); 
				}
				return;
			}
		}		
		list.addLast(value);
}


} }

#endif
