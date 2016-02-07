/*
 *	json module test
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

#include <elm/json.h>
#include <elm/util/test.h>

using namespace elm;

TEST_BEGIN(json)

	// empty object
	{
		StringBuffer buf;
		json::Saver save(buf.stream());
		save.beginObject();
		save.endObject();
		save.close();
		string r = buf.toString();
		CHECK_EQUAL(r, string("{}"));
	}

	// simple pairs
	{
		StringBuffer buf;
		json::Saver save(buf.stream());
		save.beginObject();
		save.addField("1");
		save.put(1);
		save.addField("2");
		save.put(2);
		save.endObject();
		save.close();
		string r = buf.toString();
		CHECK_EQUAL(r, string("{\"1\":1,\"2\":2}"));
	}

	// pair with an empty array
	{
		StringBuffer buf;
		json::Saver save(buf.stream());
		save.beginObject();
		save.addField("a");
		save.beginArray();
		save.endArray();
		save.endObject();
		save.close();
		string r = buf.toString();
		CHECK_EQUAL(r, string("{\"a\":[]}"));
	}

	// pair with an array
	{
		StringBuffer buf;
		json::Saver save(buf.stream());
		save.beginObject();
		save.addField("a");
		save.beginArray();
		save.put(0);
		save.put(1);
		save.put(2);
		save.put(3);
		save.endArray();
		save.endObject();
		save.close();
		string r = buf.toString();
		CHECK_EQUAL(r, string("{\"a\":[0,1,2,3]}"));
	}

	TEST_END


