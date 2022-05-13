#include <thread>

#include "gtest/gtest.h"
#include "mutex.h"

TEST(MutexTest, mutexCreation) {
  EXPECT_NO_THROW(uxp::mutex mtx);
};

TEST(MutexTest, mutexLock) {
  uxp::mutex mtx;
  EXPECT_NO_THROW(mtx.lock());
  EXPECT_NO_THROW(mtx.unlock());
};

TEST(MutexTest, RaceTest) {
  uxp::mutex mtx;
  int number = 0;
  const int iterationNumber = 1000;
  auto incrementNumber = [&mtx, &number, &iterationNumber]() {
    for (auto i = 0; i < iterationNumber; ++i) {
      mtx.lock();
      number++;
      mtx.unlock();
    }
  };
  std::thread thr1(std::ref(incrementNumber));
  std::thread thr2(std::ref(incrementNumber));
  thr1.join();
  thr2.join();
  EXPECT_EQ(number, 2 * iterationNumber);
}