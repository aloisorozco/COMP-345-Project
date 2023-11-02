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
	territoryArray.push_back(temp);

	temp = new Territory("Quebec", "c1");
	temp->setPlayer(2);
	territoryArray.push_back(temp);

	temp = new Territory("Ontario", "c1");
	temp->setPlayer(2);
	territoryArray.push_back(temp);

	temp = new Territory("Manitoba", "c1");
	temp->setPlayer(1);
	territoryArray.push_back(temp);

	temp = new Territory("BC", "c1");
	temp->setPlayer(1);
	territoryArray.push_back(temp);

	temp = new Territory("Mexico", "c1");
	temp->setPlayer(1);
	territoryArray.push_back(temp);

	temp = new Territory("USA", "c1");
	temp->setPlayer(1);
	territoryArray.push_back(temp);

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