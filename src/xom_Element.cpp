/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom_Element.cpp -- XOM Element class implementation.
 */

#include "xom_macros.h"
#include <elm/xom/Element.h>

#define NODE(p) ((xmlNodePtr)(p))

namespace elm { namespace xom {

/**
 * @class Element "Element.h" "elm/xom.h"
 * Represents an XML element.
 */


/**
 * Build an element from the parser representation.
 * @param node	Node in the parser representation.
 */
Element::Element(void *node): ParentNode(node) {
	assert(NODE(node)->type == XML_ELEMENT_NODE);
}

Element	*Element::shallowCopy(void) {
	assert(0);
}

Element::Element(Element *element): ParentNode(0) {
	assert(0);
}

Element::Element(String name): ParentNode(0) {
	assert(0);
}

Element::Element(String name, String uri): ParentNode(0) {
	assert(0);
}

void Element::addAttribute(Attribute *attribute) {
	assert(0);
}

void Element::addNamespaceDeclaration(String prefix, String uri) {
	assert(0);
}

void Element::appendChild(String text) {
	assert(0);
}

Node *Element::copy(void) {
	assert(0);
}

Attribute *Element::getAttribute(int index) {
	assert(0);
}

Attribute *Element::getAttribute(String name) {
	assert(0);
}

Attribute *Element::getAttribute(String localName, String ns) {
	assert(0);
}

int	Element::getAttributeCount(void) {
	assert(0);
}

String Element::getAttributeValue(String name) {
	assert(0);
}

String Element::getAttributeValue(String localName, String ns) {
	assert(0);
}

String Element::getBaseURI(void) {
	assert(0);
}

Elements *Element::getChildElements(void) {
	assert(0);
}

Elements *Element::getChildElements(String name) {
	assert(0);
}

Elements *Element::getChildElements(String localName, String ns) {
	assert(0);
}

Element	*Element::getFirstChildElement(String name) {
	assert(0);
}

Element	*Element::getFirstChildElement(String localName, String ns) {
	assert(0);
}

String Element::getLocalName(void) {
	assert(0);
}

int	Element::getNamespaceDeclarationCount(void) {
	assert(0);
}

String Element::getNamespacePrefix(void) {
	assert(0);
}

String Element::getNamespacePrefix(int index) {
	assert(0);
}

String Element::getNamespaceURI(void) {
	assert(0);
}

String Element::getNamespaceURI(String prefix) {
	assert(0);
}

String Element::getQualifiedName(void) {
	assert(0);
}

String Element::getValue(void) {
	assert(0);
}

void Element::insertChild(String text, int position) {
	assert(0);
}

Attribute *Element::removeAttribute(Attribute *attribute) {
	assert(0);
}

Nodes *Element::removeChildren(void) {
	assert(0);
}

void Element::removeNamespaceDeclaration(String prefix) {
	assert(0);
}

void Element::setBaseURI(String uri) {
	assert(0);
}

void Element::setLocalName(String local_name) {
	assert(0);
}

void Element::setNamespacePrefix(String prefix) {
	assert(0);
}

void Element::setNamespaceURI(String uri) {
	assert(0);
}

String Element::toString(void) {
	assert(0);
}

String Element::toXML(void) {
	assert(0);
}

} } // elm::xom
