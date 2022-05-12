#pragma once
#include <chrono>
#include <condition_variable>

#include "mutex.h"

using Time = int;

namespace uxp {
class ConditionalVariable {
 public:
  ConditionalVariable();
  void wait(uxp::mutex& mtx) {
    std::unique_lock<std::mutex> lk(mtx.mtx);
    condVariable.wait(lk);
  };
  void waitFor(uxp::mutex& mtx, Time time) {
    std::unique_lock<std::mutex> lk(mtx.mtx);
    std::chrono::seconds sec(1 * time);
    condVariable.wait_for(lk, sec);
  };
  void notify() { condVariable.notify_one(); };

 private:
  std::condition_variable condVariable;
};
}  // namespace uxp