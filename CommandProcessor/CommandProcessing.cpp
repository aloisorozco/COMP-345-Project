// CommandProcessing.cpp
#include "CommandProcessing.h"
#include <iostream>

std::string ConsoleCommandProcessor::getInputFromConsole() {
    std::string command;
    std::getline(std::cin, command);
    return command;
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(const std::string& filename, GameEngine* gameEngine) : CommandProcessor(gameEngine) {
    file.open(filename);
}

std::string FileCommandProcessorAdapter::getInputFromFile() {
    std::string command;
    if (std::getline(file, command)) {
        return command;
    }
    return "";
}

void CommandProcessor::saveCommand(const std::string& command) {
    Command cmd;
    cmd.command = command;
    commands.push_back(cmd);
}

Command CommandProcessor::getCommand() {
    Command cmd = commands.back();
    commands.pop_back();
    return cmd;
}

void CommandProcessor::saveEffect(const std::string& effect) {
    commands.back().effect = effect;
}

bool CommandProcessor::validate(const std::string& command) {
    return gameEngine->getCurrentState()->getNextState(command) != nullptr;
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

void FileCommandProcessorAdapter::readCommand() {
    std::string command;
    while (std::getline(file, command)) {
        if (validate(command)) {
            saveCommand(command);
        } else {
            Command cmd;
            cmd.command = command;
            cmd.effect = "Invalid command";
            commands.push_back(cmd);
        }
    }
}

bool CommandProcessor::isCommandsEmpty() {
    return commands.empty();
}