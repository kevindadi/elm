/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * src/io_IOException.cpp -- IOException class implementation.
 */

#include <string.h>
#include <errno.h>
#include <elm/io/io.h>

namespace elm { namespace io {

/**
 * @class IOException
 * This exception is thrown when an IO error occurs.
 */


/**
 *@fn  IOException::IOException(CString message, ...);
 * Build a new IOException with the given message.
 * @param message	Message formatted a-la printf.
 * @param ...		Arguments used in the message.
 */


/**
 *@fn  IOException::IOException(CString message, VarArg& args);
 * Build a new IOException with the given message.
 * @param message	Message formatted a-la printf.
 * @param args		Arguments used in the message.
 */

} } // elm::io
