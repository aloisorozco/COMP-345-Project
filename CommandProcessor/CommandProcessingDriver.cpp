// CommandProcessingDriver.cpp
#include "CommandProcessing.h"
#include <iostream>
#include <thread>
#include <chrono>

void printProcessor() {
    std::cout << "***** WARZONE COMMANDS PROCESSOR****\n";
    std::cout << "******************************\n";
}

void testCommandProcessor() {
    int choice;
    std::string filename;

    // Initialisation of the engine
    GameEngine engine;
    gameInit(engine);

    // Driver loop
    while (true) {

    clearScreen();
    printProcessor();
    std::cout << "** Current state: " << engine.getCurrentState()->getName() << "**\n";
    std::cout << "------------------------------" << std::endl;
    std::cout << "|| Pick between the two options:" << std::endl;
    std::cout << "|| (1) Console Commands" << std::endl;
    std::cout << "|| (2) File Commands" << std::endl;
    std::cout << "|| (3) Quit" << std::endl;
    std::cout << "|| > ";
    std::cin >> choice;

    

    if (choice == 1) {
        // Initialisation of the CommandProcessor
        ConsoleCommandProcessor consoleProcessor(&engine);

        Command K = consoleProcessor.getCommand();
        
   

        
    } else if (choice == 2) {
        
        std::cout << "---------------------\n" << "|| Enter filename: ";
        std::cin >> filename;

        // Initialisation of the CommandProcessor
        FileCommandProcessorAdapter fileProcessor(filename,&engine);
        Command K = fileProcessor.getCommand();
        
        
        
    } else if (choice == 3) {
        break;
        
    } else {
        std::cout << "Invalid choice. Please enter 1 or 2 or 3." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait for 3 seconds for displaying result
        break;
    }
    }
}

