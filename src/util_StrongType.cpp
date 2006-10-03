/*
 * $Id$
 * Copyright (c) 2006 - IRIT-UPS <casse@irit.fr>
 *
 * src/util_StrongType.h -- interface of StrongType documentation.
 */

#include <elm/util/StrongType.h>

namespace elm {
	
/**
 * @class StrongType <elm/util/StrongType.h>
 * As type defined with "typedef" command just create aliases to types, they
 * cannot be used to resolve overloading. To circumvent this problem, this class
 * provide a wrapper around the defined type that is usable as the original type
 * and that provide overload facilities.
 * 
 * This class is usually replace this kind of declaration:
 * @code
 * typedef type_exp type_name;
 * @endcode
 * by :
 * @code
 * typedef StrongType<type_exp> type_name;
 * @endcode
 * 
 * @param T	Encapsulated type.
 */

} // elm

