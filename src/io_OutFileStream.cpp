/*
 *	$Id$
 *	OutFileStream class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2004-08, IRIT UPS.
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
#include <elm/io/OutFileStream.h>

namespace elm { namespace io {

/**
 * @class OutFileStreal
 * Stream for outputting to a file.
 * @ingroup ios
 */


/**
 * Build an output file stream by creating a new file or deleting an old one.
 * @param path Path of the file to wriet to.
 */
OutFileStream::OutFileStream(const char *path)
: SystemOutStream(open(path, O_CREAT | O_TRUNC | O_WRONLY, 0777)) {
}


/**
 * Build an output file stream by creating a new file or deleting an old one.
 * @param path Path of the file to wriet to.
 */
OutFileStream::OutFileStream(const Path& path)
: SystemOutStream(open(&path.toString(), O_CREAT | O_TRUNC | O_WRONLY, 0777)) {
}


/**
 * Destructor (close the file if it is opened).
 */
OutFileStream::~OutFileStream(void) {
	close();
}

/**
 * Close the file. Subsequent writes will fail.
 */
void OutFileStream::close() {
	if(_fd >= 0) {
		::close(_fd);
		_fd = -1;
	}
}

} } // elm::io
