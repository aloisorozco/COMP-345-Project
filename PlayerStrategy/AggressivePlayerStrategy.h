#ifndef AGGRESSIVE_PLAYER_STRATEGY_H
#define AGGRESSIVE_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"

class AggressivePlayerStrategy : PlayerStrategy {

public:

	bool issueOrder();

	Territory* toAttack();

	Territory* toDefend();

};

#endif
