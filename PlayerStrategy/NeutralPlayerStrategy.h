#ifndef NEUTRAL_PLAYER_STRATEGY_H
#define NEUTRAL_PLAYER_STRATEGY_H

#include "../Map/Map.h"
#include "PlayerStrategy.h"
#include "../Player/Player.h"

class NeutralPlayerStrategy : public PlayerStrategy {

public:

	bool issueOrder(Player* player);

	Territory* toAttack(Player* player);

	Territory* toDefend(Player* player);

	~NeutralPlayerStrategy() {

	}

};

#endif
