#include <chrono>
#include <thread>

#include "conditionVariable.h"
#include "gtest/gtest.h"

TEST(CondVariableTest, ConditionVariableLockCreation) {
  uxp::mutex mtx;
  EXPECT_NO_THROW(uxp::ConditionVariable condVariable);
};

TEST(CondVariableTest, SleepAndWakeUpTest) {
  uxp::mutex mtx;
  uxp::ConditionVariable condVariable;
  int number = 0;
  const int iterationNumber = 10;
  auto incrementNumber = [&mtx, &number, &iterationNumber, &condVariable]() {
    for (auto i = 0; i < iterationNumber; ++i) {
      condVariable.wait(mtx);
      number++;
    }
  };
  auto wakeUp = [&condVariable, &iterationNumber]() {
    for (auto i = 0; i < iterationNumber; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      condVariable.notify();
    }
  };
  std::thread thr1(std::ref(incrementNumber));
  std::thread thr2(std::ref(wakeUp));
  thr1.join();
  thr2.join();
  EXPECT_EQ(number, iterationNumber);
}