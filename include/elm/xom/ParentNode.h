/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom/ParentNode.h -- XOM ParentNode class interface.
 */
#ifndef ELM_XOM_PARENT_NODE_H
#define ELM_XOM_PARENT_NODE_H

#include <elm/xom/Node.h>

namespace elm { namespace xom {

// ParentNode class
class ParentNode: public Node {
protected:
	inline ParentNode(void * node): Node(node) { };
public:
	virtual void appendChild(Node *child);
	virtual Node *getChild(int position);
	virtual int	getChildCount(void);
	virtual int	indexOf(Node *child);
	virtual void insertChild(Node *child, int position);
	virtual Node *removeChild(int position);
	virtual Node *removeChild(Node *child);
	virtual void replaceChild(Node *old_child, Node *new_child);
	virtual void setBaseURI(String URI) = 0;
};

} } // elm::xom

#endif	// ELM_XOM_PARENT_NODE_H
