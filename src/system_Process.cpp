/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * src/system_Process.cpp -- Process class interface.
 */

#include <assert.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/wait.h> 
#include <signal.h>
#include <elm/system/Process.h>
#include <elm/system/SystemException.h>

namespace elm { namespace system {

/**
 * @class Process
 * An interface with the processes of the OS.
 */


/**
 * Build a new process.
 * @param _pid	Process identifier.
 */
Process::Process(int _pid): pid(_pid) {
	assert(pid >= 0);
}


/**
 * Test if the current process is still alive.
 * @return	True if it is alive, false else.
 * @throws SystemException	On process system error.
 */
bool Process::isAlive(void) {
	if(pid < 0)
		return false;
	int result = waitpid(pid, &rcode, WNOHANG);
	if(result == 0)
		return true;
	else if(result > 0) {
		pid = -1;
		rcode = WEXITSTATUS(rcode);
		return false; 
	}
	else
		throw SystemException(errno, "process information");
}


/**
 * If the process is terminated, get the return code.
 * @return	Process termination return code.
 * @throws SystemException	On process system error.
 */
int Process::returnCode(void) {
	if(pid >= 0)
		wait();
	return rcode;
}


/**
 * Kill the given thread.
 * @throws SystemException	On process system error.
 */
void Process::kill(void) {
	assert(pid >= 0);
	if(::kill(pid, SIGKILL) < 0)
		throw SystemException(errno, "process kill");
}


/**
 * Wait the termination of the process.
 */
void Process::wait(void) {
	if(pid < 0)
		return;
	if(waitpid(pid, &rcode, 0) >= 0) {
		rcode = WEXITSTATUS(rcode);
		pid = -1;
		return;
	}
	else
		throw new SystemException(errno, "process wait");	
}

} } // elm::system
