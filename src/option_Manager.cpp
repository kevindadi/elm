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
#include <elm/data/Vector.h>
#include <elm/sys/System.h>

namespace elm { namespace option {


/**
 * @defgroup options Command Line Options
 * 
 * @code
 * #include <elm/options.h>
 * @endcode
 * 
 * ELM provides several classes to manage efficiently and easily command line
 * options. There are currently two ways to use these classes, the old approach
 * that will become quickly deprecated (please no more use it) and the new one.
 *
 * To perform the parsing of command line arguments, ELM provides two basic classes.
 * @ref elm::option::Manager represents the command as a base of documentation and as a list
 * of options items. The manager is initialized as in the following example:
 * @code
 * 	#include <elm/options.h>
 * 	...
 * 	option::Manager manager = Make("my command", Version(1, 0, 0))
 * 		.description("This is my command !")
 * 		.license("GPL V")
 * 		.author("me <me@here.there>");
 * @endcode
 *
 * According to your needs, as many configurations as needed can be passed
 * to the Make() object while maintaining type checking. Refer to
 * @ref elm::option::Manager::Make class documentation for the list of available
 * configurations.
 *
 * The options works in the same way:
 * @code
 * option::SwitchOption opt1 = Make(manager).cmd("-o").cmd("--com").help("option 1");
 * @endcode
 *
 * As many ".cmd()" method calls can be added and other configurations can be passed
 * using the same syntax. Refer to the documentations of the different option classes
 * to get details about the configuration items (@ref elm::option::Option::Make, ...).
 *
 * Using both configuration system for the manager and the option, a command is usually defined
 * as in the following example:
 * @code
 * class MyCommand: public option::Manager {
 * public:
 * 	MyCommand(void): option::Manager(Make("my-command", Version(1, 0, 0))
 * 		.description("This is my command !")
 * 		.license("GPL V")
 * 		.author("me <me@here.there>")),
 * 	opt(option::SwitchOption::Make(*this).cmd("-o").cmd("--com").help("option 1")),
 * 	val(option::ValueOption::Make(*this).cmd("-v").cmd("--val").help("my value")) { }
 * 	...
 * private:
 * 	option::SwitchOption opt;
 * 	option::ValueOption val;
 * };
 * @endcode
 *
 * At this point, the options may be used as normal values in the program as below:
 * @code
 * 	if(opt)
 * 		doSomething(val);
 * @endcode
 *
 * Free arguments, not processed by an option item, are usually handled by overriding
 * the method
 * @code
 * class MyCommand: public option::Manager {
 * public:
 * 	...
 * protected:
 * 	virtual void process(String arg) {
 * 		if(!my_arg)
 * 			my_arg = arg;
 * 		else
 * 			throw OptionException("only one argument supported !");
 *	}
 *	...
 * private:
 * 	string my_arg;
 * };
 * @endcode
 *
 * The example above supports only one argument.In this example, if the argument is not defined,
 * the argument @c arg is copied to the field @c my_arg. If it is already defined,
 * an @ref OptionException is raised. In this case, the passed message will be displayed
 * to the user and the syntax of the command will also automatically be displayed then.
 *
 * To use such a command, the @c main parameters, @c argc and @c argv, must be passed
 * to the @c parse() method:
 * @code
 * int main(int argc, char *argv[]) {
 * 	MyCommand cmd;
 * 	return cmd.parse(argc, argv);
 * }
 * @endcode
 *
 * This may be replaced by the short-cut:
 * @code
 * ELM_RUN(MyCommand)
 * @endcode
 *
 * The classes allowed are:
 *	* option::EnumOption
 *	* option::ListOption
 *	* option::SwitchOption
 *	* option::ValueOption
 */

/**
 * @def ELM_RUN
 * This macro is a short to a main function running an application class.
 * The parameter must be the name of a class extending option::Manager.
 * It replaces the mandatory main() function of a C++ application.
 * @param C		Name of the application class.
 *
 * @ingroup options
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
 * @see @ref options
 */


/**
 */
Manager::Manager(void) {
}


/**
 * Build a new option manager.
 * @param maker		Information for initialization.
 */
Manager::Manager(const Make& maker): info(maker) {
	if(info._help)
		_help_opt = new SwitchOption(SwitchOption::Make(*this)
			.cmd("-h")
			.cmd("--help")
			.description("display this help message"));
	if(info._version_opt)
		_version_opt = new SwitchOption(SwitchOption::Make(*this)
			.cmd("-v")
			.cmd("--version")
			.description("display this application version"));
}


/**
 */
Manager::~Manager(void) {
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
		info._program = args.next<const char *>();
		break;
	case option::version: {
			Version *v = args.next<Version *>();
			ASSERT(v);
			info._version = *v;
			delete v;
		}
		break;
	case option::author:
		info._author = args.next<const char *>();
		break;
	case option::copyright:
		info._copyright = args.next<const char *>();
		break;
	case option::description:
		info._description = args.next<const char *>();
		break;
	case option::free_arg:
	case option::arg_desc:
		info._free_argument_description = args.next<const char *>();
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
	if(_help_opt && _help_opt->get()) {
		displayHelp();
		sys::System::exit(1);
	}
	else if(_version_opt && _version_opt->get()) {
		displayVersion();
		sys::System::exit(1);
	}
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
void Manager::addOption(Option *option) {
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
void Manager::addShort(char cmd, Option *option) {
	string str = _ << '-' << cmd;
	ASSERTP(!cmds.hasKey(str), "command '" << cmd << "' already used");
	cmds.put(str, option);
	shorts.put(cmd, option);
}


/**
 * Add a long command (prefixed with '--')
 * @param cmd		Long command string.
 * @param option	Option to add.
 */
void Manager::addLong(cstring cmd, Option *option) {
	string str = _ << "--" << cmd;
	ASSERTP(!cmds.hasKey(str), _ << "long command \"" << str << "\" already used");
	cmds.put(str, option);
}


/**
 * Add a generic command (no prefix required).
 * @param cmd		Command to add.
 * @param option	Option to add.
 */
void Manager::addCommand(string cmd, Option *option) {
	ASSERTP(!cmds.hasKey(cmd), "command \"" << cmd << "\" already used");
	cmds.put(cmd, option);
}


/**
 * Function called to run the application after
 * the command line parse. It is called by Manager::manage()
 * and can be overridden to provide its own behaviour to
 * the application.
 *
 * The default implementation do nothing.
 *
 * @throw elm::Exception	For any error during application run.
 */
void Manager::run(void) {
}


/**
 * Call to a complete management of the application by the option
 * manager. It will parse the given parameters and call the @ref run
 * method. In case of error, it will display it and provide an exit
 * code.
 *
 * It is able to make the main program code very simple:
 * @code
 * int main(int argc, char **argv) {
 * 		return MyApplication.manager(argc, argv);
 * }
 * @endcode
 *
 * @param argc	Argument count.
 * @param argv	Argument list.
 * @return		Exit code.
 */
int Manager::manage(int argc, argv_t argv) {
	try {
		parse(argc, argv);
		run();
		return 0;
	}
	catch(OptionException& e) {
		displayHelp();
		cerr << "ERROR: command line error: " << e.message() << io::endl;
		return 1;
	}
	catch(elm::Exception& e) {
		cerr << "ERROR: " << e.message() << io::endl;
		return 2;
	}
}


/**
 * Parse the given options.
 * @param argc				Argument count.
 * @param argv				Argument vector.
 * @throw OptionException	Thrown if the syntax contains an error.
 */
void Manager::parse(int argc, Manager::argv_t argv) {
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
 * Display version information on the standard output.
 */
void Manager::displayVersion(void) {
	cout << info._program << ' ' << info._version << io::endl;
}


/**
 * Display the help text to standard error.
 */
void Manager::displayHelp(void) {

	// Display header
	cerr << info._program;
	if(version)
		 cerr << " V" << info._version;
	if(author)
		cerr << " by " << info._author;
	cerr << '\n';
	if(copyright)
		cerr << info._copyright << '\n';
	
	// Display syntax
	cerr << '\n'
		 << "USAGE: " << info._program;
	if(options)
		cerr<< " [OPTIONS]";
	if(info._free_argument_description)
		cerr << ' ' << info._free_argument_description;
	cerr << '\n';
	if(info._description)
		cerr << info._description << '\n';
	cerr << "\nOPTIONS may be:\n";

	// display the arguments
	Vector<Option *> done;
	typedef ListMap<string, Option *>::PairIter iter;
	for(iter cmd = cmds.pairs().begin(); cmd(); cmd++) {

		// already done?
		Option *option = (*cmd).snd;
		if(done.contains(option))
			continue;
		done.add(option);

		// display commands
		bool comma = false;
		for(int longCommands = 0; longCommands <= 1; longCommands++) {
			// first iterate with short, then with long commands
			for(iter ocmd = cmd; ocmd(); ocmd++)
				if((*ocmd).snd == option)
					if(    ((*ocmd).fst[1] == '-' && longCommands)
					 	|| ((*ocmd).fst[1] != '-' && !longCommands) ) {
						if(comma)
							cerr << ", ";
						cerr << (*ocmd).fst;
						comma = true;
					}
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


/**
 * @fn SwitchOption::Make Manager::make_switch(void);
 * This function is a shortcut to @ref SwitchOption::Make() to reduce the definition
 * of options inside a @ef Manager class.
 */

/**
 * @fn ValueOption<T>::Make make_value(void);
 * This function is a shortcut to @ref ValueOption::Make() to reduce the definition
 * of options inside a @ef Manager class.
 */


/**
 * @class Manager::Make
 * This class is an initializer for class @ref Manager. It procides a safe and
 * readable way to initialize an option manager. It is usually passed directly
 * to the @ref Manager constructor.
 */

/**
 * @fn Manager::Make& Manager::Make::author(cstring s);
 * Specify the author of the application.
 */

/**
 * @fn Manager::Make& Manager::Make::copyright(cstring s);
 * Specify the copyright of the application.
 */

/**
 * @fn Manager::Make& Manager::Make::description(cstring s);
 * Specify the description of the application.
 */

/**
 * @fn Manager::Make& Manager::Make::free_argument(cstring s);
 * Specify description of the free arguments.
 */

/**
 * @fn Manager::Make& Manager::Make::help(void);
 * Ask the manager to create a switch option activated with "-h" or "--help"
 * that, when activated, display help message and the list of options.
 * Then it stops the application with an exit code of 1.
 */

} } // elm::option
