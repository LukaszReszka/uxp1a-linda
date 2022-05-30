#include "gtest/gtest.h"

#include "tupleConditionParser.h"
#include "tupleValuesParser.h"
#include "tupleCondition.h"

TEST(shortcutTest, tupleShortcut1)
{
    auto valParser = TupleValuesParser(std::string("string = \"dd\", integer  = 123, float =1.1 , float =1.1"));
    auto values = valParser.parseAllValues();
    auto tuple = uxp::Tuple(values);
    EXPECT_EQ(tuple.getPatternShortcut(), "SIFF");
}

TEST(shortcutTest, tupleShortcut2)
{
    auto valParser = TupleValuesParser(std::string("float =1.1"));
    auto values = valParser.parseAllValues();
    auto tuple = uxp::Tuple(values);
    EXPECT_EQ(tuple.getPatternShortcut(), "F");
}

TEST(shortcutTest, tupleShortcut3)
{
    auto valParser = TupleValuesParser(std::string("float  =1.1, string = \"dd\", integer  = 123"));
    auto values = valParser.parseAllValues();
    auto tuple = uxp::Tuple(values);
    EXPECT_EQ(tuple.getPatternShortcut(), "FSI");
}

TEST(shortcutTest, condShortcut1)
{
    auto condParser = TupleConditionParser(std::string("string:\"dd\", integer:*, float:*"));
    EXPECT_EQ(TupleCondition(condParser.parseWholeCondition()).getShortcut(), "SIF");
}

TEST(shortcutTest, condShortcut2)
{
    auto condParser = TupleConditionParser(std::string("integer:*, float:*, string:\"dd\", string:\"dd\""));
    EXPECT_EQ(TupleCondition(condParser.parseWholeCondition()).getShortcut(), "IFSS");
}

TEST(shortcutTest, condShortcut3)
{
    auto condParser = TupleConditionParser(std::string("integer:*, float:*, integer:*, float:*"));
    EXPECT_EQ(TupleCondition(condParser.parseWholeCondition()).getShortcut(), "IFIF");
}