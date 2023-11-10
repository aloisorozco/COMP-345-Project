// GameEngine.cpp
#include "GameEngine.h"
#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include <random>

#include "../Player/Player.h"
#include "../Map/Map.h"

// Constructor for GameState. Initializes the state with a name.
GameState::GameState(std::string name) : name(name) {}

// Returns the name of the GameState.
std::string GameState::getName() const
{
    return name;
}

// Adds a transition from the current state to another state, triggered by a command.
void GameState::addTransition(const std::string &command, GameState *state)
{
    transitions[command] = state;
}

// Returns the available transitions from this state.
const std::map<std::string, GameState *> &GameState::getTransitions() const
{
    return transitions;
}

// Returns the next GameState based on the given command. If the command does not have a corresponding transition, returns nullptr.
GameState *GameState::getNextState(const std::string &command) const
{
    std::map<std::string, GameState *>::const_iterator it = transitions.find(command);
    if (it != transitions.end())
    {
        return it->second;
    }
    return nullptr;
}

GameState::GameState(const GameState &) {} // Required but not used
GameState &GameState::operator=(const GameState &)
{
    return *this;
}

ostream &operator<<(ostream &out, const GameState &)
{
    out << "Not called " << endl;
    return out;
}

// Constructor for the GameEngine class. It initializes the currentState member variable to nullptr, indicating that there is no current game state when the game engine is first created.
GameEngine::GameEngine() : currentState(nullptr), playerArray(NULL), sizeofPlayerArray(new int(0))
{
}

// Destructor for the GameEngine class. It is responsible for cleaning up memory to prevent leaks. It iterates over the states map and deletes each GameState object that it contains.
GameEngine::~GameEngine()
{
    for (std::map<std::string, GameState *>::iterator it = states.begin(); it != states.end(); ++it)
    {
        delete it->second;
    }

    delete this->playerArray;
    playerArray = NULL;

    delete this->sizeofPlayerArray;
    sizeofPlayerArray = NULL;
}

// Returns the current state of the game.
GameState *GameEngine::getCurrentState()
{
    return currentState;
}

// Returns a list of commands that can be used in the current state.
std::vector<std::string> GameEngine::getAvailableCommands()
{
    std::vector<std::string> commands;

    if (currentState != nullptr)
    {
        const std::map<std::string, GameState *> &transitions = currentState->getTransitions();
        for (std::map<std::string, GameState *>::const_iterator it = transitions.begin(); it != transitions.end(); ++it)
        {
            const std::pair<const std::string, GameState *> &pair = *it;
            commands.push_back(pair.first);
        }
    }

    return commands;
}

// Adds a new game state to the game engine. It takes a pointer to a GameState object as an argument and adds it to the states map using the game state's name as the key.
void GameEngine::addState(GameState *state)
{
    states[state->getName()] = state;
}

// Sets the initial game state for the game engine. It takes a pointer to a GameState object as an argument and sets currentState to this game state.
void GameEngine::setInitialState(GameState *state)
{
    currentState = state;
}

// Processes a command from the user. It checks if a current state exists and gets the next state based on the provided command.
void GameEngine::processCommand(const std::string &command)
{
    if (currentState == nullptr)
    {
        std::cout << "The game is not initialized." << std::endl;
        return;
    }
    GameState *nextState = currentState->getNextState(command);
    if (nextState == nullptr)
    {
        std::cout << "Invalid command." << std::endl;
    }
    else
    {
        currentState = nextState;
        std::cout << "Transitioned to state: " << currentState->getName() << std::endl;
    }
}
// NOT CALLED
GameEngine::GameEngine(const GameEngine &) {}
GameEngine &GameEngine::operator=(const GameEngine &)
{
    return *this;
}
ostream &operator<<(ostream &out, const GameEngine &)
{
    return out;
}

GameEngine GameEngine::gameInit()
{

    // state initialisation
    GameEngine engine;
    GameState *startState = new GameState("Start");
    GameState *mapLoadState = new GameState("Map Loaded");
    GameState *mapValidationState = new GameState("Map Validated");
    GameState *addPlayerState = new GameState("Players Added");
    GameState *reinforcementState = new GameState("Assign Reinforcement");
    GameState *orderChoiceState = new GameState("Issue Orders");
    GameState *orderExecuteState = new GameState("Execute Orders");
    GameState *winState = new GameState("Win");
    GameState *endState = new GameState("end");

    // Creating all the appropriate transitions.
    startState->addTransition("loadmap", mapLoadState);
    mapLoadState->addTransition("loadmap", mapLoadState);
    mapLoadState->addTransition("validatemap", mapValidationState);
    mapValidationState->addTransition("addplayer", addPlayerState);
    addPlayerState->addTransition("addplayer", addPlayerState);
    addPlayerState->addTransition("assigncountries", reinforcementState);
    reinforcementState->addTransition("issueorder", orderChoiceState);
    orderChoiceState->addTransition("issueorder", orderChoiceState);
    orderChoiceState->addTransition("endissueorders", orderExecuteState);
    orderExecuteState->addTransition("execorder", orderExecuteState);
    orderExecuteState->addTransition("endexecorders", reinforcementState);
    orderExecuteState->addTransition("win", winState);
    winState->addTransition("play", startState);
    winState->addTransition("end", endState);

    // Adding all states to the engine
    engine.addState(startState);
    engine.addState(mapLoadState);
    engine.addState(mapValidationState);
    engine.addState(addPlayerState);
    engine.addState(reinforcementState);
    engine.addState(orderChoiceState);
    engine.addState(orderExecuteState);
    engine.addState(winState);

    // Setting the initial state
    engine.setInitialState(startState);

    return engine;
}

// Fucntion for clearing terminal window using ASCII escape code
void GameEngine::clearScreen()
{
    std::cout << "\x1B[2J\x1B[H";
}

