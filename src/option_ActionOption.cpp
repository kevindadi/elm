/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * elm/option/option_ActionOption.cpp -- ActionOption class implementation.
 */

#include <assert.h>
#include <elm/option/ActionOption.h>

namespace elm { namespace option {


/**
 * @class ActionOption
 * This kind of option is used for performing an action when the option is
 * encountered in the command line option. It must be first derived to
 * assign a body to the @ref perform() method before to be used.
 */

/**
 * Build an action option with a short name.
 * @param manager		Parent option manager.
 * @param short_name	Single-letter name.
 * @param description	Option description.
 */
ActionOption::ActionOption(Manager& manager, char short_name,
CString description): StandardOption(manager, short_name, description) {
}


/**
 * Build an action option with a long name.
 * @param manager		Parent option manager.
 * @param long_name		Multiple-letter name.
 * @param description	Option description.
 */
ActionOption::ActionOption(Manager& manager, CString long_name,
CString description): StandardOption(manager, long_name, description) {
}


/**
 * Build an action option with a short name and a long name.
 * @param manager		Parent option manager.
 * @param short_name	Single-letter name.
 * @param long_name		Multiple-letter name.
 * @param description	Option description.
 */
ActionOption::ActionOption(Manager& manager, char short_name, CString long_name,
CString description)
: StandardOption(manager, short_name, long_name, description) {
}


// Option overload
usage_t ActionOption::usage(void) {
	return arg_none;
}


// Option overload
CString ActionOption::argDescription(void) {
	return "";
}


// Option overload
void ActionOption::process(String arg) {
	perform();
}


/**
 * @fn void ActionOption::perform(void);
 * Called when the matching option is found. This pure virtual method
 * must be overloaded in order to assign an action with the option.
 */
	
} } // elm::option
