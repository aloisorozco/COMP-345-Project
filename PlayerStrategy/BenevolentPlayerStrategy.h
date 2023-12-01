#ifndef BENEVOLENT_PLAYER_STRATEGY_H
#define BENEVOLENT_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"
#include "../Player/Player.h"

class BenevolentPlayerStrategy : public PlayerStrategy{

public:

	bool issueOrder(Player* player);

	Territory* toAttack(Player* player);

	Territory* toDefend(Player* player);

	~BenevolentPlayerStrategy() {

	}

	string getStrategyName();

    Territory* getWeakestTerritory(Player* player);
    Territory* getStrongestTerritory(Player* player);
};

#endif