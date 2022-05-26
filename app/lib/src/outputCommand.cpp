#include "outputCommand.h"

namespace cmd_interpreter {
    OutputCommand::OutputCommand(std::shared_ptr<Linda> &linda, uxp::Tuple tuple) {
        tuple_string = tupleToString(tuple);
        command = [&linda, &tuple]() {
            linda->output(std::move(tuple));
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