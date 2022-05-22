#include "mutex.h"
#include "mutexException.h"

namespace cmd_interpreter {
    Mutex::Mutex() {
        if (pthread_mutex_init(&mtx, NULL))
            throw MutexException(CANT_INIT_MUTEX);
        if (pthread_mutexattr_init(&mtxAttributes))
            throw MutexException(CANT_INIT_ATTRIBUTES);
        if (pthread_mutexattr_settype(&mtxAttributes, PTHREAD_MUTEX_ERRORCHECK))
            throw MutexException(CANT_SET_ATTRIBUTES);
    }

    Mutex::~Mutex() noexcept(false) {
        if (pthread_mutex_destroy(&mtx))
            throw MutexException(CANT_DESTROY_MUTEX);
        if (pthread_mutexattr_destroy(&mtxAttributes))
            throw MutexException(CANT_DESTROY_ATTRIBUTES);
    }

    void Mutex::lock() {
        if (pthread_mutex_lock(&mtx))
            throw MutexException(LOCK_ERROR);
    }

    void Mutex::unlock() {
        if (pthread_mutex_unlock(&mtx))
            throw MutexException(UNLOCK_ERROR);
    }
} // namespace cmd_interpreter