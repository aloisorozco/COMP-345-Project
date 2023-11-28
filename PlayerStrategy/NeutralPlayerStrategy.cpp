#include "../Map/Map.h"
#include "NeutralPlayerStrategy.h"

#include <chrono>
#include <thread>
#include <string>

bool NeutralPlayerStrategy::issueOrder(Player* player) {
	Map* map = player->getMap();
	Hand* hand = player->getHand();
	Deck* deck = player->getDeck();
	OrdersList* ordersList = player->getOrdersList();

	//print toDefend & toAttack to show player what he has
	Territory* toDefendTerritories = toDefend(player);
	Territory* toAttackTerritories = toAttack(player);

	cout << "\nNeutral Player " << player->getPlayerID() << "'s issue order\n" << endl;

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
	if (*player->getTroopsToDeploy() > 0) {

		cout << "Deploy troops: " << endl;
		cout << "Number of troops left to deploy: " << *player->getTroopsToDeploy() << endl;


		Territory* randomTerritory = &toDefendTerritories[(rand() % player->getSizeOfToDefend())];
		int randomNumberOfTroops = ((rand() % *player->getTroopsToDeploy()) + 1);

		cout << "\nDeploying " << randomNumberOfTroops << " troops in territory " << randomTerritory->getName() << endl;

		Deploy* deploy = new Deploy(player->getPlayerID(), "", randomNumberOfTroops, randomTerritory);
		ordersList->add(deploy);
		player->setTroopsToDeploy(*player->getTroopsToDeploy() - randomNumberOfTroops);

		this_thread::sleep_for(chrono::milliseconds(1000));

		return false;
	}
	else {
		cout << "\nEnding turn\n" << endl;
		return true;
	}
}

//returns NULL because the neutral player does not attack
Territory* NeutralPlayerStrategy::toAttack(Player* player) {
	return NULL;
}

//returns all territories, in the issue order will be random which territories get reinforced
Territory* NeutralPlayerStrategy::toDefend(Player* player) {
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

string NeutralPlayerStrategy::getStrategyName() {
	return "Neutral";
}