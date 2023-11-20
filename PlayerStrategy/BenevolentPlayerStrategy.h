#ifndef BENEVOLENT_PLAYER_STRATEGY_H
#define BENEVOLENT_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"

class BenevolentPlayerStrategy : PlayerStrategy {

public:

	bool issueOrder();

	Territory* toAttack();

	Territory* toDefend();

};

#endif