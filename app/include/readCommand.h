#pragma once
#include "readingCommands.h"

namespace cmd_interpreter {

    class ReadCommand: public ReadingCommands {
    public:
        ReadCommand(std::shared_ptr<Linda> linda, TupleCondition &cond, Time &time, std::string &cond_str);
        std::string getInfoBeforeExecution() override;
        std::string getInfoAfterExecution() override;
        ~ReadCommand() override = default;
    };

} // namespace cmd_interpreter