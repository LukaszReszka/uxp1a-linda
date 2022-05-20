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
        explicit Thread(uint id, Mutex &m): thread_id(id), output_mutex(&m) {}
        void addCommand(pointer_to_cmd command_ptr) {commands_to_execute.push_back(std::move(command_ptr));}
        static void* runThread(void *thread);
        ~Thread() = default;

    private:
        void run();

        uint thread_id;
        std::vector<pointer_to_cmd> commands_to_execute;
        Mutex *output_mutex;
    };

} // namespace cmd_interpreter
