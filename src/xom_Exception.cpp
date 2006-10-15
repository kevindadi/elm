/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * src/xom_Exception.cpp -- XOM Exception class implementation.
 */

#include <elm/xom/Exception.h>

namespace elm { namespace xom {

/**
 * @class Exception
 * Exception thrown for errors during XOM work.
 */


/**
 * Build the exception from a formatted string.
 * @param node		Node causing the exception.
 * @param format	Message format.
 * @param ...		Format arguments.
 */
Exception::Exception(Node *node, const CString& format, ...) {
	VARARG_BEGIN(args, format)
		buildMessage(format, args);
	VARARG_END
}


/**
 * Build the exception from a formatted string.
 * @param node		Node causing the exception.
 * @param format	Message format.
 * @param args		Format arguments.
 */
Exception::Exception(Node *node, const CString& format, VarArg& args) {
	buildMessage(format, args);
}


/**
 * @fn Node *Exception::node(void) const;
 * Get the node causing the exception.
 */

} } // elm::xom
