/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * src/system_SystemIO.cpp -- SystemInStream and SystemOutStream classes implementation.
 */

#include <elm/system/SystemIO.h>

namespace elm { namespace system {

/**
 * @class SystemInStream
 * This kind of stream is tied to a system input stream, that is, it may be
 * shared by processes or support system feature. @ref io::stdin is an example
 * of @ref SystemInStream.
 *  
 * @warning	Do not rely on the current inheritance of this class: it may change
 * according systems. The only right inheritance relation is with @ref io::InStream.
 */


/**
 * @class SystemOutStream
 * This kind of stream is tied to a system output stream, that is, it may be
 * shared by processes or support system feature. @ref io::stdout and
 * @ref io::stdout are examples of @ref SystemOutStream.
 *  
 * @warning	Do not rely on the current inheritance of this class: it may change
 * according systems. The only right inheritance relation is with @ref io::OutStream.
 */


// Standard Input
class StandardInStream: public SystemInStream {
public:
	inline StandardInStream(int fd): SystemInStream(fd) { };
};
static StandardInStream stdin_object(0);


// Standard Output
class StandardOutStream: public SystemOutStream {
public:
	inline StandardOutStream(int fd): SystemOutStream(fd) { };
};
static StandardOutStream stdout_object(1);
static StandardOutStream stderr_object(2);

} // system

namespace io {

/**
 * Standard input stream.
 */
system::SystemInStream& stdin = system::stdin_object; 

/**
 * Standard output stream.
 */
system::SystemOutStream& stdout = system::stdout_object; 

/**
 * Standard error stream.
 */
system::SystemOutStream& stderr = system::stderr_object; 

} } // elm::io
