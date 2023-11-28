#include "../Map/Map.h"
#include "CheaterPlayerStrategy.h"

#include <chrono>
#include <thread>
#include <string>

bool CheaterPlayerStrategy::issueOrder(Player* player) {
	Map* map = player->getMap();
	Hand* hand = player->getHand();
	Deck* deck = player->getDeck();
	OrdersList* ordersList = player->getOrdersList();

	//print toDefend & toAttack to show player what he has
	Territory* toDefendTerritories = toDefend(player);
	Territory* toAttackTerritories = toAttack(player);

	cout << "\nCheater Player " << player->getPlayerID() << "'s issue order\n" << endl;

	//idk if we should include this or not for AI players
	/*cout << "\nTerritories to defend for player " << player->getPlayerID() << endl;
	for (int i = 0; i < player->getSizeOfToDefend(); i++) {
		cout << toDefendTerritories[i] << endl;
	}
	cout << "---\n" << endl;

	cout << "Territories to attack for player " << player->getPlayerID() << endl;
	for (int i = 0; i < player->getSizeOfToAttack(); i++) {
		cout << toAttackTerritories[i] << endl;
	}
	cout << "---\n" << endl;*/

	//if player has troops to deploy, player is forced to deploy them can't issue another order
	//can remove this if if cheater player should ignore his reinforcement pool (since he is cheating)
	if (*player->getTroopsToDeploy() > 0) {

		cout << "Deploy troops: " << endl;
		cout << "Number of troops left to deploy: " << *player->getTroopsToDeploy() << endl;


		Territory* randomTerritory = &toDefendTerritories[(rand() % player->getSizeOfToDefend())];
		int randomNumberOfTroops = ((rand() % *player->getTroopsToDeploy()) + 1);

		cout << "\nDeploying " << randomNumberOfTroops << " troops in " << randomTerritory->getName() << endl;

		Deploy* deploy = new Deploy(player->getPlayerID(), "", randomNumberOfTroops, randomTerritory);
		ordersList->add(deploy);
		player->setTroopsToDeploy(*player->getTroopsToDeploy() - randomNumberOfTroops);

		this_thread::sleep_for(chrono::milliseconds(1000));

		return false;
	}
	/*
	right now implementing that cheater player conquers all territories in one turn can change
	to be instead conquering one territory per issue order 
	*/
	else {
		//conquering territories like this instead of by orders since player is cheating
		for (int i = 0; i < player->getSizeOfToAttack(); i++) {

			cout << "\nConquering territory " << toAttackTerritories[i].getName() << endl;

			map->getTerritory(toAttackTerritories[i].getName())->setPlayer(player->getPlayerID());

		}

		cout << "\nEnding turn\n" << endl;
	}
}

Territory* CheaterPlayerStrategy::toAttack(Player* player) {
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

Territory* CheaterPlayerStrategy::toDefend(Player* player) {
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

string CheaterPlayerStrategy::getStrategyName() {
	return "Cheater";
}