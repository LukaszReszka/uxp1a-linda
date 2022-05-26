#include "outputCommand.h"

namespace cmd_interpreter {
    OutputCommand::OutputCommand(std::shared_ptr<Linda> &linda, uxp::Tuple &&tuple) :tpl(std::move(tuple)) {
        tuple_string = tupleToString(tpl);
        command = [&linda, this]() {
            linda->output(std::move((this->tpl)));
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