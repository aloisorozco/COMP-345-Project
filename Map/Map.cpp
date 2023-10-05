#include <iostream>
#include <vector>
#include "Map.h"
using namespace std;

//Default constructor (Territory)
Territory::Territory() : name(new string("")), player(new int(0)), army(new int(0)), continent(new string("")) {}

//Constructor
Territory::Territory(const string& territoryName, int territoryPlayer, int territoryArmy, const string& territoryContinent): 
    name(new string(territoryName)), 
    player(new int(territoryPlayer)), 
    army(new int(territoryArmy)), 
    continent(new string(territoryContinent)) {}


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


//Getters (Territory)
string Territory::getName() const { return *name; }
int Territory::getPlayer() const { return *player; }
int Territory::getArmy() const { return *army; }
string Territory::getContinent() const { return *continent; }

//Setters (Territory)
void Territory::setName(const string& territoryName) {*name = territoryName;}
void Territory::setPlayer(int territoryPlayer) {*player = territoryPlayer;}
void Territory::setArmy(int territoryArmy) {*army = territoryArmy;}
void Territory::setContinent(const string& territoryContinent) {*continent = territoryContinent;}

//=============================================================================================================================================================================================================//


//Default constructor (Edge)
Edge::Edge() {
    source= nullptr;
    destination= nullptr;
}

//Constructor (Edge)
Edge::Edge(Territory* u, Territory* v) : source(u), destination(v) {}

//Copy constructor (Edge)
Edge::Edge(const Edge& copyEdge){
    this->source = copyEdge.source;
    this->destination = copyEdge.destination;
} 

//Destructor (Edge)
Edge::~Edge(){
    delete this-> source;
    source = NULL;

    delete this->destination;
    destination= NULL;
}

//stream insertion operator
ostream& operator << (ostream& out, const Edge& edge){
    out << "Edge  " << edge.getSource()->getName() << " -> " << edge.getDestination()->getName() << endl;
    return out;
}


//assignment operator
Edge& Edge::operator=(const Edge& edge) {
	this->setSource(edge.source);
    this->setDestination(edge.destination);
	return *this;
}


//Getters (Edge)
Territory* Edge::getSource() const { return source; }
Territory* Edge::getDestination() const { return destination; }

//Setters (Edge)
void Edge::setSource(Territory* u){*source = *u;}
void Edge::setDestination(Territory* v){*destination = *v;}

//=============================================================================================================================================================================================================//


// Default Constructor (Continent) 
Continent::Continent(): name(nullptr) {} 

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

//Getter (Continent)
string Continent::getContinentName() const { return (name != nullptr) ? *name : ""; }
const vector<Territory*>& Continent::getTerritories() const {return territories;}


//Setter (Continent)
void Continent::setName(const string& continentName) {
        if (name == nullptr) {
            name = new string(continentName);
        } else {
            *name = continentName;
        }
    }
//Add Territory to Continent 
void Continent::addTerritory(Territory* territory){
    territories.push_back(new Territory(*territory));
}

//=============================================================================================================================================================================================================//


//Default constructor (Map)
Map::Map() {}

//Constructor (Map)
Map::Map(const vector<Continent*>& inputContinents, const vector<Edge*>& inputEdges)
    : continents(inputContinents), edges(inputEdges) {}

//Copy constructor (Map)
Map::Map(const Map& copyMap) {
        for (Continent* continent : copyMap.continents) {
            continents.push_back(new Continent(*continent));
        }
        for (Edge* edge : copyMap.edges) {
            edges.push_back(new Edge(edge->getSource(), edge->getDestination()));
        }
    }
//Destructor (Map)
Map::~Map(){
    for (Continent* continent : continents){
        delete continent;
        continent = NULL;
    }
    for (Edge* edge : edges){
        delete edge;
        edge = NULL;
    }
}

//Getters (Map)
const vector<Continent*>& Map::getContinents() const { return continents; }
const vector<Edge*>& Map::getEdges() const { return edges; }

//Add Continent to Map
void Map::addContinent(Continent* continent){
    continents.push_back(new Continent(*continent));
}

