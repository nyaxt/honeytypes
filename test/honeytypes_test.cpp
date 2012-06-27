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

TEST(Var, initial_NullV)
{
	Var v;
	EXPECT_EQ(impltype_t::T_NullV, v.getType());
	EXPECT_EQ(0, v.to_int());
	EXPECT_EQ(std::string(""), v.to_str());
}

TEST(Var, copy_ctor_IntV)
{
	IntV intv(50);

	Var v(intv); // bug -> invokes move ctor instead
	EXPECT_EQ(impltype_t::T_IntV, v.getType());
	EXPECT_EQ(50, v.to_int());
	
	intv.to_int();
}

TEST(Var, move_ctor_IntV)
{
	Var v(IntV(50));
	EXPECT_EQ(impltype_t::T_IntV, v.getType());
	EXPECT_EQ(50, v.to_int());
}

TEST(Var, copy_assign_IntV)
{
	IntV intv(50);	

	Var v;
	v = intv;
	
	EXPECT_EQ(50, intv.to_int());
	EXPECT_EQ(50, v.to_int());
}

TEST(Var, move_assign_IntV)
{
	IntV intv(50);	

	Var v;
	v = std::move(intv);
	
	EXPECT_EQ(50, intv.to_int());
	EXPECT_EQ(50, v.to_int());
}
