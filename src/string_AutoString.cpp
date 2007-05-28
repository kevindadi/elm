/*
 * $Id$
 * Copyright (c) 2007, IRIT - UPS
 *
 * autostr implementation
 */

#include <elm/string/AutoString.h>

namespace elm {

/**
 * This little object make easier the construction of strings. There is no more
 * to explictely construct a string buffer, concatenates items and buid the
 * string to pass it to a parameter. Just perform the concatenation on the
 * autostr object and all work is done automatically as in the example
 * below.
 * 
 * @code
 *	void call(const String& message);
 * 
 *	for(int i = 0; i < 100; i++)
 *		call(autostr << "Hello world, " << i << " times !");
 * @endcode
 * 
 * As the @ref autostr keyword is a bit long, you may replaced it by "_".
 * 
 * @code
 *	for(int i = 0; i < 100; i++)
 *		call(_ << "Hello world, " << i << " times !");
 * @endcode
 * 
 */
AutoStringStartup autostr;
AutoStringStartup &_ = autostr;

} // elm
