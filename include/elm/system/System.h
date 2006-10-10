/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/system/System.h -- System class interface.
 */
#ifndef ELM_SYSTEM_SYSTEM_H
#define ELM_SYSTEM_SYSTEM_H

#include <elm/util/Pair.h>
#include <elm/system/SystemIO.h>

namespace elm { namespace system {

// PipeInStream class
class PipeInStream: public SystemInStream {
	friend class System;
	PipeInStream(int fd);
public:
	~PipeInStream(void);
};

// PipeOutStream class
class PipeOutStream: public SystemOutStream {
	friend class System;
	PipeOutStream(int fd);
public:
	~PipeOutStream(void);
};

// System class
class System {
public:
	static Pair<PipeInStream *, PipeOutStream *> pipe(void);
};

} } // elm::system

#endif // ELM_SYSTEM_SYSTEM_H
 
