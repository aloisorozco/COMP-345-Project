#include "../Map/Map.h"
#include "BenevolentPlayerStrategy.h"

#include <string>

bool BenevolentPlayerStrategy::issueOrder() {
	return false;
}

Territory* BenevolentPlayerStrategy::toAttack() {
	return NULL;
}

Territory* BenevolentPlayerStrategy::toDefend() {
	return NULL;
}