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

	territoryArray = new Territory[0];
	sizeOfTerritoryArray = new int(0);
	ordersList = new OrdersList();
	orderListIndex = new int(-1);//setting this one to -1 since we have an empty orderList
	hand = NULL;
	map = NULL;
	deck = NULL;

	sizeOfToAttack = new int(0);
	sizeOfToDefend = new int(0);

	troopsToDeploy = new int(0);
}

//main constructor to use other ones i will leave for now but they are not tested to work
Player::Player(Map* map, Deck* deck) {
	playerID = new int(*playerCount);
	(*playerCount)++;

	this->map = map;
	territoryArray = new Territory[0];
	sizeOfTerritoryArray = new int(0);
	ordersList = new OrdersList();
	orderListIndex = new int(-1);
	hand = new Hand(deck);
	this->deck = new Deck(*deck);

	sizeOfToAttack = new int(0);
	sizeOfToDefend = new int(0);

	troopsToDeploy = new int(0);
}

//initializing a player with a collection of territories
Player::Player(Territory* territoryArray, int sizeOfTerritoryArray) {
	playerID = new int(*playerCount);
	(*playerCount)++;

	this->territoryArray = territoryArray;
	this->sizeOfTerritoryArray = new int(sizeOfTerritoryArray);
	ordersList = new OrdersList();
	orderListIndex = new int(-1);
	hand = NULL;
	map = NULL;
	deck = NULL;

	sizeOfToAttack = new int(0);
	sizeOfToDefend = new int(0);

	troopsToDeploy = new int(0);
}

//copy constructor
Player::Player(const Player& copyPlayer) {
	Player();

	this->playerID = new int (*copyPlayer.playerID);
	this->territoryArray = copyPlayer.territoryArray;
	this->territoryArray = new Territory[*copyPlayer.sizeOfTerritoryArray];
	for (int i = 0; i < *copyPlayer.sizeOfTerritoryArray; i++) {
		this->territoryArray[i] = copyPlayer.territoryArray[i];
	}
	this->sizeOfTerritoryArray = new int(*copyPlayer.sizeOfTerritoryArray);
	this->ordersList = new OrdersList(*copyPlayer.ordersList);
	this->orderListIndex = new int(*copyPlayer.orderListIndex);
	this->hand = new Hand(*copyPlayer.hand);
	this->deck = new Deck(*copyPlayer.deck);
	this->map = new Map(*copyPlayer.map);
	this->sizeOfToAttack = new int(*copyPlayer.sizeOfToAttack);
	this->sizeOfToDefend = new int(*copyPlayer.sizeOfToDefend);
	this->troopsToDeploy = new int(*copyPlayer.troopsToDeploy);
}

//destructor to avoid any memory leaks
Player::~Player() {
	delete this->territoryArray;
	territoryArray = NULL;

	delete this->sizeOfTerritoryArray;
	sizeOfTerritoryArray = NULL;

	delete this->ordersList;
	ordersList = NULL;

	delete this->orderListIndex;
	orderListIndex = NULL;

	delete this->hand;
	hand = NULL;

	delete this->deck;
	deck = NULL;

	delete this->map;
	map = NULL;

	delete this->sizeOfToAttack;
	sizeOfToAttack = NULL;

	delete this->sizeOfToDefend;
	sizeOfToDefend = NULL;

	delete this->troopsToDeploy;
	troopsToDeploy = NULL;
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

	*sizeOfToDefend = count;
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

	*sizeOfToAttack = count;
	return toAttack;
}

