/*
 *	$Id$
 *	Option class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-07, IRIT UPS.
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
#ifndef ELM_OPTION_OPTION_H
#define ELM_OPTION_OPTION_H

#include <elm/util/VarArg.h>
#include <elm/string.h>
#include <elm/io.h>

namespace elm { namespace option {

class Manager;

// Argument usage
typedef enum usage_t {
	arg_none,
	arg_optional,
	arg_required
} usage_t;


// Option class
class Option {
public:
	inline Option(void) { }
	virtual ~Option(void) { }
	void output(io::Output& out);
	virtual CString description(void) = 0;
	virtual usage_t usage(void) = 0;
	virtual CString argDescription(void) = 0;
	virtual void process(String arg) = 0;

	// deprecated
	virtual char shortName(void);
	virtual CString longName(void);

protected:
	virtual void configure(Manager& manager, int tag, VarArg& args);
	void init(Manager& manager, int tag, ...);
	void init(Manager& manager, int tag, VarArg& args);

private:
};

// Inlines
inline io::Output& operator<<(io::Output& out, Option& opt) { opt.output(out); return out; };

} } // elm::option

#endif // ELM_OPTION_OPTION_H
