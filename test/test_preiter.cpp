/*
 * test-preiter.cpp
 *
 *  Created on: 15 juin 2020
 *      Author: casse
 */

#include <elm/iter.h>
#include <elm/test.h>

using namespace elm;

template <class T>
class MyArray {
public:

	MyArray() {
		for(int i = 0; i < 10; i++)
			t[i] = i;
	}
	~MyArray() {
	}

	class BaseIter: public PreIter<BaseIter, T> {
	public:
		inline BaseIter(const MyArray& array, int idx = 0): a(array), i(idx) { }
		inline bool ended() const { return i >= 10; }
		inline void next() { i++; }
		inline bool equals(const BaseIter& it) const { return i == it.i; }
	protected:
		const MyArray& a;
		int i;
	};

	class Iter: public BaseIter, public ConstPreIter<Iter, T> {
	public:
		using BaseIter::BaseIter;
		inline const T& item() const { return BaseIter::a.t[BaseIter::i]; }
	};

	class MutIter: public BaseIter, public MutPreIter<MutIter, T> {
	public:
		MutIter(MyArray<T>& a, int i = 0): BaseIter(a, i) { }
		inline T& item() { return const_cast<MyArray&>(BaseIter::a).t[BaseIter::i]; }
	};

	inline Iter begin() const {  return Iter(*this); }
	inline Iter end() const {  return Iter(*this, 10); }

	inline MutIter begin() {  return MutIter(*this); }
	inline MutIter end() {  return MutIter(*this, 10); }

	inline Iter cend() { return Iter(*this, 10); }

private:
	T t[10];
};


TEST_BEGIN(preiter)

{
	MyArray<int> a;
	int s = 0;
	for(auto x: a)
		s += x;
	CHECK_EQUAL(s, 45);
}

{
	const MyArray<int> a;
	int s = 0;
	for(auto x: a)
		s += x;
	CHECK_EQUAL(s, 45);
}

{
	MyArray<int> a;
	for(auto& x: a)
		x = 0;
	int s = 0;
	for(auto x: a)
		s += x;
	CHECK_EQUAL(s, 0);
}

{
	MyArray<int> a;
	CHECK(a.cend() == a.end());
	CHECK(a.end() == a.cend());
}

TEST_END


