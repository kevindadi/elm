/*
 *	$Id$
 *	xom::Document class interface
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006-07, IRIT UPS.
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

#include "xom_macros.h"
#include <elm/assert.h>
#include <elm/xom/Document.h>
#include <elm/xom/Element.h>
#include <elm/xom/NodeFactory.h>

#define NODE(p) ((xmlNodePtr)(p))
#define DOC(p) ((xmlDocPtr)(p))

namespace elm { namespace xom {

/**
 * @class Document Document.h "elm/xom.h"
 * The root object of an XML document.
 * @ingroup xom
 */


/**
 * Build a document from a reader node.
 * @param node	Parser node.
 */
Document::Document(void *node, NodeFactory *factory)
: ParentNode(node), fact(factory) {
	ASSERT(DOC(node)->type == XML_DOCUMENT_NODE);
	ASSERT(fact);
}


Document::Document(Document *document): ParentNode(0) {
	ASSERTP(0, "unsupported");
}

Document::Document(Element *root_element):
	ParentNode(xmlNewDoc((xmlChar *)"1.0")),
	fact(&NodeFactory::default_factory)
{
	ASSERTP(root_element, "null root element");
	setRootElement(root_element);
}

Node *Document::copy(void) {
	ASSERTP(0, "unsupported");
	return 0;
}

String Document::getBaseURI(void) {
	ASSERTP(0, "unsupported");
	return "";
}


/**
 * Get the root element of the document.
 * @return	Root element or null.
 */
Element *Document::getRootElement(void) {
	xmlNodePtr root = xmlDocGetRootElement(DOC(node));
	if(!root)
		return 0;
	return (Element *)get(root);
	
}

String Document::getValue(void) {
	ASSERTP(0, "unsupported");
	return "";
}

Node *Document::removeChild(int position) {
	ASSERTP(0, "unsupported");
	return 0;
}

Node *Document::removeChild(Node *child) {
	ASSERTP(0, "unsupported");
	return 0;
}

void Document::replaceChild(Node *old_child, Node *new_child) {
	ASSERTP(0, "unsupported");
}

void Document::setBaseURI(String uri) {
	ASSERTP(0, "unsupported");
}

void Document::setRootElement(Element *root) {
	ASSERTP(root, "null root");
	xmlDocSetRootElement(DOC(node), NODE(root->getNode()));
}

String Document::toString(void) {
	ASSERTP(0, "unsupported");
	return "";
}

String Document::toXML(void) {
	ASSERTP(0, "unsupported");
	return "";
}

} } // elm::xom
