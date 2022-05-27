#pragma once
#include <functional>
#include <optional>
#include <sstream>
#include "lindaCommand.h"
#include "linda.h"

namespace cmd_interpreter {

    class ReadingCommands: public LindaCommand {
    public:
        explicit ReadingCommands(TupleCondition &cond, Time& time , std::string &search_conditions): tupleCondition(cond), timeout(time) {
            std::stringstream ss(search_conditions);
            std::string word;
            while(ss >> word)
                tuple_conditions += word;
        }
        std::string getInfoBeforeExecution() override = 0;
        void execute() override;
        std::string getInfoAfterExecution() override = 0;
        ~ReadingCommands() override = default;

    protected:
        std::function<std::optional<uxp::Tuple>(void)> command;
        std::string tuple_string, tuple_conditions;
        TupleCondition tupleCondition;
        Time timeout;
    };

} // namespace cmd_interpreter

