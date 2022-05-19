#include "thread.h"
#include <iostream>

namespace cmd_interpreter {

    void Thread::runThread(Mutex &mutex) {
        for(pointer_to_cmd &cmd: commands_to_execute) {
            mutex.lock();
            std::cout << thread_id << ": " << cmd->getInfoBeforeExecution() << std::endl;
            mutex.unlock();

            cmd->execute();

            mutex.lock();
            std::cout << thread_id << ": " << cmd->getInfoAfterExecution() << std::endl;
            mutex.unlock();
        }
        pthread_exit(NULL);
    }
} // namespace cmd_interpreter