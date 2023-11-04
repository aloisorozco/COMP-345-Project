#include "Player.h"

#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <string>

using namespace std;

//used for playerID and incremented so each player has a unique id
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
	ordersList = new OrdersList();
	hand = NULL;
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

//territories to defend - for now just returns the territoryArray
Territory* Player::toDefend() {
	if (this->sizeOfTerritoryArray == 0) {
		return NULL;
	}
	return territoryArray;
}

//territories to attack - for now just returns the territoryArray
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
		cout << "Deploy order added";
		break;

	case 2:
		order = new Advance();
		this->ordersList->add(*order);
		cout << "Advance order added";
		break;

	case 3:
		order = new Bomb();
		this->ordersList->add(*order);
		cout << "Bomb order added";
		break;

	case 4:
		order = new Blockade();
		this->ordersList->add(*order);
		cout << "Blockade order added";
		break;

	case 5:
		order = new Airlift();
		this->ordersList->add(*order);
		cout << "Airlift order added";
		break;

	case 6:
		order = new Negotiate();
		this->ordersList->add(*order);
		cout << "Negotiate order added";
		break;
	
	default:
		cout << "Incorrect input\n";
		return;
		//break;

	}
	cout << " for " << *this << endl;

}

//stream insertion operator
ostream& operator << (ostream& out, const Player& player)
{
	out << "Player " << *player.playerID << endl;
	return out;
}

//assignment operator
Player& Player::operator=(const Player& player) {
	this->setTerritoryArray(player.territoryArray);
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

void Player::setPlayerID(int playerID) {
	*this->playerID = playerID;
}


void Player::setTerritoryArray(Territory* territoryArray) {
	this->territoryArray = territoryArray;
}

void Player::setOrdersList(OrdersList ordersList) {
	*this->ordersList = ordersList;
}

void Player::setHand(Hand hand) {
	*this->hand = hand;
}

void Player::setReinforcementPool(ReinforcementPool* reinforcement){
	*this->reinforcement = reinforcement;
}

int ReinforcementPool::getNumTroops() {return *this->numTroops;}
int ReinforcementPool::getPlayerOwnerID() {return *this->playerOwnerID;}
void ReinforcementPool::setNumTroops(int troops) {*this->numTroops = troops;}
void ReinforcementPool::setPlayerOwnerID(int playerID) {*this->playerOwnerID = playerID;}

void ReinforcementPool::transferTroops(Territory* territory, int troops){

	if(*this->playerOwnerID == territory->getPlayer() && *this->numTroops >= troops){
		territory->addTroops(troops);
		*this->numTroops = *this->numTroops - troops;
	}

	else if(*this->numTroops < troops){
		cout << "Invalid: Insufficient number of troops \n";
	}

	else{
		cout << "Invalid: Player does not own the territory. \n";
	}
}

void ReinforcementPool::retrieveTroops(Territory* territory, int troops){

	if(*this->playerOwnerID == territory->getPlayer() && territory->getArmy() >= troops){
		territory->removeTroops(troops);
		*this->numTroops = *this->numTroops + troops;
	}

	else if(territory->getArmy() < troops){
		cout << "Invalid: Insufficient number of troops \n";
	}

	else{
		cout << "Invalid: Player does not own the territory. \n";
	}
}