// Add Edge to Map
void Map::addEdge(Territory* source, Territory* destination){
    Edge* edge = new Edge(source, destination);
    edges.push_back(edge);
}

//Print Map
void Map::printMap(){
    for (Continent* continent : continents){
        cout << "\nContinent: " << endl; //doesnt work??
        for (Territory* territory : continent->getTerritories()){
            cout << "Territory Name: "<< territory->getName() 
                << " - Player " << territory->getPlayer() 
                <<" - Army: "<<territory->getArmy()<< endl;
        }
    }
    for (Edge* edge : edges){
        cout << "\nEdge: " << endl;
        cout << edge->getSource()->getName() << " -> " << edge->getDestination()->getName() << endl;
    }
}

void Map::DFS(const Map& map, Territory* start, unordered_set<Territory*>& visited) {
    visited.insert(start);

    // Iterate through neighboring territories
    for (Edge* edge : map.getEdges()) {
        if (edge->getSource() == start && visited.find(edge->getDestination()) == visited.end()) {
            DFS(map, edge->getDestination(), visited);
            cout<<"condition 1"<<endl; //this is not printing "condition 1
            cout<<edge->getDestination()->getName()<<endl;
        }
        else if (edge->getSource() == start && visited.find(edge->getDestination()) == visited.end()) {
            DFS(map, edge->getSource(), visited);
            cout<<"condition 2"<<endl;
            cout<<edge->getSource()->getName()<<endl;
        }
    }
}

// Function to check if the map is a connected graph
bool Map::validate(const Map& map) {
    // Get a starting territory (you can choose any)
    if (map.getContinents().empty() || map.getContinents()[0]->getTerritories().empty()) {
        // If there are no territories, it's still considered connected
        cout<<"condition 3"<<endl;
        return true;
    }
    
    Territory* startTerritory = map.getContinents()[0]->getTerritories()[0];

    // Create a set to keep track of visited territories
    unordered_set<Territory*> visited;

    // Perform DFS starting from the chosen territory
    DFS(map, startTerritory, visited);

    // Check if all territories have been visited
    
    cout<<"\n visited " <<visited.size()<<endl;
    cout<<"\n map " <<map.getContinents()[0]->getTerritories().size()<<endl;

    return visited.size() == map.getContinents()[0]->getTerritories().size();
}



int main(){

    Map map;
   
    // Create Territories
    Territory* t1= new Territory ("t1", 1, 2, "c1");
    Territory* t2= new Territory ("t2", 1, 2, "c1");
    Territory* t3= new Territory ("t3", 2, 2, "c1");
    Territory* t4= new Territory ("t4", 1, 2, "c2");
    Territory* t5= new Territory ("t5", 2, 2, "c2");
    Territory* t6= new Territory ("t6", 1, 2, "c2");
    Territory* t7= new Territory ("t7", 2, 2, "c3");
    Territory* t8= new Territory ("t8", 7, 7, "c3");

    //Create Continents
    Continent* c1= new Continent("C1");
    
    Continent* c2= new Continent("C2");
    
    Continent* c3= new Continent("C3");

    *t1=*t8;
    cout<<t1->getName()<< t1->getArmy()<<t1->getPlayer() <<endl;  
    

    c1->addTerritory(t1);
    c1->addTerritory(t2);
    c1->addTerritory(t3);
    c2->addTerritory(t4);
    c2->addTerritory(t5);
    c2->addTerritory(t6);
    c3->addTerritory(t7);


    //Add Continents to Map
    map.addContinent(c1);
    map.addContinent(c2);
    map.addContinent(c3);

    //add Edges to Map
    map.addEdge(t1, t2);
    map.addEdge(t1, t3);
    map.addEdge(t2, t3);
    map.addEdge(t1, t4);
    map.addEdge(t4, t5);
    map.addEdge(t4, t6);
    map.addEdge(t5, t6);
    map.addEdge(t7, t6);

    Edge* e1= new Edge(t1, t2);

    cout<<*e1<<endl;   

    
    //Print Map
    map.printMap();  

    cout<<*t1<<endl;

    
for (int i=0; i<4; i++){
        cout<< c1->getTerritories()[i]->getName()<<endl;

    };


return 0;
};