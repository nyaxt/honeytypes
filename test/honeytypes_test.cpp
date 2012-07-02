#include "honeytypes/types/int.h"
#include "honeytypes/types/string.h"
#include "honeytypes/var.h"
#include "honeytypes/as.h"

#include <algorithm>

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

TEST(Var, vector)
{
	std::vector<Var> vs = {IntV(1), StringV("2"), StringV("3.0"), IntV(4)};
	
	for(Var& v: vs)
	{
		std::cout << v.inspect() << std::endl;
	}
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

TEST(as, less_as)
{
	std::vector<Var> vs = {
		IntV(3),
		StringV("5"),
		IntV(1),
		StringV("4"),
		StringV("2")
	};
	
	std::sort(vs.begin(), vs.end(), ht::less_as<int>());
	
	// for(Var& v: vs) std::cout << v.inspect() << std::endl;
	EXPECT_EQ(1, ht::as<int>()(vs[0]));
	EXPECT_EQ(2, ht::as<int>()(vs[1]));
	EXPECT_EQ(3, ht::as<int>()(vs[2]));
	EXPECT_EQ(4, ht::as<int>()(vs[3]));
	EXPECT_EQ(5, ht::as<int>()(vs[4]));
}

TEST(as, greater_as)
{
	std::vector<Var> vs = {
		IntV(3),
		StringV("5"),
		IntV(1),
		StringV("4"),
		StringV("2")
	};
	
	std::sort(vs.begin(), vs.end(), ht::greater_as<int>());
	
	// for(Var& v: vs) std::cout << v.inspect() << std::endl;
	EXPECT_EQ(5, ht::as<int>()(vs[0]));
	EXPECT_EQ(4, ht::as<int>()(vs[1]));
	EXPECT_EQ(3, ht::as<int>()(vs[2]));
	EXPECT_EQ(2, ht::as<int>()(vs[3]));
	EXPECT_EQ(1, ht::as<int>()(vs[4]));
}

#if 0
{
	TableBuilder tbEntries;
	tbEntries.addColumn("thr_id", impltype_t::T_IntV);
	tbEntries.addColumn("entry_id", impltype_t::T_IntV);
	
	tbEntries.addColumn("name", impltype_t::T_StringV);
	tbEntries.addColumn("mail", impltype_t::T_StringV);
	tbEntries.addColumn("created_at", impltype_t::T_DateTimeV);
	tbEntries.addColumn("content", impltype_t::T_StringV);
	
	tbEntries.setPrimaryKey({"thr_id", "entry_id"});

	Table tEntries = tbEntries.build();
}
#endif
