/*
 *	$Id$
 *	stream functions
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2009, IRIT UPS.
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
#ifndef ELM_STRING_STREAM_H_
#define ELM_STRING_STREAM_H_

#include <elm/string.h>
#include <elm/type_info.h>

namespace elm {

// template
template <class T>
const string& operator>>(const string& str, T& val) { val = type_info<T>::null; return str; }

// specialization
template <> const string& operator>><int>(const string& str, int& val);
template <> const string& operator>><signed long>(const string& str, signed long& val);
template <> const string& operator>><unsigned long>(const string& str, unsigned long& val);

}	// elm

#endif /* ELM_STRING_STREAM_H_ */
