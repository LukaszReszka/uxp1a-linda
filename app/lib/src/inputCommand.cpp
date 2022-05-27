#include "inputCommand.h"

namespace cmd_interpreter {

    InputCommand::InputCommand(std::shared_ptr<Linda> &linda, TupleCondition &cond, Time &time, std::string &cond_str) : ReadingCommands(cond, time, cond_str) {
        command = [&linda, this]() {
            return linda->input(this->tupleCondition, this->timeout);
        };
    }

    std::string InputCommand::getInfoBeforeExecution() {
        return "Getting tuple (" + tuple_conditions + "), timeout = " + std::to_string(timeout);
    }

    std::string InputCommand::getInfoAfterExecution() {
        return "Removed tuple " + tuple_string;
    }
} // namespace cmd_interpreter