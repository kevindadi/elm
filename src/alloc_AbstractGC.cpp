/*
 *	AbstractGC class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2010, IRIT UPS.
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

#include <elm/alloc/AbstractGC.h>

namespace elm {

/**
 * @class GCManager
 * Provides an interface between a cooperative garbage collector (CGC) and the
 * application. In ELM, each CGC uses a manager (a) to provide the alive blocks
 * (using function collect()) and to safely clean up the fried objects
 * (using function clean()).
 *
 * @ingroup alloc
 */

///
GCManager::~GCManager() {
}

/**
 * @fn void GCManager::collect(AbstractGC& gc);
 * Called at the start of a garbage collection cycle, this function has to
 * call the mark() function of the garbage collection gc with each alive
 * object.
 * @param gc	Current garbage collector.
 */

/**
 * Called for each fried object. This function let the application call
 * the destructor of allocated objects. The default implementation does
 * nothing.
 * @param p		Pointer to object to destruct.
 */
void GCManager::clean(void *p) {
};


/**
 * @fn class AbstractGC;
 * Base class of cooperative garbage collectors. This kind of memory garbage
 * collector does not automatically obtains roots and linked memory blocks
 * by inspecting registers, stack and global memory but wait for this
 * information from the application itself.
 *
 * The main parameter of this class is a GCManager that provides alive blocks
 * by its function collect(). This function has to identify alive blocks by
 * calls to the mark() function of the garbage collector. This way,
 * a particular user application can provide its own method to maintain the
 * list of alive object. In addition, the GCManager let the application to
 * call the destructor when an object is friend thanks to its function
 * clean(). Notice that the use of the clean() functions may or may not be
 * implemented in a garbage collector (see documentation).
 *
 * This type of garbage collector allows to control the way the memory is
 * managed and to limit garbage collecting only to some parts of the program
 * where the roots are easily extracted. This garbage collection cycles are
 * usually shorter and the application is not forced to use the garbage
 * collector for all its memory.
 *
 * @ingroup alloc
 */

/**
 * @fn AbstractGC::AbstractGC(GCManager& m);
 * Build a garbage collector using the given manager.
 * @param m		Manager of the garbage collector.
 */

///
AbstractGC::~AbstractGC() {
}

/**
 * @fn void *AbstractGC::allocate(t::size size);
 * Allocate a block of the given size. This function is often used this way:
 *
 * @code
 * 	AbstractGC& gc;
 * 	MyClass *p = new(gc.allocate(sizeof(MyClass)) MyClass();
 * @endcode
 *
 * @param size	Size of the memory to allocate.
 * @return		Allocated object.
 */

/**
 * @fn void *AbstractGC::alloc();
 * Allocate the memory for an object of the given class.
 * This function can be used this way:
 *
 * @code
 * 	AbstractGC& gc;
 * 	MyClass *p = new(gc.alloc<MyClass>()) MyClass();
 * @endcode
 *
 * @param T		Class of the object to allocate.
 * @return		Allocated object.
 */

/**
 * Only kept for the compatibility with the memory interface.
 * Does nothing.
 * @param block		Block to free.
 */
void AbstractGC::free(void *block) {
}

/**
 * @fn void AbstractGC::runGC();
 * Called to start, by hand, a garbage collection cycle. Depending on the
 * underlying implementation, this function may be automatically called by
 * the garbage collector itself. Notice that during a garbage collection
 * cycle, any call to allocate() or alloc() is forbidden.
 */

/**
 * @fn bool AbstractGC::mark(void *data, t::size size);
 * Record the given block as alive. This function can only be called during
 * a garbage collection cycle.
 * @param data	Pointer to the alive memory block.
 * @param size	Size of the block.
 * @return		True if the block has already been collected, false else.
 */

/**
 * @fn void AbstractGC::disable();
 * Disable the automatic run of the garbage collection.
 */

/**
 * @fn void AbstractGC::enable();
 * Disable the automatic run of the garbage collection.
 * May trigger immediately a GC cycle.
 */

/**
 * @fn void AbstractGC::clean();
 * Clean the memory allocated in the garbage collector and reset it to its
 * initial state.
 */

} // elm
