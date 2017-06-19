#include "../include/elm/test.h"
#include <elm/rtti.h>
#include <elm/util/Variant.h>

using namespace elm;
using namespace elm::rtti;

typedef enum my_enum_t {
	A = 0,
	B = 1,
	C = 2
} my_enum_t;
DECLARE_ENUM(my_enum_t);


Enum<my_enum_t> my_enum_t_type(AbstractEnum::make("my_enum_t")
	.value("A", A)
	.value("B", B)
	.value("C", C)
	.alias("AA", A));
DEFINE_ENUM(my_enum_t, my_enum_t_type);

TEST_BEGIN(rtti)

	CHECK_EQUAL(&int8_type, &type_of<t::int8>());
	CHECK_EQUAL(static_cast<const Type *>(&my_enum_t_type), &type_of<my_enum_t>());
	CHECK_EQUAL(my_enum_t_type.valueFor("A"), int(A));
	CHECK_EQUAL(my_enum_t_type.valueFor("B"), int(B));
	CHECK_EQUAL(my_enum_t_type.valueFor("C"), int(C));
	CHECK_EQUAL(my_enum_t_type.valueFor("AA"), int(A));
	CHECK_EQUAL(my_enum_t_type.nameFor(A), cstring("A"));
	CHECK_EQUAL(my_enum_t_type.nameFor(B), cstring("B"));
	CHECK_EQUAL(my_enum_t_type.nameFor(C), cstring("C"));

TEST_END
