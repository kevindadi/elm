/*
 *	Time class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2020, IRIT UPS.
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

#include <elm/util/Time.h>

namespace elm {

/**
 * @class Time
 * Represents a time, a duration, a delay, etc. This class supports also
 * negative time for time subtraction.
 *
 * This class comes with usual comparison and computation operators.
 * In addition, it provides several function to access the time with different
 * units: microsecond, milliseconds, seconds, etc.
 *
 * @ingroup util
 */

/**
 * @fn inline Time::Time();
 * Initialize a time to 0.
 */

/**
 * @fn Time::Time(t::int64 t);
 * Initialize a time with the given value.
 */

/**
 * @fn Time::Time(const Time& t);
 * Copy a time.
 */

/**
 * @fn t::int64 Time::time() const;
 * Get the time raw value, currently in milliseconds.
 * @return	Time in milliseconds.
 */

/**
 * @fn t::int64 Time::micros() const;
 * Get the time in microseconds.
 * @return	Time in microseconds.
 */

/**
 * @fn t::int64 Time::millis() const;
 * Get the time in milliseconds.
 * @return	Time in milliseconds.
 */
/**
 * @fn t::int64 Time::seconds() const;
 * Get the time in seconds.
 * @return	Time in seconds.
 */
/**
 * @fn t::int64 Time::mins() const;
 * Get the time in minutes.
 * @return	Time in minutes.
 */
/**
 * @fn t::int64 Time::hours() const;
 * Get the time in hours.
 * @return	Time in hours.
 */
/**
 * @fn t::int64 Time::days() const;
 * Get the time in days.
 * @return	Time in days.
 */
/**
 * @fn t::int64 Time::years() const;
 * Get the time in years.
 * @return	Time in years.
 */

/**
 * Display a time.
 * @param out	Output stream to use.
 * @param t		Time to display.
 * @ingroup util
 */
io::Output& operator<<(io::Output& out, const Time& t) {
	static struct {
		t::int64 d;
		cstring n;
	} delays[] = {
		{ Time::ONE_Y, "y" },
		{ Time::ONE_D, "d" },
		{ Time::ONE_H, "h" },
		{ Time::ONE_M, "m" },
		{ Time::ONE_S, "" }
	};
	auto x = t.time();
	bool com = false;
	bool above_s = false;
	for(int i = 0; delays[i].d != Time::ONE_S; i++)
		if(x > delays[i].d) {
			if(com) out << ", ";
			out << (x / delays[i].d) << ' ' << delays[i].n;
			com = true;
			x = x % delays[i].d;
			above_s = true;
		}
	if(x != 0 || !above_s) {
		if(com) out << ", ";
		if(x > Time::ONE_S)
			out << (double(x) / Time::ONE_S) << " s";
		else if(x > Time::ONE_MS)
			out << (double(x) / Time::ONE_MS) << " ms";
		else
			out << x << " us";
	}
	return out;
}

};	// elm

