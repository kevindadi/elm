/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * src/io_OutStream.cpp -- implementation of abstract OutStream class.
 */

#include <unistd.h>
#include <elm/io/OutStream.h>

namespace elm { namespace io {

/**
 * @class OutStream
 * An output stream streams transfer a flow of bytes to another entity.
 * It is an abstract interface that must be implemented by standard IO, files,
 * pipes, compressors and so on.
 */

/**
 * @fn int Outstream::write(const char *buffer, int size);
 * This is the main method of an output stream: the given buffer is put on
 * the stream.
 * @param buffer	Byte buffer to write.
 * @param size		Size of the byte buffer.
 * @return				Number of transferred bytes or less than 0 for an error.
 */

/**
 * Write a byte to the stream.
 * @param byte	Byte to write.
 * @return				1 for success or less than 0 for an error.
 */
int OutStream::write(char byte) {
	char buffer = byte;
	return write(&buffer, 1);
}

/**
 * @fn int OutStream::flush()
 * Cause the current stream to dump its buffer to the medium.
 * @return 0 for success, less than 0 for error.
 */

} } // elm::io
