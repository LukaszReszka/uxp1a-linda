#pragma onc
#include "pthread.h"

namespace uxp {
class ConditionVariable;

class mutex {
 public:
  mutex(int attributes = PTHREAD_MUTEX_ERRORCHECK);
  void lock();
  void unlock();
  ~mutex() noexcept(false);

 private:
  pthread_mutex_t mtx;
  pthread_mutexattr_t mtxAttributes;
  friend class uxp::ConditionVariable;
};

};  // namespace uxp