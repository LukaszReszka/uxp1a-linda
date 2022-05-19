#pragma once
#include <string>
#include "lindaTuple.h"

namespace cmd_interpreter {

    class LindaCommand {
    public:
        virtual std::string getInfoBeforeExecution() = 0;
        virtual void execute() = 0;
        virtual std::string getInfoAfterExecution() = 0;
        virtual ~LindaCommand() = default;

    protected:
        static std::string tupleToString(const uxp::Tuple &tuple);
    };

} // namespace cmd_interpreter

