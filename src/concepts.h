/*
 *	$Id$
 *	Concepts documentation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2007-08, IRIT UPS.
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

#include "../include/elm/equiv.h"

namespace elm { namespace concept {

/**
 * @defgroup concepts Concepts
 * The ELM V2.0 uses the "concept" idea to unify the interfaces of its containers.
 * A concept is like the definition of an interface or a signature that must be implemented
 * by a class.
 * "concept" ferature is not yet defined in the C++ standard but, as soon as they will be available
 * in most C++ compiler / standards, they will be used in the declaration of ELM container classes.
 * In the meantime, the concepts provide a scheme to implement container and each container
 * provides, in its documentation, the list of implemented concepts.
 *
 * @par Collection Concepts
 * @li @ref elm::concept::Array
 * @li @ref elm::concept::BiDiList
 * @li @ref elm::concept::Collection
 * @li @ref elm::concept::Iterator
 * @li @ref elm::concept::List
 * @li @ref elm::concept::Map
 * @li @ref elm::concept::MutableArray
 * @li @ref elm::concept::MutableCollection
 * @li @ref elm::concept::MutableList
 * @li @ref elm::concept::MutableMap
 * @li @ref elm::concept::Queue
 * @li @ref elm::concept::Set
 * @li @ref elm::concept::Stack
 * 
 * @par Value Concepts
 * @li @ref elm::concept::Comparator
 * @li @ref elm::concept::Equiv
 * @li @ref elm::concept::Hash
 * 
 * @par Other Concepts
 * @li @ref elm::concept::Graph
 */

/**
 * This concept is matched by all iterators and is used by container implementing the @ref Collection
 * concept. It provides a way to traverse a collection of items. Notice that @ref PreIterator
 * provides a fast way to implement the operator overloads of this concept: iterator inheriting
 * from @ref PreIterator have just to implement ended(), item() and next().
 * 
 * @param T	Type of items of the collection.
 *
 * @par Implemented by:
 * @li @ref Range
 *
 * @ingroup concepts
 */
template <class T>
class Iterator {
public:

	/**
	 * Test if the end of the traversal is reached.
	 * @return	True if end is reached, false else.
	 */
	bool ended(void);
	
	/**
	 * Go to the next item.
	 */
	void next(void);
	
	/**
	 * Get the current item.
	 * @return Current item.
	 * @warning	Do not call this method when @ref ended() == true !
	 */
	T item(void);
	
	/**
	 * Same as ! @ref ended().
	 */
	operator bool(void);
	
	/**
	 * Same as @ref item().
	 */
	operator T (void);
	
	/**
	 * Same as @ref next().
	 */
	Iterator& operator++(int);
	
	/**
	 * Assign an operator position to the current one.
	 * @param iterator	Iterator to set the position of.
	 * @return			Current iterator.
	 */
	Iterator& operator=(const Iterator& iterator);
};


/**
 * This concepts provides methods to handle collection. A collection is an
 * unordered list of items.
 * 
 * @param T	Type of items stored in the collection.
 * 
 * @par Implemented by:
 * @li @ref Array
 * @li @ref BiDiList
 * @li @ref HashMap
 * @li @ref HashSet
 * @li @ref List
 * @li @ref ListSet
 * @li @ref SortedList
 * @li @ref Vector
 * 
 * @ingroup concepts
 */
template <class T>
class Collection {
public:

	/**
	 * Type of values in the collection.
	 */
	typedef T t;

	/**
	 * Collection type.
	 */
	typedef Collection<T> self_t;

	/**
	 * Get the number of elements in the collection.
	 * @return	Number of items.
	 */
	int count(void);
	
	/**
	 * Test if the item is containted in the collection.
	 * @param item	Item to test for.
	 * @return		True if the item is in the collection, false else.
	 */
	bool contains(const T& item);
	
