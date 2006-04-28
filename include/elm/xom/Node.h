/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom/Node.h -- XOM class interface.
 */
#ifndef ELM_XOM_NODE_H
#define ELM_XOM_NODE_H

#include <assert.h>
#include <elm/xom/String.h>

namespace elm { namespace xom {

// Predeclaration
class Node;
class Document;
class ParentNode;
class Nodes;
class XPathContext;
class Builder;

// Node class
class Node {
public:
	typedef enum kind_t {
		NONE = 0,
		ELEMENT,
		DOCUMENT,
		TEXT,
		COMMENT,
		ATTRIBUTE,
		PROCESSING_INSTRUCTION,
		DOCTYPE,
		NAMESPACE
	} kind_t;
protected:
	friend class Builder;
	void *node;
	inline Node(void *_node);
	Node *make(void *node);
	inline Node *get(void *node);
public:

	kind_t kind(void) const;
	virtual Node *copy(void) = 0;
	void detach(void);
	bool equals(const Node * node);
	virtual String getBaseURI(void) = 0;
	virtual Node *getChild(int index) = 0;
	virtual int getChildCount(void) = 0;
	Document *getDocument(void);
	ParentNode *getParent(void);
	virtual String getValue(void) = 0;
	Nodes *query(const String& xpath, XPathContext *context);
	String toXML(void);
};


// Node inlines
inline Node::Node(void *_node): node(_node) {
	assert(node);
}

} } // elm::xom

#endif // ELM_XOM_NODE_H
