/*
 * $Id$
 * Copyright (c) 2004, Alfheim Corporation.
 *
 * sllist.h -- single link list interface.
 */

#include <elm/inhstruct/SLList.h>

namespace elm { namespace inhstruct {


/**
 * @class SLNode
 * Single link node for SLList. It represents the nodes of the SLList implementation.
 * It is usally extended for getting real user nodes.
 */

/**
 * @class SLList
 * This class implement n inherited single-link list data structure. It contains SLNode nodes that
 * must be extened for containing user information.
 */

/**
 * Find the last node.
 * @return Last node of the list.
 * @warning Remark that this method is really inefficient. If you have to perform this task too often,
 * please revert to other data structure.
 */
SLNode *SLList::last(void) const {
	if(!fst)
		return 0;
	else {
		SLNode *node = fst;
		while(node->next())
			node = node->next();
		return node;
	}
}

/**
 * Count the nodes in the list.
 * @return Count of nodes in the list.
 */
int SLList::count(void) const {
	int cnt = 0;
	for(SLNode *node = fst; node; node = node->next())
		cnt++;
	return cnt;
}

/**
 * Add a node to the end of the list.
 * @param node Node to add at end.
 * @warning Remark that this method is really inefficient. If you have to perform this task too often,
 * please revert to other data structure.
 */
void SLList::addLast(SLNode *node) {
	if(!fst)
		addFirst(node);
	else
		last()->insertAfter(node);
}

/**
 * Remove the last node of the list.
 * @warning Remark that this method is really inefficient. If you have to perform this task too often,
 * please revert to other data structure.
 */
void SLList::removeLast(void) {
	
	// Find the last and its previous
	SLNode *node = fst, *prv = 0;
	while(node->next()) {
		prv = node;
		node = node->next();
	}
	
	// Remove the node
	if(prv)
		prv->removeNext();
	else
		fst = fst->next();
}

} }	// elm::namespace
