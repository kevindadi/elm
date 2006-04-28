/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * src/xom_Node.cpp -- XOM Node class implementation.
 */

#include <assert.h>
#include <libxml/tree.h>
#include <elm/xom/Node.h>
#include <elm/xom/Document.h>

#define NODE(p) ((xmlNodePtr)(p))

namespace elm { namespace xom {

/**
 * @class Node
 * The base class of nodes of a XOM XML tree.
 * Refer to http://www.xom.nu/ for more information.
 */


/**
 * Build the XOM tree from the parser nodes.
 * @param node	Parser node.
 * @return		Matching XOM node if any.
 */
Node *Node::make(void *node) {
	NodeFactory *fact = (((Document *)(NODE(node)->doc->_private)))->fact;
	Node *result;
	switch(NODE(node)->type) {
	}
	NODE(node)->_private = result;
	return result;
}


/**
 * Get the kind of node.
 * @return	Kind of node.
 */
Node::kind_t Node::kind(void) const {
	static const kind_t kinds[] = {
		NONE,					// unused
		ELEMENT,				// XML_ELEMENT_NODE = 1
    	ATTRIBUTE,				// XML_ATTRIBUTE_NODE = 2
    	TEXT,					// XML_TEXT_NODE = 3
   		TEXT,					// XML_CDATA_SECTION_NODE = 4
    	NONE,					// XML_ENTITY_REF_NODE = 5
    	NONE,					// XML_ENTITY_NODE = 6
		PROCESSING_INSTRUCTION,	// XML_PI_NODE = 7
    	COMMENT,				// XML_COMMENT_NODE = 8
		DOCUMENT,				// XML_DOCUMENT_NODE = 9
    	NONE,					// XML_DOCUMENT_TYPE_NODE = 10
    	NONE,					// XML_DOCUMENT_FRAG_NODE = 11
    	NONE,					// XML_NOTATION_NODE = 12
    	NONE,					// XML_HTML_DOCUMENT_NODE = 13
    	NONE,					// XML_DTD_NODE = 14
    	NONE,					// XML_ELEMENT_DECL = 15
    	NONE,					// XML_ATTRIBUTE_DECL = 16
    	NONE,					// XML_ENTITY_DECL = 17
    	NONE,					// XML_NAMESPACE_DECL = 18
    	NONE,					// XML_XINCLUDE_START = 19
    	NONE,					// XML_XINCLUDE_END = 20
    	NONE					// XML_DOCB_DOCUMENT_NODE
	};
	
	assert(NODE(node)->type < sizeof(kinds) / sizeof(kind_t));
	return kinds[NODE(node)->type];
}

/*	virtual Node *copy(void) const = 0;
	void detach(void);
	bool equals(const Node * node) const;
	virtual CString getBaseURI(void) const = 0;
	virtual Node *getChild(int index) const = 0;
	virtual int getChildCount(void) const = 0;
	Document *getDocument(void) const;
	ParentNode *getParent(void) const;
	virtual String getValue(void) const = 0;
	Nodes *query(String& xpath, XPathContext *context) const;
	tring toXML(void) const;*/


	
} } // elm::xom
