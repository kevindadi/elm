/*
 *	$Id$
 *	Manager class implementation
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

#include <elm/assert.h>
#include <elm/io.h>
#include <elm/option/Manager.h>
#include <elm/string.h>

namespace elm { namespace option {


/**
 * @defgroup options Command Line Options
 * 
 * @code
 * #include <elm/options.h>
 * @endcode
 * 
 * ELM provides several class to manage efficiently and easily command line
 * options. The main approach is to declare an option manager which options
 * are linked to. These objects are usually declared static (global or actual
 * class static members) and the option processing is called from the
 * main() function of the program as in the example below.
 * 
 * @code
 * #include <elm/options.h>
 * using namespace elm::option;
 * 
 * class MyManager: public Manager {
 * public:
 *	MyManager(void) {
 * 		program = "my_program";
 * 		version = "1.2";
 * 		copyright = "GPL (c) 2007 IRIT - UPS";
 * 	};
 *	virtual void process(string arg) {
 * 		cout << "add argumenet " << arg << io::endl;
 * 	}
 * } manager;
 * 
 * BoolOption ok(manager, 'c', "ok", "is ok ?");
 * StringOption arg(manager, 's', "string", "set string", "a simple string", "");
 * @endcode
 * 
 * @par The manager
 * 
 * The manager is the main entry to handle options. It provides the list of
 * options but also information about the program. To provides this kind of data,
 * one has to create a class inheriting fropm @ref Manager and to initialize
 * some fields in the constructor.
 * @li program -- name of the program,
 * @li version -- version of the program (as a string),
 * @li author -- author(s) of the program,
 * @li copyright -- licence of the program,
 * @li description -- a short description of the program,
 * @li free_argument_description -- description of non-option string in the
 * arguments.
 * 
 * Then, non-options string may be handled by overloading the Manager::process()
 * method. Each time one of this argument is found, this method will be called
 * with the string as parameter. For example, in the command below, the
 * Manager::process() method will be called twice: once with "file.txt" as
 * argument and once with "mydir/" as argument.
 * @code
 * $ cp file.txt mydir/
 * @endcode
 * 
 * @par Option Usage
 * 
 * All options inherits from the @ref Option class. Each one provides a
 * constructor taking the actual manager as parameter. The following parameters
 * may include (take a look at each class documentation for more details):
 * @li a one letter option identifier (just prefixed with '-'),
 * @li a full string option identifier (prefixed by a double '-'),
 * @li the description of the option,
 * @li the description of the option argument (if there is one),
 * @li the default value of the option argument (if there is one).
 * 
 * There are many class that allows parsing and retrieving options values as
 * @ref BoolOption, @ref IntOption, @ref StringOption or @ref EnumOption.
 * The option value may be accessed as a usual variable as in the example below:
 * @code
 * if(ok)
 * 	cout << "string argument is " << arg << io::endl;
 * @endcode
 * 
 * The @ref ActionOption class is a bit more complex because it allows
 * associating an action with an option. To achieve this, the user has to
 * derive a class from @ref ActionOption and to overload the
 * ActionOption::perform() method to implement the specific behaviour.
 */

// UnknownException
class UnknownException {
};


/**
 * @class OptionException
 * This class may be raised by options of by the option @ref Manager to
 * indicate that there is an error in command line arguments.
 * @ingroup options
 */


/**
 * Build an empty with a string message possibly containing printf-like
 * escape sequences for arguments.
 * @param message	Message formats.
 * @param ...		Arguments.
 */

OptionException::OptionException(const String& message)
: MessageException(message) {
}


/**
 * @class Manager
 * This class is used for managing the options of a command.
 * @ingroup options
 */


/**
 * Find an option by its short name.
 * @param name	Short name.
 * @return		Found option or null.
 */
Option *Manager::findShortName(char name) {
	for(int i = 0; i < options.length(); i++)
		if(options[i]->shortName() == name)
			return options[i];
	return 0;
}


/**
 * Find an option by its long name.
 * @param name	Long name.
 * @return		Found option or null.
 */
Option *Manager::findLongName(CString name) {
	for(int i = 0; i < options.length(); i++)
		if(options[i]->longName() == name)
			return options[i];
	return 0;
}


