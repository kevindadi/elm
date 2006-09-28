/*
 * $Id$
 * Copyright (c) 2006, IRIT - UPS.
 *
 * src/serial_XOMUnserializer.cpp -- XOMUnserializer class implementation.
 */

#include <elm/xom.h>
#include <elm/io/BlockInStream.h>
#include <elm/serial/SerialClass.h>
#include <elm/serial/XOMUnserializer.h>

namespace elm { namespace serial {

/**
 * @class XOMUnserializer
 * Unserializer from XML using XOM API.
 */


/**
 */
void XOMUnserializer::ref_t::put(void *&_ptr) {
	if(ptr)
		_ptr = ptr;
	else {
		patch_t *patch = new patch_t(_ptr);
		patch->next = patches;
		patches = patch;
	}
}


/**
 */		
void XOMUnserializer::ref_t::record(void *_ptr) {
	ptr = _ptr;
	for(patch_t *patch = patches, *next; patch; patch = next) {
		next = patch->next;
		patch->ptr = ptr;
		delete patch;
	}
}


/**
 * Build the unserializer for using the given element.
 * @param element	XOM element to use.
 */				
XOMUnserializer::XOMUnserializer(xom::Element *element)
: doc(0), elem(element) {
}


/**
 * Build an unserializer from the given XOM document.
 * @param path	Path document to unserialize from.
 */
XOMUnserializer::XOMUnserializer(elm::CString path)
: doc(0), elem(0) {
	xom::Builder builder;
	doc = builder.build(path);
	if(!doc)
		throw io::IOException("cannot open \"%s\"", &path);
	elem = doc->getRootElement();
	assert(elem);
}


/**
 */
XOMUnserializer::~XOMUnserializer(void) {
	if(doc)
		delete doc;
}


/**
 */
void XOMUnserializer::delayObject(void *&ptr) {
}


/**
 */	
void XOMUnserializer::close(void) {
}


/**
 */
void XOMUnserializer::readPointer(void *&ptr) {
	
	// Is there a reference ?
	CString id = elem->getAttributeValue("ref");
	if(id) {
		ref_t *ref = refs.get(id, 0);
		if(!ref) {
			ref = new ref_t();
			refs.put(id, ref);
		}
		ref->put(ptr);
	}
	
	// Else it should be embedded
	else {
		
		// Find the class
		CString clazz_name = elem->getAttributeValue("class");
		if(!clazz_name)
			clazz_name = elem->getLocalName();
		SerialClass *clazz = SerialClass::find(clazz_name);
		if(!clazz)
			throw io::IOException("no class %s\n", &clazz_name);
		ptr = clazz->create();
		clazz->unserialize(ptr, *this);
		
		// Record identification
		id = elem->getAttributeValue("id");
		if(id) {
			ref_t *ref = refs.get(id, 0);
			if(ref)
				ref->record(ptr);
			else
				refs.put(id, new ref_t(ptr));
		}
	}
}


/**
 */
void XOMUnserializer::beginObject(CString name) {
}


/**
 */
void XOMUnserializer::endObject(void) {
}


/**
 */
bool XOMUnserializer::beginField(CString name) {
	xom::Element *felem = elem->getFirstChildElement(xom::String(name));
	if(!felem)
		return false;
	elem = felem;
	return true;
}


/**
 */
void XOMUnserializer::endField(void) {
	elem = (xom::Element *)elem->getParent();
}


/**
 */
void XOMUnserializer::read(bool& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(char& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(unsigned char& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(short& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(unsigned short& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(long& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(unsigned long& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(int& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(unsigned int& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(long long& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(unsigned long long& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(float& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(double& val) {
	xom::String text = elem->getValue();
	io::BlockInStream block(text);
	in.setStream(block);
	in >> val;
	text.free();
}


/**
 */
void XOMUnserializer::read(CString& val) {
	val = elem->getValue();
}


/**
 */
void XOMUnserializer::read(String& val) {
	xom::String text = elem->getValue();
	val = String(text);
	text.free();
}

} } // elm::serial

