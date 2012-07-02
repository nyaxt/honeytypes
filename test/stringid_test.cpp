#include "honeytypes/stringid.h"

#include <gtest/gtest.h>
using namespace ht;

TEST(StringId, from_string)
{
	StringId id("abcdef");
	
	EXPECT_EQ("abcdef", id);
}

TEST(StringId, hash)
{
	std::hash<StringId> h;
	EXPECT_NE(h(StringId("abcd")), h(StringId("abcx")));
}

TEST(StringId, compare_different_hash)
{
	StringId a("a");
	StringId b("b");
	
	std::hash<StringId> h;
	EXPECT_EQ(h(a), h(a));
	EXPECT_EQ(h(b), h(b));
	EXPECT_NE(h(a), h(b));
	
	EXPECT_EQ(a, a);
	EXPECT_EQ(b, b);
	EXPECT_NE(a, b);
	EXPECT_NE(b, a);
}

