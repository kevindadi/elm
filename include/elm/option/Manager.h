/*
 *	$Id$
 *	Manager class interface
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
#ifndef ELM_OPTION_MANAGER_H
#define ELM_OPTION_MANAGER_H

#include <elm/genstruct/Vector.h>
#include <elm/option/Option.h>
#include <elm/util/Version.h>
#include <elm/util/MessageException.h>

namespace elm { namespace option {

// OptionException exception
class OptionException: public MessageException {
public:
	OptionException(const String& message);
};


// Manager
class Manager {
public:
	typedef const char * const *argv_t;
	virtual ~Manager(void) { }
	void addOption(Option *option) throw(OptionException);
	void removeOption(Option *option);
	void parse(int argc, argv_t argv) throw(OptionException);
	void displayHelp(void);

protected:
	CString program;
	Version version;
	CString author;
	CString copyright;
	CString description;
	CString free_argument_description;
	virtual void process(String arg);

private:
	genstruct::Vector<Option *> options;
	Option *findShortName(char name);
	Option *findLongName(CString name);
	void processOption(Option *option, int& i, int argc, argv_t argv, const char *earg);
};

} } //elm::option

#endif // ELM_OPTION_MANAGER_H
