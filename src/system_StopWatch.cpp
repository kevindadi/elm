/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * system_StopWatch.cpp -- StopWatch class implementation.
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
