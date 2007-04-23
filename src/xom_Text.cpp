/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom/Node.h -- XOM Text class implementation.
 */

#include <elm/assert.h>
#include <elm/xom/Text.h>
#include "xom_macros.h"

namespace elm { namespace xom {

/**
 * @class Text
 * Node containing simple text.
 */


/**
 * Build a new text node.
 * @param data	Content of the text node.
 */
Text::Text(String data): Node(xmlNewText(data)) {
	ASSERT(node);
}


/**
 * Build a new text node by cloning an existing one.
 * @param text	Text node to clone.
 */
Text::Text(const Text *text): Node(xmlCopyNode(NODE(text->node), 1)) {
	ASSERT(node);
}


/**
 */
Node *Text::copy(void) {
	return new Text(this);
}


/**
 * Set the content of the text.
 * @param data	Text to put in.
 */
void Text::setValue(String data) {
	xmlNodeSetContent(NODE(node), data);
}


/**
 * Get the text of this node.
 * @return	Node text.
 */
String Text::getText(void) {
	return NODE(node)->content;
}


/**
 */
Node *Text::getChild(int index) {
	return internGetChild(index);
}


/**
 */
int Text::getChildCount(void) {
	return internGetChildCount();
}


/**
 */
String Text::getValue(void) {
	return internGetValue();
}


/**
 */
String Text::toXML(void) {
	return internToXML();
}

} } // elm::xom
