// CommandProcessing.cpp
#include "CommandProcessing.h"
#include <iostream>
#include <limits>

void CommandProcessor::saveCommand(const std::string& command) {
    Command cmd;
    cmd.command = command;
    commands.push_back(cmd);
}

bool CommandProcessor::validate(const std::string& command) {
    // Not implemented yet -> every command is considered valid.
    return true;
}


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
            std::cout<<"| Command is valid and saved |"<< endl;
        } else {
            std::cout<<"| Command is invalid and saved |"<< endl;
        }
}

std::string ConsoleCommandProcessor::getInputFromConsole() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining input    
    std::string command;
    std::cout << "Enter command: ";
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
        return;
    }

    std::string command;
    while (std::getline(file, command)) {
        bool valid=false;
        std::cout << "New command catched : " << command ; 
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
            std::cout<<"\t| Command is valid and saved |"<< endl;
        } else {
            std::cout<<"\t| Command is invalid and saved |"<< endl;
        }
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
