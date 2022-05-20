#include "threadsController.h"
#include "interpreterException.h"

namespace cmd_interpreter {

    void ThreadsController::addCommandToThread(uint thread_id, pointer_to_cmd command) {
        if(mapIdToThread.find(thread_id) == mapIdToThread.end())
            mapIdToThread.insert({thread_id, std::make_unique<Thread>(thread_id, output_mutex)});

        mapIdToThread.at(thread_id)->addCommand(std::move(command));
    }

    void ThreadsController::launchAllThreads() {
        if(mapIdToThread.empty())
            throw InterpreterException(NO_THREADS_DEFINED);

        for(auto &iter: mapIdToThread) {
            pthread_t thread_id;
            if(!pthread_create(&thread_id, NULL, &Thread::runThread, &iter.second)) {
                cancelRunningThreads();
                waitForAllThreadsTermination();
                throw InterpreterException(CANNOT_CREATE_THREAD);
            }

            running_threads.push_back(thread_id);
        }

        waitForAllThreadsTermination();
        mapIdToThread.clear();
    }

    ThreadsController::~ThreadsController() {
        cancelRunningThreads();
        waitForAllThreadsTermination();
        mapIdToThread.clear();
    }

    void ThreadsController::waitForAllThreadsTermination() {
        for(auto thread: running_threads)
            if(!pthread_join(thread, NULL))
                throw InterpreterException(FATAL_ERROR_WHILE_THREAD_JOINING);

        running_threads.clear();
    }

    void ThreadsController::cancelRunningThreads() {
        for(auto thread: running_threads)
            if(!pthread_cancel(thread))
                throw InterpreterException(FATAL_ERROR_WHILE_THREAD_CANCELLING);
    }

} // namespace cmd_interpreter