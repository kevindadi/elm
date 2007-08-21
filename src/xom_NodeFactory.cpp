/*
 *	$Id$
 *	xom::NodeFactory class interface
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

#include <elm/assert.h>
#include <libxml/tree.h>
#include <elm/xom/NodeFactory.h>
#include <elm/xom/Document.h>
#include <elm/xom/Element.h>
#include <elm/xom/Text.h>

namespace elm { namespace xom {

/**
 * @class NodeFactory
 * Used for building nodes during a load.
 * @ingroup xom
 */


/**
 * Default node factory.
 */
NodeFactory NodeFactory::default_factory;


Attribute *NodeFactory::makeAttribute(void *node) {
	ASSERTP(0, "unsupported");
}

Comment *NodeFactory::makeComment(void *node) {
	ASSERTP(0, "unsupported");
}


/**
 * Build a document from an input stream.
 * @param node	Node used by the parser.
 */
Document *NodeFactory::makeDocument(void *node) {
	return new Document(node, this);
}

ProcessingInstruction *NodeFactory::makeProcessingInstruction(void *node) {
	ASSERTP(0, "unsupported");
}


/**
 * Build an element from its low-level reference.
 * @param node	Low-level node reference.
 */
Element	*NodeFactory::makeElement(void *node) {
	return new Element(node);
}


/**
 * Build a text from its low-level node reference.
 * @param node	Low-level node reference.
 */
Text *NodeFactory::makeText(void *node) {
	return new Text(node);
}

} } // elm::xom
