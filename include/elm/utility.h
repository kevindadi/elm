/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
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


// Pair class
template <class T1, class T2>
class Pair {
public:
	T1 fst;
	T2 snd;
	inline Pair(const T1& _fst, const T2& _snd);
	inline Pair(const Pair<T1, T2>& pair);
	inline Pair<T1, T2>& operator=(const Pair<T1, T2>& pair);
};

// Pair inlines
template <class T1, class T2>
inline Pair<T1, T2>::Pair(const T1& _fst, const T2& _snd): fst(_fst), snd(_snd) {
}

template <class T1, class T2>
inline Pair<T1, T2>::Pair(const Pair<T1, T2>& pair)
: fst(pair.fst), snd(pair.snd) {
}

template <class T1, class T2>
inline Pair<T1, T2>& Pair<T1, T2>::operator=(const Pair<T1, T2>& pair) {
	fst = pair.fst;
	snd = pair.snd;
}

};	// elm

#endif	// ELM_UTILITY_H
