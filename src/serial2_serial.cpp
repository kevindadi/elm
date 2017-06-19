/*
 *	serial module implementation
 *
 *	This file is part of OTAWA
 *	Copyright (c) 2006, IRIT UPS.
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
#include <elm/serial2/serial.h>
#include <elm/genstruct/HashTable.h>
#include <elm/util/Initializer.h>

using namespace elm::genstruct;

namespace elm { namespace serial2 {


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
 * or data collections). Yet, to serialize custom classes, the user has to
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
 * * @par Available serializers / unserializers
 *
 * ELM comes with some already implemented serializer / unserializers:
 * @li @ref TextSerializer (serializer only).
 * @li @ref XOMSerializer / @ref XOMUnserializer.
 *
 * More will be added in future versions.
 *
 * @par Enumeration Serialization
 *
 * Depending on the serialization format (textual, XML, etc), it may be useful to
 * provide more readable information for the human user. This applies typically
 * to enumeration values. ELM provides already such a facility.
 *
 * In the code below, an enumeration type is declared (in header file) and
 * serialization information is provided by "DECLARE_ENUM" macro:
 * @code
 *	#include <elm/rtti.h>
 *
 * 	typedef enum color_t {
 *			RED,
 *			GREEN,
 *			BLUE
 *		} color_t;
 *		DECLARE_ENUM(color_t);
 * @endcode
 *
 * Then, in the matching source file, you have to create an object describing
 * the enumeration type and the available enumerated values:
 * @code
 *	elm::rtti:Enum color_type(elm::rtti::make("color_")
 *			.value("RED", RED)
 *			.value("GREEN", GREEN)
 *			.value("BLUE", BLUE));
 *	DEFINE_ENUM(color_t, color_type);
 * @endcode
 *
 * The last macro `DEFINE_ENUM` link the enumeration type descriptor with the enumeration
 * type itself and provide typing information to the serialization system. Additionally,
 * a textual output of the enumerated type is also provided.
 *
 * @par Collection serialization
 *
 * @par Customizing the serialization
 *
 * Basically, what does serialization is to pass forth and back field references to classes
 * @ref Serializer for serialization and @ref Unserializer for unserialization. Depending
 * on the operation, one of the following method is called:
 * @code
 * template <> void __serialize(Serializer& s, const T& v);
 * template <> void __unserialize(Unserializer& s, T& v);
 * @endcode
 *
 * With T being the type of the field to serialize. ELM provides serializer/unserializer for most
 * basic types and most of its collection types. Providing __serialize() and __unserialize() with
 * T being your own type is a first way to specialize the serialization process. In this configuration,
 * you have to use methods provided by classes @ref Serializer and @ref Unserializer to perform
 * the actual work.
 *
 * Then, one has to remark that the type T does not need to be the one of a field of serialized object.
 * This may be any type that will refer to any object. This is the case of @ref FIELD macro that build an object
 * of type @ref Field. The trick here is that the macro @ref SERIALIZABLE creates a specific method, named
 * "__visit" in where the field are copied. This means that, when the field are built, a specific instance
 * of the class is available and usable, for example, using the "this" self pointer. This means that at the
 * construction of the field, the whole object (and its methods) are available and may be used for customizing
 * the serialization process.
 *
 * Hence, to customize the way an object is serialized, one has to:
 * @li design a dedicated class C,
 * @li build an instance of class C passing possibly the "this" pointer or any reachable object resource,
 * @li provide __serialize() and __unserialize() methods on this object.
 *
 * This is illustrated in the example below where methods getID and setID are used instead of the direct access
 * to the field itself:
 * @code
 * class MyClass;
 * class GetSetID {
 * public:
 * 		inline GetSetField(MyClass *p): _p(p) { }
 *  	MyClass *_p;
 * };
 *
 * class MyClass {
 * public:
 * 	SERIALIZABLE("my_class", GetSetID(this));
 * };
 *
 * void __serialize(Serializer& s, const GetSet& i) {
 * 		s.beginField("id");
 *		s.onValue(i._p->getID());
 *		s.endField();
 *  }
 *
 * void __unserialize(Unserializer& s, const GetSet& i) {
 * 		s.beginField("id");
 * 		string s;
 *		s.onValue(s);
 *		i._p->setID(s);
 *		s.endField();
 *  }
 * @endcode
 *
 * @par Writing a serializer
 *
 * Writing a serializer is relatively easy in ELM: one has just
 * to implement either @ref Serializer interface interfaces:
 *
 * @code
 *	#include <elm/serial2/Serializer.h>
 *	class MySerializer: public elm::serial2::Serializer {
 *	public:
 *		...
 *	};
 * @endcode
 *
 * Depending on the data to serialize, one or several functions of this
 * interface will be called.
 *
 * Simple type (boolean, integer, float, string) are generated by a call to one of the
 * Serializer::onValue() method with the corresponding type
 * for the unique parameter. Notice that the parameter to Serializer::onValue() calls
 * is a reference corresponding exactly to the read value in the object or in the
 * compound containing the value and may be used for the pointer linkage support
 * (described further).
 *
 * Serializing an enumeration value is a bit more complex:
 * the @ref Serializer::onEnum() function will receive the address of the value
 * (for pointer linkage described below), the enumerated value converted to `int`
 * and a descriptor of the enumerated type (of type @ref elm::rtti::Enum).
 *
 * Collection or array types starts by a call to Serializer::beginCompound() and terminates
 * by a call to Serializer::endCompound(). Before each item, a call to Serializer:::onItem()
 * is performed. The data item, itself, is supported by serializer function call
 * corresponding to their type (@ref Serializer::onValue(), compound access, etc).
 *
 * Object serialization is surrounded by a Serializer::beginObject() and
 * Serializer::endObject(). The first parameter of the Serializer::beginObject() contains
 * a reference to the actual class of the object. Then each serialized field surrounded
 * by Serializer::beginField() and Serializer::endField() and the field value passed
 * using other serialization methods.
 *
 * Pointers are particular values for serialization. First, circularities
 * involved by the use of pointers must be supported. This means that a pointer to object
 * must be stored in a map and when an already encountered object is referenced or
 * serialized again, a reference to it  must be serialized to ensure
 * that the same structure is rebuilt in memory. Notice that each object passed to
 * Serializer::onValue() takes a reference possibly dereferenced by "&" and that
 * Serializer::beginCompound() and Serializer::beginObject() get a pointer on their object.
 * The current implementation of serialization is not able to decide if an object is
 * referenced or not by a pointer: the serializer implementation has to provide
 * an identifier for each serialized object.
 *
 * The work of Serializer is summarized below:
 * * bool, int, float, string, cstring ⟶ Serializer::onValue()
 * * enum type ⟶ Serializer::onEnum()
 * * pointer type ⟶ Serializer::onPointer()
 * * compound type ⟶ Serializer::beginCompound(), for each item (Serializer::onItem(), value call),
 * 	 Serializer::endCompound()
 * * object type ⟶ Serializer::beginObject(), for each attribute (Serializer::beginField(), value call,
 *   Serializer::endField() ), Serializer::endObject().
 *
 * @par Writing an unserializer
 *
 * Writing an unserializer is relatively easy in ELM: one has just
 * to implement the @ref Unserializer interface:
 *
 * @code
 *	#include <elm/serial2/Unserializer.h>
 *	class MySerializer: public elm::serial2::Unserializer {
 *	public:
 *		...
 *	};
 * @endcode
 *
 * Depending on the data to serialize, one or several functions of this
 * interface will be called.
 *
 * Simple type (boolean, integer, float, string) are generated by a call to one of the
 * Unserializer::onValue() method with the corresponding type
 * for the unique parameter. The parameter is passed by reference to let the unserializer
 * change the value.
 *
 * Unserializing an enumeration value is a bit more complex:
 * the @ref Serializer::onEnum() function a descriptor of the enumerated type
 * (of type @ref elm::rtti::Enum) and must return the enumerated value as an `int`.
 *
 *
 * Collection or array types starts by a call to Unserializer::beginCompound() and terminates
 * by a call to Unserializer::endCompound(). If required, the unserialized data type can
 * call the function Unserializer::countItems() to get the count of items to unserialize
 * (this is used by some fixed-size data types like AllocArray). Then, the current item
 * is unserialized using a call to the method corresponding to its type. This is followed
 * by a call to Unserializer::nextItem() to pass to the next item.
 *
 * Object unserialization is surrounded by Unserializer::beginObject() and
 * Unserializer::endObject() calls.
 * The first parameter of the Unserializer::beginObject() contains a reference to the
 * actual class of the object. Then each unserialized is field surrounded by
 * Unserializer::beginField() and Unserializer::endField() and the field value passed
 * using other serialization methods.
 *
 * Pointer are a particular value for unserialization. Notice the unserializer must
 * maintain an identifier / reference system in order to ensure
 * that the same structure is rebuilt in memory after serialization.. Notice also that
 * each object passed to Unserializer::onValue()
 * takes a reference possibly dereferenced by "&" and that Unserializer::beginCompound() and
 * Unserializer::beginObject() get a pointer on their object.
 *
 * The work of Unserializer is summarized below:
 * * bool, int, float, string, cstring ⟶ Unserializer::onValue()
 * * enum type ⟶ Unserializer::onEnum()
 * * pointer type ⟶ Unserializer::onPointer()
 * * compound type ⟶ Unserializer::beginCompound(), for each item (value call, Unserializer::nextItem()),
 * 	 Unserializer::endCompound()
 * * object type ⟶ Unserializer::beginObject(), for each attribute (Unserializer::beginField(), value call,
 *   Unserializer::endField() ), Unserializer::endObject().
 *
 * @par Low-level of the serialization module
 *
 * Basically, serialization or unserialization applies mainly the same process. Therefore,
 * in the following, only the serialization process is described but it may be applied
 * symmetrically as is to unserialisation.
 *
 * A serialization starts with the following command:
 * @code
 * S << D;
 * @endcode
 * Where S is the Serializer object and D the data to serialize. At this point, the `operator<<`
 * is overload to support a first argument of type Serializer and a parametric type T,
 * the type of D. It simply call the function `__unserialize`(S, D).
 *
 * This function will choose which serialization process to perform. According to the type T,
 * it will select `from_class<T>`, `from_enum<T>` or `from_type<T>` or pointer specialization.
 * In case of pointer, `__serialize` call directly the function Serializer::onPointer().
 * A first way of specialization the serialization process is to provide your version of
 * `__serialize` for your own type. This is the case of collections data type that
 * specialize their specialization as compound by overriding `__serialize`.
 *
 * The `from_type<T>` specialization calls the Serializer::onValue() method (and thanks to
 * C++ type overload will call the right one).
 *
 * The `from_enum<T>` specialization calls the Serializer:: onEnum() method but has also
 * to select the enumeration type descriptor. This is obtained using elm::rtti::type_of<T>().
 *
 * The `from_class<T>` has to perform several actions (Serializer::beginClass(),
 * Serializer::beginField(), Serializer::endField() and Serializer::endClass()) but, because
 * of the inheritance in C++,it  has mainly to find the actual type of the object.
 * This is enabled by the use of the `SERIALIZABLE` macro that add a virtual function
 * named `__getSerialClass()`.
 */


