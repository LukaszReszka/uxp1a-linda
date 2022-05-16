#include <future>
#include <thread>

#include "gtest/gtest.h"
#define private public
#include "linda.h"
#undef private
#include "lindaTuple.h"
#include "tupleCondition.h"

using Time = int;

TEST(TupleTypeControlerTest, ShouldCreateTupleTypeControllerWhenOutput) {
  Linda linda = Linda();
  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  linda.output(uxp::Tuple(vec));

  EXPECT_TRUE(linda.checkIfTupleSpaceInMap("S"));
}

TEST(TupleTypeControlerTest, ShouldCreateTupleTypeControllerWhenInput) {
  Linda linda = Linda();
  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 0;
  linda.input(tupleCondition, timeout);

  EXPECT_TRUE(linda.checkIfTupleSpaceInMap("S"));
}

TEST(TupleTypeControlerTest, ShouldCreateTupleTypeControllerWhenRead) {
  Linda linda = Linda();
  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 0;
  linda.read(tupleCondition, timeout);

  EXPECT_TRUE(linda.checkIfTupleSpaceInMap("S"));
}

TEST(TupleTypeControlerTest, ShouldCreateOneTupleTypeController) {
  Linda linda = Linda();
  std::vector<std::variant<std::string, u_int32_t, float>> vec1 =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec1.push_back(std::string("test1"));
  linda.output(uxp::Tuple(vec1));
  std::vector<std::variant<std::string, u_int32_t, float>> vec2 =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec2.push_back(std::string("test2"));
  linda.output(uxp::Tuple(vec2));

  EXPECT_EQ(1, linda.tupleSpace.size());
}

TEST(TupleTypeControlerTest, ShouldCreateTwoDifferentTupleTypeControllers) {
  Linda linda = Linda();
  std::vector<std::variant<std::string, u_int32_t, float>> vec1 =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec1.push_back(std::string("test"));
  linda.output(uxp::Tuple(vec1));
  std::vector<std::variant<std::string, u_int32_t, float>> vec2 =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec2.push_back(u_int32_t(0));
  linda.output(uxp::Tuple(vec2));

  EXPECT_EQ(2, linda.tupleSpace.size());
}
