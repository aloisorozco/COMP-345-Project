// GameEngine.cpp
#include "GameEngine.h"
#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include <random>
#include <sstream>

#include "../Player/Player.h"
#include "../PlayerStrategy/PlayerStrategy.h"
#include "../PlayerStrategy/HumanPlayerStrategy.h"
#include "../PlayerStrategy/NeutralPlayerStrategy.h"
#include "../PlayerStrategy/CheaterPlayerStrategy.h"
#include "../PlayerStrategy/AggressivePlayerStrategy.h"
#include "../PlayerStrategy/BenevolentPlayerStrategy.h"
#include "../Map/Map.h"
#include "../CommandProcessor/CommandProcessing.h"

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
GameEngine::GameEngine() : currentState(new GameState("blankState")), playerArray(0), sizeofPlayerArray(new int(0)){

}

// Initialisation of the engine, creation of all states and transition.
void gameInit(GameEngine& engine)
{
    //state initialisation
    GameState* startState = new GameState("Start");
    GameState* mapLoadState = new GameState("Map Loaded");
    GameState* mapValidationState = new GameState("Map Validated");
    GameState* addPlayerState = new GameState("Players Added");
    GameState* reinforcementState = new GameState("Assign Reinforcement");
    GameState* orderChoiceState = new GameState("Issue Orders");
    GameState* orderExecuteState = new GameState("Execute Orders");
    GameState* winState = new GameState("Win");
    GameState* endState = new GameState("end");


    // Creating all the appropriate transitions.
    startState->addTransition("loadmap", mapLoadState);
    mapLoadState->addTransition("loadmap",mapLoadState);
    mapLoadState->addTransition("validatemap",mapValidationState);
    mapValidationState->addTransition("addplayer",addPlayerState);
    addPlayerState->addTransition("addplayer",addPlayerState);
    addPlayerState->addTransition("gamestart",reinforcementState);
    reinforcementState->addTransition("issueorder",orderChoiceState);
    orderChoiceState->addTransition("issueorder",orderChoiceState);
    orderChoiceState->addTransition("endissueorders",orderExecuteState);
    orderExecuteState->addTransition("execorder",orderExecuteState);
    orderExecuteState->addTransition("endexecorders",reinforcementState);
    orderExecuteState->addTransition("win",winState);
    winState->addTransition("play",startState);
    winState->addTransition("end",endState);

    //Adding all states to the engine
    engine.addState(startState);
    engine.addState(mapLoadState);
    engine.addState(mapValidationState);
    engine.addState(addPlayerState);
    engine.addState(reinforcementState);
    engine.addState(orderChoiceState);
    engine.addState(orderExecuteState);
    engine.addState(winState);

    //Setting the initial state
    engine.setInitialState(startState);

}

// Destructor for the GameEngine class. It is responsible for cleaning up memory to prevent leaks. It iterates over the states map and deletes each GameState object that it contains.
GameEngine::~GameEngine()
{
    for (std::map<std::string, GameState *>::iterator it = states.begin(); it != states.end(); ++it)
    {
        delete it->second;
    }

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
        //the equivalent to GameEngine::transition()
        Notify(this);
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

void GameEngine::addPlayer(Player *player)
{
    playerArray.push_back(player);
    *sizeofPlayerArray = playerArray.size();
}





void GameEngine::addMap(Map *map)
{
    this->map = map;
}

void GameEngine::startupPhase(GameEngine &engineArg)
{ // will input a command object

    int choice;
    string filename;

    std::cout << "Pick between the two options:" << std::endl;
    std::cout << "Console Commands (1)" << std::endl;
    std::cout << "File Commands (2)" << std::endl;
    std::cout << "> ";
    std::cin >> choice;

    // Initialize game
    GameEngine *engine = &engineArg;
    GameEngine *initializer = new GameEngine();
    gameInit(*engine);
    delete initializer;
    initializer = NULL;

    CommandProcessor *commandProcessor;

    if (choice == 1)
    {
        commandProcessor = new ConsoleCommandProcessor(engine);
    }

    else if (choice == 2)
    {
        std::cout << "Enter filename: ";
        std::cin >> filename;

        commandProcessor = new FileCommandProcessorAdapter(filename, engine);
    }

    // Initialize map and deck
    map = new Map();
    Deck *deck = new Deck();

    while (engine->getCurrentState()->getName() != "Assign Reinforcement")
    {
        std::chrono::seconds sleepDuration(2);
        // Clear screen
        clearScreen();

        // getting available commands for current state
        std::vector<std::string> availableCommands = engine->getAvailableCommands();

        // converting vector of strings into a single string separated by a \n
        std::string commandsStr;
        for (std::vector<std::string>::iterator it = availableCommands.begin(); it != availableCommands.end(); ++it)
        {
            std::string cmd = *it;
            commandsStr += "* > " + cmd + "\n";
        }

        // Print box
        printBox(engine->getCurrentState()->getName(), commandsStr);

        // Get command
        Command cmd = commandProcessor->getCommand();

        std::vector<std::string> commandWords;
        std::istringstream iss(cmd.command);
        for (std::string s; iss >> s;)
            commandWords.push_back(s);

        if (commandWords[0] == "loadmap")
        {
            // intialize map
            map = new Map();
            MapLoader *mapLoader = new MapLoader(); // loader

            if (commandWords.size() > 1)
            {
                map = mapLoader->loadMap_withName(commandWords[1]);
            }
            else
            {
                map = mapLoader->loadMap();
            }

            delete mapLoader;
            mapLoader = NULL;

            commandProcessor->saveEffect("Map loaded");
            engine->processCommand("loadmap");
            std::cout << "******************************\n";
            std::this_thread::sleep_for(sleepDuration);
        }

        else if (cmd.command == "validatemap")
        {
            if (map->validate())
            {
                commandProcessor->saveEffect("Map validated");
                engine->processCommand("validatemap");
                std::cout << "******************************\n";
                std::this_thread::sleep_for(sleepDuration);
            }
            else
            {
                // commandProcessor->saveEffect("Map is not valid");
                cout << "Map is not valid. Please select another map using the loadmap command" << endl; // still in map loaded state can call loadmap again
                delete map;
                map = NULL; // avoid memory leaks - might cause error if so will remove
                std::cout << "******************************\n";
                std::this_thread::sleep_for(sleepDuration);
            }
        }

        else if (commandWords[0] == "addplayer")
        {

            // Add players command - getCommand() from CommandProcessor object - prob a if satement here + call validate
            if (*sizeofPlayerArray > 5 && cmd.command == "addplayer")
            {
                cout << "Too many players. Please use the gamestart command to start the game" << endl;
                std::cout << "******************************\n";
                std::this_thread::sleep_for(sleepDuration);
            }
            else
            {
                PlayerStrategy* strategy = new HumanPlayerStrategy();
                Player *player = new Player(map, deck, strategy);
                engine->addPlayer(player);
                commandProcessor->saveEffect("Player added");
                engine->processCommand("addplayer");
                std::cout << "******************************\n";
                std::this_thread::sleep_for(sleepDuration);
            }
        }

        else if (cmd.command == "gamestart")
        {
            if (*sizeofPlayerArray < 2)
            {
                cout << "Not enough players. Please add more players using the addplayer command" << endl;
                std::cout << "******************************\n";
                std::this_thread::sleep_for(sleepDuration);
            }
            else
            {

                //========================================= Assign territories to players======================================================//

                // Vector of player IDs/Number
                vector<int> players;
                for (int i = 1; i < *sizeofPlayerArray + 1; i++)
                {
                    players.push_back(i);
                }

                // Set Randomization function
                int minLimit = 0;
                int maxLimit = 0;
                maxLimit = map->getTerritories().size() - 1;
                std::random_device rd;  // Seed the random number generator
                std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator
                std::uniform_int_distribution<int> distribution(minLimit, maxLimit);

                // Get territories
                vector<Territory *> territories;
                territories = map->getTerritories();

                // Randomize order of territories in territories vector created above
                for (int i = 0; i < maxLimit; i++)
                {
                    int randomIndex1 = distribution(gen);
                    int randomIndex2 = distribution(gen);
                    swap(territories[randomIndex1], territories[randomIndex2]);
                }

                // Assign territories to players in round robin fashion
                int playerIndex = 0;
                int territoryIndex = 0;
                for (Territory *territory : territories)
                {
                    territory->setPlayer(players[playerIndex]);
                    playerIndex = (playerIndex + 1) % players.size();
                    territoryIndex = (territoryIndex + 1) % territories.size();
                }

                //=======================================Order of Play=====================================================//
                // Determine order of play by rearanging player array in random order
                minLimit = 0;
                maxLimit = playerArray.size() - 1;
                std::uniform_int_distribution<int> distribution2(minLimit, maxLimit);

                for (int i = 0; i < playerArray.size(); i++)
                {
                    int randomIndex1 = distribution2(gen);
                    int randomIndex2 = distribution2(gen);
                    swap(playerArray[randomIndex1], playerArray[randomIndex2]);
                }

                // Print order of play
                cout << "Order of play: ";
                for (Player *player : playerArray)
                {
                    cout << "Player " << player->getPlayerID() << " > ";
                }

                //=======================================Reinforcements=====================================================//

                for (Player *player : playerArray)
                {
                    player->setTroopsToDeploy(50);
                }

                //========================================Draw 2 Cards======================================================//
                // Each Player draws two cards from the deck
                for (Player *player : playerArray)
                {
                    cout << "\nPlayer : " << player->getPlayerID() << endl;
                    deck->draw(player->getHand());
                    deck->draw(player->getHand());
                    cout << "Troops to deploy: " << *player->getTroopsToDeploy()
                         << endl; // for demo purpose
                }

                commandProcessor->saveEffect("Game started");
                engine->processCommand("gamestart");
                std::cout << "******************************\n";
                std::this_thread::sleep_for(sleepDuration);
            }
        }

        else
        {
            // Invalid command
            commandProcessor->saveEffect("Invalid command");
            std::cout << "******************************\n";
            std::this_thread::sleep_for(sleepDuration);
        }
    }
}

Map *GameEngine::getMap() const
{
    return map;
}



void GameEngine::play()
{

    // part 2

    // part 3
    this->mainGameLoop();
}

bool GameEngine::reinforcementPhase() {

    std::cout << "Reinforcement Phase\n"
              << endl;

    // removes player if they do not have territories from array
    for (int i = 0; i < playerArray.size(); i++)
    {
        playerArray[i]->toDefend();
        if (playerArray[i]->getSizeOfToDefend() == 0)
        {
            std::cout << "Player " << playerArray[i]->getPlayerID() << " has no territories, removing them from the game" << endl;
            playerArray.erase(playerArray.begin() + i);
        }
    }

    if (playerArray.size() == 1) {
        std::cout << "\nPlayer " << playerArray[0]->getPlayerID() << " wins!!!\n" << endl;
        return true;
    }

    //calculating troops for each player
    for (int i = 0; i < playerArray.size(); i++) {
        playerArray[i]->toDefend();
        int troops = (playerArray[i]->getSizeOfToDefend() / 3) + 3;
        
        
        // checks if owns entire continents if so add continent bonus to troops
        vector<Continent *> continents = playerArray[i]->getMap()->getContinents();

        for (Continent *continent : continents)
        {
            vector<Territory *> territories = continent->getTerritories();

            bool hasContinent = true;
            for (Territory *territory : territories)
            {
                if (!(playerArray[i]->hasTerritory(*territory)))
                {
                    hasContinent = false;
                }
            }
            if (hasContinent)
            {
                troops += continent->getBonus();
            }
        }

        playerArray[i]->setTroopsToDeploy(troops);
    }
    std::cout << "--------------------\n" << endl;
    return false;
}

void GameEngine::issueOrdersPhase() {
    std::cout << "Issuing Orders Phase\n" << endl;
    bool* playersDoneArray = new bool[*sizeofPlayerArray];

    for (int i = 0; i < playerArray.size(); i++) {
        playersDoneArray[i] = false;
        playerArray[i]->setOrderListIndex(0);
        playerArray[i]->getOrdersList()->clear();
    }
    while (true)
    {
        for (int i = 0; i < playerArray.size(); i++)
        {
            if (playersDoneArray[i])
            {
                continue;
            }
            playersDoneArray[i] = playerArray[i]->issueOrder();
        }
        bool playersDone = true;
        for (int i = 0; i < playerArray.size(); i++)
        {
            playersDone = playersDone && playersDoneArray[i];
        }
        if (playersDone)
        {
            break;
        }
    }
    std::cout << "--------------------\n"
              << endl;
}

void GameEngine::executeOrdersPhase()
{
    std::cout << "Execute Orders Phase\n"
              << endl;
    while (true)
    {
        bool executeOrdersDone = true;
        for (int i = 0; i < playerArray.size(); i++)
        {
            Order *order = playerArray[i]->getNextInOrdersList();
            if (order != NULL)
            {
                executeOrdersDone = false;

                int* playerAttackedID;

                if (dynamic_cast<Bomb*>(order) != NULL) {
                    Bomb* bomb = dynamic_cast<Bomb*>(order);

                    if (bomb->getTarget() != NULL) {
                        playerAttackedID = new int(bomb->getTarget()->getPlayer());
                    }
                }
                if (dynamic_cast<Advance*>(order) != NULL) {
                    Advance* advance = dynamic_cast<Advance*>(order);

                    if (advance->getTarget() != NULL) {
                        playerAttackedID = new int(advance->getTarget()->getPlayer());
                    }
                }

                if (order->execute() == 0) {
                    if (dynamic_cast<Bomb*>(order) != NULL) {
                        Bomb* bomb = dynamic_cast<Bomb*>(order);

                        for (int i = 0; i < playerArray.size(); i++) {
                            if (dynamic_cast<NeutralPlayerStrategy*>(playerArray[i]->getPlayerStrategy()) == NULL) {
                                continue;
                            }

                            if (*playerAttackedID == playerArray[i]->getPlayerID()) {
                                cout << "Neutral Player " << playerArray[i]->getPlayerID() << " attacked, converting into an Aggressive Player" << endl;

                                playerArray[i]->setPlayerStrategy(new AggressivePlayerStrategy());
                            }
                        }

                        delete playerAttackedID;
                        playerAttackedID = NULL;
                    }
                    if (dynamic_cast<Advance*>(order) != NULL) {
                        Advance* advance = dynamic_cast<Advance*>(order);

                        for (int i = 0; i < playerArray.size(); i++) {
                            if (dynamic_cast<NeutralPlayerStrategy*>(playerArray[i]->getPlayerStrategy()) == NULL) {
                                continue;
                            }

                            if (*playerAttackedID == playerArray[i]->getPlayerID()) {
                                cout << "\nNeutral Player " << playerArray[i]->getPlayerID() << " attacked, converting into an Aggressive Player" << endl;

                                playerArray[i]->setPlayerStrategy(new AggressivePlayerStrategy());
                            }
                        }

                        delete playerAttackedID;
                        playerAttackedID = NULL;
                    }
                }

            }
        }

        if (executeOrdersDone)
        {
            break;
        }
    }
    std::cout << "--------------------\n"
              << endl;
}

void GameEngine::mainGameLoop()
{
    // part 3 here - players already have to be set
    while (true)
    {

        //getting & setting troops
        bool gameWon = reinforcementPhase();

        if (gameWon) {
            break;
        }

        // issuing orders phase
        issueOrdersPhase();

        // executing orders phase
        executeOrdersPhase();

    }
}
string GameEngine::stringToLog() {
    return "Game Engine state: " + getCurrentState()->getName();
}

// Fucntion for clearing terminal window using ASCII escape code
void clearScreen() {
    std::cout << "\x1B[2J\x1B[H";
}

// Function for printing a helping box
void printBox(const std::string& state, const std::string& commands) {
    std::cout << "***** WARZONE GAME ENGINE ****\n";
    std::cout << "******************************\n";
    std::cout << "* Current state: " << state << "\n";
    std::cout << "* Available commands: \n" << commands << "\n";
    std::cout << "******************************\n";
}