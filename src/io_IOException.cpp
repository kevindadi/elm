/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * src/io_IOException.cpp -- IOException clas implementation.
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
 *@fn  IOException::IOException(message);
 * Build a new IOException with the given message.
 */

/**
 * Build an IO exception getting the error message from errno and from
 * the strerror() primitive.
 */
IOException::IOException(void): msg(strerror(errno)) {
}

} } // elm::io