/**
 * @class ExternalSolver
 * The external solver is used by @ref Serializer and @ref Unserializer classes
 * to solve reference to object out of the scope the currently serialized / unserialized
 * object.
 *
 * For serializing, the solver provides references to object that does not need to be
 * serialized but a reference is obtained and stored instead.
 *
 * For unserializing, this solver provide pointer to object internal to the user application
 * and that are linked with unserialized objects. When a reference cannot be solved, it is
 * considered as being provided by the application and the solver is called for solving it.
 *
 * Its default implementation considers there is not external object.
 * @ingroup serial
 */


/**
 * Null external solver.
 */
ExternalSolver ExternalSolver::null;

/**
 */
ExternalSolver::~ExternalSolver(void) {
}

/**
 * Try to resolve an external reference.
 * @param ref	Reference to resolve.
 * @return		Reference to matching object or null.
 */
void *ExternalSolver::solve(string ref) {
	return 0;
}


/**
 * Test if the given object is an external object
 * and return its reference.
 * @param object	Object to test for.
 * @return			External reference of the object or an empty string.
 */
string ExternalSolver::ref(void *object) {
	return "";
}


/**
 * @class Serializer
 *
 * Base class of serialization classes. The serialization is the conversion
 * from the memory representation of a data structure to a sequential representation.
 * This is useful to store a data structure in file or to send it over the network.
 *
 * To implement a concrete serializer, one has to inherit from this class and
 * to override the virtual functions. The serialization function will be called
 * according the serialized value.
 *
 * @ingroup serial
 */

