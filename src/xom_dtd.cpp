/*
 *	dtd module implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2020, IRIT UPS.
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

#include <elm/util/UniquePtr.h>
#include <elm/xom/dtd.h>

/**
 * @defgroup dtd DTD Support
 * [DTD](https://www.w3.org/XML/1998/06/xmlspec-report-19980910.htm) is a
 * format to describe the structure of XML files. This module not only
 * supports the description of XML but provides also a parser based on this
 * description.
 *
 * Basically, the DTD is made of two types of descriptions:
 * * The description of XML elements by their name, their attributes and
 *   their content.
 * * The description of the element attributes based on their name, their
 *   default value if any and some flags like REQUIRED (for required attributes).
 *
 * The content of the elements may be made of simple text or other elements.
 * This content can be described like regular expressions, that is as
 * sequences, alternative, repetitions or optional elements.
 *
 * @par Usage
 *
 * Let the DTD below:
 * ```
 * <!ELEMENT training (name,session*)>
 * <!ATTLIST training
 * 		id    REQUIRED CDATA
 * 		start CDATA
 * 		end   CDATA>
 * <!ELEMENT name (#PCDATA)>
 * <!ELEMENT session (EMPTY)>
 * <!ATTLIST date REQUIRED CDATA>
 * ```
 *
 * The equivalent with the DTD module is:
 * ```{cpp}
 * #include <elm/xom/dtd.h>
 * using namespace dtd;
 *
 * Element name("name", PCDATA);
 * Element session("session", EMPTY);
 * Att
 * 		date<CDATA>(session, "start", "", REQUIRED);
 * Element training("name", (name, *session));
 * Att
 * 		id<CDATA>(session, "start", "", REQUIRED),
 * 		start<CDATA>(session, "start"),
 * 		end<CDATA>(session, "end");
 * ```
 * Then to parse XOM document, one has only to write:
 * ```{cpp}
 * 	xom::Document *doc = ...;
 * 	try {
 * 		MyFactory factory;
 *		training.parse(factory, doc);
 *		use(factory.training);
 * 	}
 * 	catch(dtd::Exception& e) {
 * 		cerr << "ERROR: " << e.message() << io::endl;
 * 	}
 * ```
 *
 * This last example shows the use of another structure named
 * a Factory. A factory is an interface by the user of dtd
 * module to react to the element found in the XML document
 * and to let the application to build a data structure
 * corresponding to the parsed document.
 *
 * Continuing the example, the factory could be:
 * ```{cpp}
 *
 * class TrainingFactory: public dtd::Factory {
 * public:
 * 	void begin(dtd::Element& e) {
 *		if(e == training)
 *			training = new Training(*id, *start, *end);
 * 		else if(e == name)
 *			training->setName(*PCDATA);
 * 		else if(e == session) {
 * 			cur = new Session(*date);
 * 			training.add(cur);
 * 		}
 * 	}
 *
 * 	void getPCDATA(dtd::Element& e, xom::String s) {
 * 		if(e == name)
 * 			training->setName(s);
 * 	}
 *
 * 	Training *training;
 * };
 * ```
 * As shown in the example above, the function begin() called each time
 * an element is found. Thanks to the element parameter, the corresponding
 * action can be undertaken: build a Training object, recording the name
 * or build a session object.
 *
 * One can also observe that attributes and PCDATA records the actual
 * value they get at the begin() function call time and this value can
 * be accessed using the "*" operator.
 *
 * @par Reference
 *
 * Base classes encompass:
 * * `otawa::dtd::Content` - to describe a the content of an element.
 * * `otawa::dtd::Element` - to describe an element (that is also a dtd::Content).
 * * `otawa::dtd::Att` - to describe an attribute.
 *
 * dtd module provides also support for identifiers and references with
 * the classes:
 * * otawa::dtd::IDAtt - attribute representing an identifier.
 * * otawa::dtd::RefAtt<T> - attribute representing a reference.
 *
 * To support identifiers, the factory must be able to return a pointer to an
 * object that supports an identifier (function Factory::getRef()). In turn,
 * a reference attribute will store this object pointer when the referenced
 * identifier is resolved.
 *
 * otawa::dtd::RefAtt<T> supports also forward references (when the flag FORWARD is
 * set). In this case, if the reference cannot be resolved, it will store
 * a memo with an application object to patch obtained by a call to
 * Factory::getPatchRef(). Then when the identifier will be resolved,
 * the parser will automatically call Factory::patch() for each forward
 * reference with the patch object as parameter to let the application
 * to perform the fix.
 *
 * The content of an element may be made of:
 * * a otawa::dtd::Element itself (causing call to Factory::begin()),
 * * otawa::dtd::PCDATA to accept free text (causing call to Factory::getPCDATA()),
 * * otawa::dtd::ANY to accept anything (causing call to Factory::getAny()),
 * * otawa::dtd::Seq to accept a sequence of two contents,
 * * otawa::dtd::Alt to accept an alternative between two contents,
 * * otawa::dtd::Repeat to accept zero or more occurrences of a content,
 * * otawa::dtd::Opt to accept zero or one occurrence of a content.
 *
 * A simpler way to use Seq, Alt and Repeat contents is to use the
 * corresponding operators:
 * * ',' or '&' for a sequence
 * * '|' or '+' for an alternative,
 * * '*' (prefixed) for a repeat,
 * * '!' (prefixed) for an optional content.
 */

