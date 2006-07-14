/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS
 *
 * src/option_EnumOption.cpp -- EnumOption class implementation.
 */

#include <elm/option/EnumOption.h>

namespace elm { namespace option {

/**
 * @class EnumOption
 * This class handle enumerations in command line arguments. At construction
 * time, it receive an associative array of @ref EnumOption::value_t that 
 * matches T values with their name. The first item of this array is used
 * to get the default value of the option and the argument description for
 * help display.
 * @param T	Type of the enumerated value.
 */


/*
 * @fn EnumOption::EnumOption(Manager& manager, char short_name, CString description, value_t values[]);
 * Build an enum option with a short name.
 * @param manager		Parent option manager.
 * @param short_name	Single-letter name.
 * @param description	Option description.
 * @param values		List of enumerated values.
 */


/**
 * @fn EnumOption::EnumOption(Manager& manager, CString long_name, CString description, value_t values[]);
 * Build a boolean option with a long name.
 * @param manager		Parent option manager.
 * @param long_name		Multiple-letter name.
 * @param description	Option description.
 * @param values		List of enumerated values.
 */


/**
 * @fn EnumOption::EnumOption(Manager& manager, char short_name, CString long_name, CString description, value_t values[]);
 * Build a boolean option with a short name and a long name.
 * @param manager		Parent option manager.
 * @param short_name	Single-letter name.
 * @param long_name		Multiple-letter name.
 * @param description	Option description.
 * @param values		List of enumerated values.
 */



/**
 * @fn const T& EnumOption::value(void) const;
 * Get the current value of the option.
 * @return	Current value.
 */


/**
 * @fn void EnumOption::set(const T& value);
 * Change the current value of the option.
 * @param value	New value of the option.
 */


/**
 * @fn EnumOption::operator T(void) const;
 * Shortcut to @ref get().
 */


/**
 * @fn EnumOption& EnumOption::operator=(const T& value);
 * Shortcut to @ref set().
 */
	
} } // elm::option

