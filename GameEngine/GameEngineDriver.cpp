//GameEngineDriver.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.h"
#include "../PlayerStrategy/HumanPlayerStrategy.h"
#include "../PlayerStrategy/NeutralPlayerStrategy.h"
#include "../PlayerStrategy/CheaterPlayerStrategy.h"

// Console-driven interface that allows the user to navigate through all the states by typing commands
void testGameStates(){
    std::chrono::seconds sleepDuration(1);
    GameEngine engine;
    gameInit(engine);
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

void testStartUpPhase()
{
    GameEngine engine;

    engine.startupPhase(engine);

    cout << *engine.getMap() << endl;

    int cP1 = 0;
    int cP2 = 0;
    int Cp3 = 0;
    // int cP4 = 0;
    // int cP5 = 0;
    // int cP6 = 0;

    vector <Territory*> testTerr;
    testTerr = engine.getMap()->getTerritories();

    for (Territory *territory : testTerr)
    {
        if (territory->getPlayer() == 1)
        {
            cP1++;
        }
        if (territory->getPlayer() == 2)
        {
            cP2++;
        }
        if (territory->getPlayer() == 3)
        {
            Cp3++;
        }
        // if (territory->getPlayer() == 4)
        // {
        //     cP4++;
        // }
        // if (territory->getPlayer() == 5)
        // {
        //     cP5++;
        // }
        // if (territory->getPlayer() == 6)
        // {
        //     cP6++;
        // }
    }

    cout << cP1 << endl;
    cout << cP2 << endl;
    cout << Cp3 << endl;
    // cout << cP4 << endl;
    // cout << cP5 << endl;
    // cout << cP6 << endl;

    engine.play();
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

    PlayerStrategy* strategy = new NeutralPlayerStrategy();
    PlayerStrategy* cheaterStrategy = new HumanPlayerStrategy();

    Player* p1 = new Player(testMap, deck, strategy);
    Player* p2 = new Player(testMap, deck, cheaterStrategy);
    Player* p3 = new Player(testMap, deck, strategy);

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



    


