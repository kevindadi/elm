/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/OutFileStream.h -- out file stream interface.
 */
#ifndef ELM_IO_OUTFILESTREAM_H
#define ELM_IO_OUTFILESTREAM_H

#include <elm/string.h>
#include <elm/io/UnixOutStream.h>

namespace elm { namespace io {

// OutFileStream class
class OutFileStream: public UnixOutStream {
public:
	OutFileStream(CString path);
	virtual ~OutFileStream(void);
	inline bool isReady(void) const { return fd() >= 0; };
	void close();
};

} } // elm::io

#endif // ELM_IO_OUTFILESTREAM_H
