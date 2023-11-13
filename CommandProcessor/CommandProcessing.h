// CommandProcessing.h
#ifndef COMMANDPROCESSING_H
#define COMMANDPROCESSING_H

#include <string>
#include <vector>
#include <fstream>
#include "../Observer/LoggingObserver.h"
#include "../GameEngine/GameEngine.h"

class Command :public ILoggable, public Subject{
public:
    std::string command;
    std::string effect;
    string stringToLog() override;
};

class CommandProcessor : public ILoggable, public Subject{
protected:
    std::vector<Command> commands;
    GameEngine* gameEngine;
    virtual void readCommand() = 0;  // Pure virtual method
    bool validate(const std::string& command);
public:
    CommandProcessor(GameEngine* gameEngine) : gameEngine(gameEngine) {}
    void saveCommand(const std::string& command);
    void saveEffect(const std::string& effect);
    bool isCommandsEmpty();
    virtual Command getCommand() =0;// Pure virtual method
    string stringToLog() override;
};

class ConsoleCommandProcessor : public CommandProcessor {
public:
    ConsoleCommandProcessor(GameEngine* gameEngine) : CommandProcessor(gameEngine) {}
    Command getCommand() override;
private:
    void readCommand() override;  // Override base class method
    std::string getInputFromConsole();
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    std::string fileName;
    FileCommandProcessorAdapter() : CommandProcessor(nullptr) {}  // Default constructor
    FileCommandProcessorAdapter(const std::string& filename, GameEngine* gameEngine) : CommandProcessor(gameEngine), fileName(filename) {}
    Command getCommand() override;
private:
    void readCommand() override;  // Override base class method
};
    
// Free function

void testCommandProcessor();
#endif 
