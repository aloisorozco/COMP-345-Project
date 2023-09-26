#ifndef PLAYER_H
#define PLAYER_H

class Player {

private:
	list<Territory> territoryCollection;
	OrderList* orderList;
	Hand* hand;

public:
	Player();

	Player(const Player& playerToCopy);

	~Player();

	list<Territory> toDefend();

	list<Territory> toAttack();

	void issueOrder();

	list<Territory> getTerritoryCollection();

	OrderList* getOrderList();

	Hand* getHand();

	void setTerritoryCollection();

	void setOrderList(OrderList* orderList);

	void setHand(Hand* hand);

	ostream& operator << (ostream& out, const Player& c);

	istream& operator >> (istream& in, Player& c);

};

#endif