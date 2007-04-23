/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/option/option_Manager.cpp -- Manager class implementation.
 */

#include <elm/assert.h>
#include <elm/io.h>
#include <elm/option/Manager.h>

namespace elm { namespace option {


// UnknownException
class UnknownException {
};


/**
 * @class OptionException
 * This class may be raised by options of by the option @ref Manager to
 * indicate that there is an error in command line arguments.
 */


/**
 * Build an empty with a string message possibly containing printf-like
 * escape sequences for arguments.
 * @param message	Message formats.
 * @param ...		Arguments.
 */
OptionException::OptionException(elm::CString format, ...) {
	VARARG_BEGIN(args, format);
	buildMessage(format, args);
	VARARG_END
}


/**
 * Build an empty with a string message possibly containing printf-like
 * escape sequences for arguments.
 * @param message	Message formats.
 * @param ...		Arguments.
 */

OptionException::OptionException(elm::CString format, VarArg& args)
: MessageException(format, args) {
}


/**
 * @class Manager
 * This class is used for managing the options of a command.
 * It is usually 
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
 */
void Manager::processOption(Option *option, int& i, int argc, char **argv) {

	// No option
	if(!option)
		throw UnknownException();

	// Find the argument
	String arg;
	switch(option->usage()) {
	case arg_none:
		break;
	case arg_optional:
		if(i + 1 < argc && argv[i + 1][0] != '-')
			arg = argv[++i];
		break;
	case arg_required:
		if(i + 1 < argc && argv[i + 1][0] != '-')
			arg = argv[++i];
		else {
			throw OptionException("option \"%s\" requires an argument.",
				argv[i]);
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
void Manager::parse(int argc, char **argv) {
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
					processOption(findShortName(opts[j]), i, argc, argv);
				}
				catch(UnknownException _) {
					throw OptionException("option \"-%c\" is unknown.", opts[j]);
				}
			}
		}
		
		/* Multiple-letter argument */
		else {
			try {
				processOption(findLongName(&argv[i][2]), i, argc, argv);
			}
			catch(UnknownException _) {
				throw OptionException("option \"%s\" is unknown.", argv[i]);
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