namespace elm { namespace dtd {

/**
 * @class Exception;
 * Exception thrown when an error in DTD parsing arises.
 * @ingroup dtd
 */

///
Exception::Exception(xom::Element *element, const string& message)
	: elm::MessageException(_ << element->getDocument()->getBaseURI() << ':' << element->line() << ": " << message)
	  { }

/**
 * @class Parser;
 * Parser for DTD module.
 * @ingroup dtd
 */

///
Parser::Parser(Factory& factory, Element& element, t::uint32 flags)
		: _fact(factory), _elt(element), _flags(flags), _last_error(nullptr) { }

/**
 * @fn bool Parser::doesCrop() const;
 * Check the blank cropping option.
 * @return	True if blank cropping is activated.
 */

/**
 * @fn Factory& Parser::factory(void) const;
 * Get the factory used by the parser.
 * @return	Used factory.
 */

/**
 * @fn Element& Parser::element(void) const;
 * Get the current DTD element.
 * @return	Current DTD element.
 */

/**
 * @fn Option<xom::String> Parser::get(xom::String name) const;
 * Get an attribute value in the current XML element. This function can only
 * be called if the current XML node is an element.
 * @param name	Attribute name.
 * @return		Attribute value.
 */

/**
 * @fn xom::Element *Parser::asElement() const;
 * Get the current node as an element.
 * @return	Current element.
 */

/**
 * @fn void Parser::raise(const string& msg) const;
 * Throw an exception on the current node with the given message.
 * @param msg	Message of the exception.
 */

/**
 * @fn void Parser::fail(const string& msg) const;
 * Throw an exception for failure on the last recorded element.
 * @param msg	Message of the exception.
 */

/**
 * @fn void Parser::recordError();
 * Record the current node as supporting an error.
 */

/**
 * @fn bool Parser::ended() const;
 * Test if the iteration on the children of the current parent element
 * is ended.
 * @return True if the children iteration is at the end, fals else.
 */

/**
 * @fn xom::Node *Parser::current(void) const;
 * Get the current XML node.
 * @return	Current XML node.
 */

/**
 * @fn void Parser::next(void);
 * Move to the next child node.
 */

/**
 * @fn mark_t Parser::mark(void);
 * Get a mark on the current position.
 * @return	Current position mark.
 */

/**
 * @fn bool Parser::backtrack(mark_t mark);
 * Back track to a previously marked position.
 * @param mark	Position mark to bcktrak to.
 */

/**
 * @fn void Parser::push(Element& element);
 * Enter in the given element. The position is automatically
 * set on the first child node of the element.
 * @param element	Element to push.
 */

/**
 * @fn void Parser::pop(void);
 * Leave the current element to its parent.
 */

/**
 * @fn bool Parser::hasID(xom::String id) const;
 * Test if the given identifier is already assigned.
 * @return	True if the identifier is assigned, false else.
 */

/**
 * @fn void *Parser::getID(xom::String id) const;
 * Get the value associated with the given identifier.
 * @param id	Looked identifier.
 * @return		Pointer corresponding to the identif if any, null else.
 */

/**
 * @fn void Parser::addID(xom::String id);
 * Record the assignment of the pointer p to the identifier id and, possibly,
 * patch any pending reference.
 * @param id	Identifier to assign to.
 * @param p		Pointer to assign.
 */

/**
 * Begin the given element (and move to first child).
 * @param element	Begun element.
 */
void Parser::begin(Element& element) {

	// invoke the callback
	factory().begin(element);

	// call the postpone attributes
	for(auto att: _posts)
		att->postprocess(*this);
	_posts.clear();

	// start a new context
	_last_error = static_cast<xom::Element *>(cur.node);
	stack.push(cur);
	cur.i = 0;
	cur.elt = &element;
	setNode();
}

/**
 * End the current element.
 */
void Parser::end(bool success) {

	// leave the current context
	auto elt = cur.elt;
	cur = stack.pop();

	// manage advance
	if(!success)
		factory().backtrack(*elt);
	else {
		factory().end(*elt);
		next();
	}
}

/**
 * Declare a new identifier and possibly resolves several pending references.
 * @param id		Set ID.
 * @param element	Element where the ID is defined.
 */
void Parser::recordID(xom::String id, Element& element) {
	auto p = factory().getRef(element);
	_map.put(id, p);
	if(_patches.hasKey(id)) {
		for(const auto& b: _patches.fetch(id))
			factory().patch(*b.attr, b.object, p);
		_patches.remove(id);
	}
}

/**
 * Record a patch for a forward reference attribute that is unresolved.
 * @param id		Forward reference identifier.
 * @param attr		Attribute containing the forward reference identifier.
 */
void Parser::recordPatch(xom::String id, AbstractAttribute& attr) {
	auto p = factory().getPatchRef(attr);
	_patches.fetch(id).add(backpatch_t(&attr, p, asElement()));
}


/**
 * Parse the given XML element.
 * @param xelt		XML element to parse.
 * @throw Exception	If there is an error.
 */
void Parser::parse(xom::Element *xelt) {

	// clear the parser
	_patches.clear();
	_posts.clear();

	// prepare parsing
	_elt.reset();
	cur.elt = &_elt;
	cur.i = 0;
	cur.node = xelt;
	_last_error = xelt;

	// perform parsing
	if(!_elt.parse(*this))
		fail("cannot parse.");

	// check pending references
	if(!_patches.isEmpty()) {
		auto f = _patches.begin();
		throw Exception(
			(*f).first().xelt,
			_ << "some references are pending as " << f.key());
	}
}

/**
 * Test if the current node is empty, that is only composed of spaces.
 * @return	True if the current node is empty, false else.
 */
bool Parser::isEmpty() {
	if(cur.node->kind() != xom::Node::TEXT)
		return false;
	else {
		xom::String t = static_cast<xom::Text *>(cur.node)->getText();
		for(int i = 0; i < t.length(); i++)
			switch(t[i]) {
			case ' ':
			case '\t':
			case '\v':
			case '\n':
				continue;
			default:
				return false;
			}
		return true;
	}
}

/**
 * Look for the current node in the parent element children.
 */
void Parser::setNode() {
	if(!stack.isEmpty())
		while(cur.i < parent()->getChildCount()) {
			cur.node = parent()->getChild(cur.i);
			if(!doesCrop() || !isEmpty())
				return;
			cur.i++;
		}
	cur.node = nullptr;
}


/**
 * @class Factory;
 * A factory is an interface with the DTD parser to let the application
 * build its internal data structure the read XML elements.
 *
 * Each time an
 * element is found, the begin() function is called and the DTD attributes
 * contains the element attribute values. When the element is exited, an
 * end() is called. backtrack() is called if an error is found in the current
 * element to let the application clean up its internal data structure.
 *
 * If the XML identifier/reference is used, a pointer to the application
 * internal data structure is obtained, when an ID attribute is found, by
 * a call to getRef().
 *
 * @ingroup dtd
 */

///
Factory::~Factory(void) { }

/**
 * Called each time an element is entered. At this time, the attribute has
 * been initialized and their value can be used.
 * @param	Entered element.
 */
void Factory::begin(Element& element) {
}

/**
 * Called each time an element is completed.
 * @param element	Completed element.
 */
void Factory::end(Element& element) {
}

/**
 * Called when the analysis of an element has failed. Its allocated
 * resources can now be released. The element attributes may have their
 * value overwritten in the use in other elements.
 * @param element	Failed element.
 */
void Factory::backtrack(Element& element) {
}

/**
 * This function is called to get a reference on the current element.
 * It is called after an begin() and if one of the attribute of the
 * element is a reference.
 * @param element	Current element.
 * @return			Pointer identifying the current element.
 */
void *Factory::getRef(Element& element) {
	return nullptr;
}

/**
 * Function called when the CDATA of an element is parsed, to pass the found
 * text to the application.
 * @param data	CDATA found in the current element.
 */
void Factory::getPCDATA(xom::String data) {
}

/**
 * Function called to perform a backpatch. A backpatch is needed when a
 * reference attribute is treated with a forward reference. As the
 * reference cannot be processed immediately (the reference object is not
 * already defined), this reference is recorded and a call to this
 * function is performed as soon as the reference can be solved.
 *
 * The default implementation does nothing.
 * @param attr		DTD attribute corresponding to the reference to patch.
 * @param object	Object obtained by a call to getPatchRef().
 * @param ref		Solved reference to patch.
 */
void Factory::patch(AbstractAttribute& attr, void *object, void *ref) {
}

/**
 * This function is called to get a patch object for non-resolved forward
 * references. The returned object will then be used to patch the missing
 * reference when the function patch() is called.
 *
 * The default implementation returns a null pointer.
 * @param attr		DTD reference attribute that is unresolved.
 * @return			Object passed back at patch time.
 */
void *Factory::getPatchRef(AbstractAttribute& attr) {
	return nullptr;
}

/**
 * Function called when an ANY content is parsed. It is called for XML node
 * composing the ANY content.
 * @param node	Found node.
 */
void Factory::getAny(xom::Node *node) {
}



/**
 * @class AbstractAttribute;
 * This class is the base class of DTD attributes. It provides basic facilities
 * to describe an XML attribute: name and flags.
 *
 * The following flags are supported:
 * * AbstractAttribute::REQUIRED
 * * AbstractAttribute::STRICT
 *
 * @ingroup dtd
 */

/**
 * @var AbstractAttribute::REQUIRED;
 * Attribute flag meaning that the attribute is required to parse the element containing it.
 */

/**
 * @var AbstractAttribute::STRICT;
 * Attribute flag meaning that an error in the attribute parsing stops
 * the parsing of the whole document and raises an error.
 */

/**
 * Attribute constructor.
 * @param element	Parent element.
 * @param name		Attribute name.
 * @param flags		OR'ed combination of REQUIRED and STRICT.
 */
AbstractAttribute::AbstractAttribute(Element& element, xom::String name, t::uint32 flags)
: _elt(element), _name(name), _flags(flags), _set(false) {
	element.attrs.add(this);
}

///
AbstractAttribute::~AbstractAttribute(void) { }

/**
 * @fn xom::String AbstractAttribute::name(void) const;
 * Get the name of the attribute.
 * @return	Attribute name.
 */

/**
 * @fn bool AbstractAttribute::isRequired(void) const;
 * Test if the attribute is required.
 * @return	True if the attribute is required, false else.
 */

/**
 * @fn bool AbstractAttribute::isStrict(void) const;
 * Test if the attribute is strict.
 * @return	True if the attribute is strict, false else.
 */

/**
 * @fn bool AbstractAttribute::isSet() const;
 * Test if the attribute has been set.
 * @return	True if the attribute is set, false else.
 */

/**
 * Parse the attribute from the current element in the parser.
 * The default implementation look for the attribute. If found, the
 * function process() is called with the attribute value. Else adjust
 * the return value according to the required property.
 * @param parser	Current parser.
 * @return			True if the parsing is successful, false else.
 */
bool AbstractAttribute::parse(Parser& parser) {
	Option<xom::String> val = parser.get(_name);
	if(val.some()) {
		_set = true;
		return process(parser, val);
	}
	else {
		reset();
		return !isRequired();
	}
}

/**
 * This function is called by parse() if a value is found for the attribute.
 * The role of this function is to process the found value.
 * The default implementation does nothing but it can overridden.
 */
bool AbstractAttribute::process(Parser& parser, xom::String value) {
	return true;
}

/**
 * Function called to reset the value stored in the attribute.
 * The default implementation does nothing but it can be overridden.
 */
void AbstractAttribute::reset() {
	_set = false;
}

/**
 * Function called after the call to Factory::begin() for the element
 * containing the attribute, if it has been recorded with Parser::addPost().
 * It is used for attributes requiring the reference to the application
 * current object like identifiers or forward references.
 *
 * The default implementation does nothing.
 * @param parser	Current parser.
 */
void AbstractAttribute::postprocess(Parser& parser) {
}


/**
 * @class Content;
 * This abstract class represents the contents of an XML element. It provides
 * basically two function: parse() to parse an XML element content and reset()
 * to reset the attributes used in the content.
 * @ingroup dtd
 */
Content::~Content(void) { }

/**
 * @fn void Content::reset();
 * Called to reset the state of the content internals.
 */

/**
 * @fn bool Content::doParse(Content& content, Parser& parser);
 * For internal use only.
 */

/**
 * @fn bool Content::parse(Parser& parser);
 * Parse the content of the current element in the parser.
 * @param parser	Parser to parse with.
 */


///
class EmptyContent: public Content {
protected:
	void reset() override { };
	bool parse(Parser& parser) override {
		Parser::mark_t m = parser.mark();
		for(; !parser.ended(); parser.next())
			if(!parser.isEmpty()) {
				parser.backtrack(m);
				return false;
			}
		return true;
	}
};
static EmptyContent _empty;

/**
 * Content ensuring that the content of an XML element is empty.
 * @ingroup dtd
 */
Content& EMPTY = _empty;


///
class IgnoredContent: public Content {
protected:
	void reset() override{ }
	bool parse(Parser& parser) override {
		while(!parser.ended())
			parser.next();
		return true;
	}
};
static IgnoredContent _ignored;

/**
 * Content ignoring what is exactly in the content: always answer
 * the parsing succeeds.
 * @ingroup dtd
 */
Content& ignored = _ignored;


/**
 * @class Element;
 * DTD description of an XML element. It is made of zero or several attributes
 * and of a content. This content may be sub-elements, text, sequence of
 * elements, repetition of elements, alternative of elements or optional
 * elements.
 *
 * The easiest way to create an element is to use the Make constructor:
 * ```
 * dtd::Element cfg(dtd::make("cfg")
 * 		.attr(id)
 * 		.content((*property, entry, *bb, exit, *edge)));
 * ```
 * @ingroup xom
 */

/**
 * @class Element::Make
 * Maker class to build a DTD element.
 */

/**
 * @fn Element::Make::Make(xom::String name);
 * Build a DTD element with the given name.
 * @param Element name.
 */

/**
 * @fn Element::Make::Make& attr(Attribute& attr);
 * Add a DTD attribute to the made DTD element.
 * @param attr	Added DTD attribute.
 */

/**
 * @fn Make& Element::Make::content(Content& content);
 * Set the given content to the made DTD element. Notice that only the last
 * given content will be used.
 * @param content	Set content.
 */

/**
 * Build an empty DTD element.
 * @param name	Element name.
 */
Element::Element(xom::String name)
	: _name(name), _content(EMPTY)
	{ }

/**
 * Build an element with the given content.
 * @param name		Element name.
 * @param content	Element content.
 */
Element::Element(xom::String name, Content& content)
	: _name(name), _content(content)
	{ }

///
Element::~Element() {
}


/**
 * @fn xom::String Element::name() const;
 * Get the name of the element.
 * @return	Element name.
 */

/**
 * @fn Content& Element::content() const;
 * Get the content of the element.
 * @return	Element content.
 */

/**
 * @fn const Vector<AbstractAttribute *>& attributes() const;
 * Get the attributes of the element.
 * @return	List of attributes.
 */

///
void Element::reset() {
	for(auto a: attrs)
		a->reset();
	_content.reset();
}

///
bool Element::parse(Parser& parser) {
	if(parser.ended())
		return false;

	// check elemen
	if(parser.current()->kind() != xom::Node::ELEMENT
	|| parser.asElement()->getLocalName() != name())
		return false;

	// parse attributes
	for(int j = 0; j < attrs.length(); j++) {
		if(!attrs[j]->parse(parser)) {
			parser.recordError();
			return false;
		}
	}

	// process the content
	parser.begin(*this);
	bool success = _content.parse(parser);
	if(!parser.ended()) {
		parser.recordError();
		success = false;
	}
	parser.end(success);
	return success;
}

/**
 * Parse the current DTD element from the given XML element.
 * @param factory	Factory to call for the parsed elements.
 * @param element	XML element to parse.
 * @param flags		Flags for parsing (default set to Parser::CROP).
 * @throw Exception	Thrown if there is a format error.
 */
void Element::parse(Factory& factory, xom::Element *element, t::uint32 flags) {
	Parser parser(factory, *this, flags);
	parser.parse(element);
}


/**
 * Parse the current DTD element from the given XML document.
 * @param factory	Factory to call for the parsed elements.
 * @param doc		XML document to parse.
 * @param flags		Flags for parsing (default set to Parser::CROP).
 * @throw Exception	Thrown if there is a format error.
 */
void Element::parse(Factory& factory, xom::Document *doc, t::uint32 flags) {
	Parser parser(factory, *this, flags);
	parser.parse(doc->getRootElement());
}


/**
 * Parse the current DTD element from the given URI.
 * @param factory	Factory to call for the parsed elements.
 * @param uri		URI to parse.
 * @param flags		Flags for parsing (default set to Parser::CROP).
 * @throw Exception	Thrown if there is a format error.
 * @throw Exception	Thrown if there is an IO error.
 */
void Element::parse(Factory& factory, string uri, t::uint32 flags) {
	Parser parser(factory, *this, flags);
	xom::Builder builder;
	//auto doc = unique(builder.build(uri.asSysString()));
	UniquePtr<xom::Document> doc(builder.build(uri.asSysString()));
	if(doc == nullptr)
		throw io::IOException("bad XMl format");
	parser.parse(doc->getRootElement());
}

/**
 * Parse the current DTD element from the given input stream.
 * @param factory	Factory to call for the parsed elements.
 * @param in		Input stream to read from.
 * @param flags		Flags for parsing (default set to Parser::CROP).
 * @throw Exception	Thrown if there is a format error.
 * @throw Exception	Thrown if there is an IO error.
 */
void Element::parse(Factory& factory, io::InStream& in, t::uint32 flags) {
	Parser parser(factory, *this, flags);
	xom::Builder builder;
	//auto doc = unique(builder.build(&in));
	UniquePtr<xom::Document> doc(builder.build(&in));
	if(doc == nullptr)
		throw io::IOException("bad XMl format");
	parser.parse(doc->getRootElement());
}



/**
 * @class Optional
 * Represent an optional content: if the content is recognized,
 * it is consumed in the parser. Anyhow, a successful parse answer
 * is returned.
 * @ingroup dtd
 */

/**
 * Build an optional content.
 * @param content	Optional content.
 */
Optional::Optional(Content& content): con(content) { }

///
void Optional::reset() {
	con.reset();
}

///
bool Optional::parse(Parser& parser) {
	if(!parser.ended())
		doParse(con, parser);
	return true;
}

/**
 * @class Alt
 * Represent an alternative between two contents.
 * @ingroup dtd
 */

/**
 * Build an alternative content.
 * @param content1	First alternative.
 * @param content2	Second alternative.
 */
Alt::Alt(Content& content1, Content& content2): con1(content1), con2(content2) { }

///
bool Alt::parse(Parser& parser) {
	if(doParse(con1, parser))
		return true;
	else if(doParse(con2, parser))
		return true;
	else
		return false;
}

///
void Alt::reset() {
	con1.reset();
	con2.reset();
}


/**
 * @class Seq
 * Content representing a sequence of contents.
 * @ingroup dtd
 */

/**
 * Build a sequence content.
 * @param content1	Content first found.
 * @param content2	Content next found.
 */
Seq::Seq(Content& content1, Content& content2): con1(content1), con2(content2) { }

///
bool Seq::parse(Parser& parser) {
	if(parser.ended())
		return false;
	Parser::mark_t m = parser.mark();

	if(!doParse(con1, parser))
		return parser.backtrack(m);

	if(!doParse(con2, parser))
		return parser.backtrack(m);

	return true;
}

///
void Seq::reset() {
	con1.reset();
	con2.reset();
}


/**
 * @class Repeat
 * A content that is repeated zero or more times.
 * @ingroup dtd
 */

/**
 * Build a repeated content.
 * @param content	Repeated content.
 */
Repeat::Repeat(Content& content): con(content) { }

///
bool Repeat::parse(Parser& parser) {
	while(!parser.ended()) {
		if(!doParse(con, parser))
			break;
	}
	return true;
}

///
void Repeat::reset() {
	con.reset();
}


/**
 * @class PCDATA
 * Description of a content made of free text. Once the content of CDATA
 * is parsed, it is passed to the factory by a call to Factory::setCDATA().
 * @ingroup dtd
 */
class PCDATAContent: public Content {
protected:

	bool parse(Parser& parser) override {
		if(parser.ended()) {
			parser.factory().getPCDATA("");
			return true;
		}
		if(parser.current()->kind() != xom::Node::TEXT)
			return false;
		parser.factory().getPCDATA(static_cast<xom::Text *>(parser.current())->getText());
		parser.next();
		return true;
	}

	void reset() override {
	}
};
static PCDATAContent pcdata;


/**
 * Content representing a CDATA.
 * @see PCDATAContent
 * @ingroup dtd
 */
Content& PCDATA = pcdata;


///
class AnyContent: public Content {
public:
	bool parse(Parser& parser) override {
		while(!parser.ended()) {
			parser.factory().getAny(parser.current());
			parser.next();
		}
		return true;
	}

	void reset() override {
	}
};
static AnyContent any;

/**
 * Content supporting a sequence of both text and elements.
 * @ingroup dtd
 */
Content& ANY = any;


/**
 * @class IDAttribute
 * DTD attribute used as an identifier. The associated application object
 * is recorded in the parser identifier map thanks to a call to
 * Factory::getRef().
 * @ingroup dtd
 */

/**
 * Build an identifier attribute.
 * @param element	Parent element.
 * @param name		Attribute name.
 * @param flags		Attribute flags (see AbstractAttribute, optional).
 */
IDAttribute::IDAttribute(Element& element, xom::String name, t::uint32 flags)
	: AbstractAttribute(element, name, flags) { }

///
bool IDAttribute::process(Parser& parser, xom::String value) {
	if(parser.hasID(value)) {
		if(isStrict())
			parser.raise(_ << "already used identifier \"" << value << "\"in " << name());
		else
			return false;
	}
	_id = value;
	parser.addPost(this);
	return true;
}

///
void IDAttribute::postprocess(Parser& parser) {
	parser.recordID(_id, element());
}

///
void IDAttribute::reset() {
	AbstractAttribute::reset();
	_id = "";
}


/**
 * @class RefAttribute
 * Defines an attribute that is a reference to another XML element and
 * therefore to a specific application object (recorded from an IDAttr
 * attribute).
 *
 * @param T	Type of reference object.
 * @ingroup	dtd
 */

/**
* @fn RefAttribute::RefAttribute(xom::String name, t::uint32 flags);
* Build a reference attribute.
* @param name	Attribute name.
* @param flags	Attribute flags (see AbstractAttribute, optional).
*/

/**
 * @fn T *RefAttribute::reference() const;
 * Get the attribute reference value. May be a null pointer if the attribute
 * is not required and not found on the element.
 * @return	Attribute reference value.
 */


///
class GC {
public:
	~GC(void) {
		for(List<Content *>::Iter con; con(); con++)
			delete *con;
	}
	inline Content& add(Content *c) { to_free.add(c); return *c; }
private:
	List<Content *> to_free;
};

///
GC _gc;


/**
 * @class Attribute
 * Generic attribute that uses io::Input to parse the value of an XML
 * attribute.
 *
 * @param T	Type of the attribute.
 * @ingroup	dtd
 */

/**
 * @fn Attribute::Attribute(xom::String name, const T& init, t::uint32 flags);
 * Build a generic attribute.
 * @param name	Attribute name.
 * @param init	Initial default value.
 * @param flags	Attribute flags (see AbstractAttribute).
 */

/**
 * @fn const T& Attribute::operator*() const;
 * Get the value stored in the identifier.
 * @return	Attribute value.
 */


/**
 * Build a repeated content.
 * @param c	Repeated content.
 * @ingroup dtd
 */
Content& operator*(Content& c) { return _gc.add(new Repeat(c)); }

/**
 * Build an optional content.
 * @param c	Optional content.
 * @ingroup dtd
 */
Content& operator!(Content& c) { return _gc.add(new Optional(c)); }

/**
 * Build an alternate content.
 * @param c1	First alternative.
 * @param c2	Second alternative.
 * @ingroup dtd
 */
Content& operator+(Content& c1, Content& c2) { return _gc.add(new Alt(c1, c2)); }

/**
 * Build an alternate content.
 * @param c1	First alternative.
 * @param c2	Second alternative.
 * @ingroup dtd
 */
Content& operator|(Content& c1, Content& c2) { return _gc.add(new Alt(c1, c2)); }

/**
 * Build a sequence content.
 * @warning	This operator has the smallest precedence level and it can be
 * confused with the comma separating argument of a function call.
 * @param c1	First content in the sequence.
 * @param c2	Second content in the sequence.
 * @ingroup dtd
 */
Content& operator,(Content& c1, Content& c2) { return _gc.add(new Seq(c1, c2)); }

/**
 * Build a sequence content.
 * @param c1	First content in the sequence.
 * @param c2	Second content in the sequence.
 * @ingroup dtd
 */
Content& operator&(Content& c1, Content& c2) { return _gc.add(new Seq(c1, c2)); }


/**
 * @var const t::uint32 STRICT;
 * Attribute flag causing parsing failure if there is an error during
 * the attribute parsing.
 * @ingroup dtd
 */

/**
 * @var const t::uint32 REQUIRED
 * Attribute flag marking that the attribute as required its container element.
 * @ingroup dtd
 */

/**
 * @var const t::uint32 FORWARD
 * Attribute flag marking a reference attribute to enable support for forward
 * references.
 * @ingroup dtd
 */

/**
 * @fn const t::uint32 CROP;
 * Parser attribute indicating that the blank nodes (text made of spaces)
 * can be ignored.
 * @ingroup dtd
 */

} }		// elm::dtd
