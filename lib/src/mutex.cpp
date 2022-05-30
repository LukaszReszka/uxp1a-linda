#include "mutex.h"

#include <iostream>

#include "mutexException.h"

uxp::Mutex::Mutex(int attributes) {
  if (pthread_mutex_init(&mtx, NULL) != 0)
    throw MutexException(CANT_INIT_MUTEX);
  if (pthread_mutexattr_init(&mtxAttributes) != 0)
    throw MutexException(CANT_INIT_ATTRIBUTES);
  if (pthread_mutexattr_settype(&mtxAttributes, attributes) != 0)
    throw MutexException(CANT_SET_ATTRIBUTES);
}
uxp::Mutex::~Mutex() noexcept(false) {
  try {
    if (pthread_mutex_destroy(&mtx) != 0)
      throw MutexException(CANT_DESTROY_MUTEX);
    if (pthread_mutexattr_destroy(&mtxAttributes) != 0)
      throw MutexException(CANT_DESTROY_ATTRIBUTES);
  } catch (MutexException& mtxException) {
    std::cerr << mtxException.what() << std::endl;
  }
}

void uxp::Mutex::lock() {
  if (pthread_mutex_lock(&mtx) != 0) throw MutexException(LOCK_ERROR);
}

void uxp::Mutex::unlock() {
  if (pthread_mutex_unlock(&mtx) != 0) throw MutexException(UNLOCK_ERROR);
}