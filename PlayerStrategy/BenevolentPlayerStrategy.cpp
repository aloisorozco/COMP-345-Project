#include "../Map/Map.h"
#include "BenevolentPlayerStrategy.h"

#include <chrono>
#include <thread>
#include <string>
//Benevolent player: computer player that focuses on protecting its weak countries (deploys or advances armies
//on its weakest countries, never advances to enemy territories;

bool BenevolentPlayerStrategy::issueOrder(Player* player) {
    Map* map = player->getMap();
    Hand* hand = player->getHand();
    Deck* deck = player->getDeck();
    OrdersList* ordersList = player->getOrdersList();

    //print toDefend & toAttack to show player what he has
    Territory* toDefendTerritories = toDefend(player);
    Territory* toAttackTerritories = toAttack(player);

    Territory* weakestTerritory = getWeakestTerritory(player);


    cout << "\nBenevolent Player " << player->getPlayerID() << "'s issue order\n" << endl;

    //if player has troops to deploy, player is forced to deploy them can't issue another order
    if (*player->getTroopsToDeploy() > 0) {
        cout << "Deploy troops: " << endl;
        cout << "Number of troops left to deploy: " << *player->getTroopsToDeploy() << endl;
        cout << "\nDeploying 1 troop in " << weakestTerritory->getName() << endl;
        //we want to deploy 1 at a time and check again for country with the least amount of troops.
        Deploy* deploy = new Deploy(player->getPlayerID(), "", 1, weakestTerritory);
        ordersList->add(deploy);
        player->setTroopsToDeploy(*player->getTroopsToDeploy() - 1);

        this_thread::sleep_for(chrono::milliseconds(1000));
        return false;
    }
    else if(hand->getHandSize() > 0){
        // may use cards but will never use a card in a way that purposefully will harm anyone.
            //we want strongest after deployment.
            Territory* strongestTerritory = getStrongestTerritory(player);
            Card* card = hand->getCards().back();
            if(card->getType() == Card::ReinforcementCT){
                //check if loops back to
                player->setTroopsToDeploy(*player->getTroopsToDeploy() + 5);
                cout << "\nAdding 5 troops to deploy";
            }
            else if(card->getType() == Card::BombCT){
                //do nothing
            }
            else if(card->getType() == Card::AirliftCT){
                int troops = (strongestTerritory->getArmy() - weakestTerritory->getArmy())/2;
                ordersList->add(new Airlift(player->getPlayerID(), "", troops, strongestTerritory, weakestTerritory));
                cout << "\nAirlifting " << troops << " troops from " << strongestTerritory->getName() << " to " << weakestTerritory->getName();

            }
            else if (card->getType() == Card::BlockadeCT){
                int troops = (strongestTerritory->getArmy() - weakestTerritory->getArmy())/2;
                ordersList->add(new Blockade(player->getPlayerID(),"" ,strongestTerritory));
                cout << "\nBlockading " << strongestTerritory->getName();
            }
            else if (card->getType() == Card::DiplomacyCT){
                //prioritize negotiate with player nearest to weakest country.
                bool played = false;
                for(Territory* neighbor : weakestTerritory->getNeighbors()){
                    if (neighbor->getPlayer() != weakestTerritory->getPlayer()){
                        //Player* neighbor_player = neighbor->getPlayer();
                        ordersList->add(new Negotiate(player->getPlayerID(),"", neighbor->getPlayer()));
                        played = true;
                    }
                }
                //check for any neighbor to play card on.
                for (int i = 0; i < player->getSizeOfToDefend(); ++i) {
                    for(Territory* neighbor : toDefendTerritories[i].getNeighbors()){
                        ordersList->add(new Negotiate(player->getPlayerID(),"", neighbor->getPlayer()));
                    }
                }
            }
            else{
                cout << "\nNot issuing orders";
            }
            deck->returnCard(card);
            hand->removeCard(card);

            cout << "\nEnding turn\n" << endl;
            return false;
        }
    else{
        // ADVANCE move units from stronger weaker neighbor, no attacking
        bool alreadyAdvancing = false;
        Territory* strongestTerritory = getStrongestTerritory(player);
        for(Territory* neighbor : strongestTerritory->getNeighbors()){

            for(Order* order : player->getOrdersList()->getOrders()){
                if(dynamic_cast<Advance*>(order) != nullptr && dynamic_cast<Advance*>(order)->getSource() == strongestTerritory){
                    alreadyAdvancing = true;
                }
            }

            if(neighbor->getPlayer() == player->getPlayerID() && (strongestTerritory->getArmy()-neighbor->getArmy())/2 >= 1 && !alreadyAdvancing){
                ordersList->add(new Advance(player->getPlayerID(), "", (strongestTerritory->getArmy()-neighbor->getArmy())/2,strongestTerritory, neighbor));
                cout << "\nAdvancing " << (strongestTerritory->getArmy()-neighbor->getArmy())/2 << " troops from " << neighbor->getName() << " to " << strongestTerritory->getName();
                cout << "\nEnding turn\n" << endl;
                return false;
            }
        }
        cout << "\nEnding turn\n" << endl;
        return true;
    }
}

//returns NULL because the benevolent player does not attack
Territory* BenevolentPlayerStrategy::toAttack(Player* player) {
    return NULL;
}

//returns all territories,
Territory* BenevolentPlayerStrategy::toDefend(Player* player) {
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

Territory* BenevolentPlayerStrategy::getWeakestTerritory(Player* player){

    Map* map = player->getMap();
    if (map == NULL) {
        return 0;
    }
    int min =0;
    Territory* weakestTerritory = nullptr;
    //loop through all territories on the map
    int counter=0;
    for (Territory* territory : map->getTerritories()) {
        //set first as minimum, then compare
        if(counter ==0){
            min = territory->getArmy();
            counter++;
        }
        //if the current territory belongs to this player
        if (territory->getPlayer() == player->getPlayerID()) {
            bool isNextToEnemy = false;
            for(Territory* neighbor : territory->getNeighbors()){
                if(neighbor->getPlayer() != player->getPlayerID()){
                    isNextToEnemy = true;
                }
            }
            if(territory->getArmy() <= min && isNextToEnemy){
                weakestTerritory = territory;
                min = territory->getArmy();
            }
        }
    }

    return weakestTerritory;
}
Territory* BenevolentPlayerStrategy::getStrongestTerritory(Player* player){
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
string BenevolentPlayerStrategy::getStrategyName() {
	return "Benevolent";
}