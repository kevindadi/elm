/*
 *	$Id$
 *	StringOption class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-07, IRIT UPS.
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

#include <elm/option/StringOption.h>

namespace elm { namespace option {

/**
 * @class StringOption
 * This class is used for getting a command line option with a string argument.
 * @ingroup options
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
