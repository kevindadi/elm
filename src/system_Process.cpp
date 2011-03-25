/*
 *	$Id$
 *	Process class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
 * 
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software 
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/assert.h>
#include <sys/types.h>
#if defined(__unix)
#include <sys/errno.h>
#include <sys/wait.h>
#elif defined(__MINGW__) || defined(__MINGW32__)
#include <errno.h>
#endif
#if defined(__WIN32) || defined(__WIN64)
#include <windows.h>
#endif
#include <signal.h>
#include <elm/system/Process.h>
#include <elm/system/SystemException.h>

#include <stdio.h>

namespace elm { namespace system {

/**
 * @class Process
 * An interface with the processes of the OS.
 * @ingroup system_inter
 */


/**
 * Build a new process.
 * @param _pid	Process identifier.
 */
#if defined(__unix)
Process::Process(int _pid): pid(_pid) {
	ASSERTP(pid >= 0, "negative PID");
}
#elif defined(__WIN32) || defined(__WIN64)
Process::Process(void* _pi){
	printf("init process %d\n",GetLastError());
	reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess=reinterpret_cast<PROCESS_INFORMATION&>(_pi).hProcess;
	reinterpret_cast<PROCESS_INFORMATION&>(pi).hThread=reinterpret_cast<PROCESS_INFORMATION&>(_pi).hThread;
	reinterpret_cast<PROCESS_INFORMATION&>(pi).dwProcessId=reinterpret_cast<PROCESS_INFORMATION&>(_pi).dwProcessId;
	reinterpret_cast<PROCESS_INFORMATION&>(pi).dwThreadId=reinterpret_cast<PROCESS_INFORMATION&>(_pi).dwThreadId;
	printf("saving process %d\n",GetLastError());
}
#else
#error "Unsupported platform"
#endif


/**
 * Test if the current process is still alive.
 * @return	True if it is alive, false else.
 * @throws SystemException	On process system error.
 */
bool Process::isAlive(void) {
#if defined(__unix)
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
#elif defined(__WIN32) || defined(__WIN64)
	if(GetExitCodeProcess( reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess, &rcode ) != 0){
		if(rcode != STILL_ACTIVE)
			return false;
		else
			return true;
	}
	else
		throw SystemException(errno, "process information");
#else
#error "Unsupported platform"
#endif

}


/**
 * If the process is terminated, get the return code.
 * @return	Process termination return code.
 * @throws SystemException	On process system error.
 */
int Process::returnCode(void) {
#if defined(__unix)
	if(pid >= 0)
		wait();
	return rcode;
#elif defined(__WIN32) || defined(__WIN64)
	if(GetExitCodeProcess( reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess, &rcode) != 0){
		wait();
		return rcode;
	}
	else
		throw SystemException(errno, "process get code");
#else
#error "Unsupported platform"
#endif
}


/**
 * Kill the given thread.
 * @throws SystemException	On process system error.
 */
void Process::kill(void) {
#if defined(__unix)
	ASSERT(pid >= 0);
	if(::kill(pid, SIGKILL) < 0)
		throw SystemException(errno, "process kill");
#elif defined(__WIN32) || defined(__WIN64)
	if(::TerminateProcess(reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess, 0) == 0)
		throw SystemException(errno, "process kill");
#else
#error "Unsupported System"
#endif
}


/**
 * Wait the termination of the process.
 */
void Process::wait(void) {
#if defined(__unix)
	if(pid < 0)
		return;
	if(waitpid(pid, &rcode, 0) >= 0) {
		rcode = WEXITSTATUS(rcode);
		pid = -1;
		return;
	}
	else
		throw new SystemException(errno, "process wait");	
#elif defined(__WIN32) || defined(__WIN64)
	if(GetExitCodeProcess(reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess, &rcode) != STILL_ACTIVE)
		return;
	if(WaitForSingleObject(reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess, INFINITE) != WAIT_FAILED ){
		GetExitCodeProcess(reinterpret_cast<PROCESS_INFORMATION&>(pi).hProcess, &rcode);
		return;
	}
	else
		throw new SystemException(errno, "process wait");
#else
#error "Unsupported System"
#endif
}

} } // elm::system
