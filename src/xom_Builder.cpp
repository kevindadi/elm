/*
 * $Id$
 * Copyright (c) 2006, IRIT UPS.
 *
 * elm/xom_Builder.cpp -- XOM Builder class implementation.
 */

#include <libxml/parser.h>
#include <libxml/tree.h>
#include <elm/xom/Builder.h>
#include <elm/xom/NodeFactory.h>
#include <elm/xom/Document.h>

namespace elm { namespace xom {

/**
 * @class Builder
 * A builder may be used for building or loading an XML document.
 */


/**
 * Default factory.
 */
NodeFactory Builder::default_factory;


/**
 * Create a builder with the default node factory and no validation.
 */
Builder::Builder(void): validate(false), fact(&default_factory) {
}


/**
 * Build a document from the given system identifier.
 * @param system_id	System identifier to get the document from.
 * @return			Read document or NULL if there is an error.
 */
Document *Builder::build(CString system_id) {
	
	// Read the file
	xmlDoc *xml_doc = xmlReadFile(system_id, NULL,
		(validate ? XML_PARSE_DTDVALID : 0)
		| XML_PARSE_NOENT
		| XML_PARSE_NOBLANKS
		| XML_PARSE_NOCDATA);
	if(!xml_doc)
		return 0;
		
	// Build the document
	return fact->makeDocument(xml_doc);
}

} }	// elm::xom

