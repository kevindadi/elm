/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_option.cpp -- option module test.
 */

#include <elm/util/test.h>
#include <elm/options.h>

using namespace elm;
using namespace elm::option;

Manager man;

// EnumOption test
typedef enum val_t {
	one,
	two,
	three
} val_t;
EnumOption<int>::value_t vals[] = {
	{ "value", one },
	{ "one", one },
	{ "two", two },
	{ "three", three },
	{ "", one }
};
EnumOption<int> enum_opt(man, 'e', "enum", "", vals);

class MyCommand: public Manager {
public:
	MyCommand(void) {
		version = "1.2.3";
	}
};

// test_option()
void test_option(void) {
	CHECK_BEGIN("Option");

	try {
		// Unknown option
		{
			const char *argv[] = { "command", "--bad", 0 };
			CHECK_EXCEPTION(OptionException, man.parse(2, argv));
		};

		// EnumOption test
		{
			CHECK(enum_opt == one);
			enum_opt = two;
			CHECK(enum_opt == two);
			{
				const char *argv[] = { "command", "-e", "one", 0 };
				man.parse(3, argv);
				CHECK(enum_opt == one);
			}
			{
				const char *argv[] = { "command", "-e", "two", 0 };
				man.parse(3, argv);
				CHECK(enum_opt == two);
			}
			{
				const char *argv[] = { "command", "-e", "four", 0 };
				CHECK_EXCEPTION(OptionException, man.parse(3, argv));
			}
		}

		// check StringOption
		{
			StringOption str(man, 's', "string", "", "", "ok");
			CHECK(str);
		}
	}
	catch(OptionException& e) {
		__case.failed();
		cerr << "FAILURE: " << e.message() << io::endl;
	}

	CHECK_END
}
