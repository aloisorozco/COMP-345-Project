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
	vector<Territory*> adjacentTerritories;
	friend ostream& operator << (ostream& out, const Territory& territory);

public:	
	Territory();//Inititalize default constructor

	Territory(const string& territoryName, const string& territoryContinent); //initialize constructor

	Territory(const Territory& copyTerritory); //initialize copy constructor
	
	Territory& operator=(const Territory& territory);
	void addNeighbor(Territory* neighbor);
	bool isNeighbor(Territory* territory);

	//Getter and Setter	
	string getName() const ;
	int getPlayer() const ;
	int getArmy() const ;
	string getContinent() const;
	vector<Territory*> getNeighbors() const;
	
	void setName(const string& name);
	void setPlayer(int player);
	void setArmy(int army);
	void setContinent(const string& continent);	

	~Territory(); //initialize destructor
};


// class Edge {
// private:
// 	Territory* source;
// 	Territory* destination;

// public:
// 	Edge(); //initialize default constructor
// 	Edge(Territory* u, Territory* v); //initialize constructor
// 	Edge(const Edge& copyEdge); //initialize copy constructor

// 	Territory* getSource() const; //get start territory
// 	Territory* getDestination() const ; //get end territory

// 	void setSource(Territory* u); //set start territory
// 	void setDestination(Territory* v); //set end territory

// 	Edge& operator=(const Edge& edge);

// 	~Edge(); //initialize destructor
// };


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

	friend std::ostream& operator<<(std::ostream& os, const Continent& c); // Stream insertion operator


	~Continent(); //initialize destructor
};


class Map {
	private:
    vector<Territory*> territories;
    vector<Continent*> continents;
public:
    Map();
    Map(const Map& m); // Copy constructor
    Map& operator=(const Map& m); // Assignment operator
    friend std::ostream& operator<<(std::ostream& os, const Map& m); // Stream insertion operator

    vector<Territory*> getTerritories() const;
    vector<Continent*> getContinents() const;

    void addTerritory(Territory* t);
    void addContinent(Continent* c);

    bool isConnected() const;
    bool areContinentsConnected() const;
    bool areTerritoriesInOneContinent() const;


};





#endif