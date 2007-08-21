/*
 *	$Id$
 *	InFileStream class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-07, IRIT UPS.
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <elm/io/InFileStream.h>
#include <elm/io/io.h>

namespace elm { namespace io {

/**
 * @class InFileStream
 * Stream for outputting to a file.
 * @ingroup ios
 */

/**
 * Build an output file stream by creating a new file or deleting an old one.
 * @param path Path of the file to wriet to.
 */
InFileStream::InFileStream(CString path)
: SystemInStream(open(path.chars(), O_RDONLY, 0777)) {
	if(fd() < 0)
		throw IOException(_ << "cannot open file \"" << path
			<< "\" : " << lastErrorMessage());
}

/**
 * Destructor (close the file if it is opened).
 */
InFileStream::~InFileStream(void) {
	close();
}

/**
 * Close the file. Subsequent writes will fail.
 */
void InFileStream::close() {
	if(_fd >= 0) {
		::close(_fd);
		_fd = -1;
	}
}

} } // elm::io
