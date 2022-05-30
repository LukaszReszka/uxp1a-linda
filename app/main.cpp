#include "commandInterpreter.h"

int main() {

    auto command_interpreter = cmd_interpreter::CommandInterpreter();
    command_interpreter.runInterpreter();

    return 0;
}