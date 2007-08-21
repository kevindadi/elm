/*
 *	$Id$
 *	Generic data structures documentation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2005-07, IRIT UPS.
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

namespace elm { namespace genstruct {
 
/**
 * @defgroup gen_datastruct Generic Data Structures
 * 
 * ELM provides a collection of genericity/template based data structures.
 * 
 * @section tables Tables
 * 
 * ELM provides a wrapper around the C++ rough implementation of table. This
 * may be read-only table (@ref Table) or allocated mutable tables
 * (@ref AllocatedTable).
 * 
 * Beside, there are also table with specific management:
 * @li @ref Vector -- a simple and fast extensible table,
 * @li @ref FragTable -- a fast extensible table for big number of items
 * with a fast access,
 * @li @ref VectorQueue -- a @ref Vector based queue.
 * 
 * A very convenient table in the @ref HashTable that implements the
 * @ref concept::Map concept.
 * 
 * @section llists Linked Lists
 * 
 * There are two kinds of list:
 * @li @ref SLList -- single link list (unidirectionnal traversal),
 * @li @ref DLList -- double link list (bidirectionnal traversal).
 * 
 * @section trees Trees
 * 
 * Tree data structures with different implementation flavors may be found.
 * 
 * The simplest one is the @ref BinTree binary tree with a specialized sorted
 * version, @ref SortedBinTree.
 * 
 * A generic n-ary tree implementation is provided by the @ref Tree class while
 * the @ref DAGNode provides an iffecient implementation of tree-like Directed
 * Acyclic Graphs. 
 */

} } // elm::genstruct