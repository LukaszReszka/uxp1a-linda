#include "commandParser.h"
#include <iostream>
#include <climits>
#include "interpreterException.h"

namespace cmd_interpreter {

    int CommandParser::parseCommand(std::istream &input, pointer_to_cmd &command, std::shared_ptr<Linda> &linda) {

    }

    std::string CommandParser::getPath(std::istream &input) {
        std::string path_to_file;

        while(!std::isblank(last_read_char) && input)
            input.get(last_read_char);

        if(input && last_read_char != '\n')
        {
            input >> path_to_file;
            input.ignore(INT_MAX, '\n');
        }

        return path_to_file;
    }

    bool CommandParser::getNextChar(std::istream &input) {
        input.get(last_read_char);
        return (input && last_read_char != '\n');
    }

    int CommandParser::parseInteger(std::istream &input) {
        std::string number_str;
        while(std::isdigit(last_read_char)) {
            number_str += last_read_char;
            if(!getNextChar(input))
                throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        try {
            return std::stoi(number_str);
        } catch(std::exception &) {
            input.ignore(INT_MAX, '\n');
            throw InterpreterException(NUMBER_TOO_LARGE);
        }
    }

    void CommandParser::omitWhiteChars(std::istream &input) {
        while(std::isblank(last_read_char) && input)
            input.get(last_read_char);
    }

    void CommandParser::parseWord(std::istream &input, const std::string &&word) {
        for(char c: word) {
            if (c != last_read_char) {
                input.ignore(INT_MAX, '\n');
                throw InterpreterException(UNRECOGNIZED_COMMAND);
            }

            if (!getNextChar(input))
                throw InterpreterException(UNRECOGNIZED_COMMAND);
        }
    }

} // namespace cmd_interpreter