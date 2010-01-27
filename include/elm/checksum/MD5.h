/*
 *	$Id$
 *	MD5 class interface
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
#ifndef ELM_CHECKSUM_MD5_H
#define ELM_CHECKSUM_MD5_H

#include <elm/string.h>
#include <elm/io.h>
#include <elm/io/InStream.h>

namespace elm { namespace checksum {

// MD5 class
class MD5 {
public:
	typedef unsigned char digest_t[16];

	MD5(void);
	void digest(digest_t tab);
	void print(io::Output& out);

	void put(const void *buffer, unsigned long length);
	void put(const cstring& str);
	void put(const string& str);
	void put(io::InStream& in);
	void put(io::InStream& in, int length);

	inline MD5& operator<<(const char *str) { put(CString(str)); return *this; }
	inline MD5& operator<<(const CString& str) { put(str); return *this; }
	inline MD5& operator<<(const String& str) { put(str); return *this; }
	template <class T> inline MD5& operator<<(const T& value) { put(&value, sizeof(T)); return *this; }

private:
	typedef unsigned long int md5_size;

	void finalize(void);
	void update(void);
	void encode(unsigned char *buf);
	void addsize (unsigned char *M, md5_size index, md5_size oldlen);

	bool finalized;
	struct {
		unsigned long int A, B, C, D;
	} regs;
	unsigned char *buf;
	md5_size size;
	md5_size bits;
	digest_t _digest;
};

inline io::Output& operator<<(io::Output& out, MD5& md5) { md5.print(out); return out; }

} } // elm::checksum

#endif // ELM_CHECKSUM_MD5_H

