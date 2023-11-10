// CommandProcessingDriver.cpp
#include "CommandProcessing.h"
#include <iostream>

void testCommandProcessor() {
    int choice;
    std::string filename;
    GameEngine gameEngine;

    std::cout << "Pick between the two options:" << std::endl;
    std::cout << "Console Commands (1)" << std::endl;
    std::cout << "File Commands (2)" << std::endl;
    std::cout << "> ";
    std::cin >> choice;

    if (choice == 1) {
        ConsoleCommandProcessor consoleProcessor(&gameEngine);
        consoleProcessor.readCommand();

        Command cmd = consoleProcessor.getCommand();
        std::cout << "Command from console: " << cmd.command << ", Effect: " << cmd.effect << std::endl;
    } else if (choice == 2) {
        std::cout << "Enter filename: ";
        std::cin >> filename;

        FileCommandProcessorAdapter fileProcessor(filename, &gameEngine);
        fileProcessor.readCommand();

        while (!fileProcessor.isCommandsEmpty()) {
            Command cmd = fileProcessor.getCommand();
            std::cout << "Command from file: " << cmd.command << ", Effect: " << cmd.effect << std::endl;
        }
    } else {
        std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
    }
}

int main() {
    testCommandProcessor();
    return 0;
}