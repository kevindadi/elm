/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/genstruct/VectorQueue.h -- VectorQueue class interface.
 */
#ifndef ELM_GENSTRUCT_VECTORQUEUE_H
#define ELM_GENSTRUCT_VECTORQUEUE_H

#include <elm/assert.h>

namespace elm { namespace genstruct {
	
// VectorQueue class
template <class T>
class VectorQueue {
	int hd, tl, cap;
	T *buffer;
	void enlarge(void);
public:
	inline VectorQueue(int capacity = 4);
	inline ~VectorQueue(void);
	
	inline int capacity(void) const;
	inline int size(void) const;
	inline bool isEmpty(void) const;
	
	inline void put(const T& value);
	inline const T& get(void);
	inline T& head(void) const;
	inline void reset(void);
	
	// Operators
	inline operator bool(void) const;
	inline T *operator->(void) const;
	inline T& operator*(void) const;
};

// VectorQueue implementation

template <class T> void VectorQueue<T>::enlarge(void) {
	int new_cap = cap * 2, off = 0;
	T *new_buffer = new T[new_cap];
	if( hd > tl) {
		off = cap - hd;
		for(int i = 0; i  < off; i++)
			new_buffer[i] = buffer[hd + i];
		hd = 0;
	}
	for(int i = hd; i < tl; i++)
		new_buffer[off + i - hd] = buffer[i];
	delete [] buffer;
	tl = off + tl - hd;
	cap = new_cap;
	buffer = new_buffer;
}

template <class T> inline VectorQueue<T>::VectorQueue(int capacity)
: hd(0), tl(0), cap(1 << capacity), buffer(new T[cap]) {
	ASSERTP(cap >= 0, "capacity must be positive");
}

template <class T> inline VectorQueue<T>::~VectorQueue(void) {
	delete [] buffer;
}

template <class T> inline int VectorQueue<T>::capacity(void) const {
	return cap;
}

template <class T> inline int VectorQueue<T>::size(void) const {
	if(hd < tl)
		return tl - hd;
	else
		return (cap - hd) + tl;
}

template <class T> inline bool VectorQueue<T>::isEmpty(void) const {
	return hd == tl;
}
	
template <class T> inline void VectorQueue<T>::put(const T& value) {
	int new_tl = (tl + 1) & (cap - 1);
	if(new_tl == hd) {
		enlarge();
		new_tl = tl + 1;
	}
	buffer[tl] = value;
	tl = new_tl;
}

template <class T> inline const T& VectorQueue<T>::get(void) {
	ASSERTP(hd != tl, "queue empty");
	int res = hd;
	hd = (hd + 1) & (cap - 1);
	return buffer[res];
}

template <class T> inline T& VectorQueue<T>::head(void) const {
	ASSERTP(hd != tl, "queue empty");
	return buffer[hd];
}

template <class T> inline void VectorQueue<T>::reset(void) {
	hd = 0;
	tl = 0;
}

template <class T> inline VectorQueue<T>::operator bool(void) const {
	return !isEmpty();
}

template <class T> inline T *VectorQueue<T>::operator->(void) const {
	return &head();
}

template <class T> inline T& VectorQueue<T>::operator*(void) const {
	return head();
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_VECTORQUEUE_H

