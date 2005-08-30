/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS Corporation.
 *
 * src/util_VarArg.h -- VarArg class implementation.
 */

#include <elm/util/VarArg.h>

namespace elm {

/**
 * @class VarArg
 * This is a wrapper around the <stdarg.h> macros. This class may be used:
 * - as a wrapper around stdarg (use VARARG_BEGIN and VARARG_END macros),
 * - for avoiding ambiguity in overload between VarArg (va_list) and "..."
 * ellipsis.
 */


/**
 * @fn VarArg::VarArg(va_list& args);
 * Constructor from an existing va_list.
 * @param args	Existing va_list.
 */


/**
 * @fn VarArg::VarArg(const VarArg& args);
 * Cloning constructor.
 * @param args	VarArg to clone.
 */


/**
 * @fn T VarArg::next(void);
 * Get the next item in the variable argument list.
 * @return	Next item.
 */


/**
 * @fn va_list& VarArg::args(void);
 * Get the argument list.
 * @return	Argument list.
 */

} // elm
