/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/StringOption.h -- StringOption class interface.
 */

#include <elm/option/StringOption.h>

namespace elm { namespace option {

/**
 * @class StringOption
 * This class is used for getting a command line option with a string argument.
 */

/**
 * Build a string option with a short name.
 * @param manager			Parent option manager.
 * @param short_name		Single-letter name.
 * @param description		Option description.
 * @param arg_description	Argument description.
 * @param value				Option initial value.
 */
StringOption::StringOption(Manager& manager, char short_name, CString description,
CString arg_description, String value)
: StandardOption(manager, short_name, description), val(value),
arg_desc(arg_description) {
}


/**
 * Build a string option with a long name.
 * @param manager			Parent option manager.
 * @param long_name			Multiple-letter name.
 * @param description		Option description.
 * @param arg_description	Argument description.
 * @param value				Option initial value.
 */
StringOption::StringOption(Manager& manager, CString long_name,
CString description, CString arg_description, String value)
: StandardOption(manager, long_name, description), val(value),
arg_desc(arg_description) {
}


/**
 * Build a string option with a short name and a long name.
 * @param manager			Parent option manager.
 * @param short_name		Single-letter name.
 * @param long_name			Multiple-letter name.
 * @param description		Option description.
 * @param arg_description	Argument description.
 * @param value				Option initial value.
 */
StringOption::StringOption(Manager& manager, char short_name, CString long_name,
CString description, CString arg_description, String value)
: StandardOption(manager, short_name, long_name, description), val(value),
arg_desc(arg_description) {
}


/**
 * @fn String StringOption::value(void) const;
 * Get the current value of the option.
 * @return	Option value.
 */


/**
 * @fn void StringOption::set(String value)
 * Set the value of the option.
 * @param value	New option value.
 */


// Option overload
usage_t StringOption::usage(void) {
	return arg_required;
}


// Option overload
CString StringOption::argDescription(void) {
	return arg_desc;
}


// Option overload
void StringOption::process(String arg) {
	val = arg;
}


/**
 * @fn StringOption::operator bool(void) const;
 * Bool conversion. Useful for testing if the option is set.
 */


/**
 * @fn StringOption::operator String(void) const;
 * String conversion for getting the option value.
 */

} } // elm::option
