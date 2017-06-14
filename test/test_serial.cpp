/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_serial.cpp -- serial module test.
 */

#include <elm/io.h>
#include <elm/xom.h>
#include <elm/data/Vector.h>
#include <elm/rtti.h>
#include <elm/serial2/macros.h>
#include <elm/serial2/data.h>
#include <elm/serial2/TextSerializer.h>
#include <elm/serial2/XOMUnserializer.h>
#include "../include/elm/test.h"

using namespace elm;

// MySubClass class
class MyClass;
class MySubClass {
	SERIALIZABLE(MySubClass, c & back)
	char c;
	MyClass *back;
public:
	MySubClass(void): c(0), back(0) { }
	MySubClass(char _c, MyClass *_back): c(_c), back(_back) { };
	virtual ~MySubClass(void) { }
};



// MyClass class
class MyClass {
	SERIALIZABLE(MyClass, x & sub & sub2)
	int x;
	MySubClass sub;
	MySubClass *sub2;
public:
	MyClass(void): x(0), sub2(0) { };
	MyClass(int _x): x(_x), sub('a', this), sub2(new MySubClass('b', 0)) { };
	virtual ~MyClass(void) { }
};



// ItemClass
class ItemClass {
	SERIALIZABLE(ItemClass, x)
public:
	ItemClass(void): x(666) { }
	int x;
	virtual int getX(void) { return x; };
	virtual ~ItemClass(void) { }
};


// Item2Class
class Item2Class: public ItemClass {
	SERIALIZABLE(Item2Class, x)
public:
	virtual int getX(void) { return 666; };
	virtual ~Item2Class(void) { }
	int x;
};


// SimpleClass
class SimpleClass {
	SERIALIZABLE(SimpleClass,
		field("x", x, 0) &
		field("c", c, '\0') &
		field("f", f, 0.) &
		field("str", str) &
		field("en", en) &
		field("ref", ref) &
		field("list", list) &
		field("list2", list2) &
		field("list3", list3));
public:
	typedef enum enum_t {
		VAL1 = 0,
		VAL2,
		VAL3
	} enum_t;

	ItemClass *ref;
	int x;
	char c;
	double f;
	CString str;
	elm::Vector<int> list;
	elm::Vector<ItemClass> list2;
	elm::Vector<ItemClass *> list3;
	enum_t en;
	SimpleClass(void): ref(0), x(111), c('a'), f(0.1), str("ok"), en(VAL1) { }
	virtual ~SimpleClass(void) { }
};
//CString values[] = { "VAL1", "VAL2", "VAL3", "" };
ENUM(SimpleClass::enum_t);

ENUM_BEGIN(SimpleClass::enum_t)
	VALUE(SimpleClass::VAL1),
	VALUE(SimpleClass::VAL2),
	VALUE(SimpleClass::VAL3)
ENUM_END

/*rtti::Enum enum_t_type(rtti::Enum::make("SimpleClass:enum_t")
	.value("VAL1", SimpleClass::VAL1)
	.value("VAL2", SimpleClass::VAL2)
	.value("VAL3", SimpleClass::VAL3)
	.alias("SimpleClass::VAL1", SimpleClass::VAL1)
	.alias("SimpleClass::VAL2", SimpleClass::VAL2)
	.alias("SimpleClass::VAL3", SimpleClass::VAL3));
template <> inline const elm::rtti::Type& elm::rtti::_type<SimpleClass::enum_t>::_(void) { return enum_t_type; }*/


// Entry point
TEST_BEGIN(serial)
	
	try {
		
		// Serialize text
		io::BlockOutStream stream;
		io::Output out(stream);
		elm::serial2::TextSerializer serialize(out);
		MyClass my_object(666);
		serialize << my_object;
		serialize.flush();
		cout << stream.toString() << io::endl << io::endl;
		
		// Unserialize XML
		serial2::XOMUnserializer unser("unser.xml");
		SimpleClass res;
		unser >> res;
		unser.flush();
		CHECK_EQUAL(res.x, 666);
		CHECK_EQUAL(res.c, 'b');
		CHECK_EQUAL(res.f, 1.9);
		CHECK_EQUAL(res.str, cstring("ko"));
		CHECK_EQUAL(res.list.length(), 3);
		CHECK_EQUAL(res.en, SimpleClass::VAL2);
		CHECK_EQUAL(res.list[0], 0);
		CHECK_EQUAL(res.list[1], 1);
		CHECK_EQUAL(res.list[2], 2);
		CHECK_EQUAL(res.list2.count(), 3);
		CHECK_EQUAL(res.list2[0].x, 0);
		CHECK_EQUAL(res.list2[1].x, 1);
		CHECK_EQUAL(res.list2[2].x, 2);
		CHECK_EQUAL(res.list3.count(), 3);
		CHECK(res.list3[0]);
		CHECK_EQUAL(res.list3[0]->x, 0);
		CHECK(res.list3[1]);
		CHECK_EQUAL(res.list3[1]->x, 1);
		CHECK(res.list3[2]);
		CHECK_EQUAL(res.list3[2]->x, 2);
		CHECK_EQUAL(res.ref, &res.list2[1]);
	}
	catch(Exception& exn) {
		cerr << "ERROR: " << exn.message() << io::endl;
	}
TEST_END


// Avoid impact of template predefinition
SERIALIZE(MySubClass)
SERIALIZE(MyClass)
SERIALIZE(ItemClass)
SERIALIZE_EXTENDED(Item2Class, ItemClass)
SERIALIZE(SimpleClass)