	/**
	 * Test if the given collection is contained in the current one.
	 * @param collection	Collection to test.
	 * @return				True if it is contained, false else.
	 * @param C				Type of the collection to test.
	 */
	template <template <class _> class C>
	bool containsAll(const C<T>& collection);
	
	/**
	 * Test if the collection si empty.
	 * @return	True if the collection is empty, false else.
	 */
	bool isEmpty(void);
	
	/**
	 * Same as @ref isEmpty().
	 */
	operator bool(void);
	
	/**
	 * Iterator on the items of the collection. No assertion can be made
	 * about the order of traversal of the collection items.
	 */
	class Iter: public concept::Iterator<T> {
	public:
	
		/**
		 * Build an iterator from a collection.
		 * @param collection	Collection to traverse.
		 */
		Iter(const Collection<T>& collection);
	
	};

	/**
	 * Get an iterator on the collection.
	 * @return	Iterator.
	 */
	Iter items(void) const;

	/**
	 * Get an iterator on the collection.
	 * @return	Iterator.
	 */
	Iter operator*(void) const;

	/**
	 * Get an iterator on the collection.
	 * @return	Iterator.
	 */
	Iter begin(void) const;

	/**
	 * Get an iterator on the end of the collection.
	 * @return	End iterator.
	 */
	Iter end(void) const;

	/**
	 * Empty collection constant.
	 */
	static const Collection null;


	/**
	 * Test if both collections are equal.
	 * @param coll	Collection to compare with the current one.
	 * @param		True if both collections are equal, false.
	 */
	bool equals(const Collection& coll);

	/**
	 * Test if the current collection contains the given one.
	 * @param coll	Collection to test.
	 * @return		True if the coll is contained in the current one, false else.
	 */
	bool contains(const Collection& coll);

	/**
	 * Same as equals().
	 */
	bool operator==(const Collection& coll);

	/**
	 * Same as !equals().
	 */
	bool operator!=(const Collection& coll);

	/**
	 * Same as contains().
	 */
	bool operator>=(const Collection& coll);

	/**
	 * Same as reversed argument contains().
	 */
	bool operator<=(const Collection& coll);

	/**
	 * Same as contains() and not equals().
	 */
	bool operator>(const Collection& coll);

	/**
	 * Same as contains() with reversed arguments and not equals().
	 */
	bool operator<(const Collection& coll);

	/**
	 * Same as contains.
	 */
	bool operator<=(const T& item);

};


/**
 * This concept provides way to have collections whose content may be modified.
 * 
 * @param T	Type of items in the collection.
 *
 * @par Implemented by:
 * @li @ref Array
 * @li @ref BiDiList
 * @li @ref HashSet
 * @li @ref List
 * @li @ref ListSet
 * @li @ref SortedList
 * @li @ref Vector
 *
 * @ingroup concepts
 */
template <class T>
class MutableCollection: public  Collection<T> {
public:

	/**
	 * Remove all items from the collection.
	 */
	void clear(void);
	
	/**
	 * Add an item to the collection.
	 * @param item	Item to add.
	 */
	void add(const T& item);
	
	/**
	 * Add a collection to the current one.
	 * @param items	Collection of items to add.
	 */
	void addAll(const Collection<T>& items);
	
	/**
	 * Remove the given item from the collection.
	 * @param item	Item to remove from the collection.
	 */
	void remove(const T& item);
	
	/**
	 * Remove a collection from the current one.
	 * @param items	Items to remove.
	 */
	void removeAll(const Collection<T>& items);
	
	/**
	 * Remove a value using an iterator.
	 * @param iter	Iter giving the item to remove.
	 */
	void remove(const Iterator<T>& iter);

	/**
	 * Same as insert().
	 */
	MutableCollection<T>& operator+=(const T& item);

	/**
	 * Same as remove().
	 */
	MutableCollection<T>& operator-=(const T& item);

};


