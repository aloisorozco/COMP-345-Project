// CommandProcessing.cpp
#include "CommandProcessing.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <thread>
#include <chrono>

//Saving command to the command Vector
void CommandProcessor::saveCommand(const std::string& command) {
    Command cmd;
    cmd.command = command;
    commands.push_back(cmd);
}

//Command validation
bool CommandProcessor::validate(const std::string& command) {


    // Split the command into words for easier processing
    std::vector<std::string> commandWords ;
    std::istringstream iss(command);
    for(std::string s; iss >> s; )
        commandWords.push_back(s);

    // Get the current state of the game
    GameState* currentState = gameEngine->getCurrentState();
    

    // Check the command based on the current state
    if (currentState->getName() == "Start") {
        if (commandWords[0] == "loadmap") {
            //gameEngine->processCommand(commandWords[0]);
            return true;
        }
    }
    else if (currentState->getName() == "Map Loaded") {
        if (commandWords[0] == "validatemap") {
            //gameEngine->processCommand(commandWords[0]);
            return true;
        }
        if (commandWords[0] == "loadmap") {
            //gameEngine->processCommand(commandWords[0]);
            return true;
        }
    }
    else if (currentState->getName() == "Map Validated") {
        if (commandWords[0] == "addplayer") {
            //gameEngine->processCommand(commandWords[0]);
            return true;
        }
    }
    else if (currentState->getName() == "Players Added") {
        if (commandWords[0] == "addplayer") {
            //gameEngine->processCommand(commandWords[0]);
            return true;
        }
        if (commandWords[0] == "gamestart") {
            //gameEngine->processCommand(commandWords[0]);
            return true;
        }
    }
    else if (currentState->getName() == "Win") {
        if (commandWords[0] == "replay" || commandWords[0] == "quit") {
            return true;
        }
    }

    // If none of the conditions are met, the command is invalid
    return false;
}

//Saving the effect
void CommandProcessor::saveEffect(const std::string& effect) {
    if (!commands.empty()) {
        commands.back().effect = effect;
    }
}

bool CommandProcessor::isCommandsEmpty() {
    return commands.empty();
}


void ConsoleCommandProcessor::readCommand() {
    bool valid=false;
    std::string command = getInputFromConsole();
    if (validate(command)) {
        saveCommand(command);
        valid = true;
    } else {
        Command cmd;
        cmd.command = command;
        cmd.effect = "Invalid command";
        commands.push_back(cmd);
    }
    if (valid) {
            std::cout<<"|| Command is valid and saved "<< endl;
        } else {
            std::cout<<"|| Command is invalid and saved "<< endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait for 3 seconds for displaying result
}

std::string ConsoleCommandProcessor::getInputFromConsole() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining input    
    std::string command;
    std::cout << "---------------------\n" << "|| Enter command: ";
    std::getline(std::cin, command);
    return command;
}

Command ConsoleCommandProcessor::getCommand() {
    readCommand();
    if (!commands.empty()) {
        Command cmd = commands.front();
        commands.erase(commands.begin());
        return cmd;
    }
    return Command();  // Return an empty Command object if there are no commands
}

void FileCommandProcessorAdapter::readCommand() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait for 2 seconds for displaying result

        return;
    }

    std::string command;
    while (std::getline(file, command)) {
        bool valid=false;
        std::cout << "|| New command catched : " << command << endl; 
        if (validate(command)) {
            saveCommand(command);
            valid = true;
        } else {
            Command cmd;
            cmd.command = command;
            cmd.effect = "Invalid command";
            commands.push_back(cmd);
        }
        if (valid) {
            std::cout<<"|| Command is valid and saved "<< endl;
        } else {
            std::cout<<"|| Command is invalid and saved "<< endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3)); // Wait for 3 seconds for displaying result
        std::cout << "-----------------------" << std::endl;
    }

    file.close();
}

Command FileCommandProcessorAdapter::getCommand() {
    readCommand();
    if (!commands.empty()) {
        Command cmd = commands.front();
        commands.erase(commands.begin());
        return cmd;
    }
    return Command();  // Return an empty Command object if there are no commands
}

void printProcessor() {
    std::cout << "***** WARZONE COMMANDS PROCESSOR****\n";
    std::cout << "******************************\n";
}