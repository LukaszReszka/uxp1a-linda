#include <thread>

#include "gtest/gtest.h"
#include "tupleTypeControler.h"
#include "lindaTuple.h"
#include "tupleCondition.h"

using Time = int;

TEST(TupleTypeControlerTest, ShouldAddTuple) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();
  std::vector<std::variant<std::string, u_int32_t, float>> vec = std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  EXPECT_NO_THROW(tupleTypeControler.addTuple(tuple));
}

TEST(TupleTypeControlerTest, ShouldInputTuple) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 0;

  EXPECT_NO_THROW(tupleTypeControler.getTuple(tupleCondition, timeout));
}

