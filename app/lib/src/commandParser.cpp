#include "commandParser.h"
#include <climits>
#include "interpreterException.h"
#include "outputCommand.h"
#include "inputCommand.h"
#include "readCommand.h"
#include "tupleValuesParser.h"
#include "tupleConditionParser.h"

namespace cmd_interpreter {

    int CommandParser::parseCommand(std::istream &input, pointer_to_cmd &command, std::shared_ptr<Linda> &linda) {
        if(!getNextChar(input))
            throw InterpreterException(UNRECOGNIZED_COMMAND);

        omitWhiteChars(input);
        if(std::isdigit(last_read_char))
            return parseLindaCommand(input, command, linda);
        else if(last_read_char == 's') {
            parseSingleWordCommand(input, "start");
            return START;
        }
        else if(last_read_char == 'r') {
            parseSingleWordCommand(input, "reset");
            return RESET;
        }
        else if(last_read_char == 'h') {
            parseSingleWordCommand(input, "help");
            return HELP;
        }
        else if(last_read_char == 'e') {
            parseSingleWordCommand(input, "exit");
            return EXIT;
        }
        else if(last_read_char == 't') {
            parseSingleWordCommand(input, "threads");
            return LIST_THREADS;
        }
        else if(last_read_char == 'f') {
            parseWord(input, "file");
            return LOAD_FILE;
        }
        else if(last_read_char == '\n')
            return IDLE;

        input.ignore(INT_MAX, '\n');
        throw InterpreterException(UNRECOGNIZED_COMMAND);
    }

    std::string CommandParser::getPath(std::istream &input) {
        std::string path_to_file;

        if(!std::isblank(last_read_char) || !getNextChar(input)) {
            ignoreRestOfLine(input);
            throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        omitWhiteChars(input);
        if(last_read_char == '\n')
            throw InterpreterException(UNRECOGNIZED_COMMAND);

        while(!std::isblank(last_read_char) && last_read_char != '\n') {
            path_to_file += last_read_char;
            if(!getNextChar(input))
                throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        ignoreRestOfLine(input);
        return path_to_file;
    }

    bool CommandParser::getNextChar(std::istream &input) {
        input.get(last_read_char);
        return static_cast<bool>(input);
    }

    int CommandParser::parsePositiveInteger(std::istream &input) {
        std::string number_str;
        while(std::isdigit(last_read_char)) {
            number_str += last_read_char;
            if(!getNextChar(input))
                throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        int integer;
        try {
            integer = std::stoi(number_str);
        } catch(std::exception &) {
            ignoreRestOfLine(input);
            throw InterpreterException(NUMBER_TOO_LARGE);
        }

        if(integer <= 0) {
            ignoreRestOfLine(input);
            throw InterpreterException(NUMBER_NONPOSITIVE);
        }

        return integer;
    }

    void CommandParser::omitWhiteChars(std::istream &input) {
        while(std::isblank(last_read_char))
            if(!getNextChar(input))
                throw InterpreterException(UNRECOGNIZED_COMMAND);
    }

    void CommandParser::parseWord(std::istream &input, const std::string &&word) {
        for(char c: word) {
            if (c != last_read_char) {
                ignoreRestOfLine(input);
                throw InterpreterException(UNRECOGNIZED_COMMAND);
            }

            if (!getNextChar(input))
                throw InterpreterException(UNRECOGNIZED_COMMAND);
        }
    }

    void CommandParser::parseSingleWordCommand(std::istream &input, const std::string &&word) {
        parseWord(input, std::move(word));
        if(last_read_char != '\n') {
            input.ignore(INT_MAX, '\n');
            throw InterpreterException(UNRECOGNIZED_COMMAND);
        }
    }

    int CommandParser::parseLindaCommand(std::istream &input, pointer_to_cmd &command, std::shared_ptr<Linda> &linda) {
        int thread_id = parsePositiveInteger(input);
        omitWhiteChars(input);
        if(last_read_char != ':') {
            ignoreRestOfLine(input);
            throw InterpreterException(MISSING_COLON);
        }

        if(!getNextChar(input))
            throw InterpreterException(UNRECOGNIZED_COMMAND);

        omitWhiteChars(input);

        char operation_first_letter = last_read_char;
        if(last_read_char == 'o' || last_read_char == 'i' || last_read_char == 'r') {
            if(last_read_char == 'o')
                parseWord(input, "output");
            else if(last_read_char == 'i')
                parseWord(input, "input");
            else
                parseWord(input, "read");

            omitWhiteChars(input);
            if(last_read_char != '(' || !getNextChar(input)) {
                ignoreRestOfLine(input);
                throw InterpreterException(MISSING_PARENTHESIS);
            }

            if(operation_first_letter == 'o')
                command = std::move(parseOutputCommand(input, linda));
            else if(operation_first_letter == 'i')
                command = std::move(parseInputCommand(input, linda));
            else
                command = std::move(parseReadCommand(input, linda));
        }
        else {
            ignoreRestOfLine(input);
            throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        return thread_id;
    }

    pointer_to_cmd CommandParser::parseOutputCommand(std::istream &input, std::shared_ptr<Linda> &linda) {
        auto parsedValues = TupleValuesParser(getTillNextParenthesis(input)).parseAllValues();
        uxp::Tuple parsedTuple(parsedValues);
        pointer_to_cmd cmd = std::make_unique<OutputCommand>(linda, std::move(parsedTuple));

        if(!getNextChar(input) || last_read_char != '\n') {
            input.ignore(INT_MAX, '\n');
            throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        return cmd;
    }

    pointer_to_cmd CommandParser::parseInputCommand(std::istream &input, std::shared_ptr<Linda> &linda) {
        Time time;
        TupleCondition pattern;
        std::string pattern_str;
        parseTuplePatternAndTime(input, pattern, time, pattern_str);
        return std::make_unique<InputCommand>(linda, pattern, time, pattern_str);
    }

    pointer_to_cmd CommandParser::parseReadCommand(std::istream &input, std::shared_ptr<Linda> &linda) {
        Time time;
        TupleCondition pattern;
        std::string pattern_str;
        parseTuplePatternAndTime(input, pattern, time, pattern_str);
        return std::make_unique<ReadCommand>(linda, pattern, time, pattern_str);
    }

    std::string CommandParser::getTillNextParenthesis(std::istream &input) {
        std::string result;
        while(last_read_char != ')') {
            result += last_read_char;
            if(last_read_char == '\n' || !getNextChar(input))
                throw InterpreterException(MISSING_PARENTHESIS);
        }
        return result;
    }

    void CommandParser::parseTuplePatternAndTime(std::istream &input, TupleCondition &pattern, Time &time, std::string &cond_str) {
        omitWhiteChars(input);
        if(last_read_char != '(' || !getNextChar(input)) {
            ignoreRestOfLine(input);
            throw InterpreterException(MISSING_PARENTHESIS);
        }

        cond_str = getTillNextParenthesis(input);
        pattern = TupleCondition(TupleConditionParser(cond_str).parseWholeCondition());

        if(!getNextChar(input))
            throw InterpreterException(UNRECOGNIZED_COMMAND);

        omitWhiteChars(input);
        if(last_read_char != ',') {
            ignoreRestOfLine(input);
            throw InterpreterException(MISSING_COMMA);
        }

        if(!getNextChar(input))
            throw InterpreterException(UNRECOGNIZED_COMMAND);

        omitWhiteChars(input);
        if(!std::isdigit(last_read_char)) {
            ignoreRestOfLine(input);
            throw InterpreterException(UNRECOGNIZED_COMMAND);
        }

        time = parsePositiveInteger(input);
        omitWhiteChars(input);

        if(last_read_char != ')') {
            ignoreRestOfLine(input);
            throw InterpreterException(MISSING_PARENTHESIS);
        }

        if(!getNextChar(input) || last_read_char != '\n') {
            input.ignore(INT_MAX, '\n');
            throw InterpreterException(UNRECOGNIZED_COMMAND);
        }
    }

    void CommandParser::ignoreRestOfLine(std::istream &input) const {
        if(last_read_char != '\n')
            input.ignore(INT_MAX, '\n');
    }

} // namespace cmd_interpreter