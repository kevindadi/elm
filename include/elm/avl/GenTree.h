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
#include <elm/data/Vector.h>

namespace elm { namespace avl {

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

	class Stack {
	public:
		inline Stack(void): _top(0) { }
		inline void push(Node *node, dir_t dir)
			{ _nodes[_top] = node; _dirs[_top] = dir; _top++; }
		inline void pop(void) { _top--; }
		inline bool empty(void) const { return _top == 0; }
		inline dir_t topDir(void) const { return _dirs[_top - 1]; }
		inline Node *topNode(void) const { return _nodes[_top - 1]; }
	private:
		int _top;
		Node *_nodes[MAX_HEIGHT];
		dir_t _dirs[MAX_HEIGHT];
	};

	Node **link(const Stack& s);
	void exchange(Node *n, Node *m);
	void insert(Stack& stack, Node *node);
	void rotateRight(Stack& s);
	void rotateLeft(Stack& s);
	void remove(Stack& stack, Node *n);

	Node *_root;
	int _cnt;
};

// GenAVLTree class
template <class T, class K = IdAdapter<T>, class C = elm::Comparator<typename K::key_t> >
class GenTree: public AbstractTree {
protected:

	class Node: public AbstractTree::Node {
	public:
		inline Node(const T& item): data(item) { }
		inline Node(const Node *node): data(node->data) { }
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

	class VisitStack {
	public:
		VisitStack(void): _sp(_stack) { }
		inline void push(Node *n) { *_sp = n; _sp++; }
		inline Node *pop(void) { _sp--; return *_sp; }
		inline Node *top(void) const { return _sp[-1]; }
		inline bool empty(void) const { return _sp == _stack; }
		inline bool equals(const VisitStack& v) const
			{ 	Node *s1 = _stack, *s2 = v._stack;
				while( s1 < _sp && s2 < v._sp) { if(*s1 != *s2) return false; s1++; s2++; }
				return s1 == _sp && s2 == v._sp; }
		inline void fillLeft(Node *n)
			{ push(n); while(top()->left()) push(top()->left()); }
		inline Node *createLeft(Node *n)
			{ Node *r = new Node(n); push(r); for(Node *p= r; n != nullptr; n = n->left()) { p->_left = new Node(n); p = p->_left; push(p); }; return r; }
	private:
		Node *_stack[MAX_HEIGHT], **_sp;
	};

public:

	GenTree(void) { }
	GenTree(const GenTree<T>& tree) { copy(tree); }
	~GenTree(void) { clear(); }

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
		inline bool ended(void) const { return s.empty(); }
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
			s.fillLeft(root());
		while(!s.empty()) {
			Node *n = s.pop();
			if(!s.empty() && n == s.top()->right())
				s.fillLeft(s.top()->right());
			else
				delete n;
		}
		_root = nullptr;
	}

	void copy(const GenTree<T, K, C>& tree) {
		clear();
		VisitStack s;
		if(tree.root() != nullptr)
			_root = s.createLeft(root());
		while(!s.empty()) {
			Node *n = s.pop();
			if(!s.empty() && s.top()->right() == n)
				s.top()->_right = s.createLeft(s.top()->right());
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
		Stack s;
		Node *n = root();
		while(n) {
			int cmp = compare(item, n->key());
			if(cmp < 0) {
				n = n->left();
				s.push(n, LEFT);
			}
			else if(cmp > 0) {
				n = n->right();
				s.push(n, RIGHT);
			}
			else {
				if(n->left() == nullptr) {
					AbstractTree::remove(s, n->right());
					break;
				}
				else if(n->right() == nullptr) {
					AbstractTree::remove(s, n->left());
					break;
				}
				else {
					Node *p = n->right();
					while(p->left())
						p = p->left();
					*link(s) = p;
					exchange(p, n);
					n = p->right();
					s.push(p, RIGHT);
				}
			}
		}
		if(n)
			delete n;
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

#	ifdef ELM_AVL_CHECK
		bool __left_sorted(Node *n)
			{ return n == nullptr
				  || ((n->_left == nullptr || compare(n->left()->key(), n->key()) < 0) && __left_sorted(n->left()) && __left_sorted(n->right())); }
		bool __right_sorted(Node *n)
			{ return n == nullptr
				  || ((n->_right == nullptr || compare(n->key(), n->right()->key()) < 0) && __right_sorted(n->left()) && __right_sorted(n->right())); }
		bool __balanced(Node *n)
			{	return n == nullptr ||
				(n->_bal == __height(n->right()) - __height(n->left()) && -1 <= n->_bal && n->_bal <= 1); }
		int __height(Node *n)
			{ return n == nullptr ? 0 : (1 + max(__height(n->left()), __height(n->right()))); }
		bool __invariant(void) { return __left_sorted(root()) && __right_sorted(root()) && __balanced(root()); }
		void dump(Node *n, int t = 0)
			{	if(n == nullptr) return; dump(n->left(), t+1); for(int i = 0; i < t; i++) cout << "  ";
				cout << n->data << io::endl; dump(n->right(), t+1); }
		void dump(void) { if(root() == nullptr) cout << "empty\n"; else dump(root()); }
#	endif

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

};

} }	// elm::avl

#endif	// ELM_AVL_GENTREE_H
