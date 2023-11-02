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
	map = NULL;

	sizeOfToAttack = new int(0);
	sizeOfToDefend = new int(0);
}

Player::Player(Map* map) {
	playerID = new int(*playerCount);
	(*playerCount)++;

	this->map = map;
	territoryArray = NULL;
	sizeOfTerritoryArray = new int(0);
	ordersList = new OrdersList();
	hand = NULL;

	sizeOfToAttack = new int(0);
	sizeOfToDefend = new int(0);
}

//initializing a player with a collection of territories
Player::Player(Territory* territoryArray, int sizeOfTerritoryArray) {
	playerID = new int(*playerCount);
	(*playerCount)++;

	this->territoryArray = territoryArray;
	this->sizeOfTerritoryArray = new int(sizeOfTerritoryArray);
	ordersList = new OrdersList();
	hand = NULL;
	map = NULL;

	sizeOfToAttack = new int(0);
	sizeOfToDefend = new int(0);
}

//copy constructor
Player::Player(const Player& copyPlayer) {
	this->playerID = copyPlayer.playerID;
	this->territoryArray = copyPlayer.territoryArray;
	this->sizeOfTerritoryArray = new int(*copyPlayer.sizeOfTerritoryArray);
	this->ordersList = copyPlayer.ordersList;
	this->hand = copyPlayer.hand;
	this->map = copyPlayer.map;
	this->sizeOfToAttack = copyPlayer.sizeOfToAttack;
	this->sizeOfToDefend = copyPlayer.sizeOfToDefend;
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

	delete this->map;
	map = NULL;
}

//territories to defend
Territory* Player::toDefend() {
	if (map == NULL) {
		return 0;
	}

	Territory* temp = new Territory[map->getTerritories().size()];
	int count = 0;
	for (Territory* territory: map->getTerritories()) {
		if (territory->getPlayer() == *playerID) {
			temp[count] = *territory;
			count++;
		}
	}

	Territory* toDefend = new Territory[count];
	for (int i = 0; i < count; i++) {
		toDefend[i] = temp[i];
	}

	sizeOfToDefend = new int(count);
	return toDefend;
}

//territories to attack - super inefficient but what can you do
Territory* Player::toAttack() {
	if (map == NULL) {
		return 0;
	}

	Territory* temp = new Territory[map->getTerritories().size()];
	int count = 0;
	//loop through all territories on the map
	for (Territory* territory: map->getTerritories()) {
		//if the current territory belongs to this player
		if (territory->getPlayer() == *playerID) {
			//loop through neighbouring territories
			for (Territory* neighbor: territory->getNeighbors()) {
				//if neighbouring territory is not already in the array and the neighbouring territory does not belong to this player
				if (!isAlreadyInToAttack(temp, count, neighbor) && neighbor->getPlayer() != *playerID) {
					//add it to the array
					temp[count] = *neighbor;
					count++;
				}
			}
		}
	}

	Territory* toAttack = new Territory[count];
	for (int i = 0; i < count; i++) {
		toAttack[i] = temp[i];
	}

	sizeOfToAttack = new int(count);
	return toAttack;
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
	this->setMap(*player.map);

	this->setSizeOfToAttack(*player.sizeOfToAttack);
	this->setSizeOfToDefend(*player.sizeOfToDefend);

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

Map Player::getMap() {
	return *this->map;
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

void Player::setMap(Map map) {
	*this->map = map;
}

