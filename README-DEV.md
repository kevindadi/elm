# Elm Developper Information

## Organization

Directories:
  * include/		ELM headers.
  * src/			ELM sources.
  * test/			Test programs.
  * perf/			Performances test programs and data.
  * tools/			Tool to work with ELM.

## Working with sources

Bootstrap:
	cmake .

Under Windows (MINGW required):
	cmake . -G "MSYS Makefiles"

Auto-documentation:
	doxygen
	xdg-open autodoc/index.html

Activating the test compilation:
	cmake . -DWITH_TEST=yes

Testing:
	cd test
	./dotest		launch all automated tests
	./test-thread	thread classes

Under Windows:
	move src/libelm.dll to test/


## Documentation

All classes, function, macros, variable or type provided
to uses must be documented using the [Doxygen](http://www.stack.nl/~dimitri/doxygen/|Doxygen)
tool. Doxygen automatic documentation is very close to JavaDoc but provides 
more flexibility and support for C++. The syntax detail can be found
[here](http://www.stack.nl/~dimitri/doxygen/manual/commands.html).

Additionally, Doxygen supports Markdown wiki syntax that may be found
[here](http://daringfireball.net/projects/markdown/syntax). Below is a non-exhaustive
list of markdown syntax:
  * \n to create a new paragraph,
  * title \n ==== or # title # to create a section
  * title \n ---- or ## title ## to create a new section
  * > text to create a blockquote
  * */+/- text for a bulleted list
  * 1. text for a numbered list
  * \t text for code block
  * - - - for horizontal rule
  * [text](url) for a link
  * *text* or _text_ for emphasized text
  * **text** or __text__ for even more emphasized text
  * \c to avoid c to be used as special character
  * `text` for code text
  * ![alternate text](url) to include an image
  * ![alternate text](url caption) to include an image with caption
  * <url> for explicit link

An important rule must be applied: no documentation must be put in the header
file. Classes has to be described in the source file. For a class, a special comment
like below must be set:
	/**
	 * @class MY_CLASS
	 * documentation
	 */

For an inlined function, the documentation must be put in the source file as:
	/**
	 * @fn RETURN_TYPE MY_CLASS::FUNCTION_NAME(PARAMETERS);
	 * documentation
	 */

All resources provided by ELM must be located in a module using the Doxygen
directive @ingroup (at the end of the description):
	/**
	 * documentation
	 * @ingroup MODULE
	 */

The list of available modules may be obtained from the automatic documentation.


## Covering Types

In order, to get functions or template specializations supporting all types,
the following overload must be performed.

For base types:
  * void
  * bool
  * char (special case for character support)
  * signed/unsigned char/short/int/long/long long
  * float, double, long double

For string types:
  * const char *
  * cstring
  * const string&

Other type support encompasses:
  * T * - pointer type
  * const T& - other kind of object


## Development Directives


