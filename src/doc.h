/*
 *	Main documentation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008-17, IRIT UPS.
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
#ifndef ELM_DOC_H_
#define ELM_DOC_H_

namespace elm {

/**
 * @mainpage
 * 
 * ELM is a multi-purpose library used by the OTAWA project (http://www.otawa.fr).
 * It provides :
 * @li generic data structures,
 * @li generic interface with te operating system (files, command line, etc),
 * @li a checked plugin system,
 * @li efficient string class,
 * @li other utility classes.
 * 
 * The facilities of ELM (classes, functions, templates, etc) are sorted in the following
 * modules:
 * @li @ref alloc -- specialized allocators and interactive garbage collector,
 * @li @ref checksum -- checksum algorithms,
 * @li @ref data -- common generic data structures and associated facilities,
 * @li @ref dyndata -- data structure implementation using inheritance and virtual methods,
 * @li @ref ios -- unformatted and formatted input/output classes,
 * @li @ref json -- JSon format ELM implementation,
 * @li @ref net_mod -- network access abstraction classes,
 * @li @ref options -- command line option parsing classes,
 * @li @ref serial -- serialization facilities,
 * @li @ref string -- character string facilities,
 * @li @ref system -- system abstraction facilities (file system, plugin, random number, process management),
 * @li @ref rtti -- RTTI type support,
 * @li @ref types -- type information and other related functions,
 * @li @ref util -- miscellaneous utility classes (including debugging and testing helper classes),
 * @li @ref xom -- XML input/output classes.
 */

/*
 * @par Memory Management
 *
 * ELM supplies several classes to handle allocation and de-allocation:
 * @li default allocation scheme (@ref elm::DefaultAllocator),
 * @li allocate from a list of fixed size (@ref elm::BlockAllocator),
 * @li stack allocation with backtrack (@ref elm::StackAllocator),
 * @li semi-automatic specialized garbage collector (@ref elm::AbstractBlockAllocatorWithGC).
 *
 * And some cleanup classes or pointer management classes (@ref elm::AutoCleaner, @ref elm::AutoDestructor, @ref AutoPtr).
 *
 * @par Other Facilities
 * @li crash management (@ref elm::CrashHandler, only for Linux),
 * @li XML and XSLT using the XOM interface (@ref xom),
 * @li basic exceptions with message (@ref elm::Exception and @ref elm::MessageException),
 * @li very light test framework (@ref elm::TestCase and @ref elm::TestSet),
 * @li automatic serialization and unserialization (@ref serial),
 * @li work-around the C++ initialization fiasco (@ref elm::Initializer),
 * bit management (@ref elm::BitVector).
 */

/**
 * @defgroup utilities Development Utilities
 *
 * The entities defined in this section are targeted to help development and testing instead
 * of representing usual classes embedded in your application.
 *
 * @section deprecated Deprecation Management
 *
 * ELM provides a small macro found in <elm/deprecated.h>, called DEPRECATED.
 *
 * When put at the start of a function body, it displays a warning deprecation
 * message the first time it is called.
 *
 * @code
 * #include <elm/deprecated.h>
 *
 * class MyClass {
 * public:
 *
 * 	void myDeprecatedFunction(void) {
 * 		DEPRECATED
 * 		// body of the function
 * 	}
 * @endcode
 *
 * @section helper	Helper Methods
 *
 * ELM provides several helper method for using the different classes. They are prefixed by a double underscore and
 * all only compiled if a matching define is not provided.
 *
 * @li @c __size(): gives the full size of the data structure (removed if @c NSIZE is defined)
 * @li @c __print(): display an internal representation of the class (removed if @c NDEBUG is defined)
 *
 * @section test	Testing
 *
 * This module provides a poor, but existing, solution to unit testing in C++.
 * It provides macros and classes to perform statistics on unit testing
 * and makes automatic some test procedures.
 *
 * The example show how the module works:
 * @code
 * #include <elm/util/test.h>
 *
 * void my_test(void) {
 * 		CHECK_BEGIN("my test")
 *
 * 			// test 1
 * 			CHECK(result1 == expected1);
 *
 * 			// test 2
 * 			CHECK(result2 == expected2);
 *
 * 			...
 *
 * 		CHECK_END
 * }
 * @endcode
 *
 * The test must be enclosed in @c CHECK_BEGIN / @c CHECK_END pair and the test case name must be given.
 * Then the test are performed ending with a call to a macro allowing to test and record result of the test.
 *
 * The existing macro are:
 * @li @c CHECK(x) -- check if x is true
 * @li @c CHECK_EQUAL(result, expected) -- test equality and, if it fails, display the failed result value
 * @li @c CHECK_EXCEPTION(exception, action) -- perform the action and the test fails if the exception is not thrown
 * @li @c FAIL_ON_EXCEPTION(exception, action) -- perform the action and the test fails if the exception is thrown
 *
 * There are also some useful macros as:
 * @li @c REQUIRE(cnd, action) -- perform the action only if the given condition is true, else stop the test.
 *
 */

/**
 * @defgroup checksum Checksum Engines
 *
 * This small modules provides two checksum engines:
 * @li @ref checksum::Fletcher for fast checksumming,
 * @li @ref checksum::MD5 for MD5 checksum often used on the web.
 *
 */

}	// elm

#endif /*ELM_DOC_H_*/
