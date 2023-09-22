#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	list<Territory> toDefend();

	list<Territory> toAttack();

	void issueOrder(Order order);
};

#endif