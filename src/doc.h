/*
 *	Main documentation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008-17, IRIT UPS.
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
#ifndef ELM_DOC_H_
#define ELM_DOC_H_

namespace elm {

/**
 * @mainpage
 * 
 * ELM is a multi-purpose library used by the OTAWA project (http://www.otawa.fr).
 * It provides :
 * @li generic data structures,
 * @li generic interface with te operating system (files, command line, etc),
 * @li a checked plugin system,
 * @li efficient string class,
 * @li other utility classes.
 * 
 * The facilities of ELM (classes, functions, templates, etc) are sorted in the following
 * modules:
 * @li @ref alloc -- specialized allocators and interactive garbage collector,
 * @li @ref checksum -- checksum algorithms,
 * @li @ref data -- common generic data structures and associated facilities,
 * @li @ref dyndata -- data structure implementation using inheritance and virtual methods,
 * @li @ref ios -- unformatted and formatted input/output classes,
 * @li @ref json -- JSon format ELM implementation,
 * @li @ref net_mod -- network access abstraction classes,
 * @li @ref options -- command line option parsing classes,
 * @li @ref serial -- serialization facilities,
 * @li @ref string -- character string facilities,
 * @li @ref system -- system abstraction facilities (file system, plugin, random number, process management),
 * @li @ref rtti -- RTTI type support,
 * @li @ref types -- type information and other related functions,
 * @li @ref util -- miscellaneous utility classes (including debugging and testing helper classes),
 * @li @ref xom -- XML input/output classes.
 *
 * ELM contains a lot of useful features to make easier the developer life:
 * instead of reading the whole documentation, take a look to @ref recs
 * for a short list of more useful features.
 */

/*
 * @par Memory Management
 *
 * ELM supplies several classes to handle allocation and de-allocation:
 * @li default allocation scheme (@ref elm::DefaultAllocator),
 * @li allocate from a list of fixed size (@ref elm::BlockAllocator),
 * @li stack allocation with backtrack (@ref elm::StackAllocator),
 * @li semi-automatic specialized garbage collector (@ref elm::AbstractBlockAllocatorWithGC).
 *
 * And some cleanup classes or pointer management classes (@ref elm::AutoCleaner, @ref elm::AutoDestructor, @ref AutoPtr).
 *
 * @par Other Facilities
 * @li crash management (@ref elm::CrashHandler, only for Linux),
 * @li XML and XSLT using the XOM interface (@ref xom),
 * @li basic exceptions with message (@ref elm::Exception and @ref elm::MessageException),
 * @li very light test framework (@ref elm::TestCase and @ref elm::TestSet),
 * @li automatic serialization and unserialization (@ref serial),
 * @li work-around the C++ initialization fiasco (@ref elm::Initializer),
 * bit management (@ref elm::BitVector).
 */

/**
 * @defgroup utilities Development Utilities
 *
 * The entities defined in this section are targeted to help development and testing instead
 * of representing usual classes embedded in your application.
 *
 * @section deprecated Deprecation Management
 *
 * ELM provides a small macro found in <elm/deprecated.h>, called DEPRECATED.
 *
 * When put at the start of a function body, it displays a warning deprecation
 * message the first time it is called.
 *
 * @code
 * #include <elm/deprecated.h>
 *
 * class MyClass {
 * public:
 *
 * 	void myDeprecatedFunction(void) {
 * 		DEPRECATED
 * 		// body of the function
 * 	}
 * @endcode
 *
 * @section helper	Helper Methods
 *
 * ELM provides several helper method for using the different classes. They are prefixed by a double underscore and
 * all only compiled if a matching define is not provided.
 *
 * @li @c __size(): gives the full size of the data structure (removed if @c NSIZE is defined)
 * @li @c __print(): display an internal representation of the class (removed if @c NDEBUG is defined)
 *
 * @section test	Testing
 *
 * This module provides a poor, but existing, solution to unit testing in C++.
 * It provides macros and classes to perform statistics on unit testing
 * and makes automatic some test procedures.
 *
 * The example show how the module works:
 * @code
 * #include <elm/util/test.h>
 *
 * void my_test(void) {
 * 		CHECK_BEGIN("my test")
 *
 * 			// test 1
 * 			CHECK(result1 == expected1);
 *
 * 			// test 2
 * 			CHECK(result2 == expected2);
 *
 * 			...
 *
 * 		CHECK_END
 * }
 * @endcode
 *
 * The test must be enclosed in @c CHECK_BEGIN / @c CHECK_END pair and the test case name must be given.
 * Then the test are performed ending with a call to a macro allowing to test and record result of the test.
 *
 * The existing macro are:
 * @li @c CHECK(x) -- check if x is true
 * @li @c CHECK_EQUAL(result, expected) -- test equality and, if it fails, display the failed result value
 * @li @c CHECK_EXCEPTION(exception, action) -- perform the action and the test fails if the exception is not thrown
 * @li @c FAIL_ON_EXCEPTION(exception, action) -- perform the action and the test fails if the exception is thrown
 *
 * There are also some useful macros as:
 * @li @c REQUIRE(cnd, action) -- perform the action only if the given condition is true, else stop the test.
 *
 */

