/*
 * data.h
 *
 *  Created on: 16 janv. 2016
 *      Author: casse
 */

#ifndef ELM_DATA_H_
#define ELM_DATA_H_

namespace elm {

/**
 * @defgroup data Data Structures
 *
 * @par Principles
 * This module groups together classes implementing storage data structure. It is new in ELM 2.0
 * and try to extend and to make easier the use of classes from @ref gen_datastruct module.
 * The main differences includes:
 * @li shorter names for classes and for iterators,
 * @li include in the @ref main elm name space,
 * @li more STL compliance,
 * @li more operators overloaded.
 *
 * In addition, their documentation includes several topic allowing a better understanding
 * of their work to help choosing the better data structure:
 * @li complexity (average and worst) of basic operations like add and remove,
 * @li basic memory and element relative memory foot print.
 *
 * As for old data structures, the following topics applies:
 * @li concepts implemented by the data structure are provided,
 * @li a data structure must not be modified while an iterator is active on it unless specific methods are provided.
 *
 *
 * @par Iterator Helper Classes
 *
 * @code
 *	#include <elm/PreIterator.h>
 * @endcode
 *
 * Basically, the @ref PreIterator function avoids rewriting the large number
 * of operator overloading. In fact, only the constructor and 3 functions need
 * to be written:
 *	* ended() tests if the iterator is ended,
 *	* item() returns the currently pointer item,
 *	* next() passes to the next item if iterated collection.
 *
 * To write an iterator, it may be used as below (with T the type of iterated items):
 *	@code
 *		class MyIter: public PreIterator<MyIter, T> {
 *		public:
 *			MyIter(...) { ... };
 *			inline bool ended(void) const { return ...; }
 *			inline const T& item(void) const { return ...; }
 *			inline void next(void) { ... }
 *		private:
 *			...
 *		};
 *	@endcode
 *
 * And the use of such an iterator becomes:
 *	@code
 *		for(MyIter i(...); i; ++i)
 *			use(*i);
 *	@endcode
 *
 * Notices that if T is a pointer, the arrow iterator may be used without a star:
 * @code
 *		for(MyIter i(...); i; ++i)
 *			use(i->to_something);
 * @endcode
 *
 * Likely, @ref PreIterator provides automatic conversion to T:
 * @code
 *		for(MyIter i(...); i; ++i) {
 *			T v = i;
 *			...
 *		}
 * @endcode
 *
 * Beside, @ref PreIterator provides also a way to use iterators as in the STL.
 * You have to provide a equals() function to test for equality:
 * @code
 *		class MyIter: public PreIterator<MyIter, T> {
 *		public:
 *			MyIter(...) { ... };
 *			inline bool ended(void) const { return ...; }
 *			inline const T& item(void) const { return ...; }
 *			inline void next(void) { ... }
 *			inline bool compare(const MyIter& i) { return ...; }
 *		private:
 *			...
 *		};
 * @endcode
 *
 * And now the iteration can be written (with begin() the function returning
 * the initial iterator and end() the end iterator):
 * @code
 *	for(auto i = begin(); i != end(); ++i)
 *		use(*i);
 * @endcode
 *
 * A very fast and intuitive way to perform iteration on a collection of items proposed
 * by C++ 11 requires a couple of `begin()` and `end()` functions declared in a collection
 * object `coll`:
 * @code
 * 	for(auto i: coll)
 *		use(i);
 * @endcode
 * Notice that `i` is of type T, the type of iterated elements. As this is very convenient,
 * all ELM data classes provide `begin()` and `end()` functions.
 *
 *
 * @par Helper functions
 *
 * `<elm/data/quicksort.h>` provides a *quicksort* implementation for data collections:
 *	* @ref void quicksort(A<T>& array, const C& c)
 *	* @ref void quicksort(A<T>& array) --  quicksort implementation for data classes
 *
 * Other functions very generic processing over the collection. They generically takes
 * as parameter a collection, a class providing some specific computation and comes in
 * two flavors, with or without an additional argument.
 *
 * * @ref count(const C& c, const P& p) -- count the number of items satisfying a predicate p,
 * * @ref forall(const C& c, const P& p) -- returns true if all items satisfy the predicate p,
 * * @ref exists(const C& c, const P& p) -- return true if at least one item satifies the predicate p,
 * * @ref find(I i, const P& p) -- starting from an iterator, move it to the end or the first item satisfying the predicate p,
 * * @ref map(const C& c, const F& f, D& d) -- copy collection c to d after transformation by f,
 * * @ref iter(const C& c, const F& f) -- iterate over collection c and call f for each item,
 * * @ref fold(const C& c, const F& f, typename F::y_t t) -- iterate over collection c and use f to accumulate the value of items,
 * * @ref sum(const C& c) -- perform the sum of items of c,
 * * @ref product(const C& c) -- perform the product of items of c,
 * * @ref fill(C& c, int n, const typename C::t v) -- add n items of value v to collection c.
 *
 * @par Delegate Classes
 *
 * Delegate class in ELM allows to get references on value managed by
 * specific class functions to ensure their access or their assignment.
 *
 * They support the same operations as the C++ references:
 * @li	to access the value, they may be used as is (automatic conversion) or
 * 		with the star '*' operator,
 * @li	to change the value, the assignment '=' operator may be used.
 *
 * The following delegates exists:
 *
 * @li @ref elm::ArrayDelegate allows to use values from a
 * 			@ref elm::concept::MutableArray whose access is based on get()/set()
 * 			methods and an index,
 *
 * @li @ref elm::MapDelegate allows to use values from a
 * 			@ref elm::concept::MutableMap whose access is based on get()/put()
 * 			methods and an identifier.
 */

namespace concept {

/**
 * Predicate concept.
 * @param	T	Type of value to test.
 * @ingroup concept
 */
template <class T>
struct Predicate {
	bool operator()(const T& v);
};

/**
 * Predicate concept with additional argument.
 * @param	T	Type of value to test.
 * @param	A	Type of argument.
 * @ingroup concept
 */
template <class T, class A>
struct PredicateWithArg {
	bool operator()(const T& v, const A& a);
};

/**
 * Concept representing a function transforming a data
 * to another one of the same set.
 * @param X		Type of input argument.
 * @param Y		Type of function result.
 * @ingroup concept
 */
template <class X, class Y>
struct Function {
	typedef X x_t;
	typedef Y y_t;
	Y operator()(const X& x);
};

/**
 * Concept representing a function transforming a data
 * to another one of the same set (with additional argument).
 * @param X		Type of input argument.
 * @param Y		Type of function result.
 * @ingroup concept
 */
template <class X, class Y, class A>
struct FunctionWithArg {
	typedef X x_t;
	typedef Y y_t;
	Y operator()(const X& x, const a& a);
};

}	// concept


/**
 * @fn template <class T, template <class> class A, class C> void quicksort(A<T>& array, const C& c);
 * Sort the given array using quicksort algorithm (average complexity O(N log(N)) ).
 *
 * @param array		Array containing the values to sort.
 * @param c			Comparator to use (rely on ELM default comparator if not provided).
 * @param T			Type of values.
 * @param A			Type of array (must implement @ref Array concept).
 * @param C			Type of comparator (must implement @ref Comparator or @ref Compare concept).
 *
 * @ingroup data
 */

/**
 * @fn template <class T, template <class> class A> void quicksort(A<T>& array);
 * Sort the given array using quicksort algorithm (average complexity O(N log(N)) ).
 * The used comparator is @ref Comparator<T>.
 *
 * @param array		Array containing the values to sort.
 * @param T			Type of values.
 * @param A			Type of array (must implement @ref Array concept).
 *
 * @ingroup data
 */

/**
 * @fn int count(const C& c, const P& p);
 * Count the number of elements of c that matches the predicate p.
 * @param c		Collection to count in (must implement concept::Collection).
 * @param p		Predicate to test element (must implement concept::Predicate).
 *
 * @ingroup data
 */

/**
 * @fn int count(const C& c, const P& p, const A& a);
 * Count the number of elements of c that matches the predicate p (using addiotnal argument a).
 * @param c		Collection to count in (must implement concept::Collection).
 * @param p		Predicate to test element (must implement concept::PredicateWithArg).
 * @param a		Additional argument.
 * @ingroup data
 */

/**
 * @fn bool forall(const C& c, const P& p);
 * Test if the predicate p is true for each element of c.
 * @param c		Collection to test (must implement concept::Collection).
 * @param p		Predicate to evaluate (must implement concept::Predicate).
 * @return		True if the predicate p is true for all element of c.
 * @ingroup data
 */

/**
 * @fn bool forall(const C& c, const P& p, const A& a);
 * Test if the predicate p is true for each element of c (using an additional argument a).
 * @param c		Collection to test (must implement concept::Collection).
 * @param p		Predicate to evaluate (must implement concept::PredicateWithArg).
 * @param a		Additional argument.
 * @return		True if the predicate p is true for all element of c.
 * @ingroup data
 */

/**
 * @fn bool exists(const C& c, const P& p);
 * Test if the predicate p is true at least for one element of c.
 * @param c		Collection to test (must implement concept::Collection).
 * @param p		Predicate to evaluate (must implement concept::Predicate).
 * @return		True if at least one element is true for predicate p.
 * @ingroup data
 */

/**
 * @fn bool exists(const C& c, const P& p, const A& a);
 * Test if the predicate p is true at least for one element of c (with an additional argument).
 * @param c		Collection to test (must implement concept::Collection).
 * @param p		Predicate to evaluate (must implement concept::PredicateWithArg).
 * @param a		Additional argument.
 * @return		True if at least one element is true for predicate p.
 * @ingroup data
 */

/**
 * @fn I find(I i, const P& p);
 * Find an element starting at iterator i matching the predicate p.
 * @param i		Iterator to start look up.
 * @param p		Predicate to test (must implement concept::Predicate).
 * @return		Either the end iterator, or the iterator on the first position where o is true.
 * @ingroup data
 */

/**
 * @fn I find(I i, const P& p, const A& a);
 * Find an element starting at iterator i matching the predicate p (with additional argument).
 * @param i		Iterator to start look up.
 * @param p		Predicate to test (must implement concept::Predicate).
 * @param a		Additional argument.
 * @return		Either the end iterator, or the iterator on the first position where o is true.
 * @ingroup data
 */

/**
 * @fn void map(const C& c, const F& f, D& d);
 * Map the elements of a collection to element of another collection using
 * the function f.
 * @param c	Original collection (must implement concept::Collection).
 * @param f	Transforming function (must implement concept::Function).
 * @param d	Filled collection (must implement concept::MutableCollection).
 * @ingroup data
 */

/**
 * @fn void map(const C& c, const F& f, const A& a, D& d);
 * Map the elements of a collection to element of another collection using
 * the function f (with an additional argument).
 * @param c	Original collection (must implement concept::Collection).
 * @param f	Transforming function (must implement concept::Function).
 * @param a	Additional argument passed to the function.
 * @param d	Filled collection (must implement concept::MutableCollection).
 * @ingroup data
 */

/**
 * @fn void iter(const C& c, const F& f);
 * Apply the function f on the element of collection c (ignoring the result).
 * @param c		Collection to iterate on (must implement concept::Collection).
 * @param f		Function to apply (must implement concept::Function).
 * @ingroup data
 */

/**
 * @fn void iter(const C& c, const F& f, const A& a);
 * Apply the function f on the element of collection c (ignoring the result and with an additional argument).
 * @param c		Collection to iterate on (must implement concept::Collection).
 * @param f		Function to apply (must implement concept::FunctionWithArg).
 * @param a		Additional argument passed to f.
 * @ingroup data
 */

/**
 * @fn typename F::y_t fold(const C& c, const F& f, typename F::y_t t);
 * Evaluate the elements of the given collection with using function and accumulating
 * with value t. The final t value is then returned.
 *
 * @param c		Collection to iterate on.
 * @param f		Function to apply (must implement concept::FunctionWithArg and A and Y types must be the  same).
 * @param t		Initial value. If not provided, use F::null static value.
 * @ingroup data
 */

/**
 * @fn inline typename C::t sum(const C& c);
 * Perform the sum of the items of collection c. An implementation
 * of operator '+' must exist for these items.
 *
 * @param c		Collection to sum up.
 * @return		Result of item sum.
 * @ingroup data
 */

/**
 * @fn typename C::t product(const C& c);
 * Perform the product of the items of collection c. An implementation
 * of operator '*' must exist for these items.
 *
 * @param c		Collection to multiply together.
 * @return		Result of item product.
 * @ingroup data
 */


/**
 * @fn void fill(C& c, int n, const typename C::t v);
 * Add n items of value v to to the collection c.
 * @param c		Collection add values to.
 * @param n		Number of values to add.
 * @param v		Value to add (as a default, the null value).
 * @ingroup data
 */


/**
 * @class EquivManager
 * This class is used to control the work of container classes (see @ref data)
 * supporting lookup based on @ref Equiv test. It embeds two control objects:
 * @li eq of type E -- used to test for equality,
 * @li alloc -- for memory allocation.
 *
 * It is easily customized by changing the type parameters and by passing
 * objects to the constructor.
 *
 * @param T		Type of managed data.
 * @param E		Equivalence class (default to @ref Equiv<T>).
 * @param A		Allocation class (default to @ref DefaultAllocator).
 *
 * @ingroup data
 */

/**
 * @class CompareManager
 * This class is used to control the work of container classes (see @ref data)
 * supporting lookup and sorting based on comparisons. It embeds two control objects:
 * @li cmp of type C -- used to test for order,
 * @li alloc -- for memory allocation.
 *
 * It is easily customized by changing the type parameters and by passing
 * objects to the constructor.
 *
 * @param T		Type of managed data.
 * @param C		Comparator class (default to @ref Comparator<T>).
 * @param A		Allocation class (default to @ref DefaultAllocator).
 *
 * @ingroup data
 */

/**
 * @class HashManager
 * This class is used to control the work of container classes (see @ref data)
 * supporting lookup and sorting based on key hashing. It embeds two control objects:
 * @li hash of type H -- used to test perform hashing,
 * @li alloc -- for memory allocation.
 *
 * It is easily customized by changing the type parameters and by passing
 * objects to the constructor.
 *
 * @param K		Type of data keys.
 * @param H		Hash class (default to @ref HashKey<K>).
 * @param A		Allocation class (default to @ref DefaultAllocator).
 *
 * @ingroup data
 */

/**
 * @class ArrayDelegate
 * A delegate for accessing items of a @ref concept::MutableArray.
 *
 * @param C		Type of the container.
 * @param I		Type of the index.
 * @param T		Type of the items.
 *
 * @ingroup data
 */


/**
 * @fn ArrayDelegate::ArrayDelegate(C& container, const I& index);
 * Build a delegate for an item of the given container.
 * @param container		Item container.
 * @param index			Item index.
 */


/**
 * @fn ArrayDelegate::ArrayDelegate(const ArrayDelegate& delegate);
 * Build a delegate by cloning.
 * @param delegate	Delegate to clone.
 */


/**
 * @class MapDelegate
 * A delegate to reference item of @ref concept::MutableMap.
 *
 * @param C		Type of the container.
 * @param I		Type of the identifier.
 * @param T		Type of the item.
 * @param D		Type to get the default value (as the get() operation requires
 * 				a default value, default to @ref Default class with a value
 * 				of 0).
 *
 * @ingroup data
 */


/**
 * @fn MapDelegate::MapDelegate(C& container, const I& identifier);
 * Build a delegate for an item of a map.
 * @param	container	Item container map.
 * @param	identifier	Item map identifier.
 */


/**
 * @fn MapDelegate::MapDelegate(const MapDelegate& delegate);
 * Build a delegate by cloning.
 * @param delegate	Delegate to clone.
 */

}	// elm

#endif /* ELM_DATA_H_ */
