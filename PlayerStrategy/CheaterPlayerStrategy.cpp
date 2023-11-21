#include "../Map/Map.h"
#include "CheaterPlayerStrategy.h"

#include <string>

bool CheaterPlayerStrategy::issueOrder(Player* player) {
	return false;
}

Territory* CheaterPlayerStrategy::toAttack(Player* player) {
	return NULL;
}

Territory* CheaterPlayerStrategy::toDefend(Player* player) {
	return NULL;
}