/**
 * @defgroup checksum Checksum Engines
 *
 * This small modules provides two checksum engines:
 * @li @ref checksum::Fletcher for fast checksumming,
 * @li @ref checksum::MD5 for MD5 checksum often used on the web.
 *
 */


/**
 * @defgroup meta Meta-programming
 *
 * Meta-programming is the use of the C++ template system to implement
 * compile-time behaviors. Template meta-programming consists in providing
 * functions working on types and/or to produce values using types. It must
 * be noted that the value provided by a type is named, in ELM, "_" instead
 * of "value" used in STL.
 *
 * Included in the @ref meta namespace, the following facilities are available:
 *	* meta::_true -- type which "_" value is 1,
 *	* meta::_false -- type which "_" value is 0,
 *	* meta::n <N> -- type which "_" value is N,
 *	* meta::_if <C, T1, T2> -- if C = true, produce type T1 else produce type T2,
 *	* meta::declval <T> -- generate an abstract value of type T,
 *	* meta::is_same <T1, T2> -- type which "_" value is 1 if T1 = T2, 0 else,
 *	* meta::is_supported<T, C> -- test if the type C is instantiable with T,
 *	* meta::enable_if <C, T> -- define a type if a condition is true.
 */

namespace meta {

/**
 * @struct n
 * Type which "_" member has for value the template parameter x.
 * @param x		Stored value.
 * @ingroup meta
 */

/**
 * @struct _true
 * Type which "_" member is 1. This type is useful in the evaluation of boolean
 * in meta-programming.
 * @ingroup meta
 */

/**
 * @struct _false
 * Type which "_" member is 0. This type is useful in the evaluation of boolean
 * in meta-programming.
 * @ingroup meta
 */

/**
 * @struct _if
 * This meta-programming construction allows the selection of type depending
 * on a boolean value. If c is true, the result type is T, else the result
 * type is E.
 *
 * @param c		Condition.
 * @param T		Result type if c is true.
 * @param E		Result type if c is false.
 * @ingroup meta
 */

/**
 * @fn T& declval()
 * Function generating an abstract value of type T. The returned value is
 * abstract means it does not correspond to any value in memory and therefore
 * must not be used in classic code. A more consistent use of declval() is
 * in meta-programming when a value is needed, for instance, to select
 * a function by parameter overloading.
 *
 * For example, the code below selects the return type of a function f() taking
 * no parameter:
 * @code
 *	template <class T>
 *	decltype(meta::declval<T>().f()) ff(T *v) { return v.f(); }
 * @endcode
 *
 *
 * @param T	Type of the returned abstract value.
 * @ingroup meta
 */

/**
 * @struct is_supported
 * Type containing a value "_" which value is 1 if the template C can be
 * applied to T, 0 else.
 *
 * This type is useful to test if some property is available on a type T.
 * It is commonly used, but not limited to, to test if a function is member
 * of a type T
 *
 * In the example below, the condition has_f tests if T contains a function
 * named f taking an integer as first parameter:
 * @code
 *	template <class T>
 *	using has_f = decltype(declval<T>().f(int(0)));
 *
 *	int main() {
 *		MyClass o;
 *		if(meta::is_supported<MyClass, has_f>())
 * 			o.f(666);
 *	}
 * @endcode
 *
 * @param T	Type to test.
 * @param C	Condition to test (template supporting one parameter).
 * @ingroup meta
 */

/**
 * @struct enable_if
 * This meta-structure is useful to define a type that depends on a condition,
 * usually #SFINAE function. If the condition B is true, the returned type
 * contains a type named "_" equal to T. Else the returned structure is void.
 *
 * A typical utilization is a template definition that is configured according
 * to a specific support as in the example below. If the type contains a
 * function "f" (without argument) it is called. Else it is not.
 * @code
 *	template <class T>
 *	meta::enable_if<meta::is_supported<T, has_f> >::_ void call(T& x) { x.f(); }
 *
 *	template <class T>
 *	meta::enable_if<!meta::is_supported<T, has_f> >::_ void call(T& x) { }
 * @endcode
 *
 * @param B		Condition.
 * @param T		Type (default to void).
 * @ingroup meta
 */

}	// meta

