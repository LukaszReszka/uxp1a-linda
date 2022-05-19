#pragma once
#include "pthread.h"

namespace cmd_interpreter {

    class Mutex {
    public:
        Mutex();
        void lock();
        void unlock();
        ~Mutex() noexcept(false);

    private:
        pthread_mutex_t mtx;
        pthread_mutexattr_t mtxAttributes;
    };

} // namespace cmd_interpreter
