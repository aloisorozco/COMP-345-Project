#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

using namespace std;

// All classes must implement a correct copy constructor, assignment operator, and stream insertion operator
// Memory leaks must be avoided 
// Code must be documented using comments (user-defined classes, methods, free functions, operators)


//TODO: check if NULL works
class Player {

private:
	//TODO: territoryCollection impl tbd based on Map dependency
	list<Territory> territoryCollection;
	OrderList* orderList;
	Hand* hand;
	

public:

	Player() {
		//TODO: territoryCollection impl tbd based on Map dependency
		orderList = new OrderList();
		hand = new Hand();
	}

	Player(const Player& playerToCopy) {
		this.territoryCollection = playerToCopy.getTerritoryCollection();
		this.orderList = playerToCopy.getOrderList();
		this.hand = playerToCopy.getHand();
	}

	//TODO: check if this works
	~Player() {
		//TODO: territoryCollection impl tbd based on Map dependency
		delete orderList;
		orderList = NULL;
		delete hand;
		hand = NULL;
	}

	list<Territory> toDefend() {
		return NULL;
	}

	list<Territory> toAttack() {
		return NULL;
	}
	
	//TODO: wait for Order dependency
	void issueOrder() {

	}

	//Getters and Setters
	list<Territory> getTerritoryCollection() {
		return territoryCollection;
	}

	OrderList* getOrderList() {
		return orderList;
	}

	Hand* getHand() {
		return hand;
	}

	void setTerritoryCollection() {
		//TODO: territoryCollection impl tbd based on Map dependency
	}

	void setOrderList(OrderList* orderList) {

	}

	void setHand(Hand* hand) {

	}

	//stream insertion operators TODO: wait for dependencies
	ostream& operator << (ostream& out, const Player& c)
	{
		/*out << c.real;
		out << "+i" << c.imag << endl;*/
		return out;
	}

	istream& operator >> (istream& in, Player& c)
	{
		/*cout << "Enter Real Part ";
		in >> c.real;
		cout << "Enter Imaginary Part ";
		in >> c.imag;*/
		return in;
	}

};