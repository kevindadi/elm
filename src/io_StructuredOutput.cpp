/*
 *	StructuredOutput class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2021, IRIT UPS.
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

#include <elm/io/StructuredOutput.h>

namespace elm { namespace io {
	
/**
 * @class StructuredOutput
 * 
 * This interface is implemented to be performed structure output, that is the
 * output of values orgznized as:
 *	* base types (integer, float, boolean, string)
 *	* list of values
 *	* map of values with string keys.
 * 
 * Classical structured outputs encompasses [JSON](https://en.wikipedia.org/wiki/JSON),
 * [XML](https://en.wikipedia.org/wiki/XML) or
 * (INI)[https://en.wikipedia.org/wiki/INI_file].
 * 
 * Base types are simply written by a call to a write() function.
 * 
 * To write an list, perform a call to beginList(), as many call to write the
 * items composing the list and closing is performed by calling endList().
 * 
 * To write a map, perform a call to beginMap() and the, for each map value,
 *	* perform a call to key() with key name
 *  * and a call to a write function with the value.
 * The map is completed by a call to endMap().
 * 
 * This interface is currently implemented by:
 *	* elm::json::Saver
 *
 * @ingroup io
 */

///
StructuredOutput::~StructuredOutput() {
}
	
}}

