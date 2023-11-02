// GameEngine.cpp
#include "GameEngine.h"
#include <iostream>
#include <map>

// Constructor for GameState. Initializes the state with a name.
GameState::GameState(std::string name) : name(name) {}

// Returns the name of the GameState.
std::string GameState::getName() const {
    return name;
}

// Adds a transition from the current state to another state, triggered by a command.
void GameState::addTransition(const std::string& command, GameState* state) {
    transitions[command] = state;
}

// Returns the available transitions from this state.
const std::map<std::string, GameState*>& GameState::getTransitions() const {
    return transitions;
}

// Returns the next GameState based on the given command. If the command does not have a corresponding transition, returns nullptr.
GameState* GameState::getNextState(const std::string& command) const {
    std::map<std::string, GameState*>::const_iterator it = transitions.find(command);
    if (it != transitions.end()) {
        return it->second;
    }
    return nullptr;
}

GameState::GameState(const GameState &) {} //Required but not used
GameState &GameState::operator=(const GameState &) {
    return *this;
}

ostream &operator<<(ostream& out, const GameState &) {
    out <<"Not called "<<endl;
    return out;
}

// Constructor for the GameEngine class. It initializes the currentState member variable to nullptr, indicating that there is no current game state when the game engine is first created.
GameEngine::GameEngine() : currentState(nullptr) {

}

// Destructor for the GameEngine class. It is responsible for cleaning up memory to prevent leaks. It iterates over the states map and deletes each GameState object that it contains.
GameEngine::~GameEngine() {
    for (std::map<std::string, GameState*>::iterator it = states.begin(); it != states.end(); ++it) {
        delete it->second;
    }
}

// Returns the current state of the game.
GameState* GameEngine::getCurrentState() {
    return currentState;
}

// Returns a list of commands that can be used in the current state.
std::vector<std::string> GameEngine::getAvailableCommands() {
    std::vector<std::string> commands;

    if (currentState != nullptr) {
        const std::map<std::string, GameState*>& transitions = currentState->getTransitions();
        for (std::map<std::string, GameState*>::const_iterator it = transitions.begin(); it != transitions.end(); ++it) {
        const std::pair<const std::string, GameState*>& pair = *it;
            commands.push_back(pair.first);
        }
    }

    return commands;
}

// Adds a new game state to the game engine. It takes a pointer to a GameState object as an argument and adds it to the states map using the game state's name as the key.
void GameEngine::addState(GameState* state) {
    states[state->getName()] = state;
}

// Sets the initial game state for the game engine. It takes a pointer to a GameState object as an argument and sets currentState to this game state.
void GameEngine::setInitialState(GameState* state) {
    currentState = state;
}

// Processes a command from the user. It checks if a current state exists and gets the next state based on the provided command.
void GameEngine::processCommand(const std::string& command) 
{
    if (currentState == nullptr) {
        std::cout << "The game is not initialized." << std::endl;
        return;
    }
    GameState* nextState = currentState->getNextState(command);
    if (nextState == nullptr) {
        std::cout << "Invalid command." << std::endl;
    } else {
        currentState = nextState;
        std::cout << "Transitioned to state: " << currentState->getName() << std::endl;
    }
}
//NOT CALLED
GameEngine::GameEngine(const GameEngine &) {}
GameEngine &GameEngine::operator=(const GameEngine &) {
    return *this;
}
ostream &operator<<(ostream& out, const GameEngine &) {
    return out;
}

void GameEngine::play() {

}

void GameEngine::mainGameLoop() {
    //part 3 here
}