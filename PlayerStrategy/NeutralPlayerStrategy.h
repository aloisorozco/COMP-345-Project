#ifndef NEUTRAL_PLAYER_STRATEGY_H
#define NEUTRAL_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"

class NeutralPlayerStrategy : PlayerStrategy {

public:

	bool issueOrder();

	Territory* toAttack();

	Territory* toDefend();

};

#endif
