/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * utility.h -- useful classes interfaces.
 */
#ifndef ELM_UTILITY_H
#define ELM_UTILITY_H

#include <assert.h>
#include <elm/string.h>

namespace elm {

// Exception class
class Exception {
public:
	virtual ~Exception(void) { };
	virtual String message(void) = 0;
};


// Error class
class Error: public Exception {
};


// Optional value
template <class T> class Option {
	bool one;
	T val;
public:
	inline Option(void): one(false) { };
	inline Option(const T& value): one(true), val(value) { };
	inline Option(const Option<T> &opt): one(opt.one), val(opt.val) { };
	inline bool isOne(void) const { return one; };
	inline bool isNone(void) const { return !one; };
	inline T value(void) const { return val; };
	inline operator bool(void) const { return one; };
	inline T operator*(void) const { return val; };
	inline Option<T>& operator=(const Option<T>& opt)
		{ one = opt.one; val = opt.val; };
};


// HashKey class
template <class T> class HashKey {
public:
	static HashKey<T>& def;
	virtual unsigned long hash(T key) = 0;
	virtual bool equals(T key1, T key2) = 0;
};


// Comparator class
template <class T> class Comparator {
public:
	static Comparator<T>& def;
	virtual int compare(T v1, T v2) = 0;
};


// Lock class
class Lock {
	int usage;
public:
	inline Lock(int _usage = 0);
	virtual ~Lock(void) { };
	inline void lock(void);
	inline void unlock();
};


// AutoPtr class
template <class T> class AutoPtr {
	Lock *ptr;
	static inline Lock *null(void);
public:
	inline AutoPtr(T *p = 0);
	inline AutoPtr(const AutoPtr& locked);
	inline ~AutoPtr(void);
	inline AutoPtr& operator=(const AutoPtr& locked);
	inline AutoPtr& operator=(T *p);
	inline T *operator->(void) const;
	inline T& operator*(void) const;
	inline T *operator&(void) const;
	inline bool isNull(void) const;
	inline operator bool(void) const { return !isNull(); };
	inline bool operator==(const AutoPtr<T>& ap) const;
	inline bool operator!=(const AutoPtr<T>& ap) const;
	inline bool operator>(const AutoPtr<T>& ap) const;
	inline bool operator>=(const AutoPtr<T>& ap) const;
	inline bool operator<(const AutoPtr<T>& ap) const;
	inline bool operator<=(const AutoPtr<T>& ap) const;
};

// Lock methods
Lock::Lock(int _usage): usage(_usage) {
}
void Lock::lock(void) {
	usage++;
}
void Lock::unlock() {
	if(!(--usage))
		delete this;
}


// AutoPtr methods
template <class T> Lock *AutoPtr<T>::null(void) {
	static Lock _null(1);
	return &_null;
}
template <class T> AutoPtr<T>::AutoPtr(T *p): ptr(p ? (Lock *)p : null()) {
	ptr->lock();
}
template <class T> AutoPtr<T>::~AutoPtr(void) {
	ptr->unlock();
}
template <class T> T *AutoPtr<T>::operator->(void) const {
	assert(!isNull());
	return (T *)ptr;
}
template <class T> AutoPtr<T>::AutoPtr(const AutoPtr& locked): ptr(locked.ptr) {
	ptr->lock();
}
template <class T> AutoPtr<T>& AutoPtr<T>::operator=(const AutoPtr& locked) {
	ptr->unlock();
	ptr = locked.ptr;
	ptr->lock();
	return *this;
}
template <class T> AutoPtr<T>& AutoPtr<T>::operator=(T *p) {
	ptr->unlock();
	ptr = p ? p : null();
	ptr->lock();
	return *this;
}
template <class T> bool AutoPtr<T>::isNull(void) const {
	return ptr == null();
}
template <class T> T& AutoPtr<T>::operator*(void) const {
	assert(!isNull());
	return *(T *)ptr;
}

template <class T> T *AutoPtr<T>::operator&(void) const {
	return isNull() ? 0 : (T *)ptr;
}
template <class T> bool AutoPtr<T>::operator==(const AutoPtr<T>& ap) const {
	return ptr == ap.ptr;
}
template <class T> bool AutoPtr<T>::operator!=(const AutoPtr<T>& ap) const {
	return ptr != ap.ptr;
}
template <class T> bool AutoPtr<T>::operator>(const AutoPtr<T>& ap) const {
	return ptr > ap.ptr;
}
template <class T> bool AutoPtr<T>::operator>=(const AutoPtr<T>& ap) const {
	return ptr >= ap.ptr;
}
template <class T> bool AutoPtr<T>::operator<(const AutoPtr<T>& ap) const {
	return ptr < ap.ptr;
}
template <class T> bool AutoPtr<T>::operator<=(const AutoPtr<T>& ap) const {
	return ptr <= ap.ptr;
}


};	// elm

#endif	// ELM_UTILITY_H
