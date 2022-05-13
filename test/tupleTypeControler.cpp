#include <thread>

#include "gtest/gtest.h"
#include "tupleTypeControler.h"


TEST(TupleTypeControlerTest, RaceTest) {
  EXPECT_EQ(1, 1);
}