#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <string>

using namespace std;

//function to test players
void testPlayers() {
	//All data members of user-defined class type must be of pointer type. 
	Player* player1 = new Player();
	Player* player2 = new Player();//TODO: make this use 2nd constructor (the one with territories)

	//Testing stream insertion
	cout << *player1 << endl;

	//Issue order
	player1->issueOrder();

	//Testing attack and defend functions
	Territory* toAttackTerritories = player1->toAttack();

	Territory* toDefendTerritories = player1->toDefend();

	//Avoiding memory leaks
	player1->~Player();
	delete player1;
	player1 = NULL;


}

int main() {
	testPlayers();
	return 0;
}