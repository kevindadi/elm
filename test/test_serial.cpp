/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_serial.cpp -- serial module test.
 */

#include <elm/util/test.h>
#include <elm/io.h>
#include <elm/genstruct/HashTable.h>
#include <elm/genstruct/VectorQueue.h>
#include <elm/util/Pair.h>

using namespace elm;

namespace elm {
class ConstPtrHashKey: public HashKey<const void *> {
	virtual unsigned long hash(const void *v) {
		return (unsigned long)v;
	};
	virtual bool equals(const void *key1, const void *key2) {
		return key1 == key2;
	};
};
static ConstPtrHashKey cptr_hkey_obj;
template <> HashKey<const void *>& HashKey<const void *>::def = cptr_hkey_obj;
}

namespace elm { namespace serial {

// Serializer class
class Serializer {
	
	template <class T> static void delay(Serializer& serializer, const void *p) {
		serializer.process<T>(*(T *)p);
	}

	template <class T> void process(const T& val);

protected:
	typedef void (*delay_t)(Serializer& serializer, const void *p);
	virtual void delayObject(const void *ptr, delay_t fun) = 0;
public:
	virtual void close(void) = 0;
	
	// Write methods
	template <class T> inline void write(const T& val) { process<T>(val); };
	virtual void writeChar(char val) = 0;
	virtual void writeInt(long val) = 0;
	virtual void writeLong(long long val) = 0;
	virtual bool writePointer(const void *ptr) = 0;
	virtual void beginObject(CString name, const void *ptr) = 0;
	virtual void endObject(void) = 0;
	virtual void writeField(CString name) = 0;

	// Operators 
	template <class T> inline Serializer& operator<<(const T& val) {
		write(val);
		return *this;
	}
	
	// Private
	template <class T> inline void processField(CString name, const T& val) {
		writeField(name);
		process<T>(val);
	};
};


// Built-in types
template <> inline void Serializer::process<char>(const char& val) { writeChar(val); };
template <> inline void Serializer::process<long>(const long& val) { writeInt(val); };
template <> inline void Serializer::process<int>(const int& val) { writeInt(val); };


// Unserializer class
class Unserializer {
};

} } // elm::serial


#define SERIALIZABLE \
		friend class elm::serial::Serializer; \
	protected: \
		void __serialize(elm::serial::Serializer& _serializer) const; \
	private:

#define FIELD(name) _serializer.processField(#name, name)
#define ON_SERIAL(code) 		if(__serial) { code; }
#define ON_UNSERIAL(code)		if(!__serial) { code; }
#define SERIALIZE_BASE(clazz)	{ if(__serial) clazz::__serialize(_serializer); }

#define SERIALIZE(clazz, fields) \
	void clazz::__serialize(elm::serial::Serializer& _serializer) const  { \
		bool __serial = true; \
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



// MySubClass class
class MyClass;
class MySubClass {
	SERIALIZABLE
	char c;
	MyClass *back;
public:
	MySubClass(char _c, MyClass *_back): c(_c), back(_back) { };
};

SERIALIZE(MySubClass, FIELD(c); FIELD(back);)


// MyClass class
class MyClass {
	SERIALIZABLE
	int x;
	MySubClass sub;
	MySubClass *sub2;
public:
	MyClass(int _x): x(_x), sub('a', this), sub2(new MySubClass('b', 0)) { };
};

SERIALIZE(MyClass, FIELD(x); FIELD(sub); FIELD(sub2))


// TextSerializer class
namespace elm { namespace serial {
	
class TextSerializer: public Serializer {
	bool field;
	elm::genstruct::HashTable<const void *, int> objects;
	elm::genstruct::VectorQueue<elm::Pair<const void *, delay_t> > to_process;
	void checkField(void) {
		if(field) {
			cout << "; ";
			field = false;
		}
	}

protected:
	virtual void writeChar(char val) {
		cout << '\'' << val << '\'';
		checkField();
	}
	
	virtual void writeInt(long val) {
		cout << val;
		checkField();
	}
	
	virtual void writeLong(long long val) {
		cout << val;
		checkField();
	}
	
	virtual bool writePointer(const void *ptr) {
		cout << io::hex((unsigned long)ptr);
		checkField();
		return ptr && !objects.get(ptr);
	}

	virtual void delayObject(const void *ptr, delay_t fun) {
		to_process.put(elm::Pair<const void *, delay_t>(ptr, fun));
		objects.put(ptr, 1);
	}

	virtual void beginObject(CString name, const void *ptr) {
		objects.put(ptr, 1);
		cout << name << '(' << io::hex((unsigned long)ptr) << ") = {";
	}
	
	virtual void endObject(void) {
		cout << "}";
		checkField();
	}

	virtual void writeField(CString name) {
		field = true;
		cout << ' ' << name << " = ";
	};
	
public:
	TextSerializer(void): field(false) { };
	
	// Serializer overload
	virtual void close(void) {
		while(to_process) {
			to_process->snd(*this, to_process->fst);
			to_process.get();
		}
	}

};

} } // elm::serial

// Entry point
void test_serial(void) {
	elm::serial::TextSerializer serialize;
	MyClass my_object(666);
	serialize << my_object;
	serialize.close();
}
