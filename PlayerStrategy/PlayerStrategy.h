#ifndef PLAYER_STRATEGY_H
#define PLAYER_STRATEGY_H

#include "../Map/Map.h"

class PlayerStrategy {

public:

	virtual bool issueOrder() = 0;

	virtual Territory* toAttack() = 0;

	virtual Territory* toDefend() = 0;

};

#endif
