/*
 *	Buffer class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2018, IRIT UPS.
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

#include <elm/util/Buffer.h>

namespace elm {

/**
 * @class BufferException
 * Exception raised by the function of @ref Buffer class when there
 * is an overful access.
 */

/**
 * @class Buffer
 * The intent of this class is to provide a simple way to prevent
 * errors like buffer-overful by controlling  precisely its
 * accesses.
 *
 * There are different to use a buffer:
 *	* byte access using array notation [...],
 *	* range access by copying ranges of bytes,
 *	* controlled read or write using an external function.
 *
 * In case of an invalid access to the buffer, the exception @BufferException
 * is thrown.
 *
 * @ingroup util
 */

/**
 * @var const t::size Buffer::default_size;
 * Default buffer size.
 */

/**
 * @fn Buffer::Buffer(t::size size);
 * Build and allocate a buffer of the given size.
 * The bytes are automatically allocated and released.
 * @param size	Buffer size (default to @ref default_size).
 */

/**
 * @fn Buffer::Buffer(char *buf, t::size size);
 * Build  buffer around the given bytes.
 * @param buf	Bytes to use.
 * @param size	Size of the given byte buffer.
 */

/**
 * @fn t::size Buffer::size();
 * Get the size of the buffer.
 * @return	Buffer size.
 */

/**
 * @fn void Buffer::copyTo(void *p, t::size size, t::size offset) const;
 * Copy a range of bytes from the buffer to the given memory.
 * @param p			Pointer to memory to copy to.
 * @param size		Size of range to copy.
 * @param offset	Offset in the buffer of bytes to copy (default to 0).
 */

/**
 * @fn void Buffer::copyFrom(void *p, t::size size, t::size offset);
 * Copy a range of bytes into the buffer.
 * @param p			Pointer to bytes to copy into the buffer.
 * @param size		Size of range to copy.
 * @param offset	Offset in the buffer to copy to (default to 0).
 */

/**
 * @fn void Buffer::read(F f, t::size size, t::size offset) const;
 * Read bytes from the buffer in a controlled way using the given function.
 * This supposes that the function f is not buggy.
 *
 * @param f			Function used to read from the buffer. Must be of type void(const char *, t::size).
 * @param size		Size of bytes to read.
 * @param offset	Offset in the buffer to read from (default to 0).
 */

/**
 * @fn void Buffer::write(F f, t::size size, t::size offset);
 * Write bytes in the buffer using a function in a controlled way.
 * This supposes that the function f is not buggy.
 *
 * @param f			Function used to write to the buffer. Must be of type void(char *, t::size).
 * @param size		Size of bytes to write.
 * @param offset	Offset in the buffer to write to (default to 0).
 */

}	// elm

