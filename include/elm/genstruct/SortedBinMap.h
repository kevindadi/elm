/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/genstruct/SortedBinMap.h -- binary map interface.
 */
#ifndef ELM_GENSTRUCT_SORTEDBINMAP_H
#define ELM_GENSTRUCT_SORTEDBINMAP_H

#include <elm/utility.h>
#include <elm/inhstruct/SortedBinTree.h>

namespace elm { namespace genstruct {

// SortedBinMap class
template <class K, class T>
class SortedBinMap: private inhstruct::SortedBinTree {

protected:
	class Node: public inhstruct::SortedBinTree::Node {
		K _key;
		T _val;
	public:
		inline Node(K key, T val);
		inline Node(K key);
		inline Node(const Node& value);
		inline K key(void) const;
		inline T& value(void);
	};

	virtual int compare(inhstruct::SortedBinTree::Node *node1,
		inhstruct::SortedBinTree::Node *node2);

public:
	class Visitor {
	public:
		virtual void process(K key, T& data) = 0;
	};

private:
	class TreeVisitor: public inhstruct::SortedBinTree::Visitor {
		typename SortedBinMap<K, T>::Visitor& visitor;
	public:
		inline TreeVisitor(typename SortedBinMap<K, T>::Visitor& _visitor);
		virtual int process(inhstruct::SortedBinTree::Node *value);
	};
		
	Comparator<K>& comp;

public:	
	inline SortedBinMap(void);
	inline SortedBinMap(elm::Comparator<K>& comp);
	inline bool isEmpty(void) const;
	inline int count(void);
	inline void visit(SortedBinMap<K, T>::Visitor& visitor);
	inline Option<T> get(K key);
	inline T get(K key, T def_value);
	inline bool exists(K key);
	inline void put(K key, T value);
	inline void remove(K key);
	inline void clear(void);
};


// Node inlines
template <class K, class T>
inline SortedBinMap<K, T>::Node::Node(K key, T val): _key(key), _val(val) {
}

template <class K, class T>
inline SortedBinMap<K, T>::Node::Node(K key): _key(key) {
}

template <class K, class T>
inline SortedBinMap<K, T>::Node::Node(const Node& value)
: _key(value._key), _val(value._val) {
}

template <class K, class T>
inline K SortedBinMap<K, T>::Node::key(void) const {
	return _key;
}

template <class K, class T>
inline T& SortedBinMap<K, T>::Node::value(void) {
	return _val;
}


// TreeVisitor inlines
template <class K, class T>
inline SortedBinMap<K, T>::TreeVisitor::TreeVisitor(SortedBinMap<K, T>::Visitor& _visitor)
: visitor(_visitor) {
}

template <class K, class T>
int SortedBinMap<K, T>::TreeVisitor::process(
inhstruct::SortedBinTree::Node *value) {
	visitor.process(((Node *)value)->key(), ((Node *)value)->value());
	return 1;
}


// SortedBinMap inlines
template <class K, class T>
inline SortedBinMap<K, T>::SortedBinMap(void)
: comp(elm::Comparator<K>::def) {
}

template <class K, class T>
inline SortedBinMap<K, T>::SortedBinMap(elm::Comparator<K>& _comp)
: comp(_comp) {
}

template <class K, class T>
inline bool SortedBinMap<K, T>::isEmpty(void) const {
	return inhstruct::SortedBinTree::isEmpty();
}

template <class K, class T>
int SortedBinMap<K, T>::count(void) {
	return inhstruct::SortedBinTree::count();
}

template <class K, class T>
inline Option<T> SortedBinMap<K, T>::get(K key) {
	Node test_node(key);
	Node *res = (Node *)inhstruct::SortedBinTree::get(&test_node);
	if(!res)
		return Option<T>();	
	else
		return Option<T>(res->value());
}

template <class K, class T>
inline T SortedBinMap<K, T>::get(K key, T def_value) {
	Node test_node(key);
	Node *node = (Node *)inhstruct::SortedBinTree::get(&test_node);
	if(!node)
		return def_value;	
	else
		return node->value();
}

template <class K, class T>
inline bool SortedBinMap<K, T>::exists(K key) {
	Node test_node(key);
	Node *node = (Node *)inhstruct::SortedBinTree::get(&test_node);
	return node != 0;
}

template <class K, class T>
inline void SortedBinMap<K, T>::put(K key, T value) {
	Node *node = new Node(key, value);
	inhstruct::SortedBinTree::insert(node);
}

template <class K, class T>
inline void SortedBinMap<K, T>::remove(K key) {
	Node test_node(key);
	inhstruct::SortedBinTree::remove(&test_node);
}

template <class K, class T>
inline void SortedBinMap<K, T>::clear(void) {
	inhstruct::SortedBinTree::clear();
}

template <class K, class T>
inline void SortedBinMap<K, T>::visit(genstruct::SortedBinMap<K, T>::Visitor& visitor) {
	TreeVisitor tree_visitor(visitor);
	inhstruct::SortedBinTree::visit(&tree_visitor);
}

template <class K, class T>
int SortedBinMap<K, T>::compare(inhstruct::SortedBinTree::Node *node1,
inhstruct::SortedBinTree::Node *node2) {
	return comp.compare(((Node *)node1)->key(), ((Node *)node2)->key());
}

} } // elm::genstruct

#endif // ELM_GENSTRUCT_SORTEDBINMAP_H
