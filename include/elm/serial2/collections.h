/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * Serialization of usual collections.
 */
#ifndef ELM_SERIAL2_COLLECTION_H
#define ELM_SERIAL2_COLLECTION_H

#include <elm/serial2/serial.h>
#include <elm/genstruct/Vector.h>
#include <elm/genstruct/Table.h>

namespace elm { namespace serial2 {

using namespace genstruct;

// Table serialization
template <class T>
void __serialize(Serializer& serializer, const Table<T>& tab) {
	serializer.beginCompound();
	for(int i = 0; i < tab.count(); i++) {
		serializer.onItem();
		__serialize(serializer, tab[i]);
	}
	serializer.endCompound();
}
template <class T>
void __serialize(Serializer& serializer, Table<T>& tab) {
	__serialize(serializer, (const Table<T>&)tab);
}
template <class T>
void __serialize(Serializer& serializer, const AllocatedTable<T>& tab) {
	__serialize(serializer, (const Table<T>&)tab);
}
template <class T>
void __serialize(Serializer& serializer, AllocatedTable<T>& tab) {
	__serialize(serializer, (const Table<T>&)tab);
}


// Table unserialization
template <class T>
void __unserialize(Unserializer& serializer, AllocatedTable<T>& tab) {
	int cnt = serializer.countItems();
	if(!cnt)
		tab.allocate(0);
	else {
		tab.allocate(cnt);
		assert(serializer.beginCompound());
		for(int i = 0; i < cnt; i++) {
			__unserialize(serializer, tab[i]);
			serializer.nextItem();
		}
		serializer.endCompound();
	}
}


// Vector serialization
template <class T>
void __serialize(Serializer& serializer, const Vector<T>& vec) {
	serializer.beginCompound();
	for(int i = 0; i < vec.length(); i++) {
		serializer.onItem();
		__serialize(serializer, vec[i]);
	}
	serializer.endCompound();
}
template <class T>
void __serialize(Serializer& serializer, Vector<T>& vec) {
	__serialize(serializer, (const Vector<T>&)vec);
}

} } // elm::serial2

#endif // ELM_SERIAL2_COLLECTION_H