/**
 * @fn void Serializer::flush(void);
 * Flush to the media (disk, network) the current state
 * of the serialization.
 */

/**
 * @fn void Serializer::beginObject(const rtti::Type& clazz, const void *object);
 * Called to start the serialization of a new object.
 * @param clazz		Object class descriptor.
 * @param object	Serialized object.
 */

/**
 * @fn void Serializer::endObject(const rtti::Type& clazz, const void *object);
 * Called to finish the serialization of a new object. This function call is always
 * preceded by a call to beginObject().
 * @param clazz		Object class descriptor.
 * @param object	Serialized object.
 */

/**
 * @fn void Serializer::beginField(CString name);
 * Called to begin the serialization of a field in an object.
 *
 * This call is always preceded by call to beginObject() for the object
 * containing the field and there is no more call to this function
 * as soon as the corresponding endObject() call is performed.
 *
 * Between a call to a beginField() and of a endField(), calls to the serializer
 * functions are performed to serialize the corresponding data.
 *
 * @param name	Name of the field.
 */

/**
 * @fn void Serializer::endField(void);
 * Called to begin the serialization of a field in an object.
 *
 * This call is always preceded by call to beginField() and there is no more
 * call to this function as soon as the corresponding endObject() call is performed.
 */

/**
 * @fn void Serializer::onPointer(const rtti::Type& clazz, const void *object);
 * This function is called to serialize a pointer to an object.
 *
 * A special caution must be devoted to serialize pointer because of
 * the possibility of a circular data structures that may lead to endless
 * looping on this function.
 *
 * @param clazz		Class of the pointed object.
 * @param object	Pointed object to serialize.
 */

