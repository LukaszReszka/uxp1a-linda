#pragma once
#include <unordered_map>
#include "thread.h"
#include "mutex.h"

namespace cmd_interpreter {

    using pointer_to_thread = std::unique_ptr<Thread>;

    class ThreadsController {
    public:
        ThreadsController() { output_mutex = Mutex(); }
        void addCommandToThread(int thread_id, pointer_to_cmd command);
        void launchAllThreads();
        inline void removeSavedThreads() { mapIdToThread.clear(); }
        ~ThreadsController();

    private:
        void waitForAllThreadsTermination();
        void cancelRunningThreads();

        std::unordered_map<int, pointer_to_thread> mapIdToThread;
        std::vector<pthread_t> running_threads;
        Mutex output_mutex;
    };

} // namespace cmd_interpreter