// Function for printing a helping box
void GameEngine::printBox(const std::string &state, const std::string &commands)
{
    std::cout << "***** WARZONE GAME ENGINE ****\n";
    std::cout << "******************************\n";
    std::cout << "* Current state: " << state << "\n";
    std::cout << "* Available commands: \n"
              << commands << "\n";
    std::cout << "******************************\n";
}

GameState GameEngine::startupPhase(/*Command &command*/)
{ // will input a command object

    // intialize map
    Map *map = new Map();
    MapLoader *mapLoader = new MapLoader();

    // Load map command
    mapLoader->loadMap_withName("name of map from command input or text file");
    delete mapLoader;

    // Validate map command

    if (!map->validate())
    {
        cout << "Map was not valid. Please review your input commands and select a valid map. " << endl;
        return;
    }

    // Add players command
    int numberOfPlayers = 0;

    if (numberOfPlayers < 2 || numberOfPlayers > 6)
    {
        cout << "Invalid number of players. Please select a number between 2 and 6." << endl;
        return;
    }

    for (int i = 0; i < numberOfPlayers; i++)
    {
        Player *player = new Player(map);
        playerArray[i] = *player;
        delete player;
    }



    // gamestart command
    int minLimit = 0;
    int maxLimit = 0;
    vector <int> players = {1,2,3,4,5,6};

    // Set Randomization function
    maxLimit = map->getTerritories().size()-1;
    std::random_device rd;  // Seed the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator
    std::uniform_int_distribution<int> distribution(minLimit, maxLimit);


    //Get territories
    vector <Territory*> territories;
    territories = map->getTerritories();
    
    // Randomize order of territories in territories vector created above
    for (int i=0; i<maxLimit; i++){
        int randomIndex1 = distribution(gen);
        int randomIndex2 = distribution(gen);
        swap (territories[randomIndex1], territories[randomIndex2]);
    }

    // Assign territories to players in round robin fashion
    int playerIndex =0;
    int territoryIndex=0;
    for (Territory* territory: territories){
        territory->setPlayer(players[playerIndex]);
        playerIndex = (playerIndex+1)%players.size();
        territoryIndex = (territoryIndex+1)%territories.size();
    }


    return *currentState;
}

void GameEngine::play()
{

    // part 2

    // part 3
    mainGameLoop();
}

void GameEngine::reinforcementPhase()
{

    cout << "Reinforcement Phase\n"
         << endl;

    vector<Player> playerVector;
    for (int i = 0; i < *sizeofPlayerArray; i++)
    {
        playerVector.push_back(playerArray[i]);
    }

    // removes player if they do not have territories from array
    for (int i = 0; i < *sizeofPlayerArray; i++)
    {
        playerArray[i].toDefend();
        if (playerArray[i].getSizeOfToDefend() == 0)
        {
            cout << playerArray[i] << " has no territories, removing them from the game" << endl;
            playerVector.erase(playerVector.begin() + i);
        }
    }

    // if player was removed in vector, update array
    if (playerVector.size() != *sizeofPlayerArray)
    {
        *sizeofPlayerArray = playerVector.size();
        Player *playerArray = new Player[*sizeofPlayerArray];

        for (int i = 0; i < *sizeofPlayerArray; i++)
        {
            playerArray[i] = playerVector[i];
        }
    }

    // calculating troops for each player
    for (int i = 0; i < *sizeofPlayerArray; i++)
    {
        playerArray[i].toDefend();
        int troops = (playerArray[i].getSizeOfToDefend() / 3) + 3;

        // checks if owns entire continents if so add continent bonus to troops
        vector<Continent *> continents = playerArray[i].getMap().getContinents();

        for (Continent *continent : continents)
        {
            vector<Territory *> territories = continent->getTerritories();

            bool hasContinent = true;
            for (Territory *territory : territories)
            {
                if (!(playerArray[i].hasTerritory(*territory)))
                {
                    hasContinent = false;
                }
            }
            if (hasContinent)
            {
                troops += continent->getBonus();
            }
        }

        playerArray[i].setTroopsToDeploy(troops);
    }
    cout << "--------------------\n"
         << endl;
}

void GameEngine::issueOrdersPhase()
{
    cout << "Issuing Orders Phase\n"
         << endl;
    bool *playersDoneArray = new bool[*sizeofPlayerArray];
    while (true)
    {
        for (int i = 0; i < *sizeofPlayerArray; i++)
        {
            playersDoneArray[i] = false;
        }
        for (int i = 0; i < *sizeofPlayerArray; i++)
        {
            if (playersDoneArray[i])
            {
                continue;
            }
            playersDoneArray[i] = playerArray[i].issueOrder();
        }
        bool playersDone = true;
        for (int i = 0; i < *sizeofPlayerArray; i++)
        {
            playersDone = playersDone && playersDoneArray[i];
        }
        if (playersDone)
        {
            break;
        }
    }
    cout << "--------------------\n"
         << endl;
}

void GameEngine::executeOrdersPhase()
{
    cout << "Execute Orders Phase\n"
         << endl;
    while (true)
    {
        bool executeOrdersDone = true;
        for (int i = 0; i < *sizeofPlayerArray; i++)
        {
            Order *order = playerArray[i].getNextInOrdersList();
            if (order != NULL)
            {
                executeOrdersDone = false;
                order->execute();
            }
        }

        if (executeOrdersDone)
        {
            break;
        }
    }
    cout << "--------------------\n"
         << endl;
}

void GameEngine::mainGameLoop()
{
    // part 3 here - players already have to be set

    // getting & setting troops
    reinforcementPhase();

    // issuing orders phase
    issueOrdersPhase();

    // executing orders phase
    executeOrdersPhase();
}