/**
 * @fn void Serializer::beginCompound(const void *object);
 * This function is called to serialize a compound object, that is, an object containing
 * a collection of values with the same type.
 * @param object	Compound object to serialize.
 */

/**
 * @fn void Serializer::onItem(void);
 * For each value of a compound object, a call to this function is performed.
 *
 * This function call is always preceded by a call to beginCompound() and will not
 * call anymore after a call to endCompound().
 *
 * This call is followed by calls to other serialization function in order to
 * serialize the value itself.
 */

/**
 * @fn void Serializer::endCompound(const void*) = 0;
 * This function is called at the end of a compound.
 *
 * This function is only called after a call to beginCompound() and matches any
 * call to beginCompound().
 */

/**
 * @fn void Serializer::onEnum(const void *address, int value, const rtti::Type& clazz);
 * Called when a value of type enumerate has to be serialized.
 * @param address	Address of the value.
 * @param value		Value to serialzie.
 * @param clazz		Enumerated type.
 */

/**
 * @fn void Serializer::onValue(const bool& v);
 * Called to serialize a value of type boolean.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const signed int& v);
 * Called to serialize a value of type signed integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const unsigned int& v);
 * Called to serialize a value of type unsigned integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const signed char& v);
 * Called to serialize a value of type signed  byte.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const unsigned char& v);
 * Called to serialize a value of type unsigned byte.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const signed short& v);
 * Called to serialize a value of type signed short integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const unsigned short& v);
 * Called to serialize a value of type unsigned short integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const signed long& v);
 * Called to serialize a value of type signed long integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const unsigned long& v);
 * Called to serialize a value of type unsigned long integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const signed long long& v);
 * Called to serialize a value of type signed long long integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const unsigned long long& v);
 * Called to serialize a value of type unsigned long long integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const float& v);
 * Called to serialize a value of type single-precision floating point.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const double& v);
 * Called to serialize a value of type double-precision floating point.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const long double& v);
 * Called to serialize a value of type quadruple-precision floating point.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const cstring& v);
 * Called to serialize a value of type C string.
 * @param v		Value to serialize.
 */

/**
 * @fn void Serializer::onValue(const string& v);
 * Called to serialize a value of type ELM string.
 * @param v		Value to serialize.
 */


/**
 * @class Unserializer
 *
 * Base class of unserialization classes. The serialization is the conversion
 * from the memory representation of a data structure to a sequential representation
 * and the unserialization is the reverse operation.
 *
 * To implement a concrete unserializer, one has to inherit from this class and
 * to override the virtual functions. The unserialization function will be called
 * according the unserialized value.
 *
 * @ingroup serial
 */

