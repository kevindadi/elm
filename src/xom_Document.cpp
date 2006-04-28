/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom_Document.cpp -- XOM Document class implementation.
 */

#include "xom_macros.h"
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
	assert(DOC(node)->type == XML_DOCUMENT_NODE);
	assert(fact);
}


Document::Document(Document *document): ParentNode(0) {
	assert(0);
}

Document::Document(Element *root_element): ParentNode(0) {
	assert(0);
}
	
Node *Document::copy(void) {
	assert(0);
}

String Document::getBaseURI(void) {
	assert(0);
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
	assert(0);
}

Node *Document::removeChild(int position) {
	assert(0);
}

Node *Document::removeChild(Node *child) {
	assert(0);
}

void Document::replaceChild(Node *old_child, Node *new_child) {
	assert(0);
}

void Document::setBaseURI(String uri) {
	assert(0);
}

void Document::setRootElement(Element *root) {
	assert(0);
}

String Document::toString(void) {
	assert(0);
}

String Document::toXML(void) {
	assert(0);
}

} } // elm::xom
