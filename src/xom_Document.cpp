/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom_Document.cpp -- XOM Document class implementation.
 */

#include "xom_macros.h"
#include <elm/assert.h>
#include <elm/xom/Document.h>

#define NODE(p) ((xmlNodePtr)(p))
#define DOC(p) ((xmlDocPtr)(p))

namespace elm { namespace xom {

/**
 * @class Document Document.h "elm/xom.h"
 * The root object of an XML document.
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

Document::Document(Element *root_element): ParentNode(0) {
	ASSERTP(0, "unsupported");
}
	
Node *Document::copy(void) {
	ASSERTP(0, "unsupported");
}

String Document::getBaseURI(void) {
	ASSERTP(0, "unsupported");
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
}

Node *Document::removeChild(int position) {
	ASSERTP(0, "unsupported");
}

Node *Document::removeChild(Node *child) {
	ASSERTP(0, "unsupported");
}

void Document::replaceChild(Node *old_child, Node *new_child) {
	ASSERTP(0, "unsupported");
}

void Document::setBaseURI(String uri) {
	ASSERTP(0, "unsupported");
}

void Document::setRootElement(Element *root) {
	ASSERTP(0, "unsupported");
}

String Document::toString(void) {
	ASSERTP(0, "unsupported");
}

String Document::toXML(void) {
	ASSERTP(0, "unsupported");
}

} } // elm::xom
