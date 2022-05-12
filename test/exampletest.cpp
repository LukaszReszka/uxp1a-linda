#include "gtest/gtest.h"
#include "test.h"

TEST(blaTest, test1) {
    //arrange
    //act
    //assert
    int result = TestClass().add(1,2);
    EXPECT_EQ (result,  3);
}