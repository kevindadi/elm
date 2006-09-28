/*
 * $Id$
 * Copyright (c) 2006, IRIT - UPS.
 *
 * elm/serial/implement.h -- implementation for unserialization.
 */
#ifndef ELM_SERIAL_IMPLEMENT_H
#define ELM_SERIAL_IMPLEMENT_H

#include <elm/string.h>
#include <elm/serial/SerialClass.h>
#include <elm/serial/Serializer.h>
#include <elm/serial/Unserializer.h>

namespace elm { namespace serial {

// Macros
#define FIELD(name) 			_serializer.processField(#name, name)
#define ON_SERIAL(code) 		if(__serial) { code; }
#define ON_UNSERIAL(code)		if(!__serial) { code; }
#define SERIALIZE_BASE(clazz)	{ if(__serial) clazz::__serialize(_serializer); }

#define SERIALIZE(clazz, fields) \
	elm::serial::GenSerialClass<clazz> __sclass_##clazz(#clazz); \
	void clazz::__serialize(elm::serial::Serializer& _serializer) const  { \
		bool __serial = true; \
		fields; \
	} \
	void clazz::__unserialize(elm::serial::Unserializer& _serializer) { \
		bool __serial = false; \
		fields; \
	} \
	namespace elm { namespace serial { \
	template <> void Serializer::process(const clazz& _obj) { \
		beginObject(#clazz, &_obj); \
		_obj.__serialize(*this); \
		endObject(); \
	} \
	template <> inline void Serializer::process<clazz *>(clazz * const &val) { \
		if(writePointer(val)) \
			delayObject(val, Serializer::delay<clazz>); \
	} \
	template <> void Unserializer::process(clazz& _obj) { \
		beginObject(#clazz); \
		_obj.__unserialize(*this); \
		endObject(); \
	} \
	template <> inline void Unserializer::process<clazz *>(clazz *&val) { \
		readPointer((void*&)val); \
	} \
	} }

} } // elm::serial

#endif // ELM_SERIAL_IMPLEMENT_H
