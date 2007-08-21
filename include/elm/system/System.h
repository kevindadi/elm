/*
 *	$Id$
 *	System class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
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
#ifndef ELM_SYSTEM_SYSTEM_H
#define ELM_SYSTEM_SYSTEM_H

#include <elm/util/Pair.h>
#include <elm/system/SystemIO.h>

namespace elm { namespace system {

// PipeInStream class
class PipeInStream: public SystemInStream {
	friend class System;
	PipeInStream(int fd);
public:
	~PipeInStream(void);
};

// PipeOutStream class
class PipeOutStream: public SystemOutStream {
	friend class System;
	PipeOutStream(int fd);
public:
	~PipeOutStream(void);
};

// System class
class System {
public:
	static Pair<PipeInStream *, PipeOutStream *> pipe(void);
	static unsigned int random(unsigned int top);
};

} } // elm::system

#endif // ELM_SYSTEM_SYSTEM_H
 
