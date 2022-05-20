#include "interpreterException.h"
#include <map>
#include <string>

namespace cmd_interpreter {

    const std::map<InterpreterExceptionType, std::string> interpreterExceptionMap{
            {NO_THREADS_DEFINED, "NO THREADS DEFINED"},
            {CANNOT_CREATE_THREAD, "CANNOT CREATE SPECIFIED THREAD(S)"},
            {FATAL_ERROR_WHILE_THREAD_JOINING, "ERROR OCCURRED WHILE WAITING FOR THREAD TERMINATION"},
            {FATAL_ERROR_WHILE_THREAD_CANCELLING, "ERROR OCCURRED WHILE WAITING FOR THREAD CANCELLATION"},
    };

    const char* InterpreterException::what() const noexcept {
        return interpreterExceptionMap.at(type).c_str();
    }

} // namespace cmd_interpreter