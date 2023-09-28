#ifndef PLAYER_H
#define PLAYER_H

class Player {

private:
	//to get element in territoryArray: *(territoryArray + index)
	//this is equivalent to Territory territoryArray[] but it had
	//to be done this way because of requirements (all variables must be in pointers)
	Territory* territoryArray;
	int* sizeOfTerritoryArray;
	OrderList* orderList;
	Hand* hand;

public:
	Player();

	Player(Territory* territoryArray, int sizeOfTerritoryArray);

	Player(const Player& playerToCopy);

	~Player();

	list<Territory> toDefend();

	list<Territory> toAttack();

	void issueOrder();

	Territory getTerritoryArray();

	OrderList getOrderList();

	Hand getHand();

	void setTerritoryArray(Territory territoryArray);

	void setOrderList(OrderList orderList);

	void setHand(Hand hand);

	ostream& operator << (ostream& out, const Player& player);

	//TODO: Ask professor about whether on not to do cin stream insertion
	istream& operator >> (istream& in, Player& player);

	Player& operator=(const Player& player);

};

#endif