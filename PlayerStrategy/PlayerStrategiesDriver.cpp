#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "../PlayerStrategy/AggressivePlayerStrategy.h"
#include "../PlayerStrategy/BenevolentPlayerStrategy.h"
#include "../PlayerStrategy/CheaterPlayerStrategy.h"
#include "../PlayerStrategy/HumanPlayerStrategy.h"
#include "../PlayerStrategy/NeutralPlayerStrategy.h"


using namespace std;
//You must deliver a driver as a free function named testPlayerStrategies() that demonstrates that
// (1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern;
// (2) the strategy adopted by a player can be changed dynamically during play,
// (3) the human player makes decisions according to user interaction, and
// computer players make decisions automatically, which are both implemented using the strategy pattern
vector<Territory*> getTerritoryArray() {
    vector<Territory*> territoryArray;

    // Create Territories
    Territory* temp = new Territory("Yukon", "c1");
    temp->setPlayer(2);
    temp->setArmy(7);
    Territory* temp1 = new Territory("Quebec", "c1");
    temp1->setPlayer(2);
    temp->setArmy(3);
    Territory* temp2 = new Territory("Ontario", "c1");
    temp2->setPlayer(2);
    temp->setArmy(1);
    Territory* temp3 = new Territory("Manitoba", "c1");
    temp3->setPlayer(1);
    temp->setArmy(2);
    Territory* temp4 = new Territory("BC", "c1");
    temp4->setPlayer(1);
    temp->setArmy(9);
    Territory* temp5 = new Territory("Mexico", "c1");
    temp5->setPlayer(1);
    temp->setArmy(2);
    Territory* temp6 = new Territory("USA", "c1");
    temp6->setPlayer(1);
    temp->setArmy(15);
    temp->addNeighbor(temp1);
    temp1->addNeighbor(temp);

    temp1->addNeighbor(temp2);
    temp2->addNeighbor(temp1);

    temp->addNeighbor(temp2);
    temp2->addNeighbor(temp);

    temp5->addNeighbor(temp6);
    temp6->addNeighbor(temp5);

    temp1->addNeighbor(temp6);
    temp6->addNeighbor(temp1);

    temp2->addNeighbor(temp6);
    temp6->addNeighbor(temp2);

    territoryArray.push_back(temp);
    territoryArray.push_back(temp1);
    territoryArray.push_back(temp2);
    territoryArray.push_back(temp3);
    territoryArray.push_back(temp4);
    territoryArray.push_back(temp5);
    territoryArray.push_back(temp6);

    return territoryArray;
}

int testPlayerStrategies() {

    MapLoader loader;
    Map *testMap = loader.loadMap();

    cout << *testMap << endl;

    if (testMap->validate()) {
        cout << "\n\nMap is valid" << endl;
    } else {
        cout << "Map is not valid" << endl;
    }

    Deck *deck = new Deck();

    GameEngine *engine = new GameEngine();
    PlayerStrategy *strategy = new NeutralPlayerStrategy();
    PlayerStrategy *cheaterStrategy = new CheaterPlayerStrategy();
    PlayerStrategy *benevolentStrategy = new BenevolentPlayerStrategy();
    PlayerStrategy *aggressiveStrategy = new AggressivePlayerStrategy();
    PlayerStrategy *humanStrategy = new HumanPlayerStrategy();
    //(1) different players can be assigned different strategies that lead to different behavior using the Strategy design pattern;
    Player *p1 = new Player(testMap, deck, strategy);
    Player *p2 = new Player(testMap, deck, cheaterStrategy);
    Player *p3 = new Player(testMap, deck, strategy);
    Player *p4 = new Player(testMap, deck, benevolentStrategy);
    Player *p5 = new Player(testMap, deck, aggressiveStrategy);
    Player *p6 = new Player(testMap, deck, humanStrategy);

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

    for (Territory *territory: testMap->getTerritories()) {
        territory->setPlayer(1);
    }
    testMap->getTerritories()[0]->setPlayer(2);
    testMap->getTerritories()[1]->setPlayer(3);
    testMap->getTerritories()[2]->setPlayer(4);
    testMap->getTerritories()[3]->setPlayer(5);
    testMap->getTerritories()[4]->setPlayer(6);


    cout << "Main Game Loop start: " << endl;

    engine->mainGameLoop();
    return 0;
}
//FROM DAVID's test in playerDriver
void testPlayers() {

    Continent* continent = new Continent();
    vector<Territory*> territoryArray = getTerritoryArray();
    continent->setTerritories(territoryArray);
    Map* map = new Map();
    map->addContinent(continent);

    Deck* deck = new Deck();

    AggressivePlayerStrategy* aps1 = new AggressivePlayerStrategy();
    BenevolentPlayerStrategy* aps2 = new BenevolentPlayerStrategy();

    Player* player1 = new Player(map, deck, aps1);
    Player* player2 = new Player(map, deck, aps2);

    ////Testing stream insertion

    cout << *player1;
    cout << *player2;

    cout << "Player 2 strongest territory: " << aps2->getStrongestTerritory(player2)->getName() << endl;
    //cout << "Player 2 second strongest territory: " << aps2->getSecondStrongestTerritory(player2)->getName() << endl;

    player1->setTroopsToDeploy(10);
    player2->setTroopsToDeploy(10);

    ////Issue order

    deck->draw(player1->getHand());
    deck->draw(player2->getHand());
    deck->draw(player1->getHand());
    deck->draw(player2->getHand());

    ////Issue all orders from both players

    while(!player1->issueOrder());
    while(!player2->issueOrder());

    cout << "---" << endl;

    Territory* toAttackTerritories = player2->toAttack();

    Territory* toDefendTerritories = player2->toDefend();

    int sizeOfToAttackP2 = player2->getSizeOfToAttack();
    int sizeOfToDefendP2 = player2->getSizeOfToDefend();

    cout << "toAttackSizeP2: " << sizeOfToAttackP2 << endl;
    cout << "toDefendSizeP2: " << sizeOfToDefendP2 << endl;

    //Testing toAttack()
    cout << "Territories to attack for " << *player2 << endl;
    for (int i = 0; i < sizeOfToAttackP2; i++) {
        cout << toAttackTerritories[i] << endl;
    }
    cout << "---" << endl;

    //Testing toDefend()
    cout << "Territories to defend for " << *player2 << endl;
    for (int i = 0; i < sizeOfToDefendP2; i++) {
        cout << toDefendTerritories[i] << endl;
    }
    cout << "---" << endl;

    ////Testing attack and defend functions
    Territory* toAttackTerritories1 = player1->toAttack();

    Territory* toDefendTerritories1 = player1->toDefend();

    int sizeOfToAttackP1 = player1->getSizeOfToAttack();
    int sizeOfToDefendP1 = player1->getSizeOfToDefend();

    cout << "toAttackSizeP1: " << sizeOfToAttackP1 << endl;
    cout << "toDefendSizeP1: " << sizeOfToDefendP1 << endl;

    cout << "Territories to attack for " << *player1 << endl;
    for (int i = 0; i < sizeOfToAttackP1; i++) {
        cout << toAttackTerritories1[i] << endl;
    }
    cout << "---" << endl;

    cout << "Territories to defend for " << *player1 << endl;
    for (int i = 0; i < sizeOfToDefendP1; i++) {
        cout << toDefendTerritories1[i] << endl;
    }
    cout << "---" << endl;

    cout << "Enter any character to end : ";
    int any;
    cin >> any;

}