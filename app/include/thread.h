#pragma once
#include <vector>
#include "pthread.h"
#include "lindaCommand.h"
#include "Mutex.h"

namespace cmd_interpreter {

    class Thread {
    public:
        explicit Thread(int id, Mutex &m): thread_id(id), output_mutex(m) {}
        void addCommand(pointer_to_cmd command_ptr) {commands_to_execute.push_back(std::move(command_ptr));}
        static void* runThread(void *thread);
        std::string getThreadDetails();
        ~Thread() = default;

    private:
        void run();

        int thread_id;
        std::vector<pointer_to_cmd> commands_to_execute;
        Mutex &output_mutex;
    };

} // namespace cmd_interpreter