/**
 * This concept provides methods to handle a set of objects Usually, sets
 * provides efficient way to look for, insert or remove items and contains
 * only one version of each item.
 * 
 * Additionally, this concept must support an external operation "is in":
 * @code
 * bool operator<=(const T& val, const Set<T>& set);
 * @endcode
 * That just call the contains() function.
 *
 * @par Implemented by:
 * @li @ref HashSet
 * @li @ref ListSet
 * 
 * @param T	Type of stored items.
 * @ingroup	concepts
 */
template <class T>
class Set: public MutableCollection<T> {
public:
	
	/**
	 * Insert an item in the set avoiding item duplication.
	 * @note	If the set does not support duplicate, add() is may be
	 *			implemented as an insert.
	 */
	void insert(const T& item);

	/**
	 * Perform the join of the current set and the given one.
	* @param set	Set to join with.
	 */
	void join(const Set<T>& set);

	/**
	 * Perform the meet of the current set and the given one.
	 * @param set	Set to meet with.
	 */
	void meet(const Set<T>& set);

	/**
	 * Perform the difference of the current set and the given one.
	 * @param set	Set to make difference with.
	 */
	void diff(const Set<T>& set);

	/**
	 * Shortcut to join().
	 */
	Set<T> operator+=(const Set<T> set);

	/**
	 * Shortcut to join().
	 */
	Set<T> operator|=(const Set<T> set);

	/**
	 * Shortcut to diff().
	 */
	Set<T> operator-=(const Set<T> set);

	/**
	 * Shortcut to meet().
	 */
	Set<T> operator&=(const Set<T> set);

	/**
	 * Shortcut to meet().
	 */
	Set<T> operator*=(const Set<T> set);

	/**
	 * Build a new set joining the current set and the given one.
	 * @param set	Joined set.
	 */
	Set<T> operator+(const Set& set);

	/**
	 * Build a new set joining the current set and the given one.
	 * @param set	Joined set.
	 */
	Set<T> operator|(const Set& set);

	/**
	 * Build a new set meeting the current set and the given one.
	 * @param set	Met set.
	 */
	Set<T> operator*(const Set& set);

	/**
	 * Build a new set meeting the current set and the given one.
	 * @param set	Met set.
	 */
	Set<T> operator&(const Set& set);

	/**
	 * Build a new set making the difference between the current set and the given one.
	 * @param set	Difference set.
	 */
	Set<T> operator-(const Set& set);

};


/**
 * This concept provides methods to access an indexed list of items.
 * @param T	Type of item in the array.
 *
 * @par Implemented by:
 * @li @ref Array
 * @li @ref AllocArray
 * @li @ref Vector
 *
 * @ingroup concepts
 */
template <class T>
class Array: public  Collection<T> {
public:

	/**
	 * Same as @ref Collection::count().
	 */
	int length(void);
	
	/**
	 * Get an item by its index.
	 * @param index	Index of the item to get.
	 * @return		Item at the given index.
	 * @warning		It is an error to pass an index out of bounds.
	 */
	const T& get(int index) const;
	
	/**
	 * Get the index of a value.
	 * @param value	Value to find the index of.
	 * @param start	Index to start from.
	 * @return		Index of the item or -1 if not found.
	 */
	int indexOf(const T& value, int start = 0) const;

	/**
	 * Get the index of the last occurrence of a value.
	 * @param value	Value to find the last index of.
	 * @param start	Index to start from.
	 * @return		Index of the item or -1 if not found.
	 */
	int lastIndexOf(const T& value, int start = -1) const;
	
	/**
	 * Same as @ref get().
	 */
	const T& operator[](int index) const;	
};


/**
 * This concept provides mutable arrays.
 * @param T	Type of the items in the array.
 *
 * @par Implemented by:
 * @li @ref Array
 * @li @ref AllocArray
 * @li @ref Vector
 *
 * @ingroup concepts
 */
template <class T>
class MutableArray: public  Array<T>, public  MutableCollection<T> {
public:

