/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/system/ProcessBuilder.h -- ProcessBuilder class interface.
 */
#ifndef ELM_SYSTEM_PROCESS_BUILDER_H
#define ELM_SYSTEM_PROCESS_BUILDER_H

#include <elm/genstruct/Vector.h>
#include <elm/system/SystemIO.h>
#include <elm/system/Process.h>

namespace elm { namespace system {

// ProcessBuilder class
class ProcessBuilder {
	genstruct::Vector<CString> args;
	SystemInStream *in;
	SystemOutStream *out, *err;
public:
	ProcessBuilder(CString command);
	void addArgument(CString argument);
	void setInput(SystemInStream *_in);
	void setOutput(SystemOutStream *_out);
	void setError(SystemOutStream *_out);
	Process *run(void);
};

} } // elm::system

#endif // ELM_SYSTEM_PROCESS_BUILDER_H
