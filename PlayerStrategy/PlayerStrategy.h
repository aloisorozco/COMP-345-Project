#ifndef PLAYER_STRATEGY_H
#define PLAYER_STRATEGY_H

#include "../Map/Map.h"

class Player;

class PlayerStrategy {

public:

	inline PlayerStrategy() {

	}

	virtual bool issueOrder(Player* player) = 0;

	virtual Territory* toAttack(Player* player) = 0;

	virtual Territory* toDefend(Player* player) = 0;

	virtual ~PlayerStrategy() {

	}

};
// free function declaration
int testPlayerStrategies();
#endif
