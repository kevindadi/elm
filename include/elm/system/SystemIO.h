/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/system/SystemIO.h -- SystemInStream and SystemOutStream classes interface.
 */
#ifndef ELM_SYSTEM_SYSTEM_IO_H
#define ELM_SYSTEM_SYSTEM_IO_H

#include <elm/io/UnixInStream.h>
#include <elm/io/UnixOutStream.h>

namespace elm { namespace system {

// SystemInStream class
class SystemInStream: public io::UnixInStream {
protected:
	friend class System;
	inline SystemInStream(int fd): UnixInStream(fd) { }
	inline ~SystemInStream(void) { }
}; 

// SystemOutStream class
class SystemOutStream: public io::UnixOutStream {
protected:
	friend class System;
	inline SystemOutStream(int fd): UnixOutStream(fd) { };
	inline ~SystemOutStream(void) { }
}; 

} // system

// Standard Streams
namespace io {

extern system::SystemInStream& in; 
extern system::SystemOutStream& out; 
extern system::SystemOutStream& err; 

} } // elm::io

#endif // ELM_SYSTEM_SYSTEM_IO_H
