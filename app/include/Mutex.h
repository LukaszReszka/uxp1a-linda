#pragma once
#include <mutex>

namespace cmd_interpreter {

    class Mutex {
    public:
        Mutex() = default;
        void lock() {mtx.lock();};
        void unlock() {mtx.unlock();};
        ~Mutex() {mtx.unlock();};

    private:
        std::mutex mtx;
    };

} // namespace cmd_interpreter
