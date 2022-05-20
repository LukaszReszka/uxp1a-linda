#pragma once
#include <exception>

namespace cmd_interpreter {

    enum InterpreterExceptionType {
        NO_THREADS_DEFINED,
        CANNOT_CREATE_THREAD,
        FATAL_ERROR_WHILE_THREAD_JOINING,
        FATAL_ERROR_WHILE_THREAD_CANCELLING,
    };

    class InterpreterException: public std::exception {
    public:
        explicit InterpreterException(InterpreterExceptionType exceptionType) : type(exceptionType) {}

        [[nodiscard]] const char* what() const noexcept override;

        ~InterpreterException() override = default;
    private:
        InterpreterExceptionType type;
    };

} // namespace cmd_interpreter


