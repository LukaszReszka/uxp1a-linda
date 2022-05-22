#pragma once
#include "commandParser.h"
#include "threadsController.h"

namespace cmd_interpreter {

    class CommandInterpreter {
    public:
        CommandInterpreter();
        void runInterpreter();

    private:
        std::shared_ptr<Linda> linda;
        std::unique_ptr<CommandParser> parser;
        std::unique_ptr<ThreadsController> threads_controller;
        bool exitInterpreter = false;

        void handleCommand(std::istream &input, bool during_processing_file_command);
        void loadCommandsFromFile(std::istream &input);
    };

} // namespace cmd_interpreter
