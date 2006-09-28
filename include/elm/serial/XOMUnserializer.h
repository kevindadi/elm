/*
 * $Id$
 * Copyright (c) 2006, IRIT - UPS.
 *
 * elm/serial/XOMUnserializer.h -- XOMUnserializer class interface.
 */
#ifndef ELM_SERIAL_XOM_UNSERIALIZER_H
#define ELM_SERIAL_XOM_UNSERIALIZER_H

#include <elm/genstruct/HashTable.h>
#include <elm/serial/Unserializer.h>

namespace elm {

// Extern classes
namespace xom {
	class Document;
	class Element;
}

namespace serial {

// XOMUnserializer class
class XOMUnserializer: public Unserializer {

	typedef struct patch_t {
		struct patch_t *next;
		void *& ptr;
		inline patch_t(void*& _ptr): ptr(_ptr) { };
	} patch_t;

	typedef struct ref_t {
		void *ptr;
		patch_t *patches;
		inline ref_t(void *_ptr = 0): ptr(_ptr), patches(0) { };
		void put(void *&_ptr);
		void record(void *_ptr);
	} ref_t;

	xom::Document *doc;
	xom::Element *elem;
	elm::io::Input in;
	elm::genstruct::HashTable<CString,  ref_t *> refs;

public:
	XOMUnserializer(xom::Element *element);
	XOMUnserializer(elm::CString path);
	~XOMUnserializer(void);

	// Unserializer overload
	virtual void delayObject(void *&ptr);
	virtual void close(void);
	virtual void readPointer(void *&ptr);
	virtual void beginObject(CString name);
	virtual void endObject(void);
	virtual bool beginField(CString name);
	virtual void endField(void);
	virtual void read(bool& val);
	virtual void read(char& val);
	virtual void read(unsigned char& val);
	virtual void read(short& val);
	virtual void read(unsigned short& val);
	virtual void read(long& val);
	virtual void read(unsigned long& val);
	virtual void read(int& val);
	virtual void read(unsigned int& val);
	virtual void read(long long& val);
	virtual void read(unsigned long long& val);
	virtual void read(float& val);
	virtual void read(double& val);
	virtual void read(CString& val);
	virtual void read(String& val);
}; 

} } // elm::serial

#endif // ELM_SERIAL_XOM_UNSERIALIZER_H

