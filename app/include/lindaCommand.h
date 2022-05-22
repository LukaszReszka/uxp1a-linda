#pragma once
#include <string>
#include <memory>
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

    using pointer_to_cmd = std::unique_ptr<LindaCommand>;

} // namespace cmd_interpreter

