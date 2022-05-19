#include "readingCommands.h"

namespace cmd_interpreter {

    void ReadingCommands::execute() {
        auto read_tuple = command();
        if (read_tuple.has_value())
            tuple_string = tupleToString(*read_tuple);
        else
            tuple_string = "none";
    }

} // namespace cmd_interpreter