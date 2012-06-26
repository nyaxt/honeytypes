#include "../honeytypes.cpp"

#include <gtest/gtest.h>
using namespace ht;

TEST(Int, to_int)
{
	IntV intv(32);
	EXPECT_EQ(32, intv.to_int());

	intv = IntV(30);
	EXPECT_EQ(30, intv.to_int());
}

TEST(Val, initial_NullV)
{
	Var v;
	EXPECT_EQ(impltype_t::T_NullV, v.getType());
	EXPECT_EQ(0, v.to_int());
	EXPECT_EQ(std::string(""), v.to_str());
}

TEST(Val, copy_ctor_IntV)
{
	IntV intv(50);

	Var v(intv); // bug -> invokes move ctor instead
	EXPECT_EQ(impltype_t::T_IntV, v.getType());
	EXPECT_EQ(50, v.to_int());
	
	intv.to_int();
}

TEST(Val, move_ctor_IntV)
{
	Var v((IntV&&)(IntV(50)));
	EXPECT_EQ(impltype_t::T_IntV, v.getType());
	EXPECT_EQ(50, v.to_int());
}
