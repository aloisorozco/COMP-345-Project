#ifndef HUMAN_PLAYER_STRATEGY_H
#define HUMAN_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "../Player/Player.h"
#include "PlayerStrategy.h"

class HumanPlayerStrategy : public PlayerStrategy {

public:

	inline HumanPlayerStrategy() {

	}

	bool issueOrder(Player* player);

	Territory* toAttack(Player* player);

	Territory* toDefend(Player* player);

	~HumanPlayerStrategy() {

	}

};

#endif
