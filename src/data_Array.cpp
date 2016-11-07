/*
 *	Array classes implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
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

#include <elm/data/Array.h>

namespace elm {

/**
 * @class Array
 * An array is a simple wrapper around the C array data type.
 * It provides controlled methods to it (indexed accesses are protected with
 * assertions) and implements the @ref concept:: Collection concept
 * and therefore can be used as any collection. Yet, it doesn't manage
 * the memory of the array.
 *
 * To shorten the construction of an Array, you can use the function
 * @ref _array().
 *
 * @param T		Type of elements stored in the array.
 * @see AllocArray, _array()
 * @ingroup data
 */

/**
 * @fn Array::Array(void);
 * Build an empty array.
 */

/**
 * @fn Array::Array(int count, T *buffer);
 * Build an array using buffer as array and with size count.
 * The @ref Array will NOT be in charge of freeing this memory!
 * @param count		Array size.
 * @param buffer	Buffer Array buffer.
 */

/**
 * @var const Array<T> Array::null;
 * Singleton representing an empty array.
 */

/**
 * @fn int Array::count(void) const;
 * @return	Number of elements in the array.
 */

/**
 * @fn const T *Array::buffer(void) const;
 * @return	Buffer of the array.
 */

/**
 * @fn T *Array::buffer(void);
 * @return	Buffer of the array.
 */

/**
 * int Array::size(void) const;
 * Same as @ref count().
 */

/**
 * @class Array::Iter
 * Iterator on the elements of the array.
 */

/**
 * @fn Array::Iter Array::items(void) const;
 * @return iterator on the items of the array.
 */

/**
 * @fn void Array::set(const Iter& i, const T& val);
 * Set a value according to an iterator.
 * @param i		Non-ended iterator.
 * @param val	Value to set.
 */

/**
 * @fn void Array::set(int count, T *buffer);
 * Change the buffer of the array. The @ref Array will NOT be
 * in charge of freeing this buffer.
 * @param count		Array count.
 * @param buffer	Array buffer.
 */

/**
 * @fn void Array::set(const Array<T>& t);
 * Assign the given array t to the current array.
 * @param t		Array to assign.
 */

/**
 * @fn void Array::copy(const Array& t);
 * Copy the array t inside the current array. If the current array is smaller
 * than t, only the first elements will be copied.
 * @param t	Array to copy.
 */

/**
 * @fn void Array::fill(const T& val);
 * Fill the array with the gien value.
 * @param val	Value to copy in the array elements.
 */

/**
 * @fn const T& Array::get(int idx) const;
 * Get an element by index. Raise an assertion failure if idx is out of array bounds.
 * @param idx	Index of element to get.
 * @return		Element at index idx.
 */

/**
 * @fn T& Array::get(int idx);
 * Get a reference on an element by index. Raise an assertion failure if idx is out of array bounds.
 * @param idx	Index of element to get.
 * @return		Reference on element at index idx.
 */

/**
 * @fn void Array::set(int idx, const T& val);
 * Set an array element according to index idx. If the index is out of bound,
 * an assertion failure is raised.
 * @param idx	Index of the element to assign.
 * @param val	Value to assign.
 */

/**
 * @fn const T *Array::operator()(void) const;
 * Same as @ref buffer().
 */

/**
 * @fn T *Array::operator()(void);
 * Same as @ref buffer().
 */

/**
 * @fn const T& Array::operator[](int idx) const;
 * Same as @ref get().
 */

/**
 * @fn T& Array::operator[](int idx);
 * Same as @ref get().
 */

/**
 * @fn Array<T>& Array::operator=(const Array<T>& t);
 * Same as @ref set().
 */

/**
 * @fn  Array::operator Iter(void) const;
 * Same @ref items().
 */

/**
 * @fn Array::Iter Array::operator*(void) const;
 * Same as @ref items().
 */

/**
 * @class AllocArray
 * An @ref AllocArray is an @ref Array that manages its own memory. It may
 * be built giving its size and from another C array or @ref Array. It will
 * create its memory to store the array and it will free it at destruction
 * time.
 *
 * Only the @ref set() methods can assign to the @ref AllocArray a memory
 * not allocated by itself. If such a method is called, it will receive
 * the given array (and memory) and will free it when it will be
 * destructed.
 *
 * @param T		Type of elements stored in the array.
 * @see cArray, _array
 * @ingroup data
 */

/**
 * @fn AllocArray::AllocArray(void);
 * Build an empty array.
 */

/**
 * @fn AllocArray::AllocArray(int count, T *buffer):
 * Build an array by copying the given array.
 * @param count		Element count.
 * @param buffer	Containing the element to copy.
 */

/**
 * @fn AllocArray::AllocArray(int count);
 * Allocate an array with count size.
 * @param count	Array element count.
 */

/**
 * @fn AllocArray::AllocArray(int count, const T& val);
 * Allocate an array with count element and initialize them with val.
 * @param count	Element count.
 * @param val	Initialization value.
 */

/**
 * @fn AllocArray::AllocArray(const Array<T>& t);
 * Build a copy of the given array.
 */

/**
 * @fn AllocArray::AllocArray(const AllocArray<T>& t);
 * Build a copy of the given array.
 */

/**
 * @fn void AllocArray::copy(const Array<T>& t);
 * Perform a copy inside the current array of the given array.
 * @param t		Copied array.
 */

/**
 * @fn void Array::tie(int cnt, T *buffer);
 * If needed, release its own buffer and use now the given one.
 * This also means that the AllocArray is now in charge of freeing
 * the given buffer.
 * @param cnt		Count of elements in the buffer.
 * @param buffer	Buffer containing elements.
 */

/**
 * @fn void Array::tie(const Array<T>& t);
 * If needed, release its own buffer and use now the one of the array.
 * This also means that the AllocArray is now in charge of freeing
 * the given buffer.
 * @param t	Array to take buffer from.
 */

/**
 * @fn AllocArray<T>& AllocArray::operator=(const Array<T>& t);
 * Same as copy().
 */

/**
 * @fn AllocArray<T>& AllocArray::operator=(const AllocArray<T>& t);
 * Same as copy().
 */


/**
 * @fn Array<T> _array(int n, T t[]);
 * Short way to build an Array of type T.
 * @param n		Array element count.
 * @param t		Array element buffer.
 *
 * @see Array
 * @ingroup data
 */

}	// elm
