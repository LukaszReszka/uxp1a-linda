#pragma once
#include "readingCommands.h"

namespace cmd_interpreter {

    class InputCommand: public ReadingCommands {
    public:
        InputCommand(Linda &linda, TupleCondition &cond, Time &time, std::string &cond_str);
        std::string getInfoBeforeExecution() override;
        std::string getInfoAfterExecution() override;
        ~InputCommand() override = default;
    };

} // namespace cmd_interpreter
