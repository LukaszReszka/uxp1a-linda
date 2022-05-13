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

TEST(checkConditionTest, checkStringEqual1)
{
    auto condParser = TupleConditionParser(std::string("string:\"dd\""));
    auto valParser = TupleValuesParser(std::string("string = \"dd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringEqual2)
{
    auto condParser = TupleConditionParser(std::string("string:\"dda\""));
    auto valParser = TupleValuesParser(std::string("string = \"dd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkStringLess1)
{
    auto condParser = TupleConditionParser(std::string("string:<\"dda\""));
    auto valParser = TupleValuesParser(std::string("string = \"add\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringLess2)
{
    auto condParser = TupleConditionParser(std::string("string:<\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"ddd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkStringLessEqual1)
{
    auto condParser = TupleConditionParser(std::string("string:<=\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"ddd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkStringLessEqual2)
{
    auto condParser = TupleConditionParser(std::string("string:<=\"dda\""));
    auto valParser = TupleValuesParser(std::string("string = \"addd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringLessEqual3)
{
    auto condParser = TupleConditionParser(std::string("string:<=\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"ada\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringLessEqual4)
{
    auto condParser = TupleConditionParser(std::string("string:<=\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"adaa\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkStringGreater1)
{
    auto condParser = TupleConditionParser(std::string("string:>\"dda\""));
    auto valParser = TupleValuesParser(std::string("string = \"add\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkStringGreater2)
{
    auto condParser = TupleConditionParser(std::string("string:>\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"ddd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringGreaterEqual1)
{
    auto condParser = TupleConditionParser(std::string("string:>=\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"ddd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringGreaterEqual2)
{
    auto condParser = TupleConditionParser(std::string("string:>=\"dda\""));
    auto valParser = TupleValuesParser(std::string("string = \"addd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkStringGreaterEqual3)
{
    auto condParser = TupleConditionParser(std::string("string:>=\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"ada\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringGreaterEqual4)
{
    auto condParser = TupleConditionParser(std::string("string:>=\"ada\""));
    auto valParser = TupleValuesParser(std::string("string = \"adaa\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringEverything1)
{
    auto condParser = TupleConditionParser(std::string("string:*"));
    auto valParser = TupleValuesParser(std::string("string = \"add\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkStringEverything2)
{
    auto condParser = TupleConditionParser(std::string("string:*"));
    auto valParser = TupleValuesParser(std::string("string = \"ddd\""));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerEqual1)
{
    auto condParser = TupleConditionParser(std::string("integer:123"));
    auto valParser = TupleValuesParser(std::string("integer = 123"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerEqual2)
{
    auto condParser = TupleConditionParser(std::string("integer:123"));
    auto valParser = TupleValuesParser(std::string("integer = 124"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkIntegerLess1)
{
    auto condParser = TupleConditionParser(std::string("integer:<123"));
    auto valParser = TupleValuesParser(std::string("integer = 121"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerLess2)
{
    auto condParser = TupleConditionParser(std::string("integer:<121"));
    auto valParser = TupleValuesParser(std::string("integer = 123"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkIntegerLessEqual1)
{
    auto condParser = TupleConditionParser(std::string("integer:<=121"));
    auto valParser = TupleValuesParser(std::string("integer = 123"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkIntegerLessEqual2)
{
    auto condParser = TupleConditionParser(std::string("integer:<=123"));
    auto valParser = TupleValuesParser(std::string("integer = 121"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerLessEqual3)
{
    auto condParser = TupleConditionParser(std::string("integer:<=121"));
    auto valParser = TupleValuesParser(std::string("integer = 121"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerGreater1)
{
    auto condParser = TupleConditionParser(std::string("integer:>3"));
    auto valParser = TupleValuesParser(std::string("integer = 2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkIntegerGreater2)
{
    auto condParser = TupleConditionParser(std::string("integer:>2"));
    auto valParser = TupleValuesParser(std::string("integer = 3"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerGreaterEqual1)
{
    auto condParser = TupleConditionParser(std::string("integer:>=2"));
    auto valParser = TupleValuesParser(std::string("integer = 2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerGreaterEqual2)
{
    auto condParser = TupleConditionParser(std::string("integer:>=3"));
    auto valParser = TupleValuesParser(std::string("integer = 2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkIntegerGreaterEqual3)
{
    auto condParser = TupleConditionParser(std::string("integer:>=2"));
    auto valParser = TupleValuesParser(std::string("integer = 3"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerGreaterEqual4)
{
    auto condParser = TupleConditionParser(std::string("integer:>=5"));
    auto valParser = TupleValuesParser(std::string("integer = 5"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerEverything1)
{
    auto condParser = TupleConditionParser(std::string("integer:*"));
    auto valParser = TupleValuesParser(std::string("integer = 1"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkIntegerEverything2)
{
    auto condParser = TupleConditionParser(std::string("integer:*"));
    auto valParser = TupleValuesParser(std::string("integer = 123"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatEqual1)
{
    auto condParser = TupleConditionParser(std::string("float:123.1"));
    auto valParser = TupleValuesParser(std::string("float = 123.1"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatEqual2)
{
    auto condParser = TupleConditionParser(std::string("float:123.1"));
    auto valParser = TupleValuesParser(std::string("float = 124.2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkFloatLess1)
{
    auto condParser = TupleConditionParser(std::string("float:<123.1"));
    auto valParser = TupleValuesParser(std::string("float = 121"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatLess2)
{
    auto condParser = TupleConditionParser(std::string("float:<121"));
    auto valParser = TupleValuesParser(std::string("float = 123.2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkFloatLessEqual1)
{
    auto condParser = TupleConditionParser(std::string("float: <=121.22"));
    auto valParser = TupleValuesParser(std::string("float = 123"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkFloatLessEqual2)
{
    auto condParser = TupleConditionParser(std::string("float:<= 123"));
    auto valParser = TupleValuesParser(std::string("float = 121.3"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatLessEqual3)
{
    auto condParser = TupleConditionParser(std::string("float:<=121.1"));
    auto valParser = TupleValuesParser(std::string("float = 121.1"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatGreater1)
{
    auto condParser = TupleConditionParser(std::string("float:>3.1"));
    auto valParser = TupleValuesParser(std::string("float = 2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkFloatGreater2)
{
    auto condParser = TupleConditionParser(std::string("float:>2.2"));
    auto valParser = TupleValuesParser(std::string("float = 3.2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatGreaterEqual1)
{
    auto condParser = TupleConditionParser(std::string("float:>=2"));
    auto valParser = TupleValuesParser(std::string("float = 2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatGreaterEqual2)
{
    auto condParser = TupleConditionParser(std::string("float:>=10.12"));
    auto valParser = TupleValuesParser(std::string("float = 2"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), false);
}

TEST(checkConditionTest, checkFloatGreaterEqual3)
{
    auto condParser = TupleConditionParser(std::string("float:>=2"));
    auto valParser = TupleValuesParser(std::string("float = 3.1"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatGreaterEqual4)
{
    auto condParser = TupleConditionParser(std::string("float:>=5"));
    auto valParser = TupleValuesParser(std::string("float = 5.1"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatEverything1)
{
    auto condParser = TupleConditionParser(std::string("float:*"));
    auto valParser = TupleValuesParser(std::string("float = 1"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}

TEST(checkConditionTest, checkFloatEverything2)
{
    auto condParser = TupleConditionParser(std::string("float:*"));
    auto valParser = TupleValuesParser(std::string("float = 123.123"));
    auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
    auto tuple = uxp::Tuple(valParser.parseAllValues());
    EXPECT_EQ(tupleCondition.checkCondition(tuple), true);
}
