// CommandProcessingDriver.cpp
#include "CommandProcessing.h"
#include <iostream>

void testCommandProcessor() {
    int choice;
    std::string filename;

    // Initialisation of the engine
    GameEngine* initializer = new GameEngine();
    GameEngine engine = initializer->gameInit();
    delete initializer;

    std::cout << "Pick between the two options:" << std::endl;
    std::cout << "Console Commands (1)" << std::endl;
    std::cout << "File Commands (2)" << std::endl;
    std::cout << "> ";
    std::cin >> choice;

    

    if (choice == 1) {
        // Initialisation of the CommandProcessor
        ConsoleCommandProcessor consoleProcessor(&engine);

        consoleProcessor.getCommand();

        
    } else if (choice == 2) {
        
        std::cout << "Enter filename: ";
        std::cin >> filename;

        // Initialisation of the CommandProcessor
        FileCommandProcessorAdapter fileProcessor(filename,&engine);

        fileProcessor.getCommand();
        
    } else {
        std::cout << "Invalid choice. Please enter 1 or 2." << std::endl;
    }
}

