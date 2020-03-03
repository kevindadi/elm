/*
 * data.h
 *
 *  Created on: 16 janv. 2016
 *      Author: casse
 */

#ifndef ELM_DATA_H_
#define ELM_DATA_H_

#include <elm/data/util.h>

namespace elm {

/**
 * @defgroup data Data Structures
 *
 * @par Principles
 * This module groups together classes implementing storage data structure. It is new in ELM 2.0
 * and try to extend and to make easier the use of classes from the old @ref gen_datastruct module.
 * The main differences includes:
 * @li shorter names for classes and for iterators,
 * @li included in the @ref main elm name space,
 * @li more STL compliance,
 * @li more operators overloading,
 * @li versatile system for configuration (comparator, allocator, etc).
 *
 * In addition, their documentation includes several topic allowing a better understanding
 * of their work to help choosing the better data structure:
 * @li complexity (average and worst) of basic operations like add and remove,
 * @li basic memory and element relative memory foot print.
 *
 * As for old data structures, the following topics applies:
 * @li concepts implemented by the data structure are provided,
 * @li a data structure must not be modified while an iterator is active on it
 * unless specific methods are provided.
 *
 *
 * @par Selecting a data structure
 *
 * This sections aims to help a developer to select a data structure fittings
 * his needs. They are sorted according to different criteria: the right
 * data structure to use is the one matching most of them. The criteria
 * includes access type, collection size, etc.
 *
 * Collection size:
 * 	* fixed -- Array, BitVector, StaticStack
 * 	* small -- Vector, VectorQueue
 * 	* medium -- List, SortedList, BiDiList, TreeBag, TreeMap
 * 	* big -- FragTable, avl::Tree, avl::Map,
 * avl::Set, ListQueue, HashMap, HashSet
 *
 * Access type:
 *  * indexed -- Vector, FragTable
 *	* sequential -- Vector, List, SortedList, BiDiList, FragTable, avl::Tree
 *	* fast lookup -- avl::Tree, TreeBag, SortedList
 *	* key access -- ListMap, HashMap, avl::Map, TreeMap
 *
 * Modification type:
 *  * append -- Vector, FragTable, BiDiList
 * 	* prepend -- List
 * 	* push / pop (stack) -- StaticStack, Vector, List, BiDiList, FragTable
 * 	* append / remove first (queue) -- BiDiList, VectorQueue, ListQueue
 *  * random -- List, BiDiList
 *  * uniqueness of elements (set) -- ListSet, avl::Set, HashSet
 *  * key access (map) -- ListMap, HashMap, avl::Map, TreeMap
 *  * inter-set operation (efficient) -- BitVector
 *
 * Memory footprint:
 *	* light -- Array, Vector, VectorQueue, BitVector, StaticStack, List, ListQueue, SortedList, ListMap
 *	* medium -- BiDiList, TreeBag, TreeMap, avl::Tree, avl::Map, avl::Set, FragTable
 *	* heavy at startup -- HashTable, HashMap, HashSet
 *
 * The array below sum complexity of operations for the data structures
 * described above. When 2 complexity are give o1/o2, o1 is the average case
 * and o2 the worst case.
 *
 * For simple collections, we get:
 * Data Structure | adding         | lookup         | insertion    | removal
 * -------------- | -------------- | -------------- | ------------ | -------
 * Vector         | O(1)           | O(n)           | O(n)         | O(n)
 * List           | O(1)           | O(n)           | O(1)         | O(1)
 * BiDiList       | O(1)           | O(n)           | O(1)         | O(1)
 * ListBag        | O(log(n))/O(n) | O(log(n))/O(n) | O(1)         | O(1)
 * FragTable      | O(1)           | O(n)           | O(n)         | O(n)
 * HashTable      | O(b)           | O(b)           | O(1)         | O(1)
 * HashSet        | O(b)           | O(b)           | O(1)         | O(1)
 * avl::Tree      | O(log(n))      | O(log(n))      | O(1)         | O(log(n))
 * avl::Set       | O(log(n))      | O(log(n))      | O(1)         | O(log(n))
 *
 * * n -- number of elements in the data structure
 * * b -- number of elements in a bucket of a hash table
 * * adding -- simple addition any way in the data structure
 * * lookup -- look up of a particular element
 * * insertion -- insertion relative at an iterator position
 * * removal -- removal relative of an element pointed by an iterator
 *
 * Classic collection operations:
 * Data Structure | lookup         | insertion      | removal
 * -------------- | -------------- | -------------- | --------------
 * HashMap        | O(b)           | O(b)           | O(b)
 * avl::Map       | O(log(n))      | O(log(n))      | O(log(n))
 * TreeMap        | O(log(n))/O(n) | O(log(n))/O(n) | O(log(n))/O(n)
 * ListMap        | O(n)           | O(n)           | O(n)
 *
 * * n -- number of elements in the data structure
 * * b -- number of elements in a bucket of a hash table
 * * lookup -- look up of a particular element
 * * insertion -- insertion in the map (including lookup)
 * * removal -- removal from the map (including lookup)
 *
 * Random access to array elements:
 * Data Structure | Indexed Access
 * -------------- | --------------
 * Array          | O(1)
 * FragTable      | O(1)
 * Vector         | O(1)
 * List           | O(n)
 * BiDiList       | O(n)
 *
 * Stack (LIFO) operations:
 * Data Structure | push | pop
 * -------------- | ---- | ----
 * Vector         | O(1) | O(1)
 * List           | O(1) | O(1)
 * BiDiList       | O(1) | O(1)
 * FragTable      | O(1) | O(1)
 *
 * Queue (FIFO) operations:
 * Data Structure | put  | get
 * -------------- | ---- | ----
 * Vector         | O(n) | O(1)
 * List           | O(1) | O(n)
 * BiDiList       | O(1) | O(1)
 * FragTable      | O(n) | O(1)
 * VectorQueue    | O(1) | O(1)
 * ListQueue      | O(1) | O(1)
 *
 * Set operations:
 * Data Structure | join   | meet   | difference
 * -------------- | ------ | ------ | ----------
 * HashSet        | O(bn)  | O(bn)  | O(bn)
 * avl::Set       | O(n)   | O(n)   | O(n)
 * BitVector      | O(n)   | O(n)   | O(n)
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
 *			inline bool equals(const MyIter& i) { ... }
 *		private:
 *			...
 *		};
 *	@endcode
 *
 * And the use of such an iterator becomes:
 *	@code
 *		for(MyIter i(...); i(); ++i)
 *			use(*i);
 *	@endcode
 *
 * Notices that if T is a pointer, the arrow iterator may be used without a star:
 * @code
 *		for(MyIter i(...); i(); ++i)
 *			use(i->to_something);
 * @endcode
 *
 * Likely, @ref PreIterator provides automatic conversion to T:
 * @code
 *		for(MyIter i(...); i(); ++i) {
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
 * * @ref range(const I& b, const I& e) -- creates a pseudo-collection containing objects between given iterators.
 * * @ref nrange(const T& b, const T& e) -- creates a pseudo- numeric collection ranging from b to e.
 * * @ref select(const C& c, const P& p) -- creates a pseudo-collection containing values of p satisfying predicate p.
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
 *
 * @li @ref elm::StrictMapDelegate is like MapDelegate but thow a KeyError
 * 			exception if a non-existing key is used.
 *
 * @par Helper Classes
 *
 * The following classes may help to work or to extend the concrete data structures:
 * 	* elm::Bag -- a lightweight collection containing a fix number of elements,
 *  * elm::Slice -- provide an array view on a slice of a bigger array data structure.
 */

/**
 * @class StrictMapDelegate
 * Delegate class to access functions get/put() of map using the overload of
 * [i] operators. In the opposite to MapDelegate, this class throws a
 * KeyException if the key of a read item does not exist.
 *
 * A common use of this delegate in a class implementing a mutable map:
 * @code
 * template <class K, class T>
 * class MyMap {
 * public:
 *	typedef K key_t;
 *	typedef T val_t;
 * 	...
 *	inline StricMapDelegate<MyMap> operator[](const K& k)
 *		{ return StrictMapDelegate<MyMap>(*this, k); }
 *	...
 * };
 * @endcode
 *
 * @param T		Type of map element values.
 * @see MapDelegate
 * @ingroup data
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
 * @fn bool forall(const C& c, const P& p);
 * Test if the predicate p is true for each element of c.
 * @param c		Collection to test (must implement concept::Collection).
 * @param p		Predicate to evaluate (must implement concept::Predicate).
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
 * @fn I find(I i, const P& p);
 * Find an element starting at iterator i matching the predicate p.
 * @param i		Iterator to start look up.
 * @param p		Predicate to test (must implement concept::Predicate).
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
 * @fn void iter(const C& c, const F& f);
 * Apply the function f on the element of collection c (ignoring the result).
 * @param c		Collection to iterate on (must implement concept::Collection).
 * @param f		Function to apply (must implement concept::Function).
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
 * @fn NumRange<T> nrange(T i, T j, T s = 1);
 * Creates a range over a numeric domain spanning from i to j using a step of s.
 * @param i	Lower bound of the range (inclusive).
 * @param j	Upper bound of the range (inclusive).
 * @param s	Step in the range.
 * @return	Range from i to j (with a step of s).
 */


/**
 * @fn Range<I> range(const I& b, const I& e);
 * Creates a range from the iterator b to iterator e.
 * @param b		First position of the range (inclusive).
 * @param e		One position after the last position of the range (exclusive).
 * @return		Range from b to e.
 */


/**
 * @fn Range<SelectIter<typename C::Iter, P> > select(const C& c, const P& p);
 * Creates a range over items of collection c that satisfies the predicate p.
 * @param c		Collection to select items in.
 * @param p		Predicate to select items of c.
 * @return		Range on c items satisfying p.
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


/**
 * @fn bool equals(const C1& c1, const C2& c2);
 * Test if two collections are equals.
 * @param c1	First collection.
 * @param c2	Second collection.
 * @return		True if both collection are equal, false else.
 * @param C1	Type of first collection.
 * @param C2	Type of second collection.
 * @ingroup data
 */


/**
 * @fn Pair<typename C1::Iter, typename C2::Iter> mismatch(const C1& c1, const C2& c2);
 * Find the point of difference of two collection. Starting from the first
 * element of the two collections, progress until either finding the end of
 * a collection, or until the first different element of the collections.
 * @param c1	First collection.
 * @param c2	Second collection.
 * @return		Pair of iterators to the difference point (if any).
 * @param C1	Type of first collection.
 * @param C2	Type of second collection.
 * @ingroup data
 */


