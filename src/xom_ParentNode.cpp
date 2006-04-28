/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom_ParentNode.cpp -- XOM ParentNode class implementation.
 */

#include <elm/xom/ParentNode.h>

namespace elm { namespace xom {

/**
 * @class ParentNode
 * This class provides to the node facilities for containing children.
 */


/**
 * @fn ParentNode::ParentNode(void * node);
 * Build a node from a reader.
 * @param node	Node built by the reader.
 */


void ParentNode::appendChild(Node *child) {
	assert(0);
}

Node *ParentNode::getChild(int position) {
	assert(0);
}

int	ParentNode::getChildCount(void) {
	assert(0);
}

int	ParentNode::indexOf(Node *child) {
	assert(0);
}

void ParentNode::insertChild(Node *child, int position) {
	assert(0);
}

Node *ParentNode::removeChild(int position) {
	assert(0);
}

Node *ParentNode::removeChild(Node *child) {
	assert(0);
}

void ParentNode::replaceChild(Node *old_child, Node *new_child) {
	assert(0);
}

} } // elm::xom

