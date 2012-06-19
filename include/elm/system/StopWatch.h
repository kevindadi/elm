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
	void start(void);
	void stop(void);
	inline time_t delay(void) const;
	inline time_t startTime(void) const;
	inline time_t stopTime(void) const;
};

// Inlines
inline time_t StopWatch::delay(void) const {
	return stop_time - start_time;
}

inline time_t StopWatch::startTime(void) const {
	return start_time;
}

inline time_t StopWatch::stopTime(void) const {
	return stop_time;
}

} } // elm::system

#endif // ELM_SYSTEM_STOP_WATCH_H
