#pragma once
#include <pthread.h>

#include "mutex.h"


using Time = int;

namespace uxp {
class ConditionVariable {
 public:
  ConditionVariable();
  void wait(uxp::mutex& mtx);
  bool waitFor(uxp::mutex& mtx, Time time);
  void notify();
  ~ConditionVariable() noexcept(false);
 private:
  pthread_cond_t conditionVariable;
  struct timespec ts;
};
}  // namespace uxp