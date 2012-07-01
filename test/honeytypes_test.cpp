#include "honeytypes/types/int.h"
#include "honeytypes/types/string.h"
#include "honeytypes/var.h"
#include "honeytypes/as.h"

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

TEST(Var, copy_ctor_StringV)
{
	StringV stringv("64");
	EXPECT_EQ(64, stringv.to_int());
	
	Var v(stringv);
	EXPECT_EQ(64, v.to_int());
}

TEST(Var, move_ctor_StringV)
{
	StringV stringv("64");
	EXPECT_EQ(64, stringv.to_int());
	
	Var v(std::move(stringv));
	EXPECT_EQ(64, v.to_int());
}

TEST(Var, copy_assign_StringV)
{
	StringV stringv("64");
	EXPECT_EQ(64, stringv.to_int());
	
	Var v;
	v = stringv;
	EXPECT_EQ(64, v.to_int());
	
	EXPECT_EQ(64, stringv.to_int());
}

TEST(Var, move_assign_StringV)
{
	StringV stringv("64");
	EXPECT_EQ(64, stringv.to_int());
	
	Var v;
	v = std::move(stringv);
	EXPECT_EQ(64, v.to_int());
	
	EXPECT_EQ(0, stringv.to_int());
}

TEST(as, as_int)
{
	IntV intv(12345);
	StringV stringv("12345");
	Var v = stringv;
	
	EXPECT_EQ(12345, ht::as<int>()(intv));
	EXPECT_EQ(12345, ht::as<int>()(stringv));
	EXPECT_EQ(12345, ht::as<int>()(v));
}

TEST(Var, vector)
{
	std::vector<Var> vs = {IntV(1), StringV("2"), StringV("3.0"), IntV(4)};
	
	for(Var& v: vs)
	{
		std::cout << v.to_int() << std::endl;
	}
}
