#include "../Map/Map.h"
#include "HumanPlayerStrategy.h"

#include <string>

bool HumanPlayerStrategy::issueOrder() {
	return false;
}

Territory* HumanPlayerStrategy::toAttack() {
	return NULL;
}

Territory* HumanPlayerStrategy::toDefend() {
	return NULL;
}
