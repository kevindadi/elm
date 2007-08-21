/*
 *	$Id$
 *	StandardOption class interface
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
