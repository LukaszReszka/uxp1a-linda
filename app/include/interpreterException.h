#pragma once
#include <exception>

namespace cmd_interpreter {

    enum InterpreterExceptionType {
        // TODO typy wyjątków
    };

    class InterpreterException: public std::exception {
    public:
        explicit InterpreterException(InterpreterExceptionType exceptionType) : type(exceptionType) {}

        const char* what() const noexcept override;

        ~InterpreterException() override = default;
    private:
        InterpreterExceptionType type;
    };

} // namespace cmd_interpreter


