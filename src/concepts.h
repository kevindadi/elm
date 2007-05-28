/*
 * $Id$
 * Copyright (c) 2007 - IRIT-UPS <casse@irit.fr>
 *
 * Concepts documentation
 */

namespace elm { namespace concept {

/**
 * @page concepts Concepts
 * The ELM V0.3 will implement the concept approach. We are currently designing
 * concepts for ELM whose a list is given below that will be used to fix
 * progressively the existing classes.
 * 
 * @par Collection Concepts
 * @li @ref elm::concept::Array
 * @li @ref elm::concept::Collection
 * @li @ref elm::concept::Iterator
 * @li @ref elm::concept::MutableArray
 * @li @ref elm::concept::MutableCollection
 * 
 * @par Value Concepts
 * @li @ref elm::concept::Comparator
 * @li @ref elm::concept::Hash
 */

/**
 * This concept is matched by all iterators. It provides a way to traverse
 * a collection of items. Class matching this concept must defines the
 * following methods.
 * @param T	Type of items of the collection.
 */
template <class T>
class Iterator {
public:

	/**
	 * Just a clone constructor.
	 * @param iterator	Iterator to clone.
	 */
	Iterator(const IteratorConcept& iterator);
	
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
	const T& item(void);
	
	/**
	 * Same as ! @ref ended().
	 */
	operator bool(void);
	
	/**
	 * Same as @ref item().
	 */
	operator const T& (void);
	
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
 * @param T	Type of items stored in the collection.
 */
template <class T>
class Collection {
public:

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
	 * Test if the collection si empty.
	 * @return	True if the collection is empty, false else.
	 */
	bool isEmpty(void);
	
	/**
	 * Same as @ref isEmpty().
	 */
	operator bool(void);
	
	class Iter: public Iterator<T> {
	public:
	
		/**
		 * Build an iterator from a collection.
		 * @param collection	Collection to traverse.
		 */
		Iter(const Collection<T>& collection);
	
		/**
		 * Build an iterator from a collection.
		 * @param collection	Collection to traverse.
		 */
		Iter(const Collection<T> *collection);
	};
};


/**
 * This concept provides way to have collections whose content may be modified.
 * @param T	Type of items in the collection.
 */
template <class T>
class MutableCollection: public Collection<T> {
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
};


/**
 * This concept provides methods to access an indexed list of items.
 * @param T	Type of item in the array.
 */
template <class T>
class Array: public Collection<T> {
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
	 * Get the index of the last occurence of a value.
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
 */
template <class T>
class MutableArray: public Array<T>, public MutableCollection<T> {
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
	 * Remove the item at the given index. Following items are shift to the
	 * lower indexes.
	 * @param index	Index of the item to remove.
	 */
	void removeAt(int index);
};


/**
 * This concept must be implemented by interface to hashable objects.
 * @param T		Type of hashable objects.
 */
template <class T>
class Hash {
public:

	/**
	 * Compute the hash value of the given object.
	 * @param object	Object to hash.
	 * @return			Hash value.
	 */
	static unsigned long hash(const T& object);
	
	/**
	 * Test if two hashable objects are equal.
	 * @param object1	First object to compare.
	 * @param object2	Second object to compare.
	 * @return			True if both objects are equal, false else.
	 */
	static inline bool equals(const T& object1, const T& object2);
};


/**
 * This concept must be implemented by classes providing comparisons of values
 * (strict order).
 * @param T	Type of objects to compare.
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
	 */
	static int compare(const T& object1, const T& object2);
};

} } // elm::concept
