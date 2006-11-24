/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * Initializer class implementation.
 */

#include <elm/util/Initializer.h>

namespace elm {

/**
 * @class Initializer
 * This class is a partial solution to the problem of the initialization
 * order of static variables at the start time of a program in C++.
 * This class solve the following problem at initialization. A set of
 * static object embedded in different sources shares a common datastructure
 * whose initialization time may be happen after some of these objects.
 * @p
 * Whatever, the static object initialization is split in two phases.
 * First, the object initialize itself but not the part using the shared data.
 * Instead, they record themselves to the initializer that will, when the shared
 * data will be initialized, call the "void initialize(void)" method of each
 * recorded object ensuring final initialization after the shared data item.
 * @p
 * To achieve this goal, either the shared data item must inherit from the
 * Initializer class or an Initializer static instance must be declared after
 * the shared data item.
 * @p
 * This class has very small footprint on the memory and, except the Initializer
 * object itself, all memory used will be returned to the system after the
 * initialization stage.
 * 
 * @param T	Type of the objects to give an order to.
 */


/**
 * @fn Initializer::Initializer(void);
 * Simple constructor.
 */


/**
 * @fn void Initializer::record(T *object);
 * Record the given object to be initialized after the shared data item.
 * @param object	Object to initialize.
 */


/**
 * @fn void Initializer::startup(void);
 * Cause the initializer to start to initializer recorded objects.
 */

} // elm
