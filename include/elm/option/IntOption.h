/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/option/IntOption.h -- IntOption class interface.
 */
#ifndef ELM_OPTION_INT_OPTION_H
#define ELM_OPTION_INT_OPTION_H

#include <elm/option/StandardOption.h>

namespace elm { namespace option {

// IntOption class
class IntOption: public StandardOption {
	CString arg_desc;
	int val;
public:
	IntOption(
		Manager& manager,
		char short_name,
		CString description,
		CString arg_description,
		int value = 0);
	IntOption(
		Manager& manager,
		CString long_name,
		CString description,
		CString arg_description,
		int value = 0);
	IntOption(
		Manager& manager,
		char short_name,
		CString long_name,
		CString description,
		CString arg_description,
		int value = 0);
		
	inline int value(void) const { return val; };
	inline void set(int value) { val = value; };

	// Option overload
	virtual usage_t usage(void);
	virtual CString argDescription(void);
	virtual void process(String arg);
	
	// Operators
	inline operator int(void) const { return val; };
	inline IntOption& operator=(int value) { val = value; };
};

} } // elm::option

#endif // ELM_OPTION_BOOL_OPTION_H