 /**
  * @fn Pair<typename C1::Iter, typename C2::Iter> mismatch(const C1& c1, const C2& c2, P p);
  * Find the point of difference of two collection. Starting from the first
  * element of the two collections, progress until either finding the end of
  * a collection, or until the first different element of the collections.
  * To test if two elements matches or not, the function p is used.
  * @param c1	First collection.
  * @param c2	Second collection.
  * @param p	Match predicate to decide if two elements are different. Must
  * 			support the call p(element1, element2).
  * @return		Pair of iterators to the difference point (if any).
  * @param C1	Type of first collection.
  * @param C2	Type of second collection.
  * @param P	Type of predicate.
  * @ingroup data
  */

/**
 * @class Bag
 * A bag is a cheap collection to store an immutable array of data.
 * The allocated data encompasses only the integer for the count and the array
 * items. Yet, this requires a special procedure to create a bag using
 * the function `make` as below:
 * @code
 * float array[N] = { ... };
 * Bag<float> *bag = Bag<float>(N, array);
 * @endcode
 *
 * Yet, the release of the data is standard:
 * @code
 * delete bag;
 * @endcode
 *
 * Bag implements the following concepts:
 *	* concept::Collection
 *	* concept::Array
 *
 * @param T	Type of data stored in the bag.
 * @ingroup data
 */


/**
 * @class Slice
 * This class implement a light-weight array collection representing a slice
 * of another array collection.
 *
 * Slice implements the following concepts:
 * 	* concept::Collection
 * 	* concept::Array
 *
 * @param T		Type of elements in the slice.
 * @param D		Type of the array data structure.
 * @ingroup		data
 */

/**
 * @fn  Slice::Slice(D& array, int first, int count);
 * Build a slice for the given *array* ranging from the *first* index over
 * *count* elements.
 *
 * @param array		Parent array.
 * @param first		First index.
 * @param count		Cont of elements in the slice.
 */

/**
 * @fn D& Slice::array() const;
 * Get the parent array.
 * @return Parent array.
 */

/**
 * @fn int Slice::firstIndex() const;
 * Get the index, in the parent array, of the first element of the slice.
 * @return	Index of first element in the parent array.
 */

/**
 * @fn int Slice::lastIndex() const;
 * Get the index, in the parent array, of the last element of the slice.
 * @return	Index of last element in the parent array.
 */

}	// elm

#endif /* ELM_DATA_H_ */
