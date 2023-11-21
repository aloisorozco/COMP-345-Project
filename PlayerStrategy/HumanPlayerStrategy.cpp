#include "HumanPlayerStrategy.h"
#include "../Map/Map.h"
#include "../Player/Player.h"

#include <string>

bool HumanPlayerStrategy::issueOrder(Player* player) {

	Map* map = player->getMap();
	Hand* hand = player->getHand();
	Deck* deck = player->getDeck();
	OrdersList* ordersList = player->getOrdersList();

	//print toDefend & toAttack to show player what he has
	Territory* toDefendTerritories = toDefend(player);
	Territory* toAttackTerritories = toAttack(player);

	cout << "\nTerritories to defend for player " << player->getPlayerID() << endl;
	for (int i = 0; i < player->getSizeOfToDefend(); i++) {
		cout << toDefendTerritories[i] << endl;
	}
	cout << "---\n" << endl;

	cout << "Territories to attack for player " << player->getPlayerID() << endl;
	for (int i = 0; i < player->getSizeOfToAttack(); i++) {
		cout << toAttackTerritories[i] << endl;
	}
	cout << "---\n" << endl;
	cout << "Player " << player->getPlayerID() << "'s turn" << endl;

	//if player has troops to deploy, player is forced to deploy them can't issue another order
	if (*player->getTroopsToDeploy() > 0) {

		string tempString;
		int tempInt;
		cout << "Deploy troops: " << endl;
		cout << "Number of troops left to deploy: " << *player->getTroopsToDeploy() << endl;

		while (true) {
			cout << "Enter territory name: ";
			cin >> tempString;
			cout << "Enter troops to deploy: ";
			cin >> tempInt;

			//checks to make sure deploy is allowed
			if (tempInt <= *player->getTroopsToDeploy() && player->hasTerritory(tempString)) {
				break;
			}
			else {
				cout << "Invalid input please try again" << endl;
			}
		}
		Deploy* deploy = new Deploy(player->getPlayerID(), "", tempInt, map->getTerritory(tempString));
		//Deploy* deploy = new Deploy(tempString, tempInt);
		ordersList->add(deploy);
		player->setTroopsToDeploy(*player->getTroopsToDeploy() - tempInt);

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

		Advance* advance = new Advance(player->getPlayerID(), "", tempInt, map->getTerritory(srcInput), map->getTerritory(dstInput));
		//Advance* advance = new Advance(srcInput, dstInput, tempInt);
		ordersList->add(advance);
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

		string orderString = tempCards[cardChoice]->play(deck, hand);

		//TODO: once david merges to main going to have to dynamic cast for each type of order
		if (orderString == "Deploy") {
			player->setTroopsToDeploy(*player->getTroopsToDeploy() + 5);
		}
		else if (orderString == "Blockade") {
			string targetTerritoryString;

			cout << "\nEnter target territory name: ";
			cin >> targetTerritoryString;

			//Assuming territory name is correct
			ordersList->add(new Blockade(player->getPlayerID(), "", map->getTerritory(targetTerritoryString)));
		}
		else if (orderString == "Bomb") {
			string targetTerritoryString;

			cout << "\nEnter target territory name: ";
			cin >> targetTerritoryString;

			//Assuming territory name is correct
			ordersList->add(new Bomb(player->getPlayerID(), "", map->getTerritory(targetTerritoryString)));
		}
		else if (orderString == "Airlift") {
			string srcInput;
			string dstInput;
			int tempInt;

			while (true) {

				cout << "\nEnter source territory name: ";
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

			//Assuming territory name is correct
			ordersList->add(new Airlift(player->getPlayerID(), "", tempInt, map->getTerritory(srcInput), map->getTerritory(dstInput)));
		}
		else if (orderString == "Negotiate") {
			int tempInt;
			while (true) {

				cout << "\nEnter target player's ID: ";
				cin >> tempInt;

				if (tempInt > 0) {
					break;
				}
				else {
					cout << "Invalid player ID please try again" << endl;
				}
			}

			ordersList->add(new Negotiate(player->getPlayerID(), "", tempInt));
		}

		else {
			cout << "Invalid input, please try again" << endl;
		}

		return false;
	}
	else if (actionInput == 3) {
		//signals to game engine that no more orders will be done
		cout << "Option 3: End turn\n" << endl;
		return true;
	}
}

Territory* HumanPlayerStrategy::toAttack(Player* player) {
	Map* map = player->getMap();

	if (map == NULL) {
		return 0;
	}

	Territory* temp = new Territory[map->getTerritories().size()];
	int count = 0;
	//loop through all territories on the map
	for (Territory* territory : map->getTerritories()) {
		//if the current territory belongs to this player
		if (territory->getPlayer() == player->getPlayerID()) {
			//loop through neighbouring territories
			for (Territory* neighbor : territory->getNeighbors()) {
				//if neighbouring territory is not already in the array and the neighbouring territory does not belong to this player
				if (!player->isAlreadyInToAttack(temp, count, neighbor) && neighbor->getPlayer() != player->getPlayerID()) {
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

	player->setSizeOfToAttack(count);
	return toAttack;
}

Territory* HumanPlayerStrategy::toDefend(Player* player) {
	Map* map = player->getMap();

	if (map == NULL) {
		return 0;
	}

	Territory* temp = new Territory[map->getTerritories().size()];
	int count = 0;
	for (Territory* territory : map->getTerritories()) {
		if (territory->getPlayer() == player->getPlayerID()) {
			temp[count] = *territory;
			count++;
		}
	}

	Territory* toDefend = new Territory[count];
	for (int i = 0; i < count; i++) {
		toDefend[i] = temp[i];
	}

	player->setSizeOfToDefend(count);
	return toDefend;
}