/**
 * @defgroup recs Recipes
 *
 * @section recs_io	Efficient Input/Output
 *
 * ELM comes with several functions to make easier the access to files:
 * @code
 *	#include <elm/io.h>
 *	sys::Path p = ...;
 *	int x;
 *	auto in = io::read(p);
 *	in >> x;
 *	auto out1 = io::write(p);
 *	out1 << x;
 *	auto out2 = io::append(p);
 *	out2 << x;
 * @endcode
 *
 * These three commands open a file named *p* and returns an input/output
 * handle ready for reading or writing.
 *
 * Inputing from a string can be done in the same way:
 * @code
 *	#include <elm/io.h>
 *	int x;
 *	auto in = io::read("my string");
 *	in >> x;
 * @endcode
 *
 * Outputting to a string requires a StringBuffer:
 * @code
 *	#include <elm/string.h>
 *	StringBuffer buf;
 *	buf << 111;
 *	string s = buf.toString();
 * @endcode
 *
 * There is a short cut to this with a special named "_":
 * @code
 *	#include <elm/string.h>
 *	string s = _ << 111 <<  " euros";
 *
 * @endcode
 *
 * To read a file line by line, the function Input::lines() provides
 * an iterator:
 * @code
 *	#include <elm/io.h>
 *	auto in = open_file();
 *	for(auto line: in.lines())
 *		...
 * @endcode
 *
 * @section recs_map Using maps
 *
 * ELM comes with several map data structure:
 *	* HashMap
 *	* avl::Map
 *	* ListMap
 *
 * These map implementation shares the same concepts concept::Map and
 * concept::MutableMap. This means they are controlled in the same way.
 *
 * To add a value to the map, one can type:
 * @code
 *	MyMap<string, int> map;
 *	map.put("red", 111);
 *	map["red"] = 111;
 * @endcode
 *
 * To get a value, several alternative exists using default values or
 * options:
 * @code
 *	int x = map.get("red", -1);
 *	Option<int> y = map.get("red");
 *	int z = map["red"];
 * @endcode
 * In the last form, a KeyException is raised if there is no value for the key.
 */


/**
 * @class PreIterator
 * This class is an helper in the writing of iterators. It avoids to redefine
 * all iterator operators each time an operator is defined. The user of this
 * class has just to define four methods:
 *	* bool ended() const -- that returns true when the iteration ends,
 *	* bool equals(const Iterator& i) const -- to test if two iterators are equal,
 *	* void next() -- to move to the next item,
 *	* T item() const -- to get the current item (if any).
 *
 * Using these 4 functions, PreIterator is able to support the operators (),
 * !, ++ (prefix), ++ (suffix), *, ->, == and !=.
 *
 * For example, the iterator on an array can be written as:
 * @code
 *		template <class T>
 *		class ArrayIter: public PreIterator<ArrayIter, T> {
 *		public:
 *			inline ArrayIter(int number, T *array)
 *				: n(number), i(0), a(array) { }
 *			inline bool ended() const { return i >= n; }
 *			inline bool equals(const ArrayIter& it)
 *				{ return a == it.a && n == it.n && i == it.i; }
 *			inline void next() { i++; }
 *			inline T item() const { return a[i]; }
 *		private:
 *			int n, i;
 *			T *a;
 *		};
 * @endcode
 *
 * @param I			Type of the defined iterator.
 * @param T			Type of the items.
 * @ingroup data
 *
 * @typedef PreIterator<T>::t;
 * Type of the element held by the iterator.
 *
 * @fn bool PreIterator<T>::operator()() const;
 * Test if the iteration is ended.
 * @return	True if the iteration is ended, false else.
 *
 * @fn bool PreIterator<T>::operator!() const;
 * Test if the iteration is not ended.
 * @return	True if the iteration is not ended, false else.
 *
 * @fn  T PreIterator<T>::operator*() const;
 * Get the current item of the iterator. It is forbidden to call this function
 * if the iteration is ended.
 * @return	Current iterator item.
 *
 * @fn  T PreIterator<T>::operator->() const { return ((I *)this)->item(); }
 * Get the current item of the iterator as a deferenced pointer. It is
 * forbidden to call ths function if the iteration is ended.
 * @return	Current iterator item.
 *
 * @fn I& PreIterator<T>::operator++();
 * Move the iterator to the next item. It is forbidden to call this function
 * if the iteration is ended.
 * @return This iterator.
 *
 * @fn void PreIterator<T>::operator++(int) { ((I *)this)->next(); }
 * Move the iterator to the next item. It is forbidden to call this function
 * if the iteration is ended.
 *
 * @fn bool PreIterator<T>::operator==(const I& i) const;
 * Test if the current iterator and the argument iterator are equal.
 * @return	True if both operators are equal, false else.
 *
 * @fn bool PreIterator<>::operator!=(const I& i) const;
 * Test if the current iterator and the argument iterator are different.
 * @return	True if both operators are different, false else.
 *
 */

/**
 * @class InplacePreIterator
 * As PreIterator, this class is an helper in the writing of iterators but
 * instead of returning the iterated items, it returns a constant reference
 * to the iterated items.
 *
 * Its aims to avoid redefining
 * all iterator operators each time an operator is defined. The user of this
 * class has just to define four methods:
 *	* bool ended() const -- that returns true when the iteration ends,
 *	* bool equals(const Iterator& i) const -- to test if two iterators are equal,
 *	* void next() -- to move to the next item,
 *	* const T& item() const -- to get the current item (if any).
 *
 * Using these 4 functions, PreIterator is able to support the operators (),
 * !, ++ (prefix), ++ (suffix), *, ->, == and !=.
 *
 * @param I			Type of the defined iterator.
 * @param T			Type of the items.
 * @ingroup data
 * @deprecated		Used PreIterator with reference/non-reference item type.
 */


/**
 * @class PreIter
 * This help class provides the definition of iterator operators (), !, ++
 * (prefix), ++ (postfix), == and !=. These operations are derived from
 * 3 functions that must be declared in class I:
 *	* bool ended() -- test if the end of iteration is reached,
 *	* void next() -- move to the next item,
 *	* bool equals(const Iter& i) -- test equlity of iterators.
 *
 *	By itself, this class is not enough to declare the full set of operators
 *	of an iterator. It has to be used in conjunction with ConstPreIter and
 *	MutPreIter (or both) that will provide operator * and ->.
 *
 *	Example below shows an example of complete constant and mutable iterators:
 *	@code
 *	template <class T>
 *	class MyArray {
 *	public:
 *
 *		class BaseIter: public PreIter<Iter, T> {
 *		public:
 *			inline BaseIter(const MyArray& array, int idx = 0): a(array), i(idx) { }
 *			inline bool ended() const { return i >= 10; }
 *			inline void next() const { i++; }
 *			inline bool equals(const BaseIter& it) const { return i == it.i; }
 *		private:
 *			const MyArray<T>& a;
 *			int i;
 *		};
 *
 *		class Iter: public BaseIter, public ConstPreIter<Iter, T> {
 *		public:
 *			using BaseIter::BaseIter;
 *			inline const T& item() const { return BaseIter::a.t[BaseIter::i];
 *		};
 *		inline Iter begin() const { return Iter(*this); }
 *		inline Iter end() const { return Iter(*this, 10); }
 *
 *		class MutIter: public BaseIter, public MutPreIter<Iter, T> {
 *		public:
 *			inline MutIter(MyArray& a, int i = 0): BaseIter(a, i) { }
 *			inline T& item() { return const_cast<MyArray&>(BaseIter::a).t[BaseIter::i]; }
 *		};
 *		inline MutIter begin() { return MutIter(*this); }
 *		inline MutIter end() { return MutIter(*this, 10); }
 *
 *	private:
 *		T t[10];
 *	};
 *	@endcode
 *
 *	This code defines first a base iterator, BaseIter, that gather all functions
 *	that are common to the constant and to the mutable iterator. Then the
 *	constant iterator, Iter, can be declared: it uses the same construction as
 *	BaseIter but the access to protected fields requires to prefix them with
 *	the BaseIter class name: it is a bit ugly but required by the multiple
 *	inheritance caused by the use of ConstPreIter.
 *
 *	MutIter is a bit more complex: it inherits from BaseIter re-using the
 *	functions defined in BaseIter but also ensuring that Iter and MutIter
 *	can be compared.The constructor can not be inherited to ensure that
 *	the MyArray parameter is mutable/non-constant.This is important to ensure
 *	that the const_cast<>() of the item() is valid. This cast is required
 *	in order to expose references to the MyArray items but it is only
 *	performed if the constructor has obtained a mutable MyArray.
 *
 * @param I	Defined iterator.
 * @param T	Type of iterated items.
 * @ingroup	data
 *
 *
 * @class ConstPreIter
 * This class is an helper to define constant iterator. See PreIter for more
 * details.
 *
 * @param I	Defined iterator.
 * @param T	Type of iterated items.
 * @ingroup	data
 *
 * @class MutPreIter
 * This class is an helper to define mutable iterator. See PreIter for more
 * details.
 *
 * @param I	Defined iterator.
 * @param T	Type of iterated items.
 * @ingroup	data
 *
 */

}	// elm

#endif /* ELM_DOC_H_*/
