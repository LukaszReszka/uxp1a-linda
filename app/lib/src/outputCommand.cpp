#include "outputCommand.h"

namespace cmd_interpreter {
    OutputCommand::OutputCommand(std::shared_ptr<Linda> &linda, uxp::Tuple &&tpl) : tuple(std::move(tpl)) {
        tuple_string = tupleToString(tuple);
        command = [&linda, this]() {
            linda->output(std::move((this->tuple)));
        };
    }

    void OutputCommand::execute()  {
        command();
    }

    std::string OutputCommand::getInfoBeforeExecution() {
        return "Inserting tuple " + tuple_string;
    }

    std::string OutputCommand::getInfoAfterExecution() {
        return "Inserted tuple " + tuple_string;
    }

} // namespace cmd_interpreter