	/**
	 * Shrink the size of the array.
	 * @param length	New length of the array (less than the current length).
	 */
	void shrink(int length);

	/**
	 * Set an item in the array.
	 * @param index	Index of the item to set.
	 * @param item	Value to set.
	 */
	void set(int index, const T& item);

	/**
	 * Set an item in the array using an iterator.
	 * @param iter	Iterator on the item.
	 * @param item	Value to set.
	 */
	void set(const Iterator& iter, const T& item);
	
	/**
	 * Get a reference on an item.
	 * @param index	Index of the item to get a reference from.
	 * @return		Reference of the item.
	 */
	 T& get(int index);
	
	/**
	 * Fast access to the @ref set().
	 */
	T& operator[](int index);
	
	/**
	 * Insert an item in the array. The following items are shifted to the
	 * upper indexes.
	 * @param index	Index to insert to.
	 * @param item	Item to insert.
	 */
	void insert(int index, const T& item);
	
	/**
	 * Insert an item in the array. The following items are shifted to the
	 * upper indexes.
	 * @param iter	Iterator on the location to insert to.
	 * @param item	Item to insert.
	 */
	void insert(const Iterator& iter, const T& item);
	
	/**
	 * Remove the item at the given index. Following items are shift to the
	 * lower indexes.
	 * @param index	Index of the item to remove.
	 */
	void removeAt(int index);
	
	/**
	 * Remove the item at the given index. Following items are shift to the
	 * lower indexes.
	 * @param iter	Iterator on the item to remove.
	 */
	void removeAt(const Iterator& iter);
};


/**
 * This concepts represents stack of items (First-In First-Out).
 *
 * @param T	Type of stacked items.
 *
 * @par Implemented by:
 * @li @ref BiDiList
 * @li @ref List
 * @li @ref Vector
 *
 * @ingroup concepts
 */
template <class T>
class Stack {
public:
	
	/**
	 * Test if the stack is empty.
	 * @return	Return true if the stack is empty, false else.
	 */
	bool isEmpty(void) const;
	
	/**
	 * Get the item at the top of the stack.
	 * @return	Top item of the stack.
	 */
	const T& top(void) const;
	
	/**
	 * Pop the top item of the stack.
	 * @return	Top item.
	 */
	T pop(void);
	
	/**
	 * Push a new item in the stack.
	 * @param item	Item to push in the stack.
	 */
	void push(const T& item);
	
	/**
	 * Reset the stack to empty.
	 */
	void reset(void);
};


/**
 * Concept representing the work of a queue.
 *
 * @param T	Type of item in the queue.
 *
 * @par Implemented by:
 * @li @ref BiDiList
 * @li @ref ListQueue
 * @li @ref VectorQueue
 *
 * @ingroup concepts
 */
template <class T>
class Queue {
public:

	/**
	 * Test if the queue is empty.
	 * @return	True if the queue is empty, false else.
	 */
	bool isEmpty(void) const;
	
	/**
	 * Get the head element of the queue.
	 * @return	Head element of the queue.
	 */
	const T& head(void) const;
	
	/**
	 * Get and remove the head item of the queue.
	 * @return	Head item of the queue.
	 */
	T get(void);
	
	/**
	 * Put a new item at the tail of the queue.
	 * @param item	Item to enqueue.
	 */
	void put(const T& item);
	
	/**
	 * Make the queue empty.
	 */
	void reset(void);

};


/**
 * This concept must be implemented by interface to hashable objects.
 *
 * @param T		Type of hashable objects.
 *
 * @par Implemented by:
 * @li @ref HashKey and its specializations
 * @li @ref SelfHashKey
 *
 * @par Used by:
 * @li @ref HashMap
 * @li @ref HashSet
 * @li @ref HashTable
 *
 * @ingroup concepts
 */
template <class T>
class Hash {
public:

