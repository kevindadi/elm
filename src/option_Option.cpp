/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/Option.cpp -- Option class implementation.
 */

#include <elm/option/Option.h>

namespace elm { namespace option {

/**
 * @class Option
 * Base class of classes used for representing options with the OptionManager class.
 */


/**
 * Display the name of the option to the given output stream.
 * @param out	Stream to output to.
 */
void Option::output(io::Output& out) {
	char sname = shortName();
	CString lname = longName();
	if(sname)
		out << '-' << sname;
	if(sname && lname)
		out << '|';
	if(lname)
		out << "--" << lname;
}

	
/**
 * @fn char Option::shortName(void);
 * Get the single-character short name of the option.
 * @return	Single character or '\0' if there is no short name.
 */

	
/**
 * @fn CString Option::longName(void);
 * Get the multi-character long name of the option.
 * @return	Multi-character or an empty string if there is no long name.
 */

	
/**
 * @fn CString Option::description(void);
 * Get the description of the option.
 * @return	Option description.
 */


/**
 * @fn usage_t Option::usage(void);
 * Get the argument usage type of this function.
 * @return	Argument usage type.
 */
 
 
/**
 * @fn CString Option::argDescription(void);
 * If the option requires an argument, get the description of the argument.
 * @return Argument description.
 */
 
 
/**
 * @fn void Option::process(String arg);
 * This method is called by the option manager when the option is encountered.
 * @param arg	If the option requires an argument, the value of the argument.
 */

} }	// elm::option
