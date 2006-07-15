/*
 * $Id$
 * Copyright (c) 2004, IRIT-UPS.
 *
 * elm/option/Option.h -- Option class interface.
 */
#ifndef ELM_OPTION_OPTION_H
#define ELM_OPTION_OPTION_H

#include <elm/string.h>
#include <elm/io.h>

namespace elm { namespace option {


// Argument usage
typedef enum usage_t {
	arg_none,
	arg_optional,
	arg_required
} usage_t;


// Option class
class Option {
public:
	void output(io::Output& out);
	virtual char shortName(void) = 0;
	virtual CString longName(void) = 0;
	virtual CString description(void) = 0;
	virtual usage_t usage(void) = 0;
	virtual CString argDescription(void) = 0;
	virtual void process(String arg) = 0;
};

// Inlines
inline io::Output& operator<<(io::Output& out, Option& opt) { opt.output(out); return out; };

} } // elm::option

#endif // ELM_OPTION_OPTION_H
