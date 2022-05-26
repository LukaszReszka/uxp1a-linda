#pragma once
#include <map>
#include "thread.h"
#include "mutex.h"

namespace cmd_interpreter {

    using pointer_to_thread = std::unique_ptr<Thread>;

    class ThreadsController {
    public:
        ThreadsController() {output_mutex = std::make_shared<Mutex>();};
        void addCommandToThread(int thread_id, pointer_to_cmd command);
        void launchAllThreads();
        inline void removeSavedThreads() { mapIdToThread.clear(); }
        std::string showAllSavedThreads();
        ~ThreadsController();

    private:
        void waitForAllThreadsTermination();
        void cancelRunningThreads();

        std::map<int, pointer_to_thread> mapIdToThread;
        std::vector<pthread_t> running_threads;
        std::shared_ptr<Mutex> output_mutex;
    };

} // namespace cmd_interpreter

