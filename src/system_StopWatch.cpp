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

#include <sys/time.h>
#include <sys/resource.h>
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

/**
 * Must be called at the start of the time to measure.
 */
void StopWatch::start(void) {
	struct rusage buf;
	getrusage(RUSAGE_SELF, &buf);
	start_time = (time_t)(buf.ru_utime.tv_sec*1000000 + buf.ru_utime.tv_usec);
}

/**
 * Must be called at the end of the time to measure.
 */
void StopWatch::stop(void) {
	struct rusage buf;
	getrusage(RUSAGE_SELF, &buf);
	stop_time = (time_t)(buf.ru_utime.tv_sec*1000000 + buf.ru_utime.tv_usec);
}

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
