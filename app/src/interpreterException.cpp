#include "interpreterException.h"
#include <map>
#include <string>

namespace cmd_interpreter {

    const std::map<InterpreterExceptionType, std::string> interpreterExceptionMap{
            {NO_THREADS_DEFINED,                  "NO THREADS DEFINED"},
            {CANNOT_CREATE_THREAD,                "CANNOT CREATE SPECIFIED THREAD(S)"},
            {FATAL_ERROR_WHILE_THREAD_JOINING,    "ERROR OCCURRED WHILE WAITING FOR THREAD TERMINATION"},
            {FATAL_ERROR_WHILE_THREAD_CANCELLING, "ERROR OCCURRED WHILE WAITING FOR THREAD CANCELLATION"},
            {UNRECOGNIZED_COMMAND,                "UNRECOGNIZED COMMAND"},
            {CANNOT_OPEN_FILE,                    "CANNOT OPEN SPECIFIED FILE"},
            {CANNOT_CLOSE_FILE,                   "CANNOT CLOSE FILE"},
            {NUMBER_TOO_LARGE,                    "INTEGER TOO LARGE"},
            {NUMBER_NONPOSITIVE,                  "ONLY POSITIVE INTEGERS ALLOWED"},
            {MISSING_COLON,                       "MISSING COLON AFTER THREAD_ID"},
            {MISSING_PARENTHESIS,                 "MISSING PARENTHESIS"},
            {MISSING_COMMA,                       "MISSING COMMA"},
    };

    const char* InterpreterException::what() const noexcept {
        return interpreterExceptionMap.at(type).c_str();
    }

} // namespace cmd_interpreter