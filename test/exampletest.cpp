#include "gtest/gtest.h"
#include "test.h"
#include "linda.h"
#include "tupleConditionParser.h"
#include "tupleValuesParser.h"

TEST(shortcutTest, tupleShortcut1)
{
    auto valParser = TupleValuesParser(std::string("string = \"dd\", integer  = 123, float =1.1 , float =1.1"));
    EXPECT_EQ((uxp::Tuple(valParser.parseAllValues())).getPatternShortcut(), "SIFF");
}

TEST(shortcutTest, tupleShortcut2)
{
    auto valParser = TupleValuesParser(std::string("float =1.1"));
    EXPECT_EQ((uxp::Tuple(valParser.parseAllValues())).getPatternShortcut(), "F");
}

TEST(shortcutTest, tupleShortcut3)
{
    auto valParser = TupleValuesParser(std::string("float  =1.1, string = \"dd\", integer  = 123"));
    EXPECT_EQ((uxp::Tuple(valParser.parseAllValues())).getPatternShortcut(), "FSI");
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

TEST(blaTest, test1)
{
    // arrange
    // act
    // assert
    int result = TestClass().add(1, 2);
    EXPECT_EQ(result, 3);
}