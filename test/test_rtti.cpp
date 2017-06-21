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


//Enum my_enum_t_type(Enum::make("my_enum_t")
BEGIN_ENUM(my_enum_t)
	.value("A", A)
	.value("B", B)
	.value("C", C)
	.alias("AA", A)
END_ENUM
//DEFINE_ENUM(my_enum_t, my_enum_t_type);

class AA {
public:
	AA(void): x(666) { }
	int x;
};

CLASS(BB)
public:
	BB(void): y(111) { }
	int y;
END_CLASS

class CC: public AA, public BB {
	IS_CLASS_EXTEND(CC, BB)
public:
	CC(void): z(0) { }
	int z;
};

CLASS_EXTEND(DD, CC)
END_CLASS

IMPLEMENT(BB);
IMPLEMENT(CC);
IMPLEMENT(DD);

TEST_BEGIN(rtti)
	{
		CHECK_EQUAL(&int8_type, &type_of<t::int8>());
		const Type& t = type_of<my_enum_t>();
		CHECK_EQUAL(t.name(), string("my_enum_t"));
		const Enumerable& et = t.asEnum();
		CHECK_EQUAL(et.valueFor("A"), int(A));
		CHECK_EQUAL(et.valueFor("B"), int(B));
		CHECK_EQUAL(et.valueFor("C"), int(C));
		CHECK_EQUAL(et.valueFor("AA"), int(A));
		CHECK_EQUAL(et.nameFor(A), cstring("A"));
		CHECK_EQUAL(et.nameFor(B), cstring("B"));
		CHECK_EQUAL(et.nameFor(C), cstring("C"));
	}

	{
		DD o;
		DD *pd = &o;
		CC *pc = pd;
		AA *pa = static_cast<AA *>(pc);
		BB *pb = static_cast<BB *>(pc);
		cout << "pd = " << (void *)pd << io::endl
			 << "pc = " << (void *)pc << io::endl
			 << "pa = " << (void *)pa << io::endl
			 << "pb = " << (void *)pb << io::endl;

		CHECK_EQUAL(t::ptr(pb), CC::__type.upCast(pc));
		CHECK_EQUAL(t::ptr(pc), CC::__type.downCast(pb));
		CHECK_EQUAL(t::ptr(pc), DD::__type.upCast(pd));
		CHECK_EQUAL(t::ptr(pd), DD::__type.downCast(pc));

		CHECK_EQUAL(t::ptr(pb), DD::__type.upCast(pd, BB::__type));
		CHECK_EQUAL(t::ptr(pd), BB::__type.downCast(pb, DD::__type));
	}

TEST_END
