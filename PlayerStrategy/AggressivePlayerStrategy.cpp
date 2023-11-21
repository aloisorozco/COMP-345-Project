#include "../Map/Map.h"
#include "AggressivePlayerStrategy.h"

#include <string>

bool AggressivePlayerStrategy::issueOrder(Player* player) {
	return false;
}

Territory* AggressivePlayerStrategy::toAttack(Player* player) {
	return NULL;
}

Territory* AggressivePlayerStrategy::toDefend(Player* player) {
	return NULL;
}
