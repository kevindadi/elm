/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/Manager.h -- Manager class interface.
 */
#ifndef ELM_OPTION_MANAGER_H
#define ELM_OPTION_MANAGER_H

#include <elm/genstruct/Vector.h>
#include <elm/option/Option.h>

namespace elm { namespace option {

// OptionException exception
class OptionException {
};


// Manager
class Manager {
	genstruct::Vector<Option *> options;
	Option *findShortName(char name);
	Option *findLongName(CString name);
	void processOption(Option *option, int& i, int argc, char **argv);
protected:
	CString program;
	CString version;
	CString author;
	CString copyright;
	CString description;
	CString free_argument_description;
	virtual void process(String arg);
public:
	void addOption(Option *option);
	void removeOption(Option *option);
	void parse(int argc, char **argv);
	void displayHelp(void);
};

} } //elm::option

#endif // ELM_OPTION_MANAGER_H
