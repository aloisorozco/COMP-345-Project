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
	territoryArray[0] = Territory("t1", 1, 2, "c1");
	territoryArray[1] = Territory("t2", 1, 2, "c1");
	territoryArray[2] = Territory("t3", 2, 2, "c1");
	territoryArray[3] = Territory("t4", 1, 2, "c2");
	territoryArray[4] = Territory("t5", 2, 2, "c2");
	territoryArray[5] = Territory("t6", 1, 2, "c2");
	territoryArray[6] = Territory("t7", 2, 2, "c3");

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

	//Testing attack and defend functions
	Territory* toAttackTerritories = player2->toAttack();

	Territory* toDefendTerritories = player2->toDefend();

    //cout << "Territories to attack: " << toAttackTerritories << endl;
    //cout << "Territories to defend: " << toDefendTerritories << endl;
}

int main() {
	testPlayers();
	return 0;
}