/**
 * @fn void Unserializer::beginObject(const rtti::Type& clazz, void *object);
 * Called to start the unserialization of a new object.
 * @param clazz		Object class descriptor.
 * @param object	Unserialized object.
 */

/**
 * @fn void Unserializer::endObject(const rtti::Type& clazz, void *object);
 * Called to finish the unserialization of an object. This function call is always
 * preceded by a call to beginObject().
 * @param clazz		Object class descriptor.
 * @param object	Unserialized object.
 */

/**
 * @fn bool Unserializer::beginField(CString name);
 * Called to begin the unserialization of a field in an object.
 *
 * This call is always preceded by call to beginObject() for the object
 * containing the field and there is no more call to this function
 * as soon as the corresponding endObject() call is performed.
 *
 * Between a call to a beginField() and of a endField(), calls to the unserializer
 * functions are performed to serialize the corresponding data.
 *
 * @param name	Name of the field.
 */

/**
 * @fn void Unserializer::endField(void);
 * Called to end the unserialization of a field in an object.
 *
 * This call is always preceded by call to beginField() and there is no more
 * call to this function as soon as the corresponding endObject() call is performed.
 */

/**
 * @fn bool Unserializer::beginCompound(void*);
 * This function is called to unserialize a compound object, that is, an object containing
 * a collection of values with the same type.
 * @param object	Compound object to unserialize.
 */

/**
 * @fn bool Unserializer::nextItem(void);
 * Afgter getting a value of a compound object, a call to this function must be performed.
 *
 * This function call is always preceded by a call to beginCompound() and will not
 * call anymore after a call to endCompound().
 *
 * This call is followed by calls to other unserialization function in order to
 * unserialize the value itself.
 */

/**
 * @fn void Unserializer::endCompound(void *);
 * This function is called at the end of a compound.
 *
 * This function is only called after a call to beginCompound() and matches any
 * call to beginCompound().
 */

/**
 * @fn int Unserializer::countItems(void);
 * This function is called to get the count if items in a compound.
 *
 * If it only called after a beginCompound() and before any to nextItem().
 *
 * @return	Count of values in the compound.
 */

/**
 * @fn void Unserializer::onPointer(const rtti::Type& clazz, void **object);
 * This function is called to unserialize a pointer to an object.
 *
 * @param clazz		Class of the pointed object.
 * @param object	Pointed object to unserialize.
 */

/**
 * @fn int Unserializer::onEnum(AbstractEnum& clazz);
 * Called when a value of type enumerate has to be unserialized.
 * @param clazz		Enumerated type.
 * @return			Enumerated value.
 */

/**
 * @fn void Unserializer::onValue(bool& v);
 * Called to unserialize a value of type boolean.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(signed int& v);
 * Called to unserialize a value of type signed integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(unsigned int& v);
 * Called to unserialize a value of type unsigned integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void UnSerializer::onValue(signed char& v);
 * Called to unserialize a value of type signed  byte.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(unsigned char& v);
 * Called to unserialize a value of type unsigned byte.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(signed short& v);
 * Called to unserialize a value of type signed short integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(unsigned short& v);
 * Called to unserialize a value of type unsigned short integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(signed long& v);
 * Called to unserialize a value of type signed long integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(unsigned long& v);
 * Called to unserialize a value of type unsigned long integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(signed long long& v);
 * Called to unserialize a value of type signed long long integer.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(unsigned long long& v);
 * Called to unserialize a value of type unsigned long long integer.
 * @param v		Value to serialize.
 */

/**
 * @fn void Unserializer::onValue(float& v);
 * Called to unserialize a value of type single-precision floating point.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(double& v);
 * Called to unserialize a value of type double-precision floating point.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(long double& v);
 * Called to unserialize a value of type quadruple-precision floating point.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(cstring& v);
 * Called to unserialize a value of type C string.
 * @param v		Reference to unserialize in.
 */

/**
 * @fn void Unserializer::onValue(string& v);
 * Called to unserialize a value of type ELM string.
 * @param v		Reference to unserialize in.
 */

} } // elm::serial2
