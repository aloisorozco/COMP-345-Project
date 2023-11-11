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

Command CommandProcessor::getCommand() {
    Command cmd = commands.front();
    commands.erase(commands.begin());
    return cmd;
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
    std::string command = getInputFromConsole();
    if (validate(command)) {
        saveCommand(command);
    } else {
        Command cmd;
        cmd.command = command;
        cmd.effect = "Invalid command";
        commands.push_back(cmd);
    }
}

std::string ConsoleCommandProcessor::getInputFromConsole() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore remaining input    
    std::string command;
    std::cout << "Enter command: ";
    std::getline(std::cin, command);
    return command;
}

void FileCommandProcessorAdapter::readCommand() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << fileName << std::endl;
        return;
    }

    std::string command;
    while (std::getline(file, command)) {
        std::cout << "New command catched : " << command << std::endl; 
        if (validate(command)) {
            saveCommand(command);
        } else {
            Command cmd;
            cmd.command = command;
            cmd.effect = "Invalid command";
            commands.push_back(cmd);
        }
    }

    file.close();
}