#include "../Map/Map.h"
#include "NeutralPlayerStrategy.h"

#include <string>

bool NeutralPlayerStrategy::issueOrder(Player* player) {
	return false;
}

Territory* NeutralPlayerStrategy::toAttack(Player* player) {
	return NULL;
}

Territory* NeutralPlayerStrategy::toDefend(Player* player) {
	return NULL;
}