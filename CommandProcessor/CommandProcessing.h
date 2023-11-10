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
    Command getCommand();
    void saveEffect(const std::string& effect);
};

class ConsoleCommandProcessor : public CommandProcessor {
public:
    ConsoleCommandProcessor(GameEngine* gameEngine) : CommandProcessor(gameEngine) {}
    void readCommand();
private:
    std::string getInputFromConsole();
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
    FileCommandProcessorAdapter(const std::string& filename, GameEngine* gameEngine);
    void readCommand();
private:
    std::ifstream file;
    std::string getInputFromFile();
};