	/**
	 * Compute the hash value of the given object.
	 * @param object	Object to hash.
	 * @return			Hash value.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	static t::uint32 hash(const T& object);
	
	/**
	 * Test if two hashable objects are equal.
	 * @param object1	First object to compare.
	 * @param object2	Second object to compare.
	 * @return			True if both objects are equal, false else.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	static bool equals(const T& object1, const T& object2);

	/**
	 * Compute the hash value of the given object.
	 * @param object	Object to hash.
	 * @return			Hash value.
	 */
	t::uint32 computeHash(const T& object);

	/**
	 * Test if two hashable objects are equal.
	 * @param object1	First object to compare.
	 * @param object2	Second object to compare.
	 * @return			True if both objects are equal, false else.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	bool isEqual(const T& object1, const T& object2);

};


/**
 * This concept must be implemented by classes providing comparisons of values
 * (strict order).
 * @param T	Type of objects to compare.
 * 
 * @par Implemented by:
 * @ref AssocComparator
 * @ref Comparator
 * @ref DynamicComparator
 * @ref GlobalComparator
 * @ref ReverseComparator
 * @ref StaticComparator
 * 
 * @par Used by:
 *
 * @ingroup concepts
 */
template <class T>
class Comparator {
public:

	/**
	 * Compare two objects.
	 * @param object1	First object to compare.
	 * @param object2	Second object to compare.
	 * @return	<0 if object 1 is less than object 2, 0 if they are equals,
	 * 			>0 else.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	static int compare(const T& object1, const T& object2);

	/**
	 * Compare two objects.
	 * @param object1	First object to compare.
	 * @param object2	Second object to compare.
	 * @return	<0 if object 1 is less than object 2, 0 if they are equals,
	 * 			>0 else.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	int doCompare(const T& object1, const T& object2);

};


/**
 * This class provides methods to test for equality.
 * 
 * @par Implemented by:
 * @ref elm::Equiv
 * @ref elm::CompareEquiv
 * @ref elm::EqualsEquiv
 * 
 * @param T		Type of values to test.
 * @ingroup concepts
 */
template <class T>
class Equiv {
public:
	
	/**
	 * Test if two values are equal.
	 * @param val1	First value to test for equality.
	 * @param val2	Second value to test for equality.
	 * @return		True if both values are equal, false else.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	static bool equals(const T& val1, const T& val2);

	/**
	 * Test if two values are equal.
	 * @param val1	First value to test for equality.
	 * @param val2	Second value to test for equality.
	 * @return		True if both values are equal, false else.
	 * @deprecated	Non-static version of this method is preferred now.
	 */
	static bool isEqual(const T& val1, const T& val2);
};


/**
 * This concept is implemented by objects matching a partial order.
 * @param T	Type of compared items.
 * @ingroup concepts
 */
template <class T>
class PartialComparator {
public:

	/**
	 * The bit 0 asserts equality relation.
	 */
	static const int EQUAL = 0x001;
	
	/**
	 * The bit 1 asserts the inferiority relation.
	 */
	static const int LESS = 0x010;
	
	/**
	 * The bit 2 asserts the superioritiy relation.
	 */
	static const int GREATER = 0x100;
	
	/**
	 * All bits to zero shows that both values are uncomparable.
	 */
	static const int UNCOMP = 0x000;
	
	/**
	 * Test for equality.
	 * @param v1	Value 1 to compare.
	 * @param v2	Value 2 to compare.
	 * @return		True if both values are equals, false else.
	 */
	static bool equals(const T& v1, const T& v2);
	
	/**
	 * Test for greatness.
	 * @param v1	Value 1 to compare.
	 * @param v2	Value 2 to compare.
	 * @return		True if v1 is greater than v2, false else.
	 */
	static bool greaterThan(const T& v1, const T& v2);

	/**
	 * Test for lessness.
	 * @param v1	Value 1 to compare.
	 * @param v2	Value 2 to compare.
	 * @return		True if v1 is less than v2, false else.
	 */
	static bool lessThan(const T& v1, const T& v2);

