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

template <class T>
elm::serial::SerialClass& __make_class(elm::CString name) {
	static elm::serial::GenSerialClass<T> clazz(name);
	return clazz;
}

template <class T> inline void __serial_proceed(T& obj, Serializer& serializer) {
	obj.T::__serialize(serializer);
}

template <class T> inline void __serial_proceed(T& obj, Unserializer& unserializer) {
	obj.T::__unserialize(unserializer);
}

// Macros
#define FIELD(name) 			_serializer.processField(#name, name)
#define ON_SERIAL(code) 		if(__serial) { code; }
#define ON_UNSERIAL(code)		if(!__serial) { code; }
#define SERIALIZE_BASE(clazz)	elm::serial::__serial_proceed<clazz>((clazz&)*this, _serializer)

#define REFLEXIVITY(clazz) \
	elm::serial::SerialClass& clazz::__class = elm::serial::__make_class<clazz>(#clazz);

#define SERIALIZE(clazz, fields) \
	REFLEXIVITY(clazz) \
	void clazz::__serialize(elm::serial::Serializer& _serializer) const  { \
		fields; \
	} \
	void clazz::__unserialize(elm::serial::Unserializer& _serializer) { \
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
	} }

} } // elm::serial

#endif // ELM_SERIAL_IMPLEMENT_H
