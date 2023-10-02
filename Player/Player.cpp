#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <string>

using namespace std;

// All classes must implement a correct copy constructor, assignment operator, and stream insertion operator
// Memory leaks must be avoided 
// Code must be documented using comments (user-defined classes, methods, free functions, operators)


//TODO test that playerCount & playerID is working
int* playerCount = new int(1);

Player::Player() {
	playerID = new int(*playerCount);
	*playerCount++;

	territoryArray = NULL;
	sizeOfTerritoryArray = new int(0);
	orderList = new OrderList();
	hand = NULL;
}

Player::Player(Territory* territoryArray, int sizeOfTerritoryArray) {
	playerID = new int(*playerCount);
	*playerCount++;

	this->territoryArray = territoryArray;
	this->sizeOfTerritoryArray = new int(sizeOfTerritoryArray);
}

//TODO: is this how it should be copied?
Player::Player(const Player& copyPlayer) {
	this->playerID = copyPlayer.playerID;
	this->territoryArray = copyPlayer.territoryArray;
	this->sizeOfTerritoryArray = new int(*copyPlayer.sizeOfTerritoryArray);
	this->orderList = copyPlayer.orderList;
	this->hand = copyPlayer.hand;
}

Player::~Player() {
	delete this->territoryArray;
	territoryArray = NULL;

	delete this->sizeOfTerritoryArray;
	sizeOfTerritoryArray = NULL;

	delete this->orderList;
	orderList = NULL;

	delete this->hand;
	hand = NULL;
}

Territory* Player::toDefend() {
	//TODO: test to see if we can remove this
	if (sizeOfTerritoryArray == 0) {
		return NULL;
	}
	
	if (sizeOfTerritoryArray == 1) {
		return territoryArray;
	}

	//for now just returning the first half of the player's territory array
	int sizeOfToDefendArray = sizeOfTerritoryArray / 2;
	Territory toDefendArray[sizeOfToDefendArray];
	for (int i = 0; i < sizeOfToDefendArray; i++) {
		toDefendArray[i] = territoryArray[i];
	}

	//TODO: test that this works
	return toDefendArray;
}

Territory* Player::toAttack() {
	//TODO: need to wait on MAP dependency
	return NULL;
}

void Player::issueOrder() {
	int playerInput;

	//The different kinds of orders are: deploy, advance,
	//bomb, blockade, airlift, and negotiate
	cout << "Choose an order:\n";
	cout << "1.Deploy\n2. Advance\n3. Bomb\n4. Blockade\n5. Airlift\n6. Negotiate\n";

	cin >> playerInput;

	//TODO: test
	Order* order;

	switch (playerInput) {

	//TODO: wait on ORDER dependency
	case 1:
		order = new Deploy();
		break;

	case 2:
		order = new Advance();
		break;

	case 3:
		order = new Bomb();
		break;

	case 4:
		order = new Blockade();
		break;

	case 5:
		order = new Airlift();
		break;

	case 6:
		order = new Negotiate();
		break;
	
	default:
		cout << "Incorrect input\n";
		return;
		//break;

	this->orderList->addOrder(order);

	}

}

//stream insertion operators TODO: check if this is ok
ostream& Player::operator << (ostream& out, const Player& player)
{
	out << "Player " << playerID << endl;
	return out;
}

//TODO: check if necessary
istream& Player::operator >> (istream& in, Player& player)
{
	/*cout << "Enter Real Part ";
	in >> c.real;
	cout << "Enter Imaginary Part ";
	in >> c.imag;*/
	return in;
}

//assignment operator
Player& Player::operator=(const Player& player) {
	this->setTerritoryArray(*player.territoryArray);
	this->setOrderList(*player.orderList);
	this->setHand(*player.hand);

	return *this;
}

//Getters and Setters
int Player::getPlayerID() {
	return *this->playerID;
}

Territory Player::getTerritoryArray() {
	return *this->territoryArray;
}

OrderList Player::getOrderList() {
	return *this->orderList;
}

Hand Player::getHand() {
	return *this->hand;
}

//TODO: testSetters
void Player::setPlayerID(int playerID) {
	*this->playerID = playerID;
}


void Player::setTerritoryArray(Territory territoryArray) {
	*this->territoryArray = territoryArray;
}

void Player::setOrderList(OrderList orderList) {
	*this->orderList = orderList;
}

void Player::setHand(Hand hand) {
	*this->hand = hand;
}

