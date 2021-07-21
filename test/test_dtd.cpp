/*
 *	Test for dtd module.
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2016, IRIT UPS.
 *
 *	OTAWA is free software; you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation; either version 2 of the License, or
 *	(at your option) any later version.
 *
 *	OTAWA is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with OTAWA; if not, write to the Free Software
 *	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <elm/xom/dtd.h>
#include <elm/test.h>

using namespace elm;
using namespace dtd;


/// test 1
Element name("name", PCDATA);
Element session("session", EMPTY);
Attribute<CDATA> date(session, "date", "", REQUIRED);
Element training("training", (name, *session));
IDAttribute id(training, "id");
Attribute<CDATA> start(training, "start", "");

cstring test1 =
		"<?xml version=\"1.0\"?>\n"
		"<training id=\"ok\">\n"
		"<name>ok</name>\n"
		"<session date=\"0\"/>\n"
		"<session date=\"1\"/>\n"
		"</training>\n";

class MyFactory: public Factory {
public:
	void begin(Element& e) override {
		//cerr << "DEBUG: <" << e.name() << ">" << io::endl;
		if(e == training)
			_id = *id;
		else if(e == session)
			sessions.add(*date);
	}
	void end(Element& e) override {
		//cerr << "DEBUG: </" << e.name() << ">" << io::endl;
	}
	void getPCDATA(xom::String data) override {
		//cerr << "DEBUG: PCDATA = [" << data << "]" << io::endl;
		_name = data;
	}
	string _id;
	string _name;
	Vector<string> sessions;
};


/// Test 2
class Node {
public:
	Node(string i): id(i), ref(nullptr) { }
	string id;
	Node *ref;
};

Element node("node", EMPTY);
IDAttribute id1(node, "id", REQUIRED);
RefAttribute<Node> ref(node, "ref", FORWARD);
Element all("all", *node);

cstring test2 =
	"<?xml version=\"1.0\"?>\n"
	"<all>\n"
	"<node id=\"0\" ref=\"1\"/>\n"
	"<node id=\"1\" ref=\"0\"/>\n"
	"</all>\n";

class Factory2: public Factory {
public:
	void begin(Element& e) override {
		if(e == node) {
			nodes.add(new Node(*id1));
			if(*ref != nullptr)
				nodes.top()->ref = *ref;
		}
	}

	void *getRef(Element& e) override {
		//cerr << "DEBUG: getRef(" << e.name() << ")" << io::endl;
		if(e == node)
			return nodes.top();
		else
			return nullptr;
	}

	void *getPatchRef(/*Element& e,*/ AbstractAttribute& a) override {
		if(/*e == node &&*/ a == ref)
			return &nodes.top()->ref;
		else
			return nullptr;
	}

	void patch(AbstractAttribute& a, void *o, void *r) override {
		if(a == ref)
			*static_cast<Node **>(o) = static_cast<Node *>(r);
	}

	Vector<Node *> nodes;
};


// Test 3
cstring test3 =
		"<?xml version=\"1.0\"?>\n"
		"<T3>\n"
		"<A num=\"0\"/>\n"
		"<A num=\"1\"/>\n"
		"<B num=\"2\"/>\n"
		"<A num=\"3\"/>\n"
		"</T3>\n";

Element A("A", EMPTY);
Attribute<CDATA> A_num(A, "num", "");
Element B("B", EMPTY);
Attribute<CDATA> B_num(B, "num", "");
Element T3("T3", *(A | B));

class Item {
public:
	inline Item() { }
	inline Item(string n): num(n) { }
	string num;
};

class Factory3: public Factory {
public:
	void begin(Element& element) {
		//cerr << "DEBUG: <" << element.name() << ">" << io::endl;
		if(element == A)
			As.add(Item(*A_num));
		else if(element == B)
			Bs.add(Item(*B_num));
	}
	Vector<Item> As;
	Vector<Item> Bs;
};

TEST_BEGIN(dtd)
	{
		MyFactory factory;
		io::BlockInStream in(test1);
		training.parse(factory, in);
		CHECK_EQUAL(factory._id, string("ok"));
		CHECK_EQUAL(factory._name, string("ok"));
		CHECK_EQUAL(factory.sessions.length(), 2);
		if(factory.sessions.length() >= 1)
			CHECK_EQUAL(factory.sessions[0], string("0"));
		if(factory.sessions.length() >= 2)
			CHECK_EQUAL(factory.sessions[1], string("1"));
	}

	{
		Factory2 f;
		io::BlockInStream in(test2);
		all.parse(f, in);
		CHECK_EQUAL(f.nodes.length(), 2);
		if(f.nodes.length() == 2) {
			CHECK_EQUAL(f.nodes[0]->id, string("0"));
			CHECK_EQUAL(f.nodes[1]->id, string("1"));
			CHECK_EQUAL(f.nodes[1]->ref, f.nodes[0]);
			CHECK_EQUAL(f.nodes[0]->ref, f.nodes[1]);
		}
	}

	{
		Factory3 f;
		io::BlockInStream in(test3);
		T3.parse(f, in);
		CHECK_EQUAL(f.As.length(), 3);
		CHECK_EQUAL(f.Bs.length(), 1);
		if(f.As.length() == 3) {
			CHECK_EQUAL(f.As[0].num, string("0"));
			CHECK_EQUAL(f.As[1].num, string("1"));
			CHECK_EQUAL(f.As[2].num, string("3"));
		}
		if(f.Bs.length() == 1)
			CHECK_EQUAL(f.Bs[0].num, string("2"));
	}
TEST_END


