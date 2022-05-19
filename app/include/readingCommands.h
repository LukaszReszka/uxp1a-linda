#pragma once
#include <functional>
#include <optional>
#include "lindaCommand.h"
#include "linda.h"

namespace cmd_interpreter {

    class ReadingCommands: public LindaCommand {
    public:
        explicit ReadingCommands(std::string &search_conditions) : tuple_conditions(search_conditions) {}
        std::string getInfoBeforeExecution() override = 0;
        void execute() override;
        std::string getInfoAfterExecution() override = 0;
        ~ReadingCommands() override = default;

    protected:
        std::function<std::optional<uxp::Tuple>(void)> command;
        std::string tuple_string, tuple_conditions;
    };

} // namespace cmd_interpreter

