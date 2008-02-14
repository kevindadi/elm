/*
 *	$Id$
 *	Main documentation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2008, IRIT UPS.
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
#ifndef ELM_DOC_H_
#define ELM_DOC_H_

/**
 * @mainpage
 * 
 * ELM is a multi-purpose library used by the OTAWA project (http://www.otawa.fr).
 * It provides :
 * @li generic data structures,
 * @li generic interface with te operating system (files, command line, etc),
 * @li a checked plugin system,
 * @li efficient string class,
 * @li other utility classes.
 * 
 * Please take a look at the module part for detailed description.
 */

/**
 * @defgroup serial Serialization / unserialization
 * 
 * ELM provides support for pseudo-automatic serialization / unserialization
 * of objects.
 * 
 * The following C++ features are supported in serialization:
 * @li scalar types (integer, floats)
 * @li atomic types (strings),
 * @li class type with inheritance,
 * @li pointer and reference types with circularity detection,
 * @li array types,
 * @li ELM collection types,
 * @li enumeration with user support for value names.
 * 
 * In addition, the user can provides its own custom serialization code in
 * a serializer / unserializer independent format.
 * 
 * @par A simple example
 * 
 * The serialization or the unserialization is a very simple to perform using
 * the same interface as usual C++ input/output.
 * 
 * @code
 * #include <elm/serial2/serial.h>
 * #include <elm/serial2/TextSerializer.h>
 * #include <elm/serial2/collections.h>
 * 
 * using namespace elm;
 * 
 * int main(void) {
 *	serial2::TextSerializer serializer;
 *	serializer << "Hello, World !\n" << 666 << true;
 * 
 * 	MyClass my_object;
 *	serializer << my_object;
 * 
 *	Vector<MyClass> objects;
 *	for(int i = 0; i < 10; i++)
 *		objects.add(my_object);
 *	serializer << objects; 
 * }
 * @endcode
 * 
 * In the example above, we show how serializable objects (scalar values, string,
 * MyClass and Vector) are easily serialized by a serializer providing a text
 * output. As a default, the output is performed to the standard output. Notice
 * that the unserialization of data from the bytes produced by this example must
 * be performed in the same order. 
 * 
 * @code
 * #include <elm/serial2/serial.h>
 * #include <elm/serial2/XOMUnserializer.h>
 * #include <elm/serial2/collections.h>
 * 
 * using namespace elm;
 * 
 * int main(void) {
 *  serial2::XOMUnserializer unser("unser.xml");
 *	string str;
 *	int x;
 *	bool boolean;
 *	serializer >> str >> x >> boolean;
 * 
 * 	MyClass my_object;
 *	serializer >> my_object;
 * 
 *	Vector<MyClass> objects;
 *	serializer >> objects; 
 * }
 * }
 * @endcode
 * 
 * The unserialization above looks much like the previous serialization
 * example. It works in the same way as the input stream of C++ standard library.
 * The read values must be put in variable. Notice that in the case of the Vector,
 * the unserializer automatically allocate enough space to store the serialized
 * collection of objects.
 * @p
 * This examples illustrates also the use of an XML unserializer taking its input
 * from the file "unser.xml". This file is usual XML text that may be modified
 * by hand and that contains very few serialization-systems items.
 *
 * ELM provides serializer / unserializer for usual types (like scalars, strings
 * or data collections). Yet, to serializer custom classes, the user has to
 * add some information about the fields to work with. In our example, we use
 * the following declaration for MyClass in MyClass.h:
 * 
 * @code
 * #include <elm/serial2/macros.h>
 * #include <elm/serial2/collections.h>
 * 
 * class MyClass {
 * 	SERIALIZABLE(MyClass, FIELD(name) & FIELD(value) & FIELD(attrs));
 *	string name;
 *	int value;
 *	Vector<string> attrs;
 * public:
 *	...
 * };
 * @endcode
 * 
 * The macro SERIALIZABLE is used to add to the class some RTTI information
 * that is used by the serialization system. After the name of the class,
 * this macro takes the list of fields to serialize separated by the '&' operator
 * and embedded in the FIELD macro. The field macro is not mandatory, it allows
 * only to provide better reading on textual output by providing the name of
 * the field. This macro is used both by serialization and unserialization. 
 * 
 * @par Making a class serializable
 * 
 * In ELM, making a class serializable is very easy. One has to add some
 * RTTI information in the class declaration and add a macro in the class
 * definition file.
 * 
 * The declaration ".h" file must includes serialization headers:
 * @code
 * #include <elm/serial2/macros.h>
 * #include <elm/serial2/collections.h>
 * @endcode
 * 
 * Then, we have to add the macro SERIALIZE in the class declaration including
 * the name of the class and the list of the field to serialize separated by
 * '&'.
 * @code
 * class ClassName {
 *	SERIALIZABLE(ClassName, field1 & field2 & field3 & ...);
 *	...
 * };
 * @endcode
 *
 * In the definition ".cpp" file, we have just to put the following macro that
 * provides the implementation of the RTTI information of the class:
 * @code
 *	SERIALIZE(ClassName)
 * @endcode 
 * The passed class name must be the same between the SERIALIZABLE and the SERIALIZE
 * macro and fully qualified to avoid ambiguities.
 * 
 * Declaring a field serializable is as easy as passing its name in the SERIALIZABLE
 * list. Actually, a reference to the field is taken and used to read or write
 * the serialized values. In human readable formats (like XML or text),
 * it may be useful to provide also the identifier of the field to the
 * serialization system. This is easily done using the FIELD macro in place
 * of the field name:
 * @code
 *	SERIALIZE(MyClass, FIELD(field1) & field2 & FIELD(field3) & ...);
 * @endcode
 * 
 * Some serialization formats supports optional field definition. In this case,
 * a default value may be provided with the DFIELD macro:
 * @code
 *	SERIALIZE(MyClass, DFIELD(field1, default_value) & field2 & FIELD(field3) & ...);
 * @endcode
 * 
 * Finally, if the serialized class inherit from a serializable class, the
 * base class must be added to the list of field with the BASE macro:
 * @code
 * class MyBaseClass {
 *	SERIALIZABLE(MyBaseClass, ...);
 *	...
 * };
 * 
 * class MyClass: public MyBaseClass {
 *	SERIALIZABLE(MyClass, BASE(MyBaseClass) & field1 & ...);
 *	...
 * };
 * @endcode
 * 
 * @par Collection serialization
 * 
 * @par Customizing the serialization
 * 
 * @par Available serializers / unserializers
 * 
 * @par Writing a serialiazer
 * 
 */
#endif /*ELM_DOC_H_*/
