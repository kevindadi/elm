/*
 * $Id$
 * Copyright (c) 2006, IRIT - UPS.
 *
 * elm/serial/Unserializer.h -- Unserializer clas interface.
 */
#ifndef ELM_SERIAL_UNSERIALIZER_H
#define ELM_SERIAL_UNSERIALIZER_H

#include <elm/string.h>

namespace elm { namespace serial {

// Unserializer class
class Unserializer {
	
	template <class T> void process(T& val) { read(val); };

public:
	virtual void close(void) = 0;
	
	// Write methods
	template <class T> inline void read(T& val) { process<T>(val); };
	virtual void read(bool& val) = 0;
	virtual void read(char& val) = 0;
	virtual void read(unsigned char& val) = 0;
	virtual void read(short& val) = 0;
	virtual void read(unsigned short& val) = 0;
	virtual void read(long& val) = 0;
	virtual void read(unsigned long& val) = 0;
	virtual void read(int& val) = 0;
	virtual void read(unsigned int& val) = 0;
	virtual void read(long long& val) = 0;
	virtual void read(unsigned long long& val) = 0;
	virtual void read(float& val) = 0;
	virtual void read(double& val) = 0;
	virtual void read(CString& val) = 0;
	virtual void read(String& val) = 0;
	virtual void readPointer(void *&ptr) = 0;
	virtual void beginObject(CString name) = 0;
	virtual void endObject(void) = 0;
	virtual bool beginField(CString name) = 0;
	virtual void endField(void) = 0;

	// Operators 
	template <class T> inline Unserializer& operator>>(T& val) {
		read(val);
		return *this;
	}
	
	// Private
	template <class T> inline void processField(CString name, T& val) {
		if(beginField(name)) {
			process<T>(val);
			endField();
		}
	};
};
	
} } // elm::serial

#endif // ELM_SERIAL_UNSERIALIZER_H
