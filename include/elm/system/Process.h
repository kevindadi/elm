/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/system/Process.h -- Process class interface.
 */
#ifndef ELM_SYSTEM_PROCESS_H
#define ELM_SYSTEM_PROCESS_H


namespace elm { namespace system {

// Process class
class Process {
	friend class ProcessBuilder;
#if defined(__LINUX)
	int pid, rcode;
	Process(int _pid);
#elif defined(__WIN32) || defined(__WIN64)
	void* pi;
	unsigned long  rcode;
	Process(void* _pi);
#else
#error "System not supported"
#endif

public:
	bool isAlive(void);
	int returnCode(void);
	void kill(void);
	void wait(void);
};

} } // elm::system

#endif // ELM_SYSTEM_PROCESS_H
