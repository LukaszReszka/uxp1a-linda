#pragma once
#include <functional>
#include "lindaCommand.h"
#include "linda.h"

namespace cmd_interpreter {

    class OutputCommand: public LindaCommand {
    public:
        OutputCommand(Linda &linda, uxp::Tuple &&tuple);
        std::string getInfoBeforeExecution() override;
        void execute() override;
        std::string getInfoAfterExecution() override;
        ~OutputCommand() override = default;

    private:
        std::function<void(void)> command;
        std::string tuple_string;
    };

} // namespace cmd_interpreter
