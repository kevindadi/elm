/*
 * $Id$
 * Copyright (c) 2005, IRIT UPS.
 *
 * elm/option/ActionOption.h -- ActionOption class interface.
 */
#ifndef ELM_OPTION_ACTION_OPTION_H
#define ELM_OPTION_ACTION_OPTION_H

#include <elm/option/StandardOption.h>

namespace elm { namespace option {

// ActionOption class
class ActionOption: public StandardOption {
public:
	ActionOption(Manager& manager, char short_name, CString description);
	ActionOption(Manager& manager, CString long_name, CString description);
	ActionOption(Manager& manager, char short_name, CString long_name,
		CString description);
	virtual void perform(void) = 0;

	// Option overload
	virtual usage_t usage(void);
	virtual CString argDescription(void);
	virtual void process(String arg);
};

} } // elm::option

#endif // ELM_OPTION_ACTION_OPTION_H
