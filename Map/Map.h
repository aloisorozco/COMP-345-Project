#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;


class Territory {
private:
	string* name;
	int* player;
	int* army;
	string* continent;

public:	
	Territory();//Inititalize default constructor

	Territory(const string& territoryName, int territoryPlayer, int territoryArmy, const string& territoryContinent); //initialize constructor

	Territory(const Territory& copyTerritory); //initialize copy constructor

	Territory& operator=(const Territory& territory);

	//Getter and Setter	
	string getName() const ;
	int getPlayer() const ;
	int getArmy() const ;
	string getContinent() const;
	
	void setName(const string& name);
	void setPlayer(int player);
	void setArmy(int army);
	void setContinent(const string& continent);	

	~Territory(); //initialize destructor
};


class Edge {
private:
	Territory* source;
	Territory* destination;

public:
	Edge(); //initialize default constructor
	Edge(Territory* u, Territory* v); //initialize constructor
	Edge(const Edge& copyEdge); //initialize copy constructor

	Territory* getSource() const; //get start territory
	Territory* getDestination() const ; //get end territory

	void setSource(Territory* u); //set start territory
	void setDestination(Territory* v); //set end territory

	Edge& operator=(const Edge& edge);

	~Edge(); //initialize destructor
};


class Continent {
private:
	string* name;
	vector<Territory*> territories;

public:
	Continent(); //initialize default constructor
	Continent(const string& continentName); //initialize constructor
	Continent(const Continent& copyContinent); //initialize copy constructor

	string getContinentName() const; //get continent name
	const vector<Territory*>& getTerritories() const; //get territories

	void setName(const string& continentName); //set continent name

	void addTerritory(Territory* territory); //add territory to continent
	void printContinent(); //print continent

	bool validateContinent();//TODO: validate continent

	~Continent(); //initialize destructor
};


class Map {
private:
	vector<Continent*> continents;
	vector<Edge*> edges;

public:
	Map(); //initialize default constructor
	Map(const vector<Continent*>& inputContinents, const vector<Edge*>& inputEdges); //initialize constructor
	Map(const Map& copyMap); //initialize copy constructor

	const vector<Continent*>& getContinents() const; //get continents
	const vector<Edge*>& getEdges() const; //get edges

	void addContinent(Continent* continent); //add continent to map
	void addEdge(Territory* start, Territory* end); //add edge to map

	bool validateMap(); //TODO: validate map

	void printMap(); //print map

	void DFS(const Map& map, Territory* start, unordered_set<Territory*>& visited);
	bool validate (const Map& map);

	~Map(); //initialize destructor
};





#endif