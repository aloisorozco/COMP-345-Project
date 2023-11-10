//GameEngineDriver.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.h"





// Console-driven interface that allows the user to navigate through all the states by typing commands
void testGameStates(){
    std::chrono::seconds sleepDuration(1);
    GameEngine* initializer = new GameEngine();
    GameEngine engine = initializer->gameInit();
    delete initializer;
    

    std::string command;
    while (true) {
        // Clearing terminal screen
        engine.clearScreen();

        //getting available commands for current state
        std::vector<std::string> availableCommands = engine.getAvailableCommands();
        
        //converting vector of strings into a single string separated by a \n
        std::string commandsStr;
        for (std::vector<std::string>::iterator it = availableCommands.begin(); it != availableCommands.end(); ++it) {
            std::string cmd = *it;
            commandsStr += "* > " +cmd + "\n";
        }

        // Displaying status box
        engine.printBox(engine.getCurrentState()->getName(), commandsStr);
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

void testMainGameLoop() {

    cout << "Choose Africa map for example" << endl;

    MapLoader loader;
    Map* testMap = loader.loadMap();

    cout << *testMap << endl;

    if (testMap->validate())
    {
        cout << "\n\nMap is valid" << endl;
    }
    else
    {
        cout << "Map is not valid" << endl;
    }

    Deck* deck = new Deck();

    GameEngine* engine = new GameEngine();
    engine->addPlayer(new Player(testMap, deck));
    engine->addPlayer(new Player(testMap, deck));
    engine->addPlayer(new Player(testMap, deck));

    testMap->setContinents(testMap->getContinents());

    for (Territory* territory : testMap->getTerritories()) {
        territory->setPlayer(1);
    }
    testMap->getTerritories()[0]->setPlayer(2);

    cout << "Main Game Loop start: " << endl;

    engine->mainGameLoop();

}



    


