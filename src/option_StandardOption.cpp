/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/option_StandardOption.cpp -- StandardOption class implementation.
 */

#include <elm/assert.h>
#include <elm/option/StandardOption.h>

namespace elm { namespace option {


/**
 * @class StandardOption
 * This abstract class factorize the handling of options (short and long) and option description.
 */


/**
 * Build an option with a short name.
 * @param manager		Parent option manager.
 * @param short_name	Single letter name.
 * @param description	Option description.
 */
StandardOption::StandardOption(Manager& manager, char short_name, CString description)
: sname(short_name), lname(""), desc(description) {
	ASSERTP(sname && sname != '-', "bad short option name");
	manager.addOption(this);
}


/**
 * Build an option with a long name.
 * @param manager		Parent option manager.
 * @param long_name		Multiple letter name.
 * @param description	Option description.
 */
StandardOption::StandardOption(Manager& manager, CString long_name, CString description)
: sname(0), lname(long_name), desc(description) {
	ASSERTP(long_name && long_name[0] != '-', "bad long option name");
	manager.addOption(this);
}


/**
 * Build an option with a short name and a long name.
 * @param manager		Parent option manager.
 * @param short_name	Single letter name.
 * @param long_name		Multiple letter name.
 * @param description	Option description.
 */
StandardOption::StandardOption(Manager& manager, char short_name, CString long_name, CString description)
: sname(short_name), lname(long_name), desc(description) {
	ASSERTP(sname && sname != '-', "bad short option name");
	ASSERTP(long_name && long_name[0] != '-', "bad long option name");
	manager.addOption(this);
}


// Option overload
char StandardOption::shortName(void) {
	return sname;
}


// Option overload
CString StandardOption::longName(void) {
	return lname;
}


// Option overload
CString StandardOption::description(void) {
	return desc;
}

} } // elm::option

