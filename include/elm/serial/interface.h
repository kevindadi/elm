/*
 * $Id$
 * Copyright (c) 2006, IRIT - UPS.
 *
 * elm/serial/interface.h -- interface for unserialization.
 */
#ifndef ELM_SERIAL_INTERFACE_H
#define ELM_SERIAL_INTERFACE_H

namespace elm { namespace serial {

// Extern classes
class SerialClass;
class Serializer;
class Unserializer;

// Macros
#define REFLEXIVE \
public: \
	static elm::serial::SerialClass& __class; \
private:

#define SERIALIZABLE \
	REFLEXIVE \
	public: \
		virtual void __serialize(elm::serial::Serializer& _serializer) const; \
		void __serialize(elm::serial::Unserializer& _serializer); \
	private:

} } // elm::serial

#endif // ELM_SERIAL_INTERFACE_H
