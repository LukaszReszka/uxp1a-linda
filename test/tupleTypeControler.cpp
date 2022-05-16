#include <future>
#include <thread>

#include "gtest/gtest.h"
#define private public
#include "tupleTypeControler.h"
#undef private
#include "lindaTuple.h"
#include "tupleCondition.h"

using Time = int;

TEST(TupleTypeControlerTest, ShouldAddTuple) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();
  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);
  EXPECT_EQ(tuple.getValues(), tupleTypeControler.tuples.at(0).getValues());
}

TEST(TupleTypeControlerTest, ShouldGetNulloptTuple) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 0;

  EXPECT_EQ(std::nullopt, tupleTypeControler.getTuple(tupleCondition, timeout));
}

TEST(TupleTypeControlerTest, ShouldReadNulloptTuple) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 0;

  EXPECT_EQ(std::nullopt,
            tupleTypeControler.readTuple(tupleCondition, timeout));
}

TEST(TupleTypeControlerTest, ShouldGetTupleAfterAdd) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 1000;

  EXPECT_EQ(tuple.getValues(),
            tupleTypeControler.getTuple(tupleCondition, timeout)->getValues());
}

TEST(TupleTypeControlerTest, ShouldReadTupleAfterAdd) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 1000;

  EXPECT_EQ(tuple.getValues(),
            tupleTypeControler.readTuple(tupleCondition, timeout)->getValues());
}

TEST(TupleTypeControlerTest, ShouldGetTupleBeforeAdd) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto getTuple = [&tupleTypeControler]() {
    auto condition = Condition();
    condition.valueType = ValueType::stringType;
    condition.operationType = OperationType::everything;
    condition.value = "test";
    auto conditionVector = std::vector<Condition>();
    conditionVector.push_back(condition);
    TupleCondition tupleCondition = TupleCondition(conditionVector);
    Time timeout = 1000;
    return tupleTypeControler.getTuple(tupleCondition, timeout);
  };

  auto futureGetTuple = std::async(getTuple);

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto returnedTuple = futureGetTuple.get();

  EXPECT_EQ(tuple.getValues(), returnedTuple->getValues());
}

TEST(TupleTypeControlerTest, ShouldReadTupleBeforeAdd) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto readTuple = [&tupleTypeControler]() {
    auto condition = Condition();
    condition.valueType = ValueType::stringType;
    condition.operationType = OperationType::everything;
    condition.value = "test";
    auto conditionVector = std::vector<Condition>();
    conditionVector.push_back(condition);
    TupleCondition tupleCondition = TupleCondition(conditionVector);
    Time timeout = 1000;
    return tupleTypeControler.readTuple(tupleCondition, timeout);
  };

  auto futureReadTuple = std::async(readTuple);

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto returnedTuple = futureReadTuple.get();

  EXPECT_EQ(tuple.getValues(), returnedTuple->getValues());
}

TEST(TupleTypeControlerTest, ShouldRemoveTupleWhenGetTupleIsExecuted) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 1000;
  tupleTypeControler.getTuple(tupleCondition, timeout);
  EXPECT_EQ(0, tupleTypeControler.tuples.size());
}

TEST(TupleTypeControlerTest, ShouldNotRemoveTupleWhenReadTupleIsExecuted) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto condition = Condition();
  condition.valueType = ValueType::stringType;
  condition.operationType = OperationType::everything;
  condition.value = "test";
  auto conditionVector = std::vector<Condition>();
  conditionVector.push_back(condition);
  TupleCondition tupleCondition = TupleCondition(conditionVector);
  Time timeout = 1000;

  tupleTypeControler.readTuple(tupleCondition, timeout);
  EXPECT_EQ(1, tupleTypeControler.tuples.size());
}

TEST(TupleTypeControlerTest, ShouldPerformAddGetRead) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto getTuple = [&tupleTypeControler]() {
    auto condition = Condition();
    condition.valueType = ValueType::stringType;
    condition.operationType = OperationType::everything;
    condition.value = "test";
    auto conditionVector = std::vector<Condition>();
    conditionVector.push_back(condition);
    TupleCondition tupleCondition = TupleCondition(conditionVector);
    Time timeout = 1000;
    return tupleTypeControler.getTuple(tupleCondition, timeout);
  };

  auto readTuple = [&tupleTypeControler]() {
    auto condition = Condition();
    condition.valueType = ValueType::stringType;
    condition.operationType = OperationType::everything;
    condition.value = "test";
    auto conditionVector = std::vector<Condition>();
    conditionVector.push_back(condition);
    TupleCondition tupleCondition = TupleCondition(conditionVector);
    Time timeout = 1;
    return tupleTypeControler.readTuple(tupleCondition, timeout);
  };

  auto futureGetTuple = std::async(getTuple);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  auto futureReadTuple = std::async(readTuple);

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto returnedGetTuple = futureGetTuple.get();
  auto returnedReadTuple = futureReadTuple.get();

  EXPECT_EQ(tuple.getValues(), returnedGetTuple->getValues());
  EXPECT_EQ(std::nullopt, returnedReadTuple);
  EXPECT_EQ(0, tupleTypeControler.tuples.size());
}

TEST(TupleTypeControlerTest, ShouldPerformAddReadGet) {
  TupleTypeControler tupleTypeControler = TupleTypeControler();

  auto getTuple = [&tupleTypeControler]() {
    auto condition = Condition();
    condition.valueType = ValueType::stringType;
    condition.operationType = OperationType::everything;
    condition.value = "test";
    auto conditionVector = std::vector<Condition>();
    conditionVector.push_back(condition);
    TupleCondition tupleCondition = TupleCondition(conditionVector);
    Time timeout = 1;
    return tupleTypeControler.getTuple(tupleCondition, timeout);
  };

  auto readTuple = [&tupleTypeControler]() {
    auto condition = Condition();
    condition.valueType = ValueType::stringType;
    condition.operationType = OperationType::everything;
    condition.value = "test";
    auto conditionVector = std::vector<Condition>();
    conditionVector.push_back(condition);
    TupleCondition tupleCondition = TupleCondition(conditionVector);
    Time timeout = 1000;
    return tupleTypeControler.readTuple(tupleCondition, timeout);
  };

  auto futureReadTuple = std::async(readTuple);
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  auto futureGetTuple = std::async(getTuple);

  std::vector<std::variant<std::string, u_int32_t, float>> vec =
      std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("test"));
  uxp::Tuple tuple = uxp::Tuple(vec);
  tupleTypeControler.addTuple(tuple);

  auto returnedReadTuple = futureReadTuple.get();
  auto returnedGetTuple = futureGetTuple.get();

  EXPECT_EQ(tuple.getValues(), returnedReadTuple->getValues());
  EXPECT_EQ(tuple.getValues(), returnedGetTuple->getValues());
  EXPECT_EQ(0, tupleTypeControler.tuples.size());
}