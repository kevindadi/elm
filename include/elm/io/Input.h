/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * elm/io/Input.h -- Input class interface.
 */
#ifndef ELM_IO_INPUT_H
#define ELM_IO_INPUT_H

#include <elm/utility.h>
#include <elm/io/InStream.h>

namespace elm { namespace io {

// Input class
class Input {
	InStream *strm;
	int buf;
	int get(void);
	void back(int chr);
public:
	inline Input(void): strm(&stdin), buf(-1) { };
	inline Input(InStream& stream): strm(&stream), buf(-1) { };
	inline InStream& stream(void) const { return *strm; };
	inline void setStream(InStream& stream) { strm = &stream; buf = -1; };
	
	bool scanBool(void);
	char scanChar(void);
	long scanInt(void);
	long long scanLong(void);
	double scanDouble(void);
	String scanWord(void);
	String scanLine(void);
	void swallow(char chr);
	void swallow(CString string);
	void swallow(const String& string);
	void swallowBlank(void);
	
	inline Input& operator>>(bool& value) { value = scanBool(); return *this; };
	inline Input& operator>>(char& value) { value = scanChar(); return *this; };
	inline Input& operator>>(unsigned char& value) { value = scanInt(); return *this; };
	inline Input& operator>>(short& value) { value = scanInt(); return *this; };
	inline Input& operator>>(unsigned short& value) { value = scanInt(); return *this; };
	inline Input& operator>>(int& value) { value = scanInt(); return *this; };
	inline Input& operator>>(unsigned int& value) { value = scanInt(); return *this; };
	inline Input& operator>>(long& value) { value = scanInt(); return *this; };
	inline Input& operator>>(unsigned long& value) { value = scanInt(); return *this; };
	inline Input& operator>>(long long& value) { value = scanLong(); return *this; };
	inline Input& operator>>(unsigned long long& value) { value= scanLong(); return *this; };
	inline Input& operator>>(float& value) { value = scanDouble(); return *this; };
	inline Input& operator>>(double& value) { value = scanDouble(); return *this; };
	inline Input& operator>>(String& value) { value = scanLine(); return *this; };
	/*inline Input& operator>>(const char value) { swallow(value); return *this; };
	inline Input& operator>>(CString value) { swallow(value); return *this; };
	inline Input& operator>>(const String& value) { swallow(value); return *this; };*/
};

} } // elm::io

#endif	// ELM_IO_INPUT_H
