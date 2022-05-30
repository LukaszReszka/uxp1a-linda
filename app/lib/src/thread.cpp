#include "thread.h"
#include <iostream>

namespace cmd_interpreter {

    void* Thread::runThread(void * thread) {
        auto thd = static_cast<Thread*>(thread);
        thd->run();
        pthread_exit(NULL);
    }

    std::string Thread::getThreadDetails() {
        std::string result = "%%%% Thread " + std::to_string(thread_id) + " %%%%\n";
        for(pointer_to_cmd &cmd: commands_to_execute)
            result += cmd->getInfoBeforeExecution() + "\n";

        return result;
    }

    void Thread::run() {
        for(auto &cmd: commands_to_execute) {
            std::unique_lock<std::mutex> guard(output_mutex);
            std::cout << thread_id << ": " << cmd->getInfoBeforeExecution() << std::endl;
            guard.unlock();

            cmd->execute();

            guard.lock();
            std::cout << thread_id << ": " << cmd->getInfoAfterExecution() << std::endl;
        }
    }

} // namespace cmd_interpreter