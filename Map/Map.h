#ifndef MAP_H
#define MAP_H
#include <iostream>
using namespace std;

class Territory {

public:
	Territory();

};

struct node {
	int player; //0 neutral, 1 player 1, 2 player 2
	int army; //number of troops

	string name; //name of node
	string country; //name of country	
	int territory; //territory number for mulitplier
	int multiplier; //mulitplier for territory occupied
	string continent; //continent territory is on

	int *const attack; //use pointer to attack countries, pointer can't change it can edit the int
	const node *next; //pointer for adjecent nodes
	
};

struct mapEdges{
	int startVertice;
	int endVertice;
};

class Map{
//Create Graph from nodes
};






#endif