//issuing order
bool Player::issueOrder() {

	//print toDefend & toAttack to show player what he has
	Territory* toDefendTerritories = toDefend();
	Territory* toAttackTerritories = toAttack();

	cout << "\nTerritories to defend for player " << *playerID << endl;
	for (int i = 0; i < getSizeOfToDefend(); i++) {
		cout << toDefendTerritories[i] << endl;
	}
	cout << "---\n" << endl;

	cout << "Territories to attack for player " << *playerID << endl;
	for (int i = 0; i < getSizeOfToAttack(); i++) {
		cout << toAttackTerritories[i] << endl;
	}
	cout << "---\n" << endl;
	cout << "Player " << *playerID << "'s turn" << endl;

	/*cout << "Map: " << endl;
	cout << *map << endl;
	cout << "---\n" << endl;*/
	

	if (*troopsToDeploy > 0) {

		string tempString;
		int tempInt;
		cout << "Deploy troops: " << endl;
		cout << "Number of troops left to deploy: " << *troopsToDeploy << endl;

		while (true) {
			cout << "Enter territory name: ";
			cin >> tempString;
			cout << "Enter troops to deploy: ";
			cin >> tempInt;

			//TODO: also need to call validate function to see if territory belongs to player
			if (tempInt <= *troopsToDeploy && hasTerritory(tempString)) {
				break;
			}
			else {
				cout << "Invalid input please try again" << endl;
			}
		}

		Deploy* deploy = new Deploy(tempString, tempInt);
		ordersList->add(*deploy);
		troopsToDeploy = new int(*troopsToDeploy - tempInt);
		
		return false;
	}

	//choose advance troops or play a card if have one or end turn
	int actionInput;
	
	while (true) {
		cout << "Choose an action: " << endl;

		cout << "1. Advance troops" << endl;
		cout << "2. Play a card" << endl;
		cout << "3. End turn" << endl;

		cin >> actionInput;

		if (actionInput > 0 && actionInput < 4) {
			if (actionInput == 2 && hand->getHandSize() == 0) {
				cout << "No cards in hand at the moment please select another option" << endl;
			}
			else {
				break;
			}
		}
	}
	if (actionInput == 1) {
		//makes an advance object with inputs but does not validate input
		string srcInput;
		string dstInput;
		int tempInt;
		while (true) {
			
			cout << "Option 1: Advance troops\n" << endl;

			cout << "Enter source territory name: ";
			cin >> srcInput;

			cout << "Enter destination territory name: ";
			cin >> dstInput;
			;
			cout << "Enter troops to advance: ";
			cin >> tempInt;

			if (tempInt > 0) {
				break;
			}
			else {
				cout << "Invalid number of troops to advance please try again" << endl;
			}
		}
		

		Advance* advance = new Advance(srcInput, dstInput, tempInt);
		ordersList->add(*advance);
		return false;
	}
	else if (actionInput == 2) {
		int cardChoice;
		vector<Card*> tempCards = hand->getCards();

		while (true) {
			cout << "Option 2: Play a card\n" << endl;
			cout << "Displaying cards in hand:\n" << endl;

			for (int i = 0; i < tempCards.size(); i++) {
				cout << "Card " << i << ": " << *tempCards[i] << endl;
			}

			cout << "Choose a card to play:\n" << endl;
			cin >> cardChoice;

			if (cardChoice >= 0 || cardChoice < tempCards.size()) {
				break;
			}
			else {
				cout << "Invalid card choice please try again" << endl;
			}
		}
		
		cout << "\nCard chosen:" << endl;
		cout << *tempCards[cardChoice] << endl;

		Order* order = tempCards[cardChoice]->play(deck, hand);

		if (dynamic_cast<const Deploy*>(order)) {
			*troopsToDeploy += 5;
		}
		else {
			ordersList->add(*order);
		}

		return false;
	}
	else if (actionInput == 3) {
		//signals to game engine that no more orders will be done
		cout << "Option 4: End turn\n" << endl;
		return true;
	}
	
}

bool Player::hasTerritory(string territoryName) {
	Territory* toDefendArray = toDefend();
	for (int i = 0; i < *sizeOfToDefend; i++) {
		if (toDefendArray[i].getName() == territoryName) {
			return true;
		}
	}
	return false;
}

bool Player::hasTerritory(Territory territory) {
	Territory* toDefendArray = toDefend();
	for (int i = 0; i < *sizeOfToDefend; i++) {
		if (toDefendArray[i].getName() == territory.getName()) {
			return true;
		}
	}
	return false;
}

Order* Player::getNextInOrdersList() {
	if (*orderListIndex >= ordersList->getOrders().size()) {
		return NULL;
	}
	return ordersList->get(*orderListIndex++);
}

//stream insertion operator
ostream& operator << (ostream& out, const Player& player)
{
	out << "Player " << *player.playerID << endl;
	return out;
}

//assignment operator
Player& Player::operator=(const Player& player) {
	this->setPlayerID(*player.playerID);

	this->setTerritoryArray(player.territoryArray);
	this->setOrdersList(*player.ordersList);
	this->setOrderListIndex(*player.orderListIndex);
	this->setHand(player.hand);
	this->deck = new Deck(*player.deck);
	this->setMap(player.map);

	this->setSizeOfToAttack(*player.sizeOfToAttack);
	this->setSizeOfToDefend(*player.sizeOfToDefend);

	this->troopsToDeploy = player.troopsToDeploy;

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

Hand* Player::getHand() {
	return this->hand;
}

Map* Player::getMap() {
	return this->map;
}

void Player::setPlayerID(int playerID) {
	this->playerID = new int(playerID);
}


void Player::setTerritoryArray(Territory* territoryArray) {
	this->territoryArray = territoryArray;
}

void Player::setOrdersList(OrdersList ordersList) {
	*this->ordersList = ordersList;
}

void Player::setHand(Hand* hand) {
	this->hand = hand;
}

void Player::setMap(Map* map) {
	this->map = map;
}

