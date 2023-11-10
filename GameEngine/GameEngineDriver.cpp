//GameEngineDriver.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.h"





// Console-driven interface that allows the user to navigate through all the states by typing commands
void testGameStates(){
    std::chrono::seconds sleepDuration(1);
    GameEngine* initializer = new GameEngine();
    GameEngine engine = initializer->gameInit();
    delete initializer;
    

    std::string command;
    while (true) {
        // Clearing terminal screen
        engine.clearScreen();

        //getting available commands for current state
        std::vector<std::string> availableCommands = engine.getAvailableCommands();
        
        //converting vector of strings into a single string separated by a \n
        std::string commandsStr;
        for (std::vector<std::string>::iterator it = availableCommands.begin(); it != availableCommands.end(); ++it) {
            std::string cmd = *it;
            commandsStr += "* > " +cmd + "\n";
        }

        // Displaying status box
        engine.printBox(engine.getCurrentState()->getName(), commandsStr);
        std::cout << "Enter command: ";
        std::cin >> command;
        if (command == "end") {
            std::cout<<"Game ended";
            break;
        }

        // Displaying result of the command
        std::cout << "\n- ";
        engine.processCommand(command);
        std::cout << "******************************\n";
        std::this_thread::sleep_for(sleepDuration);
        
    }
}



    