	/**
	 * Perform a soft comparison: any value may be compared.
	 * @param v1	Value 1 to compare.
	 * @param v2	Value 2 to compare.
	 * @return		A bit field composed by EQUAL, LESS, GREATER.
	 */
	static int compare(const T& v1, const T& v2);
};


/**
 * This concept defines collections of items retrievable by an assigned key.
 * @par
 * Implemented by:
 * @li @ref elm::HashMap
 * @li @ref elm::ListMap
 * @par
 * @ingroup concepts
 */
template <class K, class T>
class Map: public  Collection<Pair<K, T> > {
public:
	
	/**
	 * Get a value by its key.
	 * @param key	Key to get the value for.
	 * @return		The matching value.
	 */
	Option<const T&> get(const K& key) const;
	
	/**
	 * Get a value by its key.
	 * @param key	Key to get the value for.
	 * @param def	Default value to return if the key is not found.
	 * @return		Found value or default value.
	 */
	const T& get(const K& key, const T& def) const;

	/**
	 * Test if the key is defined in the map.
	 * @param key	Key to look for.
	 * @return		True if the key is defined in the map, false else.
	 */
	bool hasKey(const K& key) const;

	/**
	 * Iterator on the keys stored in the map.
	 */
	class KeyIterator: public Iterator<K> {
	public:
	
		/**
		 * Iterates on the given map.
		 * @param map	Map to iterate on.
		 */
		KeyIterator(const Map<K, T>& map);
		
		/**
		 * Copy the given iterator.
		 * @param iter	Iterator to copy.
		 */
		KeyIterator(const KeyIterator& iter);
	};
	
	/**
	 * Iterator giving access to keys and values stored in the map.
	 */
	class PairIterator: public Iterator<Pair<K, T> > {
	public:
	
		/**
		 * An iterator on values and keys of the map.
		 * @param map	Map to iterate on.
		 */
		PairIterator(const Map<K, T>& map);
		
		/**
		 * An iterator by copy.
		 * @param iter	Iterator to copy.
		 */
		PairIterator(const ValueIterator& iter);
	};
};


/**
 * A map that may be modified.
 * @par
 * Implemented by:
 * @li @ref elm::HashMap
 * @li @ref elm::ListMap
 * @par
 * @ingroup concepts
 */
template <class K, class T>
class MutableMap: public  Map<K, T>, public Collection<Pair<K, T> > {
public:
	
	/**
	 * Put a new value in the map.
	 * @param key	Key of the item to put.
	 * @param value	Value of the item to put.
	 */
	void put(const K& key, const T& value);
	
	/**
	 * Remove a value by its key.
	 * @param key	Key of the value to remove.
	 */
	void remove(const K& key);
	
	/**
	 * Remove an item using an iterator.
	 * @param iter	Iterator to use.
	 */
	void remove(const PairIterator& iter);
};


/**
 * A list is an ordered sequence of items. It implements the @ref Collection
 * concept but the iterator traverse the list in the sequence of the items.
 *
 * @par Implemented by:
 * @ref elm::List
 * @ref elm::BiDiList
 * 
 * @ingroup concepts
 */
template <class T>
class List: public Collection<T> {
public:
	
	/**
	 * Get the first item of the list.
	 * @return	First item.
	 */
	const T& first(void);
	
	/**
	 * Get the last item of the list.
	 * @return	Last item.
	 */ 
	const T& last(void);
	
	/**
	 * Find the iterator of the item equal to the given one in the list.
	 * @param item	Item to look for.
	 * @return		Iterator on the found item, ended item if not found.
	 */
	Iterator<T> find(const T& item);

	/**
	 * Find the iterator of the item equal to the given one in the list.
	 * @param item	Item to look for.
	 * @param iter	Position to start from.
	 * @return		Iterator on the found item, ended item if not found.
	 */
	Iterator<T> find(const T& item, const Iterator& start);
};


/**
 * A list is an ordered sequence of items. It implements the MutableCollection
 * concept but the iterator traverse the list in the sequence of the items.
 *
 * @par Implemented by:
 * @ref elm::BiDiList
 * @ref elm::List
 * 
 * @ingroup concepts
 */
template <class T>
class MutableList: public List<T>, public MutableCollection<T> {
public:
	
	/**
	 * Add an item as the first item before other items..
	 * @param item	Item to add.
	 */
	void addFirst(const T& item);
	
	/**
	 * Add an item as the last item after other items.
	 * @param item	Item to add.
	 */
	void addLast(const T& item);
	
	/**
	 * Remove the first item.
	 */
	void removeFirst(void);
	
	/**
	 * Remove the last item.
	 */
	void removeLast(void);
	
	/**
	 * Add an item after another one.
	 * @param pos	Position to add after.
	 * @param item	Item to add.
	 */
	void addAfter(const Iterator<T>& pos, const T& item);
	
	/**
	 * Add an item before another one.
	 * @param pos	Position to add before.
	 * @param item	Item to add.
	 */
	void addBefore(const Iterator<T>& pos, const T& item);
	
	/**
	 * Change an item in the list.
	 * @param pos	Position of the item to change.
	 * @param item	New item to replace with.
	 */
	void set(const Iterator<T>& pos, const T& item);
};


/**
 * A bidirectionnal list that may be as efficiently forward traversed as
 * backward traversed. Mainly, it provides a BackIterator class for
 * back traversal.
 * 
 * @par Implemented by:
 * @ref elm::BiDiList
 * 
 * @ingroup concepts
 */
template <class T>
class BiDiList: public List<T> {
public:
	
	/**
	 * Iterator for forward traversal of the list.
	 */
	class Iterator: public List<T>::Iterator {
	public:
		Iterator(const BiDiList<T>& list);
		Iterator(const Iterator<T>& iter);
		Iterator(const BackIterator<T>& iter);
		Iterator& operator=(const BackIterator<T>& iter);
	};
	
	/**
	 * Iterator for backward traversal of the list.
	 */
	class BackIterator: public Iterator<T> {
	public:
		BackIterator(const BiDiList<T>& list);
		BackIterator(const BackIterator<T>& iter);
		BackIterator(const Iterator<T>& iter);
		BackIterator& operator=(const BackIterator<T>& iter);		
		BackIterator& operator=(const Iterator<T>& iter);		
	};
};


/**
 * This class are used for data whose only a part represents an identifier
 * when comparison must be done.
 * @param K		Type of the key.
 * @param T		Type of the item.
 *
 * Implemented by:
 * @li	@ref elm::Id<T>
 * @li @ref elm::PairAdapter<K, T>
 */
template <class K, class T>
class Key {
public:
	
	/**
	 * Type of the key.
	 */
	typedef K key_t;
	
	/**
	 * Get the key from a value.
	 * @param value	Value to get the key of.
	 * @return		Key of the current value.
	 */
	static const K& key(const T& value);
};


/**
 * The Compare concept enables the comparison of values
 * using a single method @ref compare. Unlike @ref
 * Comparator, it supports a comparison induced from an
 * instance and, therefore, dependeng not only on the type
 * but also on the instance state.
 *
 * @param T		Type of value to compare.
 */
template <class T>
class Compare {
public:
		int compare(T v1, T v2);
};


/**
 * A predicate enables testing of an item and returns true or false.
 * They are usually used by set functions as @ref elm::forall()
 * or elm::exists().
 *
 * @param T		Type of item to test.
 */
template <class T>
class Predicate {
public:

	/**
	 * Test if the predicate is true for the given item.
	 * @param item	Item to test.
	 * @return		True or false according to the internal policy.
	 */
	bool test(const T& item);
};

} } // elm::concept
