/*
 * $Id$
 * Copyright (c) 2006, IRIT-UPS.
 *
 * test/test_serial.cpp -- serial module test.
 */

#include <elm/util/test.h>
#include <elm/io.h>
#include <elm/xom.h>
#include <elm/serial/interface.h>
#include <elm/serial/implement.h>
#include <elm/serial/XOMUnserializer.h>
#include <elm/serial/TextSerializer.h>

using namespace elm;

// MySubClass class
class MyClass;
class MySubClass {
	SERIALIZABLE
	char c;
	MyClass *back;
public:
	MySubClass(void) { }
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
	MyClass(void) { };
	MyClass(int _x): x(_x), sub('a', this), sub2(new MySubClass('b', 0)) { };
};

SERIALIZE(MyClass, FIELD(x); FIELD(sub); FIELD(sub2))


// SimpleClass
class SimpleClass {
	SERIALIZABLE
public:
	int x;
	char c;
	double f;
	CString str;
	SimpleClass(void): x(111), c('a'), f(0.1), str("ok") { };
};
SERIALIZE(SimpleClass, FIELD(x); FIELD(c); FIELD(f); FIELD(str))


// Entry point
void test_serial(void) {
	
	// Serialize text
	elm::serial::TextSerializer serialize;
	MyClass my_object(666);
	serialize << my_object;
	serialize.close();
	
	// Unserialize XML
	serial::XOMUnserializer unser("unser.xml");
	SimpleClass res;
	unser >> res;
	cout << "res.x = " << res.x << io::endl;
	cout << "res.c = " << res.c << io::endl;
	cout << "res.f = " << res.f << io::endl;
	cout << "res.str = " << res.str << io::endl;
}
