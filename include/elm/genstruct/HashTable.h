/*
 *	$Id$
 *	genstruct::HashTable class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-08, IRIT UPS.
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
#ifndef ELM_GENSTRUCT_HASHTABLE_H
#define ELM_GENSTRUCT_HASHTABLE_H

#include <elm/util/Pair.h>
#include <elm/PreIterator.h>
#include <elm/util/HashKey.h>
#include <elm/type_info.h>

namespace elm { namespace genstruct {

// InHashTable class
template <class K, class T, class H = HashKey<K> >
class HashTable {

	typedef struct node_t {
		node_t *next;
		K key;
		T value;
		node_t(const K& key) : key(key) { }
	} node_t;

	int size;
	node_t **tab;

	node_t *find(const K& key) {
		int i = H::hash(key) % size;
		for(node_t *node = tab[i], *prev = 0; node; prev = node, node = node->next)
			if(H::equals(node->key, key)) {
				if(prev) { prev->next = node->next; node->next = tab[i]; tab[i] = node; }
				return node;
			}
		return 0;
	}

	node_t *make(const K& key, const T& value)
		{ int i = H::hash(key) % size; node_t *node = new node_t(key); node->next = tab[i];
		tab[i] = node; node->value = value; return node; }

	// InternIterator
	class InternIterator {
	public:
		inline InternIterator(const HashTable<K, T, H>& _htab): htab(&_htab) { i = 0; step(); }
		inline InternIterator(const InternIterator& it): node(it.node), htab(it.htab), i(it.i) { }
		inline InternIterator& operator=(const InternIterator& it) { htab = it.htab; i = it.i; node = it.node; }
		inline bool ended(void) const { return i >= htab->size; }
		inline void next(void) { node = node->next; if(!node) { i++; step(); }  }
	protected:
		node_t *node;
	private:
		inline void step(void) { for(; i < htab->size; i++) if(htab->tab[i]) { node = htab->tab[i]; break; } }
		const HashTable<K, T, H> *htab;
		int i;
	};

	class Ref {
	public:
		inline Ref(HashTable<K, T, H>& tab, const K& key): t(tab), k(key) { }
		inline operator const K&(void) const { return get(); }
		inline const T& operator*(void) const { return get(); };
		inline T& operator=(const T& v) const {
			node_t *node = t.find(k);
			if(!node)
				node = t.make(k, v);
			return node->value;
		}
	private:
		inline const T& get(void) const { node_t *node = t.find(k); ASSERTP(node, "key " << k << " not in hashtab"); return node->value; }
		HashTable<K, T, H>& t;
		const K& k;
	};

public:
	HashTable(int _size = 211): size(_size), tab(new node_t *[_size])
		{ for(int i = 0; i < size; i++) tab[i] = 0; }
	~HashTable(void)
		{ clear(); delete [] tab; }

	bool isEmpty(void) const
		{ for(int i = 0; i <size; i++) if(tab[i]) return false; return true; }
	int count(void) const
	 	 { int cnt = 0; for(int i = 0; i < size; i++) for(node_t *cur = tab[i]; cur; cur = cur->next) cnt++; return cnt; }

	inline Option<T> get(const K& key)
		{ node_t *node = find(key); return node ? Option<T>(type_info<T>::get(node->value)) : Option<T>(); }
	inline const T get(const K& key, const T& def_value)
		{ node_t *node = find(key); return node ? type_info<T>::get(node->value) : def_value; }
	inline bool hasKey(const K& key)
	 	 { node_t *node = find(key); return node != 0; }
	inline bool exists(const K& key) { return hasKey(key); };

	inline Ref operator[](const K& key) { return Ref(*this, key); }

	void put(const K& key, const T& value)
		{ node_t *node = find(key); if(node) node->value = value; else add(key, value); }
	void add(const K& key, const T& value) { make(key, value); }
	void putAll(const HashTable<K, T, H>& htab)
		{ for(int i = 0; i < htab.size; i++) for(node_t *node = htab.tab[i]; node; node = node->next)  put(type_info<K>::get(node->key), type_info<T>::get(node->value)); }

	void remove(const K& key) {
		int i = H::hash(key) % size;
		for(node_t *node = tab[i], *prev = 0; node; prev = node, node = node->next)
			if(H::equals(type_info<K>::get(node->key), key)) {
				if(prev)
					prev->next = node->next;
				else
					tab[i] = node->next;
				delete node;
				break;
			}
	}

	void clear(void) {
		for(int i = 0; i < size; i++) {
			for(node_t *cur = tab[i], *next; cur; cur = next) { next = cur->next; delete cur; }
			tab[i] = 0;
		}
	}

	// KeyIterator class
	class KeyIterator: public InternIterator, public PreIterator<KeyIterator, K> {
	public:
		inline KeyIterator(const HashTable<K, T, H>& htab): InternIterator(htab) { };
		inline KeyIterator(const KeyIterator& it): InternIterator(it) { }
		inline KeyIterator& operator=(const KeyIterator& it) { InternIterator::operator==(it); return *this; }
		inline const K& item(void) const { return type_info<K>::get(this->node->key); }
	};

	// Iterator class
	class Iterator: public InternIterator, public PreIterator<Iterator, T> {
	public:
		inline Iterator(const HashTable<K, T, H>& htab): InternIterator(htab) { };
		inline Iterator(const Iterator& it): InternIterator(it) { }
		inline Iterator& operator=(const Iterator& it) { InternIterator::operator=(it); return *this; }
		inline const T& item(void) const { return type_info<T>::get(this->node->value); }
		inline const T& useItem(void) const { return type_info<T>::get(this->node->value); }
		inline const K& key(void) const { return type_info<K>::get(this->node->key); };
	};

	// PairIterator class
	class PairIterator: public InternIterator, public PreIterator<PairIterator, Pair<K, T> > {
	public:
		inline PairIterator(const HashTable<K, T, H>& htab): InternIterator(htab) { };
		inline PairIterator(const PairIterator& it): InternIterator(it) { }
		inline PairIterator& operator=(const PairIterator& it) { InternIterator::operator=(it); return *this; }
		inline Pair<K, T> item(void) const { return pair(type_info<K>::get(this->node->key), this->node->value); }
	};

	// SameKeyIterator
	class SameKeyIterator: public PreIterator<SameKeyIterator, T> {
		const HashTable<K, T, H>& htab;
		K key;
		node_t *node;
		int i;
	public:
		inline SameKeyIterator(const HashTable<K, T, H>& _htab, const K& _key)
			: htab(_htab)
			{	type_info<K>::put(key, _key); i = H::hash(key) % size;
				for (node = htab.tab[i]; node && (node->key != key); node = node->next)
					;
				ASSERT(node != NULL); }
		inline bool ended(void) const {	return node == 0; }
		inline void next(void)
			{ node = node->next; for (node = htab.tab[i]; node && (type_info<K>::get(node->key) != type_info<K>::get(key)); node = node->next); }
		inline const T& item(void) const { return this->node->value; }
	};

};

} }	// elm::genstruct

#endif	// ELM_GENSTRUCT_HASHTABLE_H
