#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

class Player {

private:

	//for stream insertion operator
	int* playerID;

	//to get element in territoryArray: *(territoryArray + index)
	//this is equivalent to Territory territoryArray[] but it had
	//to be done this way because of requirements (all variables must be in pointers)
	Territory* territoryArray;
	int* sizeOfTerritoryArray;
	OrdersList* ordersList;
	Hand* hand;

	friend ostream& operator << (ostream& out, const Player& player);

public:

	Player();

	Player(Territory* territoryArray, int sizeOfTerritoryArray);

	Player(const Player& playerToCopy);

	~Player();

	Territory* toDefend();

	Territory* toAttack();

	void issueOrder();

	int getPlayerID();

	Territory getTerritoryArray();

	OrdersList getOrdersList();

	Hand getHand();

	void setPlayerID(int playerID);

	void setTerritoryArray(Territory* territoryArray);

	void setOrdersList(OrdersList ordersList);

	void setHand(Hand hand);

	Player& operator=(const Player& player);

};

// free function declaration
void testPlayers();

#endif