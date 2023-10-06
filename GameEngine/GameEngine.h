// GameEngine.h
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H


#include <string>
#include <map>
#include <vector>




// The GameState class represents a single state in a game.
// Each state has a name and a set of transitions that lead to other states.
class GameState {
public:
    // Constructor that initializes the state with a name.
    GameState(std::string name);

    // Returns the name of the state.
    std::string getName() const;



    // Adds a transition from this state to another state.
    // The transition is triggered by a command (a string).
    void addTransition(const std::string& command, GameState* state);

    // Returns the state that a given command leads to.
    // If the command does not lead to a state, returns null.
    GameState* getNextState(const std::string& command) const;

    // Returns the available transitions from this state.
    const std::map<std::string, GameState*>& getTransitions() const;

private:
    // The name of this state.
    std::string name;

    // A map from commands to states. Each entry represents a transition.
    std::map<std::string, GameState*> transitions;
};

// The GameEngine class manages the game states and processes commands.
class GameEngine {
public:
    // Default constructor that initializes the game engine.
    GameEngine();

    // Destructor that cleans up the game engine.
    ~GameEngine();

    // Returns the current state of the game.
    GameState* getCurrentState();

    // Returns a list of commands that can be used in the current state.
    std::vector<std::string> getAvailableCommands();

    // Adds a state to the game engine.
    // The game engine does not take ownership of the state; it is the caller's responsibility to manage the state's memory.
    void addState(GameState* state);

    // Sets the initial state of the game.
    // The game engine does not take ownership of the state; it is the caller's responsibility to manage the state's memory.
    void setInitialState(GameState* state);

    // Processes a command.
    // This will cause the game engine to transition to a different state, if the command corresponds to a valid transition from the current state.
    void processCommand(const std::string& command);

private:
    // A map from state names to states. Contains all the states in the game.
    std::map<std::string, GameState*> states;

    // The current state of the game.
    GameState* currentState;
};

//free functions declaration
void testGameStates();
#endif // GAME_ENGINE_H
