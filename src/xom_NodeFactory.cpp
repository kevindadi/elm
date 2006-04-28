/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * src/xom_NodeFactory.cpp -- XOM NodeFactory class implementation.
 */

#include <assert.h>
#include <libxml/tree.h>
#include <elm/xom/NodeFactory.h>
#include <elm/xom/Document.h>

namespace elm { namespace xom {

/**
 * @class NodeFactory NodeFactory.h "elm/xom.h"
 * Used for building nodes during a load.
 */


/**
 * Default node factory.
 */
NodeFactory NodeFactory::default_factory;


Attribute *NodeFactory::makeAttribute(void *node) {
	assert(0);
}

Comment *NodeFactory::makeComment(void *node) {
	assert(0);
}


/**
 * Build a document from an input stream.
 * @param node	Node used by the parser.
 */
Document *NodeFactory::makeDocument(void *node) {
	return new Document(node, this);
}

ProcessingInstruction *NodeFactory::makeProcessingInstruction(void *node) {
	assert(0);
}

Element	*NodeFactory::makeRootElement(void *node) {
	assert(0);
}

Text *NodeFactory::makeText(void *node) {
	assert(0);
}

} } // elm::xom
