#include "../Map/Map.h"
#include "BenevolentPlayerStrategy.h"

#include <string>

bool BenevolentPlayerStrategy::issueOrder(Player* player) {
	return false;
}

Territory* BenevolentPlayerStrategy::toAttack(Player* player) {
	return NULL;
}

Territory* BenevolentPlayerStrategy::toDefend(Player* player) {
	return NULL;
}