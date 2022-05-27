#include "commandInterpreter.h"
#include <iostream>
#include <climits>
#include <fstream>
#include "interpreterException.h"
#include "parserException.h"

namespace cmd_interpreter {

    const std::string COMMAND_PROMPT = ">>> ";
    const std::string WELCOME_MESSAGE = "Linda Command Interpreter - type 'help' for list of available instructions";
    const std::string HELP_MESSAGE = "List of available instructions:\n"
                                     "> Linda Commands:\n"
                                     ">> thread_id:output(tuple), e.g. 0:output(string=\"ok\", float =1.1)\n"
                                     ">> thread_id:input((tuple_pattern), timeout_string), e.g. 1:input((string:\"no\", "
                                     "integer:*), 100)\n"
                                     ">> thread_id:read((tuple_pattern), timeout_string), e.g. 2:read((integer:<5), 200)\n"
                                     "> start -> launch all predefined threads\n"
                                     "> reset -> reset Linda and all saved threads\n"
                                     "> threads -> list details about all saved threads\n"
                                     "> file <path> -> read Linda commands from specified file; apart from <path> (single 'word'), rest of the line will be ignored\n"
                                     "> exit -> exit interpreter.\n"
                                     "After each command the '\\n' is required\n\n";

    CommandInterpreter::CommandInterpreter() {
        linda = std::make_shared<Linda>();
        threads_controller = std::make_unique<ThreadsController>();
        parser = std::make_unique<CommandParser>();
    }

    void CommandInterpreter::runInterpreter() {
        system("clear");
        exitInterpreter = false;
        std::cout << WELCOME_MESSAGE << std::endl;

        do {
            std::cout << COMMAND_PROMPT;
            try {
                handleCommand(std::cin, false);

            } catch (const ParserException &e) {
                std::cout << "ERROR: " << e.what() << std::endl;
                std::cin.clear();
                std::cin.ignore(INT_MAX, '\n');

            } catch (const InterpreterException &e) {
                std::cin.clear();
                std::cout << "ERROR: " << e.what() << std::endl;
            }
        } while(!exitInterpreter);
    }

    void CommandInterpreter::handleCommand(std::istream &input, bool during_processing_file_command) {
        pointer_to_cmd cmd;

        int cmd_type = parser->parseCommand(input, cmd, linda);

        if (cmd_type >= LINDA_COMMAND_MIN_THREAD_ID)
            threads_controller->addCommandToThread(cmd_type, std::move(cmd));
        else if(cmd_type == IDLE)
            return;
        else if(!during_processing_file_command) {
            if (cmd_type == START)
                threads_controller->launchAllThreads();
            else if (cmd_type == RESET) {
                threads_controller->removeSavedThreads();
                linda = std::make_shared<Linda>();
                std::cout << "Reset done" << std::endl;
            } else if (cmd_type == LOAD_FILE)
                loadCommandsSavedInFile(input);
            else if (cmd_type == LIST_THREADS)
                std::cout << threads_controller->showAllSavedThreads();
            else if (cmd_type == HELP)
                std::cout << HELP_MESSAGE;
            else if (cmd_type == EXIT)
                exitInterpreter = true;
            else
                throw InterpreterException(UNRECOGNIZED_COMMAND);
        }
        else
            throw InterpreterException(UNRECOGNIZED_COMMAND);
    }

    void CommandInterpreter::loadCommandsSavedInFile(std::istream &input) {
        std::ifstream file(parser->getPath(input), std::ifstream::in);

        if(!file)
            throw InterpreterException(CANNOT_OPEN_FILE);

        unsigned int line_number = 1;
        do {
            try {
                handleCommand(file, true);

            } catch (const ParserException &e) {
                std::cout << "ERROR (line " + std::to_string(line_number) + "): " << e.what() << std::endl;

            } catch (const InterpreterException &e) {
                std::cout << "ERROR (line " + std::to_string(line_number) + "): " << e.what() << std::endl;
            }
            ++line_number;
        } while(!file.eof());

        std::cout << "Loaded Linda commands from file" << std::endl;

        file.close();
        if(!file)
            throw InterpreterException(CANNOT_CLOSE_FILE);
    }

} // namespace cmd_interpreter