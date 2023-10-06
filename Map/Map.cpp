#include <iostream>
#include <vector>
#include "Map.h"
using namespace std;

//Default constructor (Territory)
Territory::Territory() : name(new string("")), player(new int(0)), army(new int(0)), continent(new string("")) {}

//Constructor
Territory::Territory(const string& territoryName, const string& territoryContinent): 
    name(new string(territoryName)),     
    continent(new string(territoryContinent)),
    player(new int(0)),
    army(new int(2)),
    adjacentTerritories(vector<Territory*>()) 
    {}


//Copy constructor (Territory)
Territory::Territory(const Territory& copyTerritory){
    this->name = copyTerritory.name;
    this->player = copyTerritory.player;
    this->army = copyTerritory.army;
    this->continent = copyTerritory.continent;
}

//Destructor (Territory)
Territory::~Territory() {
    delete this->name;
    name = NULL;

    delete this->player;
    player = NULL;

    delete this->army;
    army = NULL;

    delete this->continent;
    continent = NULL;
}

//stream insertion operator
ostream& operator << (ostream& out, const Territory& territory)
{
	out << "Territory " << territory.getName() << endl;
    out << "Player " << territory.getPlayer() << endl;
    out << "Army " << territory.getArmy() << endl;
    out << "Continent " << territory.getContinent() << endl;
	return out;
}

//assignment operator
Territory& Territory::operator=(const Territory& territory) {
	this->setName(*territory.name);
	this->setPlayer(*territory.player);
	this->setArmy(*territory.army);
    this->setContinent(*territory.continent);

	return *this;
}

void Territory::addNeighbor(Territory* neighbor) {
    adjacentTerritories.push_back(neighbor);
}

bool Territory::isNeighbor(Territory* territory) {
    for (Territory* neighbor : adjacentTerritories) {
        if (neighbor == territory) {
            return true;
        }
    }
    return false;
}


//Getters (Territory)
string Territory::getName() const { return *name; }
int Territory::getPlayer() const { return *player; }
int Territory::getArmy() const { return *army; }
string Territory::getContinent() const { return *continent; }
vector<Territory*> Territory::getNeighbors() const { return adjacentTerritories; }

//Setters (Territory)
void Territory::setName(const string& territoryName) {*name = territoryName;}
void Territory::setPlayer(int territoryPlayer) {*player = territoryPlayer;}
void Territory::setArmy(int territoryArmy) {*army = territoryArmy;}
void Territory::setContinent(const string& territoryContinent) {*continent = territoryContinent;}

//=============================================================================================================================================================================================================//


// Default Constructor (Continent) 
Continent::Continent(): name(new string ("")) {} 

//Constructor (Continent)
Continent::Continent(const string& continentName): name(new string(continentName)){}

//Copy constructor (Continent)
Continent::Continent(const Continent& copyContinent) {
    for (Territory* territory : copyContinent.territories) {
        territories.push_back(new Territory(*territory));
    }
}

//Destructor (Continent)
Continent::~Continent(){
    delete name;
    name = nullptr;
    for (Territory* territory : territories){
        delete territory;
        territory = NULL;               
    }
}

//Add Territory to Continent 
void Continent::addTerritory(Territory* territory){
    territories.push_back(new Territory(*territory));
}

//Getter (Continent)
string Continent::getContinentName() const { return *name; }
const vector<Territory*>& Continent::getTerritories() const {return territories;}


//Setter (Continent)
void Continent::setName(const string& continentName) {
        if (name == nullptr) {
            name = new string(continentName);
        } else {
            *name = continentName;
        }
    }


//=============================================================================================================================================================================================================//


Map::Map() {}

void Map::addContinent(Continent* continent) {
    continents.push_back(continent);
}

void Map::addTerritory(Territory* territory) {
    territories.push_back(territory);
}

vector<Continent*> Map::getContinents() const {
    return continents;
}

vector<Territory*> Map::getTerritories() const {
    return territories;
}

/*

int main(){

    Territory* t1 = new Territory("Canada", "North America");
    Territory* t2 = new Territory("USA", "North America");
    Territory* t3 = new Territory("Mexico", "North America");
    Territory* t4 = new Territory("Brazil", "South America");
    Territory* t5 = new Territory("Argentina", "South America");
    Territory* t6 = new Territory("Peru", "South America");
    Territory* t7 = new Territory("England", "Europe");

    t1->addNeighbor(t2);
    t1->addNeighbor(t3);
    t2->addNeighbor(t1);
    t2->addNeighbor(t3);
    t2->addNeighbor(t4);
    t3->addNeighbor(t1);
    t3->addNeighbor(t2);
    t3->addNeighbor(t4);
    t4->addNeighbor(t2);
    t4->addNeighbor(t3);
    t4->addNeighbor(t5);
    t4->addNeighbor(t6);
    t5->addNeighbor(t4);
    t6->addNeighbor(t4);
    t7->addNeighbor(t6);
    t6->addNeighbor(t7);


    cout<<*t1<<endl;

    for (int i = 0; i < t1->getNeighbors().size(); i++){
        cout<<t1->getNeighbors()[i]->getName()<<endl;
    }

    Continent* c1 = new Continent("North America");
    Continent* c2 = new Continent("South America");
    Continent* c3 = new Continent("Europe");

    cout<<c1->getContinentName()<<endl;

    Map* m1 = new Map();

    m1->addContinent(c1);
    m1->addContinent(c2);
    m1->addContinent(c3);

    cout<<m1->getContinents()[0]->getTerritories().size()<<endl;

    for(int i=0; i<m1->getContinents().size(); i++){
        for(int j=0; j<m1->getContinents()[i]->getTerritories().size(); j++){
            cout<<m1->getContinents()[i]->getTerritories()[j]->getName()<<endl;
        }
        cout<<m1->getContinents()[i]->getContinentName()<<endl;
            
    }



    return 0;
}
*/

