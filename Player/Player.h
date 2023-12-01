#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "../PlayerStrategy/PlayerStrategy.h"
#include "../PlayerStrategy/AggressivePlayerStrategy.h"

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
	int* orderListIndex;
	Hand* hand;
	Deck* deck;

	int* troopsToDeploy;

	int* sizeOfToDefend;
	int* sizeOfToAttack;
	
	//reference of map
	Map* map;

	PlayerStrategy* strategy;

	friend ostream& operator << (ostream& out, const Player& player);

public:

	Player();
	
	Player(Map* map, Deck* deck, PlayerStrategy* strategy);

	Player(Territory* territoryArray, int sizeOfTerritoryArray);

	Player(const Player& playerToCopy);

	~Player();

	Territory* toDefend();

	Territory* toAttack();

	bool issueOrder();

	//void orderOrdersList();

	bool hasTerritory(string territoryName);

	bool hasTerritory(Territory territory);

	Order* getNextInOrdersList();

	int getPlayerID();

	Territory getTerritoryArray();

	OrdersList* getOrdersList();

	Hand* getHand();

	Map* getMap();

	void setPlayerID(int playerID);

	void setTerritoryArray(Territory* territoryArray);

	void setOrdersList(OrdersList ordersList);

	void setHand(Hand* hand);

	void setMap(Map* map);

	int getSizeOfToDefend() {
		return *sizeOfToDefend;
	}

	int getSizeOfToAttack() {
		return *sizeOfToAttack;
	}

	void setSizeOfToDefend(int i) {
		*sizeOfToDefend = i;
	}

	void setSizeOfToAttack(int i) {
		*sizeOfToAttack = i;
	}

	int* getTroopsToDeploy() {
		return troopsToDeploy;
	}

	void setTroopsToDeploy(int troops) {
		*this->troopsToDeploy = troops;
	}

	int getOrderListIndex() {
		return *orderListIndex;
	}

	void setOrderListIndex(int index) {
		*this->orderListIndex = index;
	}

	PlayerStrategy* getPlayerStrategy() {
		return strategy;
	}

	void setPlayerStrategy(PlayerStrategy* strategy) {
		this->strategy = strategy;
	}

	Player& operator=(const Player& player);
	
	Deck* getDeck() {
		return deck;
	}

	//check to make sure we do not add duplicate territories in the toAttack array
	bool isAlreadyInToAttack(Territory* curToAttack, int sizeOfCurToAttack, Territory* territoryToAdd) {
		for (int i = 0; i < sizeOfCurToAttack; i++) {
			//assuming each territory has a unique name
			if (curToAttack[i].getName() == territoryToAdd->getName()) {
				return true;
			}
		}
		return false;
	}

};

// free function declaration
void testPlayers();

#endif