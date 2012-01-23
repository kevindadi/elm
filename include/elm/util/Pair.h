/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * elm/util/Pair.h -- interface of Pair class.
 */
#ifndef ELM_UTIL_PAIR_H
#define ELM_UTIL_PAIR_H

namespace elm {

namespace io { class Output; }

// Pair class
template <class T1, class T2>
class Pair {
public:
	T1 fst;
	T2 snd;
	inline Pair(void) { }
	inline Pair(const T1& _fst, const T2& _snd)
		: fst(_fst), snd(_snd) { }
	inline Pair(const Pair<T1, T2>& pair)
		: fst(pair.fst), snd(pair.snd) { }
	inline Pair<T1, T2>& operator=(const Pair<T1, T2>& pair) 
		{ fst = pair.fst; snd = pair.snd; return *this; }
	inline bool operator==(const Pair<T1, T2>& pair) const
		{
	return ((fst== pair.fst) && (snd == pair.snd));
}
};


// Shortcuts
template <class T1, class T2>
inline Pair<T1, T2> pair(const T1& v1, const T2& v2) {
	return Pair<T1, T2>(v1, v2);
}

template <class T1, class T2>
io::Output& operator<<(io::Output& out, Pair<T1, T2>& p)
	{ out << p.fst << ", " << p.snd; return out; }

} // elm

#endif /* ELM_UTIL_PAIR_H */
