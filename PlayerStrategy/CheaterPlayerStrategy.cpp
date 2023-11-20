#include "../Map/Map.h"
#include "CheaterPlayerStrategy.h"

#include <string>

bool CheaterPlayerStrategy::issueOrder() {
	return false;
}

Territory* CheaterPlayerStrategy::toAttack() {
	return NULL;
}

Territory* CheaterPlayerStrategy::toDefend() {
	return NULL;
}
