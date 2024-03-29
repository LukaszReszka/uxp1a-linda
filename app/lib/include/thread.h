#pragma once
#include <vector>
#include <mutex>
#include "pthread.h"
#include "lindaCommand.h"

namespace cmd_interpreter {

    class Thread {
    public:
        explicit Thread(int id, std::mutex &m): thread_id(id), output_mutex(m) {}
        void addCommand(pointer_to_cmd command_ptr) {commands_to_execute.push_back(std::move(command_ptr));}
        static void* runThread(void *thread);
        std::string getThreadDetails();
        ~Thread() = default;

    private:
        void run();

        int thread_id;
        std::vector<pointer_to_cmd> commands_to_execute;
        std::mutex &output_mutex;
    };

} // namespace cmd_interpreter
