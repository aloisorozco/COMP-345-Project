// CommandProcessing.h
#include <string>
#include <vector>
#include <fstream>
#include "../GameEngine/GameEngine.h"

class Command {
public:
    std::string command;
    std::string effect;
};

class CommandProcessor {
protected:
    std::vector<Command> commands;
    GameEngine* gameEngine;
    void saveCommand(const std::string& command);
    bool validate(const std::string& command);
public:
    CommandProcessor(GameEngine* gameEngine) : gameEngine(gameEngine) {}
    virtual void readCommand() = 0;  // Pure virtual method
    Command getCommand();
    void saveEffect(const std::string& effect);
    bool isCommandsEmpty();
};

class ConsoleCommandProcessor : public CommandProcessor {
public:
    ConsoleCommandProcessor(GameEngine* gameEngine) : CommandProcessor(gameEngine) {}
    void readCommand() override;  // Override base class method
private:
    std::string getInputFromConsole();
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    std::string fileName;
    FileCommandProcessorAdapter() : CommandProcessor(nullptr) {}  // Default constructor
    FileCommandProcessorAdapter(const std::string& filename, GameEngine* gameEngine) : CommandProcessor(gameEngine), fileName(filename) {}
    void readCommand() override;  // Override base class method
};
