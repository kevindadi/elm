/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/system/SystemIO.h -- SystemInStream and SystemOutStream classes interface.
 */
#ifndef ELM_SYSTEM_SYSTEM_IO_H
#define ELM_SYSTEM_SYSTEM_IO_H

#if defined(__UNIX)
#include <elm/io/UnixInStream.h>
#include <elm/io/UnixOutStream.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <elm/io/WinInStream.h>
#include <elm/io/WinOutStream.h>
#endif

namespace elm { namespace system {

// SystemInStream class
#if defined(__UNIX)
class SystemInStream: public io::UnixInStream {
protected:
	friend class System;
	inline SystemInStream(int fd): UnixInStream(fd) { }
	inline ~SystemInStream(void) { }
};
#elif defined(__WIN32) || defined(__WIN64)
class SystemInStream: public io::WinInStream {
protected:
	friend class System;
public:
	inline SystemInStream(void* fd): WinInStream(WinInStream::fd()) { }
	inline ~SystemInStream(void) { }
};
#endif


// SystemOutStream class
#if defined(__UNIX)
class SystemOutStream: public io::UnixOutStream {
protected:
	friend class System;
	inline SystemOutStream(int fd): UnixOutStream(fd) { };
	inline ~SystemOutStream(void) { }
};
#elif defined(__WIN32) || defined(__WIN64)
class SystemOutStream: public io::WinOutStream {
protected:
	friend class System;
public:
	inline SystemOutStream(void* fd): WinOutStream(WinOutStream::fd()) { }
	inline ~SystemOutStream(void) { }
};
#endif


} // system

// Standard Streams
namespace io {

extern system::SystemInStream& in;
extern system::SystemOutStream& out;
extern system::SystemOutStream& err;

} } // elm::io

#endif // ELM_SYSTEM_SYSTEM_IO_H
