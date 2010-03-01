/*
 *	$Id$
 *	SwitchOption class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-09, IRIT UPS.
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

#include <elm/option/SwitchOption.h>

namespace elm { namespace option {

/**
 * @class SwitchOption
 * An option to handle simple switch option (boolean).
 */


/**
 * Constructor with a short command "-x".
 * @param man			Owner manager.
 * @param cmd			Single character command.
 * @param description	Option description.
 */
SwitchOption::SwitchOption(Manager& man, char cmd, cstring description)
: val(false), desc(description) {
	init(man, SHORT, cmd, END);
}


/**
 * Constructor with a long command "--xxx".
 * @param man			Owner manager.
 * @param cmd			Multi-character command.
 * @param description	Option description.
 */
SwitchOption::SwitchOption(Manager& man, cstring cmd, cstring description)
: val(false), desc(description) {
	init(man, LONG, &cmd, END);
}


/**
 * Completely free constructor. Supported tags includes
 * @ref CMD, @ref SHORT, @ref LONG, @ref DESCRIPTION and @ref DEFAULT (bool).
 */
SwitchOption::SwitchOption(Manager& man, int tag ...)
: val(false) {
	VARARG_BEGIN(args, tag)
		init(man, tag, args);
	VARARG_END
}


/**
 */
cstring SwitchOption::description(void) {
	return desc;
}


/**
 */
usage_t SwitchOption::usage(void) {
	return option::arg_none;
}


/**
 */
cstring SwitchOption::argDescription(void) {
	return "";
}


/**
 */
void SwitchOption::process(string arg) {
	val = true;
}


/**
 */
void SwitchOption::configure(Manager& manager, int tag, VarArg& args) {
	switch(tag) {
	case DESCRIPTION:
		desc = args.next<const char *>();
		break;
	case DEFAULT:
		val = args.next<bool>();
		break;
	default:
		Option::configure(manager, tag, args);
		break;
	}
}

} } // otawa::option

