#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <cstdlib>
#include "Map.h"
using namespace std;

//Default constructor (Territory)
Territory::Territory() : name(new string("")), player(new int(0)), army(new int(0)), continent(new string("")) {}

//Constructor
Territory::Territory(const string& territoryName, const string& territoryContinent): 
    name(new string(territoryName)),     
    continent(new string(territoryContinent)),
    player(new int(0)),
    army(new int(2))
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
    for (Territory* neighbor : territory.getNeighbors()) {
        out << "Neighbor: " << neighbor->getName() << endl;
    }
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

void Territory::addTroops(int troops) {*army = *army + troops;}
void Territory::removeTroops(int troops) {if(troops >= *army){*army = *army - troops;}}

void Territory::transferTroops(Territory* territory, int troops){

    if(this->getPlayer() == territory->getPlayer()){
        if(*this->army >= troops){
            this->removeTroops(troops);
            territory->addTroops(troops);
        }

        else{
            territory->addTroops(*this->army);
            this->setArmy(0);
        }
    }

    else{

        int chance;
        int remaining = *this->army >= troops ? troops : *this->army;

        this->removeTroops(remaining);

        while(remaining > 0 && territory->army > 0){
            chance = rand() % 100;
            if(chance >= 40){
                territory->removeTroops(1);
            }

            chance = rand() % 100;
            if(chance >= 30){
                remaining--;
            }
        }

        if(territory->army <= 0){
            territory->setPlayer(this->getPlayer());
            territory->setArmy(remaining);
        }
    }
    
}

//=============================================================================================================================================================================================================//


// Default Constructor (Continent) 
Continent::Continent(): name(new string ("")) {} 

//Constructor (Continent)
Continent::Continent(const string& continentName): name(new string(continentName)){}

//Copy constructor (Continent)
Continent::Continent(const Continent& copyContinent) {
    for (Territory* territory : copyContinent.territories) {
        territories.push_back(territory);
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
    territories.push_back(territory);
}

//stream insertion operator
ostream& operator << (std::ostream& os, const Continent& c)
{
	os << "Continent " << c.getContinentName() << endl;     
	return os;
}

//assignment operator
Continent& Continent::operator=(const Continent& continent) {
	this->setName(*continent.name);
	this->setTerritories(continent.territories);
	return *this;
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

void Continent::setTerritories(const vector<Territory*>& continentTerritories) {
    for (Territory* territory : continentTerritories) {
        territories.push_back(territory);
    }
}




//=============================================================================================================================================================================================================//


Map::Map() {}

void Map::addContinent(Continent* continent) {
    continents.push_back(continent);
}

vector<Continent*> Map::getContinents() const {
    return continents;
}

void Map::setContinents(const vector<Continent*>& continents) {
    this->continents = continents;
}

ostream& operator<<(std::ostream& os, const Map& m){

   
    
    // Iterate through continents and territories and print their details.
    for (const Continent* continent : m.continents) {
        
        os << "Continent: " << continent->getContinentName() <<"\n"<< std::endl;
        for (const Territory* territory : continent->getTerritories()) {
            os <<*territory<<endl;
        }
        os<<"===============================================\n\n";
    }
    
    return os;
}

Map& Map::operator=(const Map& m){
    this->setContinents(m.getContinents());
    return *this;
}

bool Map::isMapConnected() {
    //initalize visited list and stack of territories from map
    set<const Territory*> visited;    
    const Territory* startingTerritory = this->getContinents()[0]->getTerritories()[0]; // Start from the first territory.
    std::stack<const Territory*> stack;
    stack.push(startingTerritory);
    

    while (!stack.empty()) {
        const Territory* currentTerritory = stack.top();
        stack.pop();
        
        // Mark the current territory as visited.
        visited.insert(currentTerritory);
        
        // Get the neighbors of the current territory.
        for (Territory* neighbor : currentTerritory->getNeighbors()) {
            if (visited.find(neighbor) == visited.end()) {
                stack.push(neighbor);
            }        
        }
    }

    // Check if all territories were visited.
    for (const Continent* continent : continents) {
        for (const Territory* territory : continent->getTerritories()) {
            if (visited.find(territory) == visited.end()) {
                
                // If any territory was not visited, the map is not valid.
                return false;
            }
        }
    }
    return true;
}

bool Map::isContinentConnected() {
    //initalize visited list and stack of territories from continent
    set<const Territory*> visited;    
    const Territory* startingTerritory = continents[0]->getTerritories()[0]; // Start from the first territory.
    std::stack<const Territory*> stack;
    stack.push(startingTerritory);
    
    while (!stack.empty()) {        
        const Territory* currentTerritory = stack.top();       
        stack.pop();
        // Mark the current territory as visited.
        visited.insert(currentTerritory);
        
        
        // Get the neighbors of the current territory.
        for (Territory* neighbor : currentTerritory->getNeighbors()) {
            if (visited.find(neighbor) == visited.end()) {
                stack.push(neighbor);
            }        
        }
    }

    // Check if all territories were visited.
    for (const Continent* continent : continents) {
        for (const Territory* territory : continent->getTerritories()) {
            if (visited.find(territory) == visited.end()) {
                
                // If any territory was not visited, the map is not valid.
                return false;
            }
        }
    }
    return true;
}

bool Map::checkTerritoriesInContinents() {
    std::set<const Territory*> territoriesSet; // To keep track of visited territories.

    for (const Continent* continent : continents) {
        for (const Territory* territory : continent->getTerritories()) {
            if (territoriesSet.find(territory) != territoriesSet.end()) {
                // If the territory is already in the set, it is assigned to multiple continents.
                return false;
            }
            territoriesSet.insert(territory);
        }
    }

    // If all territories are assigned to continents only once, return true.
    return true;
}

bool Map::validate() {
    if (this->getContinents().empty()) {
        cout<<"No continents"<<endl;
        // If there are no continents, the map is not valid.
        return false;
    }

    if (!isMapConnected() || !isContinentConnected()) {
        cout<<"Map is not connected"<<endl;
        // If the map is not connected, it is not valid.
        return false;
    }
    if (!checkTerritoriesInContinents()) {
        cout<<"Territories are not in continents"<<endl;
        // If a territory is assigned to multiple continents, the map is not valid.
        return false;
    }

    return true;
}




/* Test for map functionality
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

   

    

    

    Continent* c1 = new Continent("North America");
    Continent* c2 = new Continent("South America");
    Continent* c3 = new Continent("Europe");

    
    c1->addTerritory(t1);
    c1->addTerritory(t2);
    c1->addTerritory(t3);
    c2->addTerritory(t4);
    c2->addTerritory(t5);
    c2->addTerritory(t6);
    c3->addTerritory(t7);

   
    

    Map* m1 = new Map();

    m1->addContinent(c1);
    m1->addContinent(c2);
    m1->addContinent(c3);

   
    // cout<<m1->getContinents().size()<<endl;

    cout<<"Map is "<<m1->validate()<<endl;
    
    cout<<*m1<<endl;
    
    



    return 0;
};

*/