/**
 * Process an option with or without argument need.
 * @param option	Option to process.
 * @param i			Current index.
 * @param argc		Top index.
 * @pâram argv		Argument vector.
 * @param earg		Argument following an equal !
 */
void Manager::processOption(
	Option *option,
	int& i,
	int argc,
	const char **argv,
	const char *earg
) {

	// No option
	if(!option)
		throw UnknownException();

	// Find the argument
	String arg;
	switch(option->usage()) {
	case arg_none:
		if(earg)
			throw OptionException(_ << "option \"" << argv[i]
				<< "\" requires no argument.");
		break;
	case arg_optional:
		if(earg)
			arg = earg;
		else if(i + 1 < argc && argv[i + 1][0] != '-')
			arg = argv[++i];
		break;
	case arg_required:
		if(earg)
			arg = earg;
		else if(i + 1 < argc && argv[i + 1][0] != '-')
			arg = argv[++i];
		else {
			throw OptionException(_ << "option \"" << argv[i]
				<< "\" requires an argument.");
		}
		break;	
	}
	
	// Process the option
	option->process(arg);
}


/**
 * Called each time a free argumend (not tied to an option) is found.
 * @param arg	Free argument value.
 */
void Manager::process(String arg) {
}


/**
 * Add an option to the manager.
 * @param option	Option to add.
 */
void Manager::addOption(Option *option) {
	ASSERTP(option, "null option");
	options.add(option);
}


/**	void displayHelp(void);
 * Remove the option from the manager.
 * @param option	Option to remove.
 */
void Manager::removeOption(Option *option) {
	options.remove(option);
}

class BadArgumentException {
};

/**
 * Parse the given options.
 * @param argc	Argument count.
 * @param argv	Argument vector.
 */
void Manager::parse(int argc, const char **argv) {
	ASSERTP(argv, "null argv");
	ASSERTP(argc > 0, "negative argc");
	for(int i = 1; i < argc; i++) {
	
		/* Free argument */
		if(argv[i][0] != '-') {
			process(argv[i]);
			continue;
		}
		
		/* Single-letter argument */
		else if(argv[i][1] != '-') {
			CString opts = argv[i];
			for(int j = 1; opts[j]; j++) {
				try {
					processOption(findShortName(opts[j]), i, argc, argv, 0);
				}
				catch(UnknownException _) {
					throw OptionException(elm::_ <<
						"option \"-" << opts[j] << "\" is unknown.");
				}
			}
		}
		
		/* Multiple-letter argument */
		else {
			try {
				cstring arg = argv[i];
				int eq = arg.indexOf('=');
				if(eq == -1)
					processOption(findLongName(&argv[i][2]), i, argc, argv, 0);
				else {
					string name = arg.substring(2, eq);
					processOption(findLongName(&name), i, argc, argv, &arg + eq + 1);
				}
			}
			catch(UnknownException _) {
				throw OptionException(elm::_ <<
					"option \"" << argv[i] << "\" is unknown.");
			}
		}
	}
}


/**
 * Display the help text to standard error.
 */
void Manager::displayHelp(void) {
	int i;

	/* Display header */
	cerr << program;
	if(version)
		 cerr << " V" << version;
	if(author)
		cerr << " by " << author;
	cerr << '\n';
	if(copyright)
		cerr << copyright << '\n';
	
	/* Display syntax */
	cerr << '\n'
		 << "USAGE: " << program;
	for(i = 0; i < options.length(); i++) {
		cerr << " [" << *options[i];
		switch(options[i]->usage()) {
		case arg_none:
			break;
		case arg_optional:
			cerr << " [" << options[i]->argDescription() << ']';
			break;
		case arg_required:
			cerr << ' ' << options[i]->argDescription();
			break;
		}
		cerr << ']';
	}
	if(free_argument_description)
		cerr << ' ' << free_argument_description;
	cerr << '\n';
	if(description)
		cerr << description << '\n';
	
	/* Display option description */
	if(options)
		for(i = 0; i < options.length(); i++) {
			cerr << *options[i];
			switch(options[i]->usage()) {
			case arg_none:
				break;
			case arg_optional:
				cerr << "=[" << options[i]->argDescription() << ']';
				break;
			case arg_required:
				cerr << '=' << options[i]->argDescription();
				break;
			}
			cerr << '\t' << options[i]->description() << '\n';
		}
}

} } // elm::option

