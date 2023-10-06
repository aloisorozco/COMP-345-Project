//GameEngineDriver.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.h"

// Initialisation of the engine, creation of all states and transition.
GameEngine gameInit() {

    //state initialisation
    GameEngine engine;
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
    addPlayerState->addTransition("assigncountries",reinforcementState);
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

    return engine;
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

// Console-driven interface that allows the user to navigate through all the states by typing commands
void testGameStates(){
    std::chrono::seconds sleepDuration(1);
    GameEngine engine = gameInit();
    std::string command;
    while (true) {
        // Clearing terminal screen
        clearScreen();

        //getting available commands for current state
        std::vector<std::string> availableCommands = engine.getAvailableCommands();
        
        //converting vector of strings into a single string separated by a \n
        std::string commandsStr;
        for (std::vector<std::string>::iterator it = availableCommands.begin(); it != availableCommands.end(); ++it) {
            std::string cmd = *it;
            commandsStr += "* > " +cmd + "\n";
        }

        // Displaying status box
        printBox(engine.getCurrentState()->getName(), commandsStr);
        std::cout << "Enter command: ";
        std::cin >> command;
        if (command == "end") {
            std::cout<<"Game ended";
            break;
        }

        // Displaying result of the command
        std::cout << "\n- ";
        engine.processCommand(command);
        std::cout << "******************************\n";
        std::this_thread::sleep_for(sleepDuration);
        
    }
}



    


