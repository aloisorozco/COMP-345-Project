#ifndef ORDERS_H
#define ORDERS_H

class OrderList {

public:
	OrderList();

	addOrder(Order* order);

};

class Order {

public:
	Order();

};

class Deploy : public Order {

public:
	Deploy();

};

class Advance : public Order {

public:
	Advance();

};

class Bomb : public Order {

public:
	Bomb();

};

class Blockade : public Order {

public:
	Blockade();

};

class Airlift : public Order {

public:
	Airlift();

};

class Negotiate : public Order {

public:
	Negotiate();

};

#endif