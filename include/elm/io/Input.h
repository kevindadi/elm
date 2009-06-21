/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/io/Input.h -- Input class interface.
 */
#ifndef ELM_IO_INPUT_H
#define ELM_IO_INPUT_H

#include <elm/string.h>
#include <elm/io/InStream.h>

namespace elm { namespace io {

// Input class
class Input {
public:
	inline Input(void): strm(&stdin), buf(-1) { };
	inline Input(InStream& stream): strm(&stream), buf(-1) { };
	inline InStream& stream(void) const { return *strm; };
	inline void setStream(InStream& stream) { strm = &stream; buf = -1; };

	bool scanBool(void);
	char scanChar(void);
	long scanLong(void);
	unsigned long scanULong(void);
	long long scanLLong(void);
	unsigned long long scanULLong(void);
	double scanDouble(void);
	String scanWord(void);
	String scanLine(void);
	void swallow(char chr);
	void swallow(CString str);
	void swallow(const String& str);
	void swallowBlank(void);

	inline Input& operator>>(bool& value) { value = scanBool(); return *this; };
	inline Input& operator>>(char& value) { value = scanChar(); return *this; };
	inline Input& operator>>(unsigned char& value) { value = scanULong(); return *this; };
	inline Input& operator>>(short& value) { value = scanLong(); return *this; };
	inline Input& operator>>(unsigned short& value) { value = scanULong(); return *this; };
	inline Input& operator>>(int& value) { value = scanLong(); return *this; };
	inline Input& operator>>(unsigned int& value) { value = scanULong(); return *this; };
	inline Input& operator>>(long& value) { value = scanLong(); return *this; };
	inline Input& operator>>(unsigned long& value) { value = scanULong(); return *this; };
	inline Input& operator>>(long long& value) { value = scanLLong(); return *this; };
	inline Input& operator>>(unsigned long long& value) { value= scanULLong(); return *this; };
	inline Input& operator>>(float& value) { value = scanDouble(); return *this; };
	inline Input& operator>>(double& value) { value = scanDouble(); return *this; };
	inline Input& operator>>(String& value) { value = scanLine(); return *this; };

private:
	InStream *strm;
	int buf;
	int get(void);
	void back(int chr);
};

} } // elm::io

#endif	// ELM_IO_INPUT_H
