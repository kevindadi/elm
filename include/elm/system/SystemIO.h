/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/system/SystemIO.h -- SystemInStream and SystemOutStream classes interface.
 */
#ifndef ELM_SYSTEM_SYSTEM_IO_H
#define ELM_SYSTEM_SYSTEM_IO_H

// Unix system streams
#if defined(__unix)
#	include <elm/io/UnixInStream.h>
#	include <elm/io/UnixOutStream.h>

	namespace elm { namespace system {

	class SystemInStream: public io::UnixInStream {
	public:
		inline SystemInStream(int fd): UnixInStream(fd) { }
	protected:
		friend class System;
	};

	class SystemOutStream: public io::UnixOutStream {
	public:
		inline SystemOutStream(int fd): UnixOutStream(fd) { };
	protected:
		friend class System;
	};

	} }		// elm::system

// Windows system streams
#elif defined(__WIN32) || defined(__WIN64)
#	include <elm/io/WinInStream.h>
#	include <elm/io/WinOutStream.h>

	namespace elm { namespace system {

	class SystemInStream: public io::WinInStream {
	protected:
		friend class System;
	public:
		inline SystemInStream(void* fd): WinInStream(WinInStream::fd()) { }
		inline ~SystemInStream(void) { }
	};

	class SystemOutStream: public io::WinOutStream {
	protected:
		friend class System;
	public:
		inline SystemOutStream(void* fd): WinOutStream(WinOutStream::fd()) { }
		inline ~SystemOutStream(void) { }
	};

	} }		// elm::system

// unsupported OS
#else
#	error "Unsupported OS !"
#endif


// Standard Streams
namespace elm { namespace io {

extern system::SystemInStream& in;
extern system::SystemOutStream& out;
extern system::SystemOutStream& err;

} } // elm::io

#endif // ELM_SYSTEM_SYSTEM_IO_H
