#include "interpreterException.h"
#include <map>
#include <string>

namespace cmd_interpreter {

    const std::map<InterpreterExceptionType, std::string> interpreterExceptionMap{
            //TODO opisy błędów typu: {UNKNOWN_VALUETYPE, "THERE IS UNKNOWN VALUE TYPE"},
    };

    const char* InterpreterException::what() const noexcept {
        return interpreterExceptionMap.at(type).c_str();
    }

} // namespace cmd_interpreter