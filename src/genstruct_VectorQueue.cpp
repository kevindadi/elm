/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * src/genstruct_VectorQueue.cpp -- VectorQueue class implementation.
 */

#include <elm/genstruct/VectorQueue.h>

namespace elm { namespace genstruct {

/**
 * @class VectorQueue
 * This class implements a queue as an extendable vector.
 */
 

/**
 * @fn VectorQueue::VectorQueue(int capacity);
 * Build a new vector queque. The passed capacity will be used for computing
 * the actual capacity as power of two of the capacity.
 * @param capacity	Capacity exponent.
 */


/**
 * @fn int VectorQueue::capacity(void) const;
 * Get the current capacity of the queue.
 * @return	Current capacity.
 */


/**
 * @fn int VectorQueue::size(void) const;
 * Get the current size of the queue.
 * @return	Queue size.
 */


/**
 * @fn bool VectorQueue::isEmpty(void) const;
 * Test if the queue is empty.
 * @return	True if the queue is empty, false else.
 */


/**
 * @fn void VectorQueue::put(const T& item);
 * Put an item at the head of the queue.
 * @param item	Item to put.
 */


/**
 * @fn const T& VectorQueue::get(void);
 * Get and remove the head item of the queue.
 * @warning It is an error to perform this call when the queue is empty.
 * @return	Head item.
 */


/**
 * @fn const T& VectorQueue::head(void);
 * Get the head item of the queue without removing it.
 * @warning It is an error to perform this call when the queue is empty.
 * @return	Head item.
 */


/**
 * @fn void VectorQueue::reset(void);
 * Reset the queue to its initialstate (except for the capacity) and remove
 * all enqueued items.
 */

} } // elm::genstruct
