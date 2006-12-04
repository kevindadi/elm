/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * Ref class implementation.
 */

#include <elm/util/Ref.h>

namespace elm {

/**
 * @class Ref
 * This class allows handling pointer as references but they provide
 * assignment operators.
 * @param T	Pointe type.
 */ 


/**
 * @fn Ref::Ref(T *_ptr);
 * Build a new reference.
 * @param _ptr	Pointer to store in.
 */


/**
 * @fn Ref::Ref(const Ref<T>& ref);
 * Cloning constructor.
 * @param ref	Cloned reference.
 */


/**
 * @fn Ref::operator T& (void) const;
 * Automatic conversion to reference.
 * @return	Reference on pointed object.
 */


/**
 * @fn T *Ref::operator&(void) const;
 * Get the stored pointer.
 * @return Stored pointer.
 */


/**
 * @fn Ref& Ref::operator=(T *_ptr);
 * Assignment with a pointer.
 * @param _ptr	Assigned pointer.
 * @return		Current object.
 */


/**
 * @fn Ref& Ref::operator=(const Ref<T>& ref);
 * Assignment with a reference.
 * @param ref	Assigned reference.
 * @return 		Current object.
 */


/**
 * @fn T *Ref::operator->(void) const;
 * Only way to perform unreference with structure and objects.
 * @return	Pointer on object.
 */


/**
 * @fn Ref<T>& Ref::operator=(const T& val);
 * Assignment of the pointed value.
 * @param val	Assigned value.
 * @return		Current object.
 */

} // elm
