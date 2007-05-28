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
 * @param message	Message.
 */
Exception::Exception(Node *node, const String& message)
: MessageException(message) {
}


/**
 * @fn Node *Exception::node(void) const;
 * Get the node causing the exception.
 */

} } // elm::xom
