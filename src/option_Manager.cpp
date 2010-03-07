/*
 *	$Id$
 *	Manager class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-10, IRIT UPS.
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
 * options. There are currently two ways to use these classes, the old approach
 * that will become quickly deprecated (please no more use it) and the new one.
 *
 * @par The Old Approach
 *
 * The main approach is to declare an option manager which options
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
 * 		cout << "add argument " << arg << io::endl;
 * 	}
 * } manager;
 * 
 * BoolOption ok(manager, 'c', "ok", "is ok ?");
 * StringOption arg(manager, 's', "string", "set string", "a simple string", "");
 * @endcode
 * 
 * @par The New Approach
 *
 * The goal of the new approach is to remove as much developer disturbance as possible.
 * The full option configuration is based on a class Config that records and install
 * configuration in a more natural way. The Config instances are build from inline
 * functions (@ref elm::option::add(), etc) passed to the option or manager constructor.
 *
 * The previous example will become:
 * @code
 * #include <elm/options.h>
 * using namespace elm::option;
 *
 * class MyManager: public Manager {
 * public:
 *	MyManager(void): Manager(
 * 		program("my_program"),
 * 		version(1, 2),
 * 		copyright( "GPL (c) 2007 IRIT - UPS"),
 * 		end())
 * 	{ };
 *
 *	virtual void process(string arg) {
 * 		cout << "add argument " << arg << io::endl;
 * 	}
 * } manager;
 *
 * BoolOption ok(manager, cmd('c'), cmd("ok"), description("is ok ?"), end());
 * StringOption arg(manager, cmd('s'), cmd("string"), description("set string"), arg_description("a simple string"), def(""), end());
 * @endcode
 *
 *  This approach add a lot of flexibility because (1) all arguments do not need to be passed
 *  to the constructor (only the used ones) and (2) as many commands ('-' short name or '--' long name)
 *  as needed may be added to an option. As an example, look at the @ref BoolOption below:
 *  @code
 *  BoolOption verbose(manager, cmd('c'), cmd("verbose"), cmd('V'), end());
 *  @endcode
 *
 *  The only requirement is that the configuration list passed to the manager or to an option
 *  is terminated by and end() call.
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
 * Build a manager with the new method.
 * @param config	First configuration item.
 * @param ...		end() ended configuration item list.
 */
Manager::Manager(int tag, ...) {
	VARARG_BEGIN(args, tag)
		while(tag != end) {
			configure(tag, args);
			tag = args.next<int>();
		}
	VARARG_END
}


/**
 * Called for each configuration tag.
 * May be overload to customize Manager configuration.
 * @param tag	Current tag.
 * @param args	Argument list.
 */
void Manager::configure(int tag, VarArg& args) {
	switch(tag) {
	case option::program:
		program = args.next<const char *>();
		break;
	case option::version: {
			Version *v = args.next<Version *>();
			ASSERT(v);
			version = *v;
			delete v;
		}
		break;
	case option::author:
		author = args.next<const char *>();
		break;
	case option::copyright:
		copyright = args.next<const char *>();
		break;
	case option::description:
		description = args.next<const char *>();
		break;
	case option::free_arg:
		free_argument_description = args.next<const char *>();
		break;
	default:
		ASSERTP(false, "unknown configuration tag: " << tag);
	}
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
	Manager::argv_t argv,
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
 * @param option				Option to add.
 * @throw OptionException		If the short name or the long name is already used.
 */
void Manager::addOption(Option *option) throw(OptionException) {
	ASSERTP(option, "null option");
	options.add(option);
}


/**
 * Remove the option from the manager.
 * @param option	Option to remove.
 */
void Manager::removeOption(Option *option) {
	options.remove(option);
}


/**
 * Add a short command.
 * @param cmd		Short command character.
 * @param option	Option to add.
 */
void Manager::addShort(char cmd, Option *option) throw(OptionException) {
	string str = _ << '-' << cmd;
	ASSERTP(!cmds.contains(str), _ << "command '" << cmd << "' already used");
	cmds.put(str, option);
	shorts.put(cmd, option);
}


/**
 * Add a long command (prefixed with '--')
 * @param cmd		Long command string.
 * @param option	Option to add.
 */
void Manager::addLong(cstring cmd, Option *option) throw(OptionException) {
	string str = _ << "--" << cmd;
	ASSERTP(!cmds.contains(str), _ << "long command \"" << str << "\" already used");
	cmds.put(str, option);
}


/**
 * Add a generic command (no prefix required).
 * @param cmd		Command to add.
 * @param option	Option to add.
 */
void Manager::addCommand(string cmd, Option *option) throw(OptionException) {
	ASSERTP(!cmds.contains(cmd), "command \"" << cmd << "\" already used");
	cmds.put(cmd, option);
}


/**
 * Parse the given options.
 * @param argc				Argument count.
 * @param argv				Argument vector.
 * @throw OptionException	Thrown if the syntax contains an error.
 */
void Manager::parse(int argc, Manager::argv_t argv) throw(OptionException) {
	ASSERTP(argv, "null argv");
	ASSERTP(argc > 0, "negative argc");
	for(int i = 1; i < argc; i++) {
		string arg = argv[i];
		const char *earg = 0;

		// look for a command
		Option *option = cmds.get(arg, 0);
		if(!option) {
			int p = arg.indexOf('=');
			if(p >= 0) {
				option = cmds.get(arg.substring(0, p), 0);
				earg = argv[i] + p + 1;
			}
		}
		if(option)
			processOption(option, i, argc, argv, earg);

		// Free argument
		else if(arg.length() > 0 && arg[0] != '-')
			process(arg);
		
		// aggregated short name command
		else if(arg.length() > 1 && arg[1] != '-') {
			for(int j = 1; j < arg.length(); j++) {
				Option *option = shorts.get(arg[j], 0);
				if(!option)
					throw OptionException(_ << "option '" << arg[j] << "' in " << arg << " unknown !");
				processOption(option, i, argc, argv, 0);
			}
		}
		
		// none found: error
		else
			throw OptionException(elm::_ << "option \"" << arg << "\" is unknown.");
	}
}


/**
 * Display the help text to standard error.
 */
void Manager::displayHelp(void) {

	// Display header
	cerr << program;
	if(version)
		 cerr << " V" << version;
	if(author)
		cerr << " by " << author;
	cerr << '\n';
	if(copyright)
		cerr << copyright << '\n';
	
	// Display syntax
	cerr << '\n'
		 << "USAGE: " << program;
	if(options)
		cerr<< " [OPTIONS]";
	if(free_argument_description)
		cerr << ' ' << free_argument_description;
	cerr << '\n';
	if(description)
		cerr << description << '\n';
	cerr << "OPTIONS may be:\n";
	
	// Display option description
	for(genstruct::Vector<Option *>::Iterator option(options); option; option++) {

		// display commands
		bool fst = true;
		for(genstruct::SortedBinMap<string, Option *>::PairIterator pair(cmds); pair; pair++)
			if((*pair).snd == option) {
				if(fst)
					fst = false;
				else
					cerr << ", ";
				cerr << (*pair).fst;
			}

		// display argument
		switch(option->usage()) {
		case arg_none:
			break;
		case arg_optional:
			cerr << " [" << option->argDescription() << ']';
			break;
		case arg_required:
			cerr << ' ' << option->argDescription();
			break;
		}

		// display description
		cerr << "\n\t" << option->description() << io::endl;
	}
}

} } // elm::option

