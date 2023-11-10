// CommandProcessingDriver.cpp
#include "CommandProcessing.h"
#include <iostream>

void testCommandProcessor() {
    GameEngine gameEngine;
    ConsoleCommandProcessor consoleProcessor(&gameEngine);
    FileCommandProcessorAdapter fileProcessor("commands.txt", &gameEngine);

    consoleProcessor.readCommand();
    fileProcessor.readCommand();

    Command cmd = consoleProcessor.getCommand();
    std::cout << "Command from console: " << cmd.command << ", Effect: " << cmd.effect << std::endl;

    cmd = fileProcessor.getCommand();
    std::cout << "Command from file: " << cmd.command << ", Effect: " << cmd.effect << std::endl;

}

int main() {
    testCommandProcessor();
    return 0;
}