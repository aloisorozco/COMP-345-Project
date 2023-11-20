#ifndef CHEATER_PLAYER_STRATEGY_H
#define CHEATER_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"

class CheaterPlayerStrategy : PlayerStrategy {

public:

	bool issueOrder();

	Territory* toAttack();

	Territory* toDefend();

};

#endif

