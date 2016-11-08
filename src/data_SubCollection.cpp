/*
 *	SubCollection class implementation
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

#include <elm/data/SubCollection.h>

namespace elm {

/**
 * @class class SubCollection
 * A sub-collection, as shown by its name, represents
 * a part of collection ranging from one iterator
 * to another iterator.
 *
 * Implements concept::Collection.
 *
 * A fast way to build a sub-collection is to use the function
 * sub_coll().
 *
 * @param I		Type of iterators.
 * @ingroup data
 * @see sub_coll()
 */


/**
 * @fn SubCollection::SubCollection(const I& begin, const I& end);
 * Build a sub-collection the begin iterator to the end iterator (exclusive).
 * @param begin		Iterator on the first element of the collection.
 * @param end		End iterator past the last element of the collection (may be ended).
 */

/**
 * @fn SubCollection<I> sub_coll(const I& begin, const I& end);
 * Fast way to build a sub-collection.
 * @param begin		Iterator on the first element of the collection.
 * @param end		End iterator past the last element of the collection (may be ended).
 * @ingroup data
 */

}	// elm
