/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/StandardOption.h -- StandardOption class interface.
 */
#ifndef ELM_OPTION_STANDARD_OPTION_H
#define ELM_OPTION_STANDARD_OPTION_H

#include <elm/option/Manager.h>
#include <elm/option/Option.h>

namespace elm { namespace option {

// StandardOption class
class StandardOption: public Option {
	char sname;
	CString lname;
	CString desc;
public:
	
	// Constructors
	StandardOption(Manager& manager, char short_name, CString description);
	StandardOption(Manager& manager, CString long_name, CString description);
	StandardOption(Manager& manager, char short_name, CString long_name, CString description);

	// CommandOption overload
	virtual char shortName(void);
	virtual CString longName(void);
	virtual CString description(void);
};

} } // elm::option

#endif // ELM_OPTION_STANDARD_OPTION_H
