/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/OutFileStream.h -- out file stream interface.
 */
#ifndef ELM_IO_OUTFILESTREAM_H
#define ELM_IO_OUTFILESTREAM_H

#include <elm/string.h>
#include <elm/system/SystemIO.h>

namespace elm { namespace io {

// OutFileStream class
class OutFileStream: public system::SystemOutStream {
public:
	OutFileStream(CString path);
	virtual ~OutFileStream(void);
	inline bool isReady(void) const { return fd() >= 0; };
	void close();
};

} } // elm::io

#endif // ELM_IO_OUTFILESTREAM_H
