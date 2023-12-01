#include "../Map/Map.h"
#include "AggressivePlayerStrategy.h"

#include <string>
#include <thread>
#include <limits>

bool AggressivePlayerStrategy::issueOrder(Player* player) {
	Map* map = player->getMap();
	Hand* hand = player->getHand();
	Deck* deck = player->getDeck();
	OrdersList* ordersList = player->getOrdersList();

	//print toDefend & toAttack to show player what he has
	Territory* toDefendTerritories = toDefend(player);
	Territory* toAttackTerritories = toAttack(player);

	Territory* strongestTerritory = getStrongestTerritory(player);

	cout << "\nAggressive Player " << player->getPlayerID() << "'s issue order\n" << endl;

	//if player has troops to deploy, player is forced to deploy them can't issue another order. Aggressive player will deploy to the strongest territory
	if (*player->getTroopsToDeploy() > 0) {

		cout << "Deploy troops: " << endl;
		cout << "Number of troops left to deploy: " << *player->getTroopsToDeploy() << endl;

		cout << "\nDeploying " << *player->getTroopsToDeploy() << " troops in " << strongestTerritory->getName() << endl;

		Deploy* deploy = new Deploy(player->getPlayerID(), "", *player->getTroopsToDeploy(), strongestTerritory);
		ordersList->add(deploy);
		player->setTroopsToDeploy(0);

		this_thread::sleep_for(chrono::milliseconds(1000));

		cout << "\nEnding turn\n" << endl;
		return false;
	}
	
	else {
		
		//Will first check if there are cards yet
		if(hand->getHandSize() > 0){

			Card* card = hand->getCards().back();
            cout<<"The card currently about to be played is :"<<card->cardTypeToString()<<endl;
			Territory* target = map->getTerritory(toAttackTerritories[rand() % player->getSizeOfToAttack()].getName());

			if(card->getType() == Card::ReinforcementCT){

				player->setTroopsToDeploy(*player->getTroopsToDeploy() + 5);
				cout << "\nAdding 5 troops to deploy";
			}

			else if(card->getType() == Card::BombCT){

				
				ordersList->add(new Bomb(player->getPlayerID(), "", target));
				cout << "\nBombing " << target->getName();
			}

			else if(card->getType() == Card::AirliftCT){

				Territory* secondStrongest = getSecondStrongestTerritory(player);

				ordersList->add(new Airlift(player->getPlayerID(), "", secondStrongest->getArmy(), secondStrongest, strongestTerritory));
				cout << "\nAirlifting " << secondStrongest->getArmy() << " troops from " << secondStrongest->getName() << " to " << strongestTerritory->getName();
			}

			//Aggressive Player will ignore cards with no offensive nature
			else{
				cout << "\nNot issuing orders";
			}

			deck->returnCard(card);
			hand->removeCard(card);


			cout << "\nEnding turn\n" << endl;
			return false;
		}

		else{

			//If there are no cards left, Aggressive player will first advance troops from adjacent territories to the strongest one
			bool alreadyAdvancing = false;
			for(Territory* neighbor : strongestTerritory->getNeighbors()){

				for(Order* order : player->getOrdersList()->getOrders()){

					if(dynamic_cast<Advance*>(order) != nullptr && dynamic_cast<Advance*>(order)->getSource() == neighbor){
						alreadyAdvancing = true;
					}
				}

				if(neighbor->getPlayer() == player->getPlayerID() && neighbor->getArmy() > 0 && !alreadyAdvancing){

					ordersList->add(new Advance(player->getPlayerID(), "", neighbor->getArmy(), neighbor, strongestTerritory));
					cout << "\nAdvancing " << neighbor->getArmy() << " troops from " << neighbor->getName() << " to " << strongestTerritory->getName();
					cout << "\nEnding turn\n" << endl;
					return false;
				}
			}

			//Once adjacent territories' troops are all 0, the strongest territory will attack a random enemy territory
			Territory* target = map->getTerritory(toAttackTerritories[rand() % player->getSizeOfToAttack()].getName());
			
			ordersList->add(new Advance(player->getPlayerID(), "", strongestTerritory->getArmy(), strongestTerritory, target));
			cout << "\nAdvancing all troops from " << strongestTerritory->getName() << " to " << target->getName();
			cout << "\nEnding turn\n" << endl;
			return true;
		}

		cout << "\nEnding turn\n" << endl;
		return true;
	}
}

//Returns an array of enemy territories adjacent to strongest territory
Territory* AggressivePlayerStrategy::toAttack(Player* player) {

	Territory* strongestTerritory = getStrongestTerritory(player);

	int count = 0;

	for(Territory* territory : strongestTerritory->getNeighbors()){

		if(territory->getPlayer() != player->getPlayerID()){
			count++;
		}
	}

	player->setSizeOfToAttack(count);
	Territory* enemies = new Territory[count];

	int i = 0;

	for(Territory* territory : strongestTerritory->getNeighbors()){

		if(territory->getPlayer() != player->getPlayerID()){
			enemies[i] = *territory;
			i++;
		}
	}

	return enemies;

}
//Just to print out what it currently owns.
Territory* AggressivePlayerStrategy::toDefend(Player* player) {
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

//Returns the territory with the most troops, which is going to attack(borders enemy)
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

			if(territory->getArmy() >= max && isNextToEnemy){

				strongestTerritory = territory;
				max = territory->getArmy();
			}
		}
	}

	return strongestTerritory;
}

//Returns the second territory with most troops. Used exclusively with airlift orders to decide the source territory.
Territory* AggressivePlayerStrategy::getSecondStrongestTerritory(Player* player){

	Map* map = player->getMap();

	if (map == NULL) {
		return 0;
	}

	Territory* strongestTerritory = getStrongestTerritory(player);
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

			if(territory->getArmy() >= max && isNextToEnemy && strongestTerritory != territory){

				strongestTerritory = territory;
				max = territory->getArmy();
			}
		}
	}

	return strongestTerritory;
}

string AggressivePlayerStrategy::getStrategyName() {
	return "Aggressive";
}
