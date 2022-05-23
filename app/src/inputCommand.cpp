#include "inputCommand.h"

namespace cmd_interpreter {

    InputCommand::InputCommand(std::shared_ptr<Linda> linda, TupleCondition &cond, Time &time, std::string &cond_str) : ReadingCommands(cond_str) {
        command = [&linda, &cond, &time]() {
            return linda->input(cond, time);
        };
    }

    std::string InputCommand::getInfoBeforeExecution() {
        return "Getting tuple " + tuple_conditions + " ...";
    }

    std::string InputCommand::getInfoAfterExecution() {
        return "Removed tuple " + tuple_string;
    }
} // namespace cmd_interpreter