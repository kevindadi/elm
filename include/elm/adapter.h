/*
 *	adapter module interface
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
#ifndef ELM_ADAPTER_H_
#define ELM_ADAPTER_H_

namespace elm {

// Id adapter
template <class T>
class IdAdapter {
public:
	typedef T t;
	static inline const T& key(const T& v) { return v; }
	static inline const T& value(const T& v) { return v; }
	static inline T& ref(T& v) { return v; }
};


// Pair adapter
template <class K, class T>
class PairAdapter {
public:
	typedef K t;
	typedef Pair<K, T> d;
	static inline const K& key(const d& v) { return v.fst; }
	static inline const T& value(const d& v) { return v.snd; }
	static inline T& ref(d& v) { return v.snd; }
};

}	// elm

#endif /* ELM_ADAPTER_H_ */
