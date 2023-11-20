#include "../Map/Map.h"
#include "AggressivePlayerStrategy.h"

#include <string>

bool AggressivePlayerStrategy::issueOrder() {
	return false;
}

Territory* AggressivePlayerStrategy::toAttack() {
	return NULL;
}

Territory* AggressivePlayerStrategy::toDefend() {
	return NULL;
}
