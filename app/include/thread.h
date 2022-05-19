#pragma once
#include <vector>
#include <memory>
#include "pthread.h"
#include "lindaCommand.h"
#include "mutex.h"

namespace cmd_interpreter {

    typedef unsigned int uint;
    using pointer_to_cmd = std::unique_ptr<LindaCommand>;

    class Thread {
    public:
        explicit Thread(uint id): thread_id(id) {}
        void addCommand(pointer_to_cmd command_ptr) {commands_to_execute.push_back(std::move(command_ptr));}
        void runThread(Mutex &mutex);
        ~Thread() = default;

    private:
        uint thread_id;
        pthread_t thread;
        std::vector<pointer_to_cmd> commands_to_execute;
    };

} // namespace cmd_interpreter
