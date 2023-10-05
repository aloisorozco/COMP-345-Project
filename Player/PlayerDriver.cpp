#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

Territory* getTerritoryArray() {
	Territory* territoryArray = new Territory[7];

    // Create Territories
	territoryArray[0] = Territory("Yukon", 2, 2, "c1");
	territoryArray[1] = Territory("Quebec", 2, 2, "c1");
	territoryArray[2] = Territory("Ontario", 2, 2, "c1");
	territoryArray[3] = Territory("Manitoba", 2, 2, "c1");
	territoryArray[4] = Territory("BC", 2, 2, "c1");
	territoryArray[5] = Territory("Mexico", 2, 2, "c1");
	territoryArray[6] = Territory("USA", 2, 2, "c1");

	return territoryArray;
}

//function to test players
void testPlayers() {

	Player* player1 = new Player();

	Territory* territoryArray = getTerritoryArray();

    Player* player2 = new Player(territoryArray, 7);

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
	for (int i = 0; i < 7; i++) {
		cout << toAttackTerritories[i] << endl;
	}
	cout << "---" << endl;
	
	cout << "Territories to defend for " << *player2 << endl;
	for (int i = 0; i < 7; i++) {
		cout << toDefendTerritories[i] << endl;
	}
	cout << "---" << endl;

	Territory* territoryArray1 = getTerritoryArray();
	player1->setTerritoryArray(territoryArray1);

	//Testing attack and defend functions
	Territory* toAttackTerritories1 = player1->toAttack();

	Territory* toDefendTerritories1 = player1->toDefend();

	cout << "Territories to attack for " << *player1 << endl;
	for (int i = 0; i < 7; i++) {
		cout << toAttackTerritories1[i] << endl;
	}
	cout << "---" << endl;

	cout << "Territories to defend for " << *player1 << endl;
	for (int i = 0; i < 7; i++) {
		cout << toDefendTerritories1[i] << endl;
	}
	cout << "---" << endl;

}