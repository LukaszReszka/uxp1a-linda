#pragma once
#include "lindaCommand.h"
#include "linda.h"

namespace cmd_interpreter {

    enum CommandType {
        LINDA_COMMAND_MIN_THREAD_ID = 0,
        START = -1,
        RESET = -2,
        EXIT = -3,
        HELP = -4,
        LOAD_FILE = -5
    };

    class CommandParser {
    public:
        int parseCommand(std::istream &input, pointer_to_cmd &command, std::shared_ptr<Linda> &linda);
        std::string getPath(std::istream &input);

    private:
        char last_read_char;
        int parseInteger(std::istream &input);
        bool getNextChar(std::istream &input);
        void omitWhiteChars(std::istream &input);
        void parseWord(std::istream &input, const std::string &&word);
    };

} // namespace cmd_interpreter
