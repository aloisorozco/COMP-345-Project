#ifndef CHEATER_PLAYER_STRATEGY_H
#define CHEATER_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"
#include "../Player/Player.h"

class CheaterPlayerStrategy : public PlayerStrategy {

public:

	bool issueOrder(Player* player);

	Territory* toAttack(Player* player);

	Territory* toDefend(Player* player);

	~CheaterPlayerStrategy() {

	}

	string getStrategyName(); 
};

#endif

