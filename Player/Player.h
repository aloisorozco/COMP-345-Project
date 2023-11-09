#ifndef PLAYER_H
#define PLAYER_H

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

class ReinforcementPool{

	private:
		int* numTroops;
		int* playerOwnerID;

	public:

		ReinforcementPool() : numTroops(0), playerOwnerID(0) {};
		ReinforcementPool(int* numTroops, int* playerOwnerID) : numTroops(numTroops), playerOwnerID(playerOwnerID) {};

		int getNumTroops();
		int getPlayerOwnerID();
		void setNumTroops(int troops);
		void setPlayerOwnerID(int playerID);

		void transferTroops(Territory* territory, int troops);
		void retrieveTroops(Territory* territory, int troops);
		void clearTroops();

		ReinforcementPool& operator=(const ReinforcementPool& reinforcementPool){
			if (this != &reinforcementPool) {
                delete numTroops;
                delete playerOwnerID;

                this->numTroops = new int(*reinforcementPool.numTroops);
                this->playerOwnerID = new int(*reinforcementPool.playerOwnerID);
            }
            return *this;
		}
};

class Player {

private:

	//for stream insertion operator
	int* playerID;

	//to get element in territoryArray: *(territoryArray + index)
	//this is equivalent to Territory territoryArray[] but it had
	//to be done this way because of requirements (all variables must be in pointers)
	Territory* territoryArray;
	ReinforcementPool* reinforcement;
	int* sizeOfTerritoryArray;
	OrdersList* ordersList;
	int* orderListIndex;
	Hand* hand;

	int* troopsToDeploy;

	int* sizeOfToDefend;
	int* sizeOfToAttack;
	
	//reference of map
	Map* map;

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

	friend ostream& operator << (ostream& out, const Player& player);

public:

	Player();

	Player(bool neutral);

	Player(Map* map);

	Player(Territory* territoryArray, int sizeOfTerritoryArray);

	Player(const Player& playerToCopy);

	~Player();

	Territory* toDefend();

	Territory* toAttack();

	bool issueOrder();

	bool hasTerritory(string territoryName);

	bool hasTerritory(Territory territory);

	Order* getNextInOrdersList();

	int getPlayerID();

	Territory getTerritoryArray();

	OrdersList getOrdersList();

	Hand getHand();

	Map getMap();

	void setPlayerID(int playerID);

	void setTerritoryArray(Territory* territoryArray);

	void setOrdersList(OrdersList ordersList);

	void setHand(Hand hand);

	void setMap(Map map);

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

	ReinforcementPool getReinforcementPool(){
		return *reinforcement;
	}

	void setReinforcementPool(ReinforcementPool reinforcementt){
		*this->reinforcement = reinforcementt;
	}

	Player& operator=(const Player& player);

};



// free function declaration
void testPlayers();

#endif