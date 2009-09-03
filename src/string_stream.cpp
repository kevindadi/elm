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

#include <elm/string/stream.h>
#include <elm/io/Input.h>
#include <elm/io/BlockInStream.h>

namespace elm {

#define OUT(T) \
	template <> const string& operator>><T>(const string& str, T& val)  { \
		io::BlockInStream block(str); \
		io::Input in(block); \
		in >> val; \
		return str; \
	}

OUT(int)
OUT(signed long)
OUT(unsigned long)

} // elm
