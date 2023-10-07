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
	Territory();

	Territory(const string& territoryName, const string& territoryContinent);

	Territory(const Territory& copyTerritory); 
	
	Territory& operator=(const Territory& territory);

	void addNeighbor(Territory* neighbor);
	bool isNeighbor(Territory* territory);

		
	string getName() const ;
	int getPlayer() const ;
	int getArmy() const ;
	string getContinent() const;
	vector<Territory*> getNeighbors() const;
	
	void setName(const string& name);
	void setPlayer(int player);
	void setArmy(int army);
	void setContinent(const string& continent);	

	~Territory(); 
};


class Continent {
private:
	string* name;
	vector<Territory*> territories;

	

public:
	Continent(); 
	Continent(const string& continentName); 
	Continent(const Continent& copyContinent); 
	~Continent();

	Continent& operator=(const Continent& continent);
	friend ostream& operator<<(std::ostream& os, const Continent& c);	

	void addTerritory(Territory* territory); 

	string getContinentName() const; 
	const vector<Territory*>& getTerritories() const; 

	void setName(const string& continentName);
	void setTerritories(const vector<Territory*>& continentTerritories);	
};


class Map {
	private:
    vector<Continent*> continents;
public:
    Map();
    Map(const Map& m); // Copy constructor
    Map& operator=(const Map& m); // Assignment operator
    friend std::ostream& operator<<(std::ostream& os, const Map& m); // Stream insertion operator

    
    

    void addContinent(Continent* c);

    bool areTerritoriesInOneContinent();

	bool validate() ;
	bool isMapConnected();
	bool isContinentConnected();
	bool checkTerritoriesInContinents();

	vector<Continent*> getContinents() const;

	void setContinents(const vector<Continent*>& continents);
};

void testLoadMaps();



#endif