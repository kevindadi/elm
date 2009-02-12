/*
 *	$Id$
 *	xom::Serializer class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2009, IRIT UPS.
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

#include <elm/xom/Serializer.h>

namespace elm { namespace xom {

/**
 * Create a new serializer that uses the UTF-8 encoding.
 * @param out_stream	the output stream to write the document on
 */
Serializer::Serializer(io::OutStream& out)
:	_out(out),
	_encoding("UTF-8"),
	_line_separator("\n"),
	_indent(0),
	_max_length(0),
	_preserve(false),
	_normalize(false)
{
}

/**
 * Create a new serializer that uses the specified encoding. The encoding must be
 * recognized by the libxml.
 * @param out		the output stream to write the document on
 * @param encoding	the character encoding for the serialization
 */
Serializer::Serializer(io::OutStream& out, string encoding)
:	_out(out),
	_encoding(encoding),
	_line_separator("\n"),
	_indent(0),
	_max_length(0),
	_preserve(false),
	_normalize(false)
{	
}


/**
 * Flush the out stream.
 */
void Serializer::flush(void) {
	_out.flush();
}


/**
 * Returns the current column number of the output stream. This method useful for subclasses that implement
 * their own pretty printing strategies by inserting white space and line breaks at appropriate points.
 * Columns are counted based on Unicode characters, not UTF-8 chars. A surrogate pair counts as one character
 * in this context, not two. However, a character followed by a combining character (e.g. e followed by
 * combining accent acute) counts as two characters. This latter choice (treating combining characters
 * like regular characters) is under review, and may change in the future if it's not too big a performance hit.
 * @return	the current column number
 */
int Serializer::getColumnNumber(void) {
	return 0;
}

/**
 * Writes the current line break string onto the underlying output stream
 * and indents as specified by the current level and the indent property.
 */
void Serializer::breakLine(void) {
	_out << _line_separator;
}


/**
 * Writes an attribute in the form name="value". Characters in the attribute value are escaped as necessary.
 * @param attribute the Attribute to write
 */
void Serializer::write(Attribute *attribute) {
}


/*virtual void write(Comment *comment);
virtual void write(DocType *doctype);
virtual void write(Document *doc);
virtual void write(Element *element);
virtual void write(ProcessingInstruction *instruction);
virtual void write(Text *text);
virtual void writeAttributes(Element *element);
virtual void writeAttributeValue(const string& value);
virtual void writeChild(Node *node);
virtual void writeEmptyElementTag(Element *element);
virtual void writeEndTag(Element *element);
virtual void writeEscaped(const string& text);
virtual void writeNamespaceDeclaration(const string& prefix, const string& uri);
virtual void writeNamespaceDeclarations(Element *element);
virtual void writeRaw(const string& text);
virtual void writeStartTag(Element *element);
virtual void writeXMLDeclaration(void);*/

} } // elm::xom
