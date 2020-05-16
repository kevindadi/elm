/*
 *	VarExpander class implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2019, IRIT UPS.
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

#include <elm/io/VarExpander.h>
#include <elm/io/BufferedOutStream.h>
#include <elm/sys/System.h>

namespace elm { namespace io {

/**
 * @class VarExpander
 * This class a character flow filter replacing symbol invocation by the symbol
 * value. Basically, a symbol invocation is of an escape character (default
 * to '$') followed by a brace open character (one of '(', '{'), the symbol
 * name and a brace close character (one of ')', '}'). This string is
 * replaced in the character flow with the string associated with the symbol.
 *
 * The association is implemented by a call to function VarExpander::resolve().
 * If required, the association is cached and no more call to this function
 * is performed for this symbol. To specialize the variable expansion, one
 * has to overload this function. The default implementation returns an
 * empty string.
 *
 * This class may be used as an OutStream or simply by passing a string and
 * getting the result from the function VarExpander::expand().
 *
 * The code below expands the variable of the chacter flow using OS
 * environment variables:
 * @code
 * class OSExpander: public io::VarExpander {
 * protected:
 * 	string resolve(string name, bool& rec) override {
 * 		return sys::System::getEnv(&name);
 * 	}
 * };
 *
 * OSExpander e;
 * sys::Path p = e.expand("${HOME}/mydir");
 *
 * @endcode
 *
 * @ingroup io
 */

/**
 * Default expander constructor: output is performed to starandard output.
 */
VarExpander::VarExpander(): VarExpander(io::out) {
}

/**
 * Expander constructor with the given output.
 * @param out	Output stream to use.
 */
VarExpander::VarExpander(OutStream& out):
	esc('$'),
	open("{("),
	close("})"),
	state(COPY),
	expected(0),
	_out(&out)
{ }

/**
 * @fn char VarExpander::escape() const;
 * Get escape character.
 * @return	Escape chacter.
 */

/**
 * @fn VarExpander& VarExpander::escape(char e);
 * Change the escape character.
 * @param e		new escape character.
 */

/**
 * @fn VarExpander& VarExpander::resetBrace();
 * Reset the list of supported open-close characters.
 */

/**
 * @fn VarExpander& VarExpander::brace(char o, char c);
 * Added the given set of brace characters.
 * @param o		Open brace character.
 * @param c		Close brace character.
 */

/**
 * Expand the given string.
 * @param s		String to expand.
 * @return		s with symbols expanded.
 */
string VarExpander::expand(string s) {
	StringBuffer b;
	OutStream *old = _out;
	_out = &b.stream();
	write(s.toCString().chars(), s.length());
	_out = old;
	b.flush();
	return b.toString();
}

///
int VarExpander::write(const char *buffer, int size) {
	for(int i = 0; i < size; i++) {
		int r = write(buffer[i]);
		if(r != 1)
			return i;
	}
	return size;
}

///
int VarExpander::write(char byte) {

	switch(state) {

	case COPY:
		if(byte == esc) {
			state = ESC;
			return 1;
		}
		else
			return _out->write(byte);

	case ESC:
		if(byte == esc)
			return _out->write(esc);
		else {
			int p = open.indexOf(byte);
			if(p < 0) {
				state = COPY;
				return _out->write(byte);
			}
			else {
				state = OPEN;
				name.reset();
				expected = close[p];
				return 1;
			}
		}

	case OPEN:
		if(byte != expected) {
			name << byte;
			return 1;
		}
		else {
			string n = name.toString();
			string x;
			auto v = map.get(n);
			if(v.isOne())
				x = *v;
			else {
				bool rec = true;
				x = resolve(n, rec);
				if(rec)
					map.put(n, x);
			}
			state = COPY;
			int r = _out->write(x.toCString().chars(), x.length());
			if(r != x.length())
				return -1;
			else
				return 1;
		}

	default:
		ASSERT(false);
		return -1;
	}
}

///
int VarExpander::flush(void) {
	return _out->flush();
}

///
CString VarExpander::lastErrorMessage(void) {
	return _out->lastErrorMessage();
}

///
bool VarExpander::supportsANSI() const {
	return _out->supportsANSI();
}

/**
 * This function has to be overridden to provide symbol definition.
 * The default implementation just returns the empty string.
 * @param name		Symbol name to look for.
 * @param record	If set to false, the symbol will not be cached.
 * @return			Symbol value corresponding to the given symbol name.
 */
string VarExpander::resolve(string name, bool& record) {
	return "";
}


/**
 * @class OSExpander
 * Variable expander replacing symbols by OS variables.
 * @ingroup io
 */

///
string OSExpander::resolve(string name, bool& record) {
	record = false;
	return sys::System::getEnv(name.toCString().chars());
}

/**
 * Expand the variable in the given string, replacing variable invocation
 * by OS variable values.
 * @param s	String to replace in.
 * @return	s with variable replaced.
 */
string expandOSVars(string s) {
	static OSExpander e;
	return e.expand(s);
}

} }		// elm::io

