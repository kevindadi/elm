/*
 * $Id$
 * Copyright (c) 2004-07, IRIT - UPS
 *
 * elm/option/option_BoolOption.cpp -- BoolOption class implementation.
 */

#include <elm/assert.h>
#include <elm/option/BoolOption.h>

namespace elm { namespace option {


/**
 * @class BoolOption
 * This class is used for getting boolean option usually marked by simple flag.
 */

/**
 * !!TODO!!
 * Very sad side effect not detected by compiler BoolOption(_, _, str, str) is viewed as first cast,
 * last string being converted to boolean.
 * Too bad for user. Perhaps change the order of constructors. Else either the default intialization
 * must be mandatory or onyl one complete form of option building muste exists.
 * Same problem arises with strings and there is no solution.
 */

/**
 * Build a boolean option with a short name.
 * @param manager		Parent option manager.
 * @param short_name	Single-letter name.
 * @param description	Option description.
 * @param value			Option initial value.
 */
BoolOption::BoolOption(Manager& manager, char short_name, CString description, bool value)
: StandardOption(manager, short_name, description), val(value) {
}


/**
 * Build a boolean option with a long name.
 * @param manager		Parent option manager.
 * @param long_name		Multiple-letter name.
 * @param description	Option description.
 * @param value			Option initial value.
 */
BoolOption::BoolOption(Manager& manager, CString long_name, CString description, bool value)
: StandardOption(manager, long_name, description), val(value) {
}


/**
 * Build a boolean option with a short name and a long name.
 * @param manager		Parent option manager.
 * @param short_name	Single-letter name.
 * @param long_name		Multiple-letter name.
 * @param description	Option description.
 * @param value			Option initial value.
 */
BoolOption::BoolOption(Manager& manager, char short_name, CString long_name,
CString description, bool value)
: StandardOption(manager, short_name, long_name, description), val(value) {
}


/**
 * @fn bool BoolOption::value(void) const;
 * Get the current value of the option.
 * @return	Option value.
 */


/**
 * @fn void BoolOption::set(bool value);
 * Set the value of the option.
 * @param value	New option value.
 */


// Option overload
usage_t BoolOption::usage(void) {
	return arg_none;
}


// Option overload
CString BoolOption::argDescription(void) {
	return "";
}


// Option overload
void BoolOption::process(String arg) {
	val = true;
}


/**
 * @fn BoolOption::operator bool(void) const;
 * Boolean conversion for getting option value.
 */


} } // elm::option
