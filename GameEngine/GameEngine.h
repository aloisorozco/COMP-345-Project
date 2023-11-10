// GameEngine.h
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "../Player/Player.h"
#include "../Observer/LoggingObserver.h"
#include <string>
#include <map>
#include <vector>

using namespace std;
class ILoggable;
class Subject;
// copy constructor, assignment operator, and stream insertion operator.

// The GameState class represents a single state in a game.
// Each state has a name and a set of transitions that lead to other states.

class GameState {
public:
    // Constructor that initializes the state with a name.
    GameState(std::string name);
    GameState(const GameState&); // 1.copy constructor
    GameState& operator =(const GameState&); // 2.copy operator
    friend ostream& operator<<(ostream&,const GameState&); // 3.stream insertion
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
class GameEngine : public ILoggable, public Subject{
public:
    // Default constructor that initializes the game engine.
    GameEngine();
    GameEngine(const GameEngine&); // 1.copy constructor
    GameEngine& operator =(const GameEngine&); // 2.copy operator
    friend ostream& operator<<(ostream&,const GameEngine&); // 3.stream insertion
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

    void play();

    void mainGameLoop();

    void startupPhase();

    void reinforcementPhase();

    void issueOrdersPhase();

    void executeOrdersPhase();

    void setPlayers(vector<Player*> players) {
        playerArray = players;
    }

    void addPlayer(Player* player) {
        playerArray.push_back(player);
        /*Player* temp = new Player[*sizeofPlayerArray];
        playerArray = new Player[*sizeofPlayerArray + 1];

        for (int i = 0; i < *sizeofPlayerArray; i++) {
            playerArray[i] = temp[i];
        }

        playerArray[*sizeofPlayerArray] = *player;
        sizeofPlayerArray++;*/
    }
    string stringToLog() override;
private:
    // A map from state names to states. Contains all the states in the game.
    std::map<std::string, GameState*> states;

    // The current state of the game.
    GameState* currentState;

    vector<Player*> playerArray;
    int* sizeofPlayerArray;
};

//free functions declaration
void testGameStates();

void testMainGameLoop();
GameEngine gameInit();
#endif // GAME_ENGINE_H
