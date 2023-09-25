#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

using namespace std;

class Player {
private:

	list<Territory> territoryCollection;
	OrderList orderList;
	Hand hand;
	

public:

	Player() {

	}

	list<Territory> toDefend() {
		return null;
	}

	list<Territory> toAttack() {
		return null;
	}

	void issueOrder(Order order) {

	}

};