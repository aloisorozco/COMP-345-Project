#include "../Map/Map.h"
#include "NeutralPlayerStrategy.h"

#include <string>

bool NeutralPlayerStrategy::issueOrder() {
	return false;
}

Territory* NeutralPlayerStrategy::toAttack() {
	return NULL;
}

Territory* NeutralPlayerStrategy::toDefend() {
	return NULL;
}