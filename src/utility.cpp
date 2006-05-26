/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * collection.cc -- collection classes implementation.
 */

#include <elm/utility.h>

namespace elm {

// int_hkey
class IntHashKey: public HashKey<int> {
	virtual unsigned long hash(int v) {
		return (unsigned long)v;
	};
	virtual bool equals(int key1, int key2) {
		return key1 == key2;
	};
};
static IntHashKey int_hkey_obj;
template <> HashKey<int>& HashKey<int>::def = int_hkey_obj;

// pointer_hkey
class PointerHashKey: public HashKey<void *> {
	virtual unsigned long hash(void *v) {
		return (unsigned long)v;
	};
	virtual bool equals(void *key1, void * key2) {
		return key1 == key2;
	};
};
static PointerHashKey pointer_hkey_obj;
template <> HashKey<void *>& HashKey<void *>::def = pointer_hkey_obj;

// cstring_hkey
class CStringHashKey: public HashKey<CString> {
	virtual unsigned long hash(CString str) {
		unsigned long h = 0, g;
		const char *id = str.chars();
		while(*id) {
			h = (h << 4) + *id;
			if(g = h & 0xf0000000) {
				h = h ^ (g >> 24);
				h = h ^ g;
			}
			id++;
		}
		return h;
	};
	virtual bool equals(CString key1, CString key2) {
		return key1 == key2;
	};
};
static CStringHashKey cstring_hkey_obj;
template <> HashKey<CString>& HashKey<CString>::def = cstring_hkey_obj;

// string_hkey
class StringHashKey: public HashKey<String> {
	virtual unsigned long hash(String str) {
		unsigned long h = 0, g;
		for(int i = 0; i < str.length(); i++) {
			h = (h << 4) + str.charAt(i);
			if(g = h & 0xf0000000) {
				h = h ^ (g >> 24);
				h = h ^ g;
			}
		}
		return h;
	};
	virtual bool equals(String key1, String key2) {
		return key1 == key2;
	};
};
static StringHashKey string_hkey_obj;
template <> HashKey<String>& HashKey<String>::def = string_hkey_obj;

// int_comp
class IntComparator: public Comparator<int> {
	virtual int compare(int v1, int v2) {
		return v1 > v2 ? 1 : (v1 == v2 ? 0 : -1);
	};
};
static IntComparator int_comp_obj;
template <> Comparator<int>& Comparator<int>::def = int_comp_obj;

// pointer_comp
class PointerComparator: public Comparator<void *> {
	virtual int compare(void *v1, void *v2) {
		return v1 > v2 ? 1 : (v1 == v2 ? 0 : -1);
	};
};
static PointerComparator pointer_comp_obj;
template <> Comparator<void *>& Comparator<void *>::def = pointer_comp_obj;

// cstring_comp
class CStringComparator: public Comparator<CString> {
	virtual int compare(CString v1, CString v2) {
		return v1.compare(v2);
	};
};
static CStringComparator cstring_comp_obj;
template <> Comparator<CString>& Comparator<CString>::def = cstring_comp_obj;

// string_comp
class StringComparator: public Comparator<String> {
	virtual int compare(String v1, String v2) {
		return v1.compare(v2);
	};
};
static StringComparator string_comp_obj;
template <> Comparator<String>& Comparator<String>::def = string_comp_obj;


/**
 * @class Pair
 * This template class is mainly useful for returning or passing in parameter
 * a data item composed of a two values.
 * @param T1	First value type.
 * @param T2	Second value type.
 */


/**
 * @var Pair::fst;
 * The first value of the pair : may be read or written.
 */


/**
 * @var Pair::snd;
 * The second value of the pair : may be read or written.
 */


/**
 * @fn Pair::Pair(const T1& _fst, const T2& _snd);
 * Build a pair from two values.
 * @param _fst	First value.
 * @param _snd	Second value.
 */


/**
 * @fn Pair::Pair(const Pair<T1, T2>& pair);
 * Build a pair by copying another pair.
 * @param pair	Pair to copy.
 */


/**
 * @fn Pair<T1, T2>& Pair::operator=(const Pair<T1, T2>& pair);
 * Assignment overload for pairs.
 * @param pair	Pair to assign.
 * @return		Current pair.
 */

};
