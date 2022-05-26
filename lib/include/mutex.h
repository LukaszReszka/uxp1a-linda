#pragma once
#include "pthread.h"

namespace uxp {
class ConditionVariable;

class Mutex {
 public:
  Mutex(int attributes = PTHREAD_MUTEX_ERRORCHECK);
  void lock();
  void unlock();
  ~Mutex() noexcept(false);

 private:
  pthread_mutex_t mtx;
  pthread_mutexattr_t mtxAttributes;
  friend class uxp::ConditionVariable;
};

};  // namespace uxp