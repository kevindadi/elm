/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/StringOption.h -- StringOption class interface.
 */
#ifndef ELM_OPTION_STRING_OPTION_H
#define ELM_OPTION_STRING_OPTION_H

#include <elm/option/StandardOption.h>

namespace elm { namespace option {

// StringOption class
class StringOption: public StandardOption {
	String val;
	CString arg_desc;
public:
	StringOption(Manager& manager, char short_name, CString description,
		CString arg_description, String value = "");
	StringOption(Manager& manager, CString long_name, CString description,
		CString arg_description, String value = "");
	StringOption(Manager& manager, char short_name, CString long_name,
		CString description, CString arg_description, String value = "");
	inline String value(void) const { return val; };
	inline void set(String value) { val = value; };

	// Option overload
	virtual usage_t usage(void);
	virtual CString argDescription(void);
	virtual void process(String arg);
	
	// Operators
	inline operator bool(void) const { return val; };
	inline operator String(void) const { return val; };
};

} } // elm::option

#endif	// ELM_OPTION_STRING_OPTION_H
