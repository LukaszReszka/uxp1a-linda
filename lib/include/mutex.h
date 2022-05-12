#pragma once
#include <mutex>

namespace uxp {
class ConditionalVariable;

class mutex {
 public:
  mutex() { };
  inline void lock() { mtx.lock(); };
  inline void unlock() { mtx.unlock(); };

 private:
  std::mutex mtx;
  friend class uxp::ConditionalVariable;
};

};  // namespace uxp