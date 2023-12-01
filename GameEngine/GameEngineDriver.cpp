//GameEngineDriver.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include "GameEngine.h"
#include "../PlayerStrategy/AggressivePlayerStrategy.h"
#include "../PlayerStrategy/BenevolentPlayerStrategy.h"
#include "../PlayerStrategy/CheaterPlayerStrategy.h"
#include "../PlayerStrategy/HumanPlayerStrategy.h"
#include "../PlayerStrategy/NeutralPlayerStrategy.h"

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
    deck->setDeckSize(12);
    GameEngine* engine = new GameEngine();

    PlayerStrategy* strategy = new NeutralPlayerStrategy();
    PlayerStrategy* cheaterStrategy = new CheaterPlayerStrategy();
    PlayerStrategy* benevolentStrategy = new BenevolentPlayerStrategy();
    PlayerStrategy* aggressiveStrategy = new AggressivePlayerStrategy();
    PlayerStrategy* humanStrategy = new HumanPlayerStrategy();
    //(1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern;
    Player* p1 = new Player(testMap, deck, strategy);
    Player* p2 = new Player(testMap, deck, cheaterStrategy);
    Player* p3 = new Player(testMap, deck, strategy);
    Player* p4 = new Player(testMap, deck, benevolentStrategy);
    Player* p5 = new Player(testMap, deck, aggressiveStrategy);
    Player* p6 = new Player(testMap, deck, humanStrategy);

    //deck size 12, give 2 cards per player
    for (int i = 0; i < 2; i++) {
        deck->draw(p1->getHand());
        deck->draw(p2->getHand());
        deck->draw(p3->getHand());
        deck->draw(p4->getHand());
        deck->draw(p5->getHand());
        deck->draw(p6->getHand());
    }
    engine->addPlayer(p1);
    engine->addPlayer(p2);
    engine->addPlayer(p3);
    engine->addPlayer(p4);
    engine->addPlayer(p5);
    engine->addPlayer(p6);

    testMap->setContinents(testMap->getContinents());

    for (Territory* territory : testMap->getTerritories()) {
        territory->setPlayer(1);
    }
    testMap->getTerritories()[0]->setPlayer(2);
    testMap->getTerritories()[1]->setPlayer(3);
    testMap->getTerritories()[2]->setPlayer(4);
    testMap->getTerritories()[3]->setPlayer(5);
    testMap->getTerritories()[4]->setPlayer(6);


    cout << "Main Game Loop start: " << endl;

    engine->mainGameLoop();

}



    


