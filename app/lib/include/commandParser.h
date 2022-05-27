#pragma once

#include "lindaCommand.h"
#include "linda.h"

namespace cmd_interpreter {

    enum CommandType {
        LINDA_COMMAND_MIN_THREAD_ID = 1,
        IDLE = 0,
        START = -1,
        RESET = -2,
        EXIT = -3,
        HELP = -4,
        LOAD_FILE = -5,
        LIST_THREADS = -6
    };

    class CommandParser {
    public:
        int parseCommand(std::istream &input, pointer_to_cmd &command, std::shared_ptr<Linda> &linda);
        std::string getPath(std::istream &input);

    private:
        char last_read_char;
        int parsePositiveInteger(std::istream &input);
        bool getNextChar(std::istream &input);
        void omitWhiteChars(std::istream &input);
        void parseWord(std::istream &input, const std::string &&word);
        void parseSingleWordCommand(std::istream &input, const std::string &&word);
        int parseLindaCommand(std::istream &input, pointer_to_cmd &command, std::shared_ptr<Linda> &linda);
        pointer_to_cmd parseOutputCommand(std::istream &input, std::shared_ptr<Linda> &linda);
        pointer_to_cmd parseInputCommand(std::istream &input, std::shared_ptr<Linda> &linda);
        pointer_to_cmd parseReadCommand(std::istream &input, std::shared_ptr<Linda> &linda);
        void parseTuplePatternAndTime(std::istream &input, TupleCondition &pattern, Time &time,  std::string &cond_str);
        std::string getTillNextParenthesis(std::istream &input);
        void ignoreRestOfLine(std::istream &input) const;
    };

} // namespace cmd_interpreter
