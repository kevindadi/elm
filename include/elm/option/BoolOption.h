/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/BoolOption.h -- BoolOption class interface.
 */
#ifndef ELM_OPTION_BOOL_OPTION_H
#define ELM_OPTION_BOOL_OPTION_H

#include <elm/option/StandardOption.h>

namespace elm { namespace option {

// BoolOption class
class BoolOption: public StandardOption {
	bool val;
public:
	BoolOption(Manager& manager, char short_name, CString description,
		bool value = false);
	BoolOption(Manager& manager, CString long_name, CString description,
		bool value = false);
	BoolOption(Manager& manager, char short_name, CString long_name,
		CString description, bool value = false);
	inline bool value(void) const { return val; };
	inline void set(bool value) { val = value; };

	// Option overload
	virtual usage_t usage(void);
	virtual CString argDescription(void);
	virtual void process(String arg);
	
	// Operators
	inline operator bool(void) const { return val; };
};

} } // elm::option

#endif // ELM_OPTION_BOOL_OPTION_H
