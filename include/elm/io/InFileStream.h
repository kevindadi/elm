/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * elm/io/InFileStream.h -- interface for InFilestream class.
 */
#ifndef ELM_IO_INFILESTREAM_H
#define ELM_IO_INFILESTREAM_H

#include <elm/string.h>
#include <elm/io/UnixInStream.h>

namespace elm { namespace io {

// InFileStream class
class InFileStream: public UnixInStream {
public:
	InFileStream(CString path);
	virtual ~InFileStream(void);
	inline bool isReady(void) const { return fd() >= 0; };
	void close();
};

} } // elm::io

#endif // ELM_IO_INFILESTREAM_H
