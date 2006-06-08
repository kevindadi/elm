/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/Pair.h -- interface of Pair class.
 */
#ifndef ELM_UTIL_PAIR_H
#define ELM_UTIL_PAIR_H

namespace elm {

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

} // elm

#endif /* ELM_UTIL_PAIR_H */
