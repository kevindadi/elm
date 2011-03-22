/*
 *	$Id$
 *	StopWatch class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
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

#if defined(__unix)
#include <sys/time.h>
#include <sys/resource.h>
#elif defined(__WIN32) || defined(__WIN64)
#include <time.h>
#include <windows.h>
#endif
#include <unistd.h>
#include <elm/system/StopWatch.h>
#include <elm/io.h>
namespace elm { namespace system {

/**
 * @class StopWatch
 * This class implements a stopwatch for measuring working time of program.
 * Create a stopwatch, call start() just before the code to measure and stop()
 * jus after it and delay() will return the time execute in process time (if
 * the OS allows this).
 * @ingroup system_inter
 */

//used on windows to convert FILETIME to uint64
#if defined(__WIN32) || defined(__WIN64)
time_t to_int64(FILETIME ft) {
	return static_cast<time_t>(ft.dwHighDateTime) << 32 | ft.dwLowDateTime;
}
#endif

/**
 * Must be called at the start of the time to measure.
 */
#if defined(__unix)
void StopWatch::start(void) {
	struct rusage buf;
	getrusage(RUSAGE_SELF, &buf);
	start_time = (time_t)(buf.ru_utime.tv_sec*1000000 + buf.ru_utime.tv_usec);
}
#elif defined(__WIN32) || defined(__WIN64)
void StopWatch::start(PROCESS_INFORMATION *pi){

}
#else
void StopWatch::start(){
	throw "Unsupported System";
}
#endif

/**
 * Must be called at the end of the time to measure.
 */
#if defined(__unix)
void StopWatch::stop(void) {
	struct rusage buf;
	getrusage(RUSAGE_SELF, &buf);
	stop_time = (time_t)(buf.ru_utime.tv_sec*1000000 + buf.ru_utime.tv_usec);
}
#elif defined(__WIN32) || defined(__WIN64)
void StopWatch::stop(PROCESS_INFORMATION *pi){
	LPFILETIME lpCreationTime;
	LPFILETIME lpExitTime;
	LPFILETIME lpKernelTime;
	LPFILETIME lpUserTime;
	GetProcessTimes(pi,lpCreationTime,lpExitTime,lpKernelTime,lpUserTime);
	//
	// start_time et stop_time a revoir ?
	//
	start_time=to_int64(*lpCreationTime);
	stop_time=to_int64(*lpExitTime);
	delay_time=to_int64(*lpKernelTime);
}
#else
void StopWatch::stop(){
	throw "Unsupported System";
}
#endif


/**
 * @fn time_t StopWatch::delay(void) const;
 * Get the delay in micro-seconds between the start() call and the stop() call.
 * @return	Delay in micro-seconds.
 */

/**
 * @fn time_t StopWatch::startTime(void) const;
 * Get the time when the start() has been called.
 * @return	Start time in micro-seconds.
 */

/**
 * @fn time_t StopWatchstopTime(void) const;
 * Get the time when the stop() has been called.
 * @return	Stop time in micro-seconds.
 */

} } // elm::system
