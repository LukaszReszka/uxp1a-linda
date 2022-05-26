#include "readCommand.h"

namespace cmd_interpreter {

    ReadCommand::ReadCommand(std::shared_ptr<Linda> &linda, TupleCondition &cond, Time &time, std::string &cond_str) : ReadingCommands(cond_str) {
        command = [&linda, &cond, &time]() {
            return linda->read(cond, time);
        };
    }

    std::string ReadCommand::getInfoBeforeExecution() {
        return "Reading tuple " + tuple_conditions;
    }

    std::string ReadCommand::getInfoAfterExecution() {
        return "Read tuple " + tuple_string;
    }
} // namespace cmd_interpreter