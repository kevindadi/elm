/*
 * $Id$
 * Copyright (c) 2005, IRIT-UPS.
 *
 * elm/system/StopWatch.h -- StopWatch class interface.
 */
#ifndef ELM_SYSTEM_STOP_WATCH_H
#define ELM_SYSTEM_STOP_WATCH_H

#include <elm/types.h>

namespace elm { namespace system {

// Time type
typedef t::uint64 time_t;

// StopWatch class
class StopWatch {
	time_t start_time, stop_time;
#if defined(__WIN32) || defined(__WIN64)
	time_t delay_time;
#endif
public:
#if defined(__LINUX)
	void start(void);
	void stop(void);
#elif defined(__WIN32) || defined(__WIN64)
	void start(PROCESS_INFORMATION *pi);
	void stop(PROCESS_INFORMATION *pi);
#endif
	inline time_t delay(void) const;
	inline time_t startTime(void) const;
	inline time_t stopTime(void) const;
};

// Inlines
inline time_t StopWatch::delay(void) const {
#if defined(__LINUX)
	return stop_time - start_time;
#elif defined(__WIN32) || defined(__WIN64)
	return delay_time;
#endif
}

inline time_t StopWatch::startTime(void) const {
	return start_time;
}

inline time_t StopWatch::stopTime(void) const {
	return stop_time;
}

} } // elm::system

#endif // ELM_SYSTEM_STOP_WATCH_H
