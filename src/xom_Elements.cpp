/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * src/xom_Elements.h -- XOM Elements class implementation.
 */

#include <elm/assert.h>
#include <elm/xom/Elements.h>
#include <elm/xom/Element.h>
#include "xom_macros.h"

namespace elm { namespace xom {

/**
 * @class Elements
 * A read-only list of elements for traversal purposes. Changes to the document
 * from which this list was generated are not reflected in this list. Changes to
 * the individual Element objects in the list are reflected.
 */


/**
 * @fn Element *Elements::get(int index) const;
 * Returns the indexth element in the list. The first element has index 0. The
 * last element has index size() - 1.
 * @param index the element to return 
 * @return 		the element at the specified position.
 */


/**
 * @fn int Elements::size(void) const;
 * Returns the number of elements in the list. This is guaranteed non-negative.
 * @return the number of elements in the list.
 */


/**
 * @fn Element *Elements::operator[](int index) const;
 * Shortcut to @ref get().
 */

} } // elm::xom
