#ifndef HUMAN_PLAYER_STRATEGY_H
#define HUMAN_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"

class HumanPlayerStrategy : PlayerStrategy {

public:

	bool issueOrder();

	Territory* toAttack();

	Territory* toDefend();

};

#endif
