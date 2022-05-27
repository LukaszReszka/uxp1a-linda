#include "readCommand.h"

namespace cmd_interpreter {

    ReadCommand::ReadCommand(std::shared_ptr<Linda> &linda, TupleCondition &cond, Time &time, std::string &cond_str) : ReadingCommands(cond, time, cond_str) {
        command = [&linda, this]() {
            return linda->read(this->tupleCondition, this->timeout);
        };
    }

    std::string ReadCommand::getInfoBeforeExecution() {
        return "Reading tuple (" + tuple_conditions + "), timeout = " + std::to_string(timeout);
    }

    std::string ReadCommand::getInfoAfterExecution() {
        return "Read tuple " + tuple_string;
    }
} // namespace cmd_interpreter