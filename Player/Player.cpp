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
	//assign playerCount to playerID and increment playerCount
	playerID = new int(*playerCount);
	(*playerCount)++;

	territoryArray = NULL;
	sizeOfTerritoryArray = new int(0);
	ordersList = new OrdersList();
	hand = NULL;
}

//initializing a player with a collection of territories
Player::Player(Territory* territoryArray, int sizeOfTerritoryArray) {
	playerID = new int(*playerCount);
	(*playerCount)++;

	this->territoryArray = territoryArray;
	this->sizeOfTerritoryArray = new int(sizeOfTerritoryArray);
}

//copy constructor
Player::Player(const Player& copyPlayer) {
	this->playerID = copyPlayer.playerID;
	this->territoryArray = copyPlayer.territoryArray;
	this->sizeOfTerritoryArray = new int(*copyPlayer.sizeOfTerritoryArray);
	this->ordersList = copyPlayer.ordersList;
	this->hand = copyPlayer.hand;
}

//destructor to avoid any memory leaks
Player::~Player() {
	delete this->territoryArray;
	territoryArray = NULL;

	delete this->sizeOfTerritoryArray;
	sizeOfTerritoryArray = NULL;

	delete this->ordersList;
	ordersList = NULL;

	delete this->hand;
	hand = NULL;
}

Territory* Player::toDefend() {
	if (this->sizeOfTerritoryArray == 0) {
		return NULL;
	}
	return territoryArray;
}

Territory* Player::toAttack() {
	if (this->sizeOfTerritoryArray == 0) {
		return NULL;
	}
	return territoryArray;
}

//issuing order
void Player::issueOrder() {
	int playerInput;

	//The different kinds of orders are: deploy, advance,
	//bomb, blockade, airlift, and negotiate
	cout << "Choose an order:\n";
	cout << "1.Deploy\n2. Advance\n3. Bomb\n4. Blockade\n5. Airlift\n6. Negotiate\n";

	//getting player input
	cin >> playerInput;

	Order* order;

	//creating and adding order object to player's order list
	switch (playerInput) {
	case 1:
		order = new Deploy();
		this->ordersList->add(*order);
		cout << "Deploy order added\n";
		break;

	case 2:
		order = new Advance();
		this->ordersList->add(*order);
		cout << "Advance order added\n";
		break;

	case 3:
		order = new Bomb();
		this->ordersList->add(*order);
		cout << "Bomb order added\n";
		break;

	case 4:
		order = new Blockade();
		this->ordersList->add(*order);
		cout << "Blockade order added\n";
		break;

	case 5:
		order = new Airlift();
		this->ordersList->add(*order);
		cout << "Airlift order added\n";
		break;

	case 6:
		order = new Negotiate();
		this->ordersList->add(*order);
		cout << "Negotiate order added\n";
		break;
	
	default:
		cout << "Incorrect input\n";
		return;
		//break;

	}

}

//stream insertion operator
ostream& operator << (ostream& out, const Player& player)
{
	out << "Player " << *player.playerID << endl;
	return out;
}

//assignment operator
Player& Player::operator=(const Player& player) {
	this->setTerritoryArray(*player.territoryArray);
	this->setOrdersList(*player.ordersList);
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

OrdersList Player::getOrdersList() {
	return *this->ordersList;
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

void Player::setOrdersList(OrdersList ordersList) {
	*this->ordersList = ordersList;
}

void Player::setHand(Hand hand) {
	*this->hand = hand;
}

