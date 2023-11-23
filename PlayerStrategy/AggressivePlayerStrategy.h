#ifndef AGGRESSIVE_PLAYER_STRATEGY_H
#define AGGRESSIVE_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"
#include "../Player/Player.h"

class AggressivePlayerStrategy : public PlayerStrategy {

public:

	bool issueOrder(Player* player);

	Territory* toAttack(Player* player);

	Territory* toDefend(Player* player);

	~AggressivePlayerStrategy() {

	}

};

#endif
