/*
 *	avl::GenTree class interface
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
#ifndef ELM_AVL_GENTREE_H
#define ELM_AVL_GENTREE_H

#include <elm/utility.h>
#include <elm/PreIterator.h>
#include <elm/adapter.h>
#include <elm/array.h>
#include <elm/data/StaticStack.h>
#include <elm/data/Vector.h>

namespace elm { namespace avl {

template <class T> class Debug;

// Private class
class AbstractTree {
public:
	inline int count(void) const { return _cnt; }

protected:
	static const int MAX_HEIGHT = 32;
	typedef signed char balance_t;
	typedef enum {
		LEFT = -1,
		RIGHT = +1
	} dir_t;

	inline AbstractTree(void): _root(nullptr), _cnt(0) { }

	class Node {
	public:
		inline Node(void): _left(nullptr), _right(nullptr), _bal(0) { }
		Node *_left, *_right;
		balance_t _bal;
	};

	class Stack: public StaticStack<Pair<Node *, dir_t>, MAX_HEIGHT> {
	public:
		inline Stack(void) { }
		inline void push(Node *node, dir_t dir)
			{ StaticStack<Pair<Node *, dir_t>, MAX_HEIGHT>::push(pair(node, dir)); }
		inline dir_t topDir(void) const { return this->top().snd; }
		inline Node *topNode(void) const { return this->top().fst; }
	};

	Node **link(const Stack& s);
	void exchange(Node *n, Node *m);
	void insert(Stack& stack, Node *node);
	void rotateRight(Stack& s);
	void rotateLeft(Stack& s);
	void remove(Stack& stack, Node *n);
	Node *leftMost(Stack& s, Node *n);

	Node *_root;
	int _cnt;
};

// GenAVLTree class
template <class T, class K = IdAdapter<T>, class C = elm::Comparator<typename K::key_t> >
class GenTree: public AbstractTree {
	friend class Debug<T>;
protected:

	class Node: public AbstractTree::Node {
	public:
		inline Node(const T& item): data(item) { }
		inline Node(const Node *node): data(node->data) { _bal = node->_bal; }
		inline Node *left(void) { return static_cast<Node *>(_left); }
		inline Node *right(void) { return static_cast<Node *>(_right); }
		inline const typename K::key_t& key(void) const { return K::key(data); }
		T data;
	};

	inline Node *root(void) const { return static_cast<Node *>(_root); }

	class Stack: public AbstractTree::Stack {
	public:
		inline Node *topNode(void) const { return static_cast<Node *>(AbstractTree::Stack::topNode()); }
	};

	class VisitStack: public StaticStack<Node *, MAX_HEIGHT> {
	public:
		inline VisitStack(void) { }
		inline VisitStack(Node *n) { this->push(n); }
		inline void copyLeft(VisitStack& s)
			{ s.top()->_left = new Node(this->top()->left()); s.push(s.top()->left()); this->push(this->top()->left()); }
		inline void copyRight(VisitStack& s)
			{ s.top()->_right = new Node(this->top()->right()); s.push(s.top()->right()); this->push(this->top()->right()); }
	};

public:

	GenTree(void) { }
	GenTree(const GenTree<T>& tree) { copy(tree); }
	~GenTree(void) { /*clear();*/ }

	inline T *get(const typename K::key_t& key)
		{ Node *node = find(key); if(!node) return 0; else return &node->data; }
	inline const T *get(const typename K::key_t& key) const
		{ const Node *node = find(key); if(!node) return 0; else return &node->data; }

	// Collection concept
	inline int count(void) const { return _cnt; }
	inline bool contains(const typename K::key_t& item) const { return find(item) != nullptr; }
	inline bool isEmpty(void) const { return _cnt == 0; }
	inline operator bool(void) const { return !isEmpty(); }

	template <template <class _> class Co>
	inline bool containsAll(const Co<T>& coll) const
		{ for(typename Co<T>::Iterator iter(coll); iter; iter++)
			if(!contains(iter)) return false; return true; }

	// Iterator class
	class Iterator: public PreIterator<Iterator, const T&> {
	public:
		inline Iterator(void) { }
		inline Iterator(const GenTree<T, K, C>& tree)
			{ if(tree.root()) visit(tree.root()); }
		inline bool ended(void) const { return s.isEmpty(); }
		void next(void) {
			while(true) {
				Node *last = s.pop();
				if(ended()) return;
				if(last == s.top()->left()) { s.push(s.top()); break; }
				else if(last == s.top() && s.top()->right()) { visit(s.top()->right()); break; }
			}
		}
		inline const T& item(void) const { return s.top()->data; }
		inline bool operator==(const Iterator& i) const { return s.equals(i.s); }
		inline bool operator!=(const Iterator& i) const { return !operator==(i); }

	protected:
		inline T& data(void) { return s.top()->data; }

	private:
		void visit(Node *node) {
			if(!node) return;
			s.push(node);
			while(s.top()->left()) s.push(s.top()->left());
			s.push(s.top());
		}
		VisitStack s;
	};
	inline Iterator begin(void) const { return Iterator(*this); }
	inline Iterator end(void) const { return Iterator(); }

	// MutableCollection concept
	void clear(void) {
		VisitStack s;
		if(root() != nullptr)
			s.push(root());
		while(!s.isEmpty()) {
			Node *n = s.pop();
			if(n->left() != nullptr)
				s.push(n->left());
			if(n->right() != nullptr)
				s.push(n->right());
			delete n;
		}
		_root = nullptr;
		_cnt = 0;
	}

	void copy(const GenTree<T, K, C>& tree) {
		clear();
		if(!tree._root)
			return;
		_root = new Node(tree.root());
		_cnt = tree._cnt;
		VisitStack ss(tree.root()), st(root());
		while(!ss.isEmpty()) {
			if(ss.top()->left() != nullptr)
				ss.copyLeft(st);
			else {
				while(ss.top()->right() == nullptr) {
					Node *prv;
					do {
						prv = ss.pop();
						st.pop();
						if(ss.isEmpty())
							return;
					}
					while(ss.top()->right() == prv);
				}
				ss.copyRight(st);
			}
		}
	}
	inline GenTree<T, K, C>& operator=(const GenTree<T, K, C>& tree) { copy(tree); return *this; }

	void add(const T& item) {
		Stack s;
		Node *n = lookup(s, K::key(item));
		if(n == nullptr)
			AbstractTree::insert(s, new Node(item));
	}

	void set(const T& item) {
		add(item);
	}

	void remove(const typename K::key_t& item) {

		// find the node
		Stack s;
		Node *n = lookup(s, item);
		if(n == nullptr)
			return;

		// simple leaf cases
		if(n->left() == nullptr)
			AbstractTree::remove(s, n->right());
		else if(n->right() == nullptr)
			AbstractTree::remove(s, n->left());

		// in middle case
		else {
			s.push(n, RIGHT);
			Node *p = static_cast<Node *>(leftMost(s, n->right()));
			cerr << "p = " << (void *)p  << io::endl;
			exchange(p, n);
			AbstractTree::remove(s, p->right());
		}
	}

	inline void remove(const Iterator& iter) { remove(iter.item()); }
	template <class CC> inline void addAll(const CC& coll)
		{ for(typename CC::Iterator iter(coll); iter; iter++) add(iter); }
	template <class CC> inline void removeAll(const CC& coll)
		{ for(typename CC::Iterator iter(coll); iter; iter++) remove(iter); }

	bool equals(const GenTree<T, K, C>& tree) const {
		GenTree<T, K, C>:: Iterator ai(*this), bi(tree);
		for(; ai && bi; ai++, bi++)
			if(!(C::compare(*ai, *bi) == 0))
				return false;
		return !ai && !bi;
	}
	inline bool operator==(const GenTree<T, K, C>& tree) const { return equals(tree); }
	inline bool operator!=(const GenTree<T, K, C>& tree) const { return !equals(tree); }

private:

	inline int compare(const typename K::key_t& k1, const typename K::key_t& k2) const
		{ return C::compare(k1, k2); }

	Node *lookup(Stack& s, const typename K::key_t& key) const {
		Node *p = root();
		while(p != nullptr) {
			int cmp = compare(key, K::key(p->data));
			if(cmp == 0)
				break;
			else if(cmp < 0) {
				s.push(p, LEFT);
				p = p->left();
			}
			else {
				s.push(p, RIGHT);
				p = p->right();
			}
		}
		return p;
	}

	Node *find(const typename K::key_t& key) const {
		for(Node *p = root(); p;) {
			int cmp = compare(key, p->key());
			if(cmp < 0)
				p = p->left();
			else if(cmp > 0)
				p = p->right();
			else
				return p;
		}
		return nullptr;
    }

	void exchange(Node *n, Node *p) {
		auto t = p->data;
		p->data = n->data;
		n->data = t;
	}
};

} }	// elm::avl

#endif	// ELM_AVL_GENTREE_H
