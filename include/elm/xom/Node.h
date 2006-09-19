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
class NodeFactory;
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
	friend class Elements;
	void *node;
	Node(void *_node);
	Node *make(void *node);
	inline Node *get(void *node);
	Node *internCopy(void);
	Node *internGetChild(int index);
	int internGetChildCount(void);
	String internGetValue(void);
	String internToXML(void);
public:
	inline void *getNode(void) const;

	kind_t kind(void) const;
	virtual Node *copy(void) = 0;
	void detach(void);
	bool equals(const Node * node) const;
	virtual String getBaseURI(void);
	virtual Node *getChild(int index) = 0;
	virtual int getChildCount(void) = 0;
	virtual Document *getDocument(void);
	virtual ParentNode *getParent(void);
	virtual String getValue(void) = 0;
	virtual Nodes *query(const String& xpath);
	virtual Nodes *query(const String& xpath, XPathContext *context);
	virtual String toXML(void) = 0;
};


// Node inlines
inline void *Node::getNode(void) const {
	return node;
}

} } // elm::xom

#endif // ELM_XOM_NODE_H
