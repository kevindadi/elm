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
 * Includes also function as:
 * @li @ref void quicksort(A<T>& array, const C& c)
 * @li @ref void quicksort(A<T>& array)
 *
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
 * void map(const C& c, const F& f, D& d);
 * Map the elements of a collection to element of another collection using
 * the function f.
 * @param c	Original collection (must implement concept::Collection).
 * @param f	Transforming function (must implement concept::Function).
 * @param d	Filled collection (must implement concept::MutableCollection).
 * @ingroup data
 */

/**
 * void map(const C& c, const F& f, const A& a, D& d);
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

template <class C>
inline typename C::t sum(const C& c)
	{ return fold(c, Single<Add<typename C::t> >::_, 0); }

template <class C>
inline typename C::t product(const C& c)
	{ return fold(c, Single<Mul<typename C::t> >::_); }


// construction operations
template <class C>
inline void fill(C& c, int n, const typename C::t v = type_info<typename C::t>::null)
	{ for(int i = 0; i < n; i++) c.add(v); }

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

}	// elm

#endif /* ELM_DATA_H_ */
