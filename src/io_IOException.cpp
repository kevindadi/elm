/*
 *	$Id$
 *	IOException class implementation
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

#include <string.h>
#include <errno.h>
#include <elm/io/io.h>

namespace elm { namespace io {

/**
 * @defgroup ios Input / Output System
 * 
 * The input/output of ELM is a merge of the C++ standard library system and of
 * the Java standard library. From the former, it uses the "<<" and ">>"
 * operators overload. From the latter, it implements the two IO access:
 * low-level classes manage streams of bytes and the high-level provides
 * formatting facilities.
 * 
 * @section high_level High-Level Input / Output
 * 
 * This level provides formatted input/output as in C++ standard library, that
 * is, through the "<<" and ">>" operators. The formatted output class is
 * @ref Output and the formatted input class is @ref Input.
 * 
 * Three global variables give access to the standard input/output:
 * @li cin -- standard input,
 * @li cout -- standard output,
 * @li cerr -- standard error.
 * 
 * Most basic types are supported (including @ref String and @ref CString).
 * Some constants are provided for special output:
 * @li @ref elm::io::endl -- new line.
 * 
 * Unlike the C++ standard library, the output format is managed thrugh special
 * formatting objects. For integer, the work is performed by @ref IntFormat
 * that provides display features like representation base, field width,
 * alignment, uppercase letters for base greater than 10, signess, padding.
 * These features may easily be accessed with special functions:
 * @li @ref io::base -- select a specific base,
 * @li @ref io::bin -- binary base,
 * @li @ref io::hex -- hexadecimal base,
 * @li @ref op::width -- field with,
 * @li @ref io::align -- alignment,
 * @li @ref io::left -- alignment to left,
 * @li @ref io::center -- centered alignment,
 * @li @ref io::right -- alignment to right,
 * @li @ref io::pad -- padding character,
 * @li @ref io::uppercase -- uppercase character for digits greater than 10,
 * @li @ref io::lowercase -- lowercase character for digits greater than 10.
 * 
 * Below, an example to format an integer as an hexadecimal pointer:
 * @code
 * 	int i;
 *	IntFormat ptr(IntFormat v) {
 * 		return io::uppercase(io::hex(io::width(8, io::pad('0', io::right(v))))); 
 * 	}
 * 	cout << ptr(v) << io::endl;
 * @endcode
 * 
 * More formats will come soon (for float numbers for example).
 * 
 * The errors are managed here using exception objects derivated from the
 * @ref IOException class.  
 * 
 * @section low_level Byte Streams
 * 
 * The low-level IO system is only responsible for exchanging streams of bytes.
 * 
 * All input streams must inherit from the @ref InStream class and defines the
 * following functions:
 * @li read(buffer) -- read some bytes into the given buffer,
 * @li read() -- read one byte.
 * ELM provides byte input streams for files (@ref InFileStream), for memory
 * blocks (@ref BlockInStream) or system pipes (@ref PipeInStream).
 * 
 * The errors are returned by the called functions. Either a positive value,
 * or a value of @ref InStream::FAILED (error on the media), or
 * @ref InStream::ENDED (end of the media reached). Information about the
 * errors may be obtained by the lastErrorMessage() method.
 * 
 * All output streams must inherit from the @ref OutStream class and defines the
 * following functions:
 * @li write(buffer) -- write some bytes from the given buffer,
 * @li write() -- write one byte,
 * @li @ref flush() -- ensures that all written btes have been transfered to
 * the media.
 * ELM provides byte output streams for files (@ref OutFileStream), for memory
 * blocks (@ref BlockOutStream) or system pipes (@ref PipeOutStream).
 * 
 * The errors are returned as negative value by this functions. Information
 * about the errors may be obtained by the lastErrorMessage() method.
 */


/**
 * @class IOException
 * This exception is thrown when an IO error occurs.
 * @ingroup ios
 */


/**
 *@fn  IOException::IOException(CString message, ...);
 * Build a new IOException with the given message.
 * @param message	Message formatted a-la printf.
 * @param ...		Arguments used in the message.
 */


/**
 *@fn  IOException::IOException(CString message, VarArg& args);
 * Build a new IOException with the given message.
 * @param message	Message formatted a-la printf.
 * @param args		Arguments used in the message.
 */

} } // elm::io
