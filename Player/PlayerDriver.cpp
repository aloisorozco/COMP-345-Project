#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<Territory*> getTerritoryArray() {
	vector<Territory*> territoryArray;

    // Create Territories
	Territory* temp = new Territory("Yukon", "c1");
	temp->setPlayer(2);

	Territory* temp1 = new Territory("Quebec", "c1");
	temp1->setPlayer(2);

	Territory* temp2 = new Territory("Ontario", "c1");
	temp2->setPlayer(2);

	Territory* temp3 = new Territory("Manitoba", "c1");
	temp3->setPlayer(1);

	Territory* temp4 = new Territory("BC", "c1");
	temp4->setPlayer(1);

	Territory* temp5 = new Territory("Mexico", "c1");
	temp5->setPlayer(1);

	Territory* temp6 = new Territory("USA", "c1");
	temp6->setPlayer(1);

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

//function to test players
void testPlayers() {

	Continent* continent = new Continent();
	vector<Territory*> territoryArray = getTerritoryArray();
	continent->setTerritories(territoryArray);
	Map* map = new Map();
	map->addContinent(continent);

	Player* player1 = new Player(map);
    Player* player2 = new Player(map);

	//Testing stream insertion
	cout << *player1 << endl;
	cout << *player2 << endl;

	//Issue order
	player1->issueOrder();
	cout << "---" << endl;

	//Testing attack and defend functions
	Territory* toAttackTerritories = player2->toAttack();

	Territory* toDefendTerritories = player2->toDefend();

	cout << "Territories to attack for " << *player2 << endl;
	for (int i = 0; i < player2->getSizeOfToAttack(); i++) {
		cout << toAttackTerritories[i] << endl;
	}
	cout << "---" << endl;
	
	cout << "Territories to defend for " << *player2 << endl;
	for (int i = 0; i < player2->getSizeOfToDefend(); i++) {
		cout << toDefendTerritories[i] << endl;
	}
	cout << "---" << endl;

	/*Territory* territoryArray1 = getTerritoryArray();
	player1->setTerritoryArray(territoryArray1);*/
	//player1->setMap(*map);
	//THIS LINE ABOVE DOES NOT WORK SOMETHING WITH THE COPY CONSTRUCTOR OF MAP IDK WHY WILL INVESTIGATE AFTER

	//Testing attack and defend functions
	Territory* toAttackTerritories1 = player1->toAttack();

	Territory* toDefendTerritories1 = player1->toDefend();

	cout << "Territories to attack for " << *player1 << endl;
	for (int i = 0; i < player1->getSizeOfToAttack(); i++) {
		cout << toAttackTerritories1[i] << endl;
	}
	cout << "---" << endl;

	cout << "Territories to defend for " << *player1 << endl;
	for (int i = 0; i < player1->getSizeOfToDefend(); i++) {
		cout << toDefendTerritories1[i] << endl;
	}
	cout << "---" << endl;

}