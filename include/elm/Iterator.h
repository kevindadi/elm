/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * collection.h -- collection classes interfaces.
 */
#ifndef ELM_DATASTRUCT_ITERATOR_H
#define ELM_DATASTRUCT_ITERATOR_H

namespace elm {


// PreIterator class
template <class I, class T>
class PreIterator {
public:
	inline operator bool(void) const
		{ return !((I *)this)->ended(); }
	inline operator T(void) const
		{ return ((I *)this)->item(); }
	inline I& operator++(void)
		{ ((I *)this)->next(); return *(I *)this; }
	inline I& operator++(int)
		{ ((I *)this)->next(); return *(I *)this; }
	inline T operator*(void) const
		{ return ((I *)this)->item(); }
	inline T operator->(void) const
		{ return ((I *)this)->item(); }
};


// PreBiDiIterator class
template <class I, class T>
class PreBiDiIterator: public PreIterator<I, T> {
public:
	inline I& operator--(void)
		{ ((I *)this)->previous(); return *(I *)this; }
	inline I& operator--(int)
		{ ((I *)this)->previous(); return *(I *)this; } 
}; 


// IteratorInst class
template <class T> class IteratorInst {
public:
	virtual bool ended(void) const = 0;
	virtual T item(void) const = 0;
	virtual void next(void) = 0;
	inline IteratorInst<T>& operator++(int _);
	inline operator bool(void) const;
	inline T operator*(void) const;
	inline T operator->(void) const;
	inline operator T(void) const;
};


// IteratorObject class
template <class I, class T>
class IteratorObject: public IteratorInst<T> {
	I iter;
public:
	inline IteratorObject(I& _iter);
	virtual bool ended(void) const;
	virtual T item(void) const;
	virtual void next(void);	
};
	

// Iterator class
template <class T> class Iterator {
protected:
	IteratorInst<T> *iter;
public:
	inline Iterator(IteratorInst<T> *_iter);
	inline ~Iterator(void);
	inline bool ended(void) const;
	inline T item(void) const;
	inline void next(void);
	inline Iterator<T>& operator++(int _);
	inline operator bool(void) const;
	inline T operator*(void) const;
	inline T operator->(void) const;
	inline operator T(void) const;
};


// MutableIteratorInst class
template <class T> class MutableIteratorInst {
public:
	virtual bool ended(void) const = 0;
	virtual T& item(void) = 0;
	virtual void next(void) = 0;
	virtual void remove(void) = 0;
};


// MutableIterator class
template <class T> class MutableIterator {
protected:
	MutableIteratorInst<T> *edit;
public:
	inline MutableIterator(MutableIteratorInst<T> *_edit);
	inline ~MutableIterator(void);
	inline bool ended(void) const;
	inline T& item(void);
	inline void next(void);
	inline void remove(void);
	inline MutableIterator<T>& operator++(int _);
	inline operator bool(void) const;
	inline T operator*(void) const;
};


// IteratorInst methods
template <class T> inline IteratorInst<T>& IteratorInst<T>::operator++(int _) {
	next(); return *this;
}

template <class T> inline IteratorInst<T>::operator bool(void) const {
	return !ended();
}

template <class T> inline T IteratorInst<T>::operator*(void) const {
	return item();
}

template <class T> inline T IteratorInst<T>::operator->(void) const {
	return item();
}

template <class T> inline IteratorInst<T>::operator T(void) const {
	return item();
}


// Iterator methods
template <class T> Iterator<T>::Iterator(IteratorInst<T> *_iter): iter(_iter) {
}
template <class T> Iterator<T>::~Iterator(void) {
	delete iter;
}
template <class T> bool Iterator<T>::ended(void) const {
	return iter->ended();
}
template <class T> T Iterator<T>::item(void) const {
	return iter->item();
}
template <class T> void Iterator<T>::next(void) {
	iter->next();
}
template <class T> Iterator<T>& Iterator<T>::operator++(int _) {
	next();
	return *this;
}
template <class T> Iterator<T>::operator bool(void) const {
	return !ended();
}
template <class T> T Iterator<T>::operator*(void) const {
	return item();
};
template <class T> T Iterator<T>::operator->(void) const {
	return item();
};
template <class T> inline Iterator<T>::operator T(void) const {
		return item();
}


// MutableIterator methods
template <class T>
MutableIterator<T>::MutableIterator(MutableIteratorInst<T> *_edit)
: edit(_edit) {
}

template <class T> MutableIterator<T>::~MutableIterator(void) {
	delete edit;
}

template <class T> bool MutableIterator<T>::ended(void) const {
	return edit->ended();
}

template <class T> T& MutableIterator<T>::item(void) {
	return edit->item();
}

template <class T> void MutableIterator<T>::next(void) {
	edit->next();
}

template <class T> void MutableIterator<T>::remove(void) {
	edit->remove();
}

template <class T> MutableIterator<T>& MutableIterator<T>::operator++(int _) {
	next();
	return *this;
}

template <class T> MutableIterator<T>::operator bool(void) const {
	return !ended();
}

template <class T> T MutableIterator<T>::operator*(void) const {
	return item();
};


// IteratorObject inlines
template <class I, class T>
inline IteratorObject<I, T>::IteratorObject(I& _iter): iter(_iter) {
};
template <class I, class T>
bool IteratorObject<I, T>::ended(void) const {
	return iter.ended();
};
template <class I, class T>
T IteratorObject<I, T>::item(void) const {
	return iter.item();
};
template <class I, class T>
void IteratorObject<I, T>::next(void) {
	iter.next();
};

} // elm::datastruct

#endif // ELM_DATASTRUCT_ITERATOR_H
