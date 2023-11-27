#include "../Map/Map.h"
#include "AggressivePlayerStrategy.h"

#include <string>
#include <thread>

bool AggressivePlayerStrategy::issueOrder(Player* player) {
	Map* map = player->getMap();
	Hand* hand = player->getHand();
	Deck* deck = player->getDeck();
	OrdersList* ordersList = player->getOrdersList();

	//print toDefend & toAttack to show player what he has
	Territory* toDefendTerritories = toDefend(player);
	Territory* toAttackTerritories = toAttack(player);

	int toDefendTerritoriesSize = toDefendSize(player);
	int toAttackTerritoriesSize = toAttackSize(player);

	Territory* strongestTerritory = getStrongestTerritory(player);

	cout << "\nAggressive Player " << player->getPlayerID() << "'s issue order\n" << endl;

	//if player has troops to deploy, player is forced to deploy them can't issue another order
	if (*player->getTroopsToDeploy() > 0) {

		cout << "Deploy troops: " << endl;
		cout << "Number of troops left to deploy: " << *player->getTroopsToDeploy() << endl;

		cout << "\nDeploying " << *player->getTroopsToDeploy() << " troops in " << strongestTerritory->getName() << endl;

		Deploy* deploy = new Deploy(player->getPlayerID(), "", *player->getTroopsToDeploy(), strongestTerritory);
		ordersList->add(deploy);
		player->setTroopsToDeploy(0);

		this_thread::sleep_for(chrono::milliseconds(1000));

		return false;
	}
	
	else {
		
		if(hand->getCards().size() > 0){

			Card* card = hand->getCards().back();

			Territory* target = map->getTerritory(toAttackTerritories[rand() % toAttackTerritoriesSize].getName());

			if(card->getType() == Card::ReinforcementCT){

				player->setTroopsToDeploy(*player->getTroopsToDeploy() + 5);
				deck->returnCard(card);
			}

			else if(card->getType() == Card::BombCT){

				ordersList->add(new Bomb(player->getPlayerID(), "", target));
				deck->returnCard(card);
			}

			else if(card->getType() == Card::AirliftCT){

				Territory* secondStrongest = getSecondStrongestTerritory(player);

				ordersList->add(new Airlift(player->getPlayerID(), "", secondStrongest->getArmy(), secondStrongest, strongestTerritory));
				deck->returnCard(card);
			}

			else{

				deck->returnCard(card);
			}

			return false;
		}

		else{

			for(Territory* neighbor : strongestTerritory->getNeighbors()){

				if(neighbor->getPlayer() == player->getPlayerID()){

					ordersList->add(new Advance(player->getPlayerID(), "", neighbor->getArmy(), neighbor, strongestTerritory));
					return false;
				}
			}
			
			ordersList->add(new Advance(player->getPlayerID(), "", strongestTerritory->getArmy(), strongestTerritory, map->getTerritory(toAttackTerritories[rand() % toAttackTerritoriesSize].getName())));
			return true;
		}

		cout << "\nEnding turn\n" << endl;
	}
}

Territory* AggressivePlayerStrategy::toAttack(Player* player) {

	Territory* strongestTerritory = getStrongestTerritory(player);

	int count = 0;

	for(Territory* territory : strongestTerritory->getNeighbors()){

		if(territory->getPlayer() != player->getPlayerID()){
			count++;
		}
	}

	Territory* enemies = new Territory[count];

	int i = 0;

	for(Territory* territory : strongestTerritory->getNeighbors()){

		if(territory->getPlayer() != player->getPlayerID()){
			enemies[i] = *territory;
		}
		i++;
	}

	return enemies;

}

Territory* AggressivePlayerStrategy::toDefend(Player* player) {
	
	player->setSizeOfToDefend(0);
	return new Territory[0];
}

int AggressivePlayerStrategy::toAttackSize(Player* player){

	Territory* strongestTerritory = getStrongestTerritory(player);

	int count = 0;

	for(Territory* territory : strongestTerritory->getNeighbors()){

		if(territory->getPlayer() != player->getPlayerID()){
			count++;
		}
	}

	return count;
}

int AggressivePlayerStrategy::toDefendSize(Player* player){
	return 0;
}

Territory* AggressivePlayerStrategy::getStrongestTerritory(Player* player){

	Map* map = player->getMap();

	if (map == NULL) {
		return 0;
	}

	Territory* strongestTerritory = nullptr;
	int max = 0;
	//loop through all territories on the map
	for (Territory* territory : map->getTerritories()) {
		//if the current territory belongs to this player
		if (territory->getPlayer() == player->getPlayerID()) {

			bool isNextToEnemy = false;
			for(Territory* neighbor : territory->getNeighbors()){

				if(neighbor->getPlayer() != player->getPlayerID()){

					isNextToEnemy = true;
				}
			}

			if(territory->getArmy() > max && isNextToEnemy){

				strongestTerritory = territory;
				max = territory->getArmy();
			}
		}
	}

	return strongestTerritory;
}

Territory* AggressivePlayerStrategy::getSecondStrongestTerritory(Player* player){

	Map* map = player->getMap();

	if (map == NULL) {
		return 0;
	}

	Territory* strongestTerritory = nullptr;
	Territory* secondStrongestTerritory = nullptr;
	int max = 0;
	//loop through all territories on the map
	for (Territory* territory : map->getTerritories()) {
		//if the current territory belongs to this player
		if (territory->getPlayer() == player->getPlayerID()) {

			bool isNextToEnemy = false;
			for(Territory* neighbor : territory->getNeighbors()){

				if(neighbor->getPlayer() != player->getPlayerID()){

					isNextToEnemy = true;
				}
			}

			if(territory->getArmy() > max && isNextToEnemy){
				
				secondStrongestTerritory = strongestTerritory;
				strongestTerritory = territory;
				max = territory->getArmy();
			}
		}
	}

	return strongestTerritory;
}
