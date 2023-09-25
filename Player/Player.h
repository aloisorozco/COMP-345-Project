#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	Player();

	list<Territory> toDefend();

	list<Territory> toAttack();

	void issueOrder(Order order);
};

#endif