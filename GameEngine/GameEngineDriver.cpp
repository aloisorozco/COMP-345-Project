//GameEngineDriver.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.h"





// Console-driven interface that allows the user to navigate through all the states by typing commands
void testGameStates(){
    std::chrono::seconds sleepDuration(1);
    GameEngine engine;
    engine.gameInit(engine);
    
    

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

    Player* p1 = new Player(testMap, deck);
    Player* p2 = new Player(testMap, deck);
    Player* p3 = new Player(testMap, deck);

    for (int i = 0; i < 5; i++) {
        deck->draw(p1->getHand());
    }

    engine->addPlayer(p1);
    engine->addPlayer(p2);
    engine->addPlayer(p3);

    testMap->setContinents(testMap->getContinents());

    for (Territory* territory : testMap->getTerritories()) {
        territory->setPlayer(1);
    }
    testMap->getTerritories()[0]->setPlayer(2);

    cout << "Main Game Loop start: " << endl;

    engine->mainGameLoop();

}



    


