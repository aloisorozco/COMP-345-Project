#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <random>
#include "Map.h"
using namespace std;
namespace fs = std::filesystem;

// Default constructor (Territory)
Territory::Territory() : name(new string("")), player(new int(0)), army(new int(0)), continent(new string("")) {}

// Constructor
Territory::Territory(const string &territoryName, const string &territoryContinent) : name(new string(territoryName)),
                                                                                      continent(new string(territoryContinent)),
                                                                                      player(new int(0)),
                                                                                      army(new int(0))
{}

// Copy constructor (Territory)
Territory::Territory(const Territory &copyTerritory)
{
    this->name = new string(*copyTerritory.name);
    this->player = new int(*copyTerritory.player);
    this->army = new int(*copyTerritory.army);
    this->continent = new string(*copyTerritory.continent);
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

        while(remaining > 0 && *territory->army > 0){
            chance = rand() % 100;
            if(chance >= 40){
                territory->removeTroops(1);
            }

            chance = rand() % 100;
            if(chance >= 30){
                remaining--;
            }
        }

        if(*territory->army <= 0){
            territory->setPlayer(this->getPlayer());
            territory->setArmy(remaining);
        }
    }
    
}

//=============================================================================================================================================================================================================//


// Default Constructor (Continent)
Continent::Continent() : name(new string("")), bonus(new int(0)) {}

// Constructor (Continent)
Continent::Continent(const string &continentName) : name(new string(continentName)) {}

Continent::Continent(const string &continentName, int b) : name(new string(continentName)), bonus(new int(b)) {}

// Copy constructor (Continent)
Continent::Continent(const Continent &copyContinent)
{
    for (Territory *territory : copyContinent.territories)
    {
        territories.push_back(territory);
    }
    this->bonus = new int(*copyContinent.bonus);
}

// Destructor (Continent)
Continent::~Continent()
{
    delete name;
    name = nullptr;
    for (Territory *territory : territories)
    {
        delete territory;
        territory = NULL;
    }

    delete bonus;
    bonus = NULL;
}

// Add Territory to Continent
void Continent::addTerritory(Territory *territory)
{
    territories.push_back(territory);
}

// stream insertion operator
ostream &operator<<(std::ostream &os, const Continent &c)
{
    os << "Continent " << c.getContinentName() << endl;
    return os;
}

// assignment operator
Continent &Continent::operator=(const Continent &continent)
{
    this->setName(*continent.name);
    this->setTerritories(continent.territories);
    this->setBonus(*continent.bonus);
    return *this;
}

// Getter (Continent)
string Continent::getContinentName() const { return *name; }
int Continent::getBonus() const { return *bonus; }
const vector<Territory *> &Continent::getTerritories() const { return territories; }

// Setter (Continent)
void Continent::setName(const string &continentName)
{
    if (name == nullptr)
    {
        name = new string(continentName);
    }
    else
    {
        *name = continentName;
    }
}



void Continent::setBonus(int bonus){
    
	*this->bonus = bonus;

}

void Continent::setTerritories(const vector<Territory *> &continentTerritories)
{
    for (Territory *territory : continentTerritories)
    {
        territories.push_back(territory);
    }
}


//=============================================================================================================================================================================================================//


Map::Map() {}

Map::Map(const Map &m)
{
    this->continents = m.continents;
    this->territories = m.territories;
}

Map::~Map()
{
    for (Continent *c : continents)
    {
        delete c;
        c = NULL;
    }

    for (Territory *t : territories)
    {
        delete t;
        t = NULL;
    }
}

void Map::addContinent(Continent *continent)
{
    continents.push_back(continent);
    for (Territory *territory : continent->getTerritories())
    {
        territories.push_back(territory);
    }
}

vector<Continent*> Map::getContinents() const {
    return continents;
}

void Map::setContinents(const vector<Continent *> &continents)
{
    this->continents = continents;
    for (Continent *continent : continents)
    {
        for (Territory *territory : continent->getTerritories())
        {
            territories.push_back(territory);
        }
    }
}

Territory* Map::getTerritory(string name) {
    for (Territory* territory : territories) {
        if (territory->getName() == name) {
            return territory;
        }
    }
    return NULL;
}

vector<Territory *> Map::getTerritories()
{

    vector <Territory*> territories;

    continents = this->getContinents();

    for (Continent *continent: continents){
        for (Territory *territory: continent->getTerritories()){
            territories.push_back(territory);
        }
    }

    return territories;
}




ostream &operator<<(std::ostream &os, const Map &m)
{

    // Iterate through continents and territories and print their details.
    for (const Continent *continent : m.continents)
    {
        os << "Continent: " << continent->getContinentName() << "\n"<< std::endl;
        os << "Bonus: " << continent->getBonus() << "\n"<< std::endl;

        for (const Territory *territory : continent->getTerritories())
        {
            os << *territory << endl;
        }
        os << "===============================================\n\n";
    }

    return os;
}

Map& Map::operator=(const Map& m){
    this->setContinents(m.getContinents());
    return *this;
}

bool Map::isMapConnected()
{
    // initalize visited list and stack of territories from map
    set<const Territory *> visited;
    const Territory *startingTerritory = this->getContinents()[0]->getTerritories()[0]; // Start from the first territory.
    std::stack<const Territory *> stack;
    stack.push(startingTerritory);

    while (!stack.empty())
    {
        const Territory *currentTerritory = stack.top();
        stack.pop();

        // Mark the current territory as visited.
        visited.insert(currentTerritory);

        // Get the neighbors of the current territory.
        for (Territory *neighbor : currentTerritory->getNeighbors())
        {
            if (visited.find(neighbor) == visited.end())
            {
                stack.push(neighbor);
            }
        }
    }

    // Check if all territories were visited.
    for (const Continent *continent : continents)
    {
        for (const Territory *territory : continent->getTerritories())
        {
            if (visited.find(territory) == visited.end())
            {

                // If any territory was not visited, the map is not valid.
                return false;
            }
        }
    }
    return true;
}

bool Map::isContinentConnected()
{
    // initalize visited list and stack of territories from continent
    set<const Territory *> visited;
    const Territory *startingTerritory = continents[0]->getTerritories()[0]; // Start from the first territory.
    std::stack<const Territory *> stack;
    stack.push(startingTerritory);

    while (!stack.empty())
    {
        const Territory *currentTerritory = stack.top();
        stack.pop();
        // Mark the current territory as visited.
        visited.insert(currentTerritory);

        // Get the neighbors of the current territory.
        for (Territory *neighbor : currentTerritory->getNeighbors())
        {
            if (visited.find(neighbor) == visited.end())
            {
                stack.push(neighbor);
            }
        }
    }

    // Check if all territories were visited.
    for (const Continent *continent : continents)
    {
        for (const Territory *territory : continent->getTerritories())
        {
            if (visited.find(territory) == visited.end())
            {

                // If any territory was not visited, the map is not valid.
                return false;
            }
        }
    }
    return true;
}

bool Map::checkTerritoriesInContinents()
{
    std::set<const Territory *> territoriesSet; // To keep track of visited territories.

    for (const Continent *continent : continents)
    {
        for (const Territory *territory : continent->getTerritories())
        {
            if (territoriesSet.find(territory) != territoriesSet.end())
            {
                // If the territory is already in the set, it is assigned to multiple continents.
                return false;
            }
            territoriesSet.insert(territory);
        }
    }

    // If all territories are assigned to continents only once, return true.
    return true;
}

bool Map::validate()
{
    if (this->getContinents().empty())
    {
        cout << "No continents" << endl;
        // If there are no continents, the map is not valid.
        return false;
    }

    if (!isMapConnected() || !isContinentConnected())
    {
        cout << "Map is not connected" << endl;
        // If the map is not connected, it is not valid.
        return false;
    }
    if (!checkTerritoriesInContinents())
    {
        cout << "Territories are not in continents" << endl;
        // If a territory is assigned to multiple continents, the map is not valid.
        return false;
    }

    return true;
}

Map* Map::getMap() const{
    return (Map*)this;
}

// ================================================================================================= //


Map* MapLoader::getMap() const
{
    return map;
}

Map *MapLoader::loadMap()
{

    map = new Map();

    // Get the current working directory
    fs::path currentDir = fs::current_path();

    // Search for a ".map" file in the current directory
    vector<string> mapFiles;
    string mapFileName;

    for (const auto &entry : fs::directory_iterator(currentDir))
    {
        if (entry.is_regular_file() && (entry.path().extension() == ".map" || entry.path().extension() == ".txt"))
        {
            mapFileName = entry.path().filename().string();

            // Open the ".map" file
            std::ifstream file(mapFileName);

            // Check if the file is open
            if (!file.is_open())
            {
                std::cerr << "Failed to open the '.map' file: " << mapFileName << std::endl;
                continue; // Skip to the next file
            }

            std::string firstLine;
            if (std::getline(file, firstLine) && firstLine.find("[Map]") == 0)
            {
                // The first line starts with "[Map]", so this is the correct file
                mapFiles.push_back(mapFileName);
                file.close();
            }

            if (std::getline(file, firstLine) && firstLine.find("[Map]") != 0)
            {
                file.close(); // Close the file, as it doesn't start with "[Map]"
            }
        }
    }

    cout << "You can open the following files: " << endl;
    for (const string &mapFile : mapFiles)
    {
        cout << mapFile << endl;
    }

    bool test = true;

    while (test)
    {
        cout << "\nSelect the file you want to load: ";
        cin >> mapFileName;

        bool isValidFile = false;
        for (int i = 0; i < mapFiles.size(); i++)
        {
            if (mapFileName == mapFiles[i])
            {
                isValidFile = true;
                break;
            }
        }

        if (isValidFile)
        {
            cout << "\nLoading: " << mapFileName << "...\n\n"
                 << endl;
            break;
        }
        else
        {
            cout << "\nInvalid file name, please try again" << endl;
        }
    }

    // Check if a ".map" file with "[Map]" as the first line was found
    if (mapFileName.empty())
    {
        std::cerr << "No '.map' file with '[Map]' as the first line found in the current directory." << std::endl;
    }

    // Open the selected ".map" file
    std::ifstream file(mapFileName);
    cout << mapFileName << endl;

    // Check if the file is open
    if (!file.is_open())
    {
        std::cerr << "Failed to open the '.map' file: " << mapFileName << std::endl;
    }

    string line;
    bool isContinentSection = false;
    bool isTerritorySection = false;

    vector<Territory *> territories; // Store territories temporarily

    while (getline(file, line))
    {
        if (line == "[Continents]")
        {
            isTerritorySection = false;
            isContinentSection = true;
            continue;
        }
        else if (line == "[Territories]")
        {
            isContinentSection = false;
            isTerritorySection = true;
            continue;
        }

        if (isContinentSection && line != "")
        {
            string continentName = line.substr(0, line.find('='));
            int bonus = stoi(line.substr(line.find('=') + 1));
            Continent *continent = new Continent(continentName, bonus);
            map->addContinent(continent);
        }
        else if (isTerritorySection && line != "")
        {
            stringstream ss(line);
            string territoryName;
            getline(ss, territoryName, ',');
            string x, y, continentName;
            getline(ss, x, ',');
            getline(ss, y, ',');
            getline(ss, continentName, ',');
            Territory *territory = new Territory(territoryName, continentName);
            territories.push_back(territory);
        }
    }

    file.close();

    // Now that all territories are created, let's add their neighbors
    file.open(mapFileName); // Reopen the file
    isContinentSection = false;
    isTerritorySection = false;

    while (getline(file, line))
    {
        if (line == "[Continents]")
        {
            isTerritorySection = false;
            isContinentSection = true;
            continue;
        }
        else if (line == "[Territories]")
        {
            isContinentSection = false;
            isTerritorySection = true;
            continue;
        }

        if (isTerritorySection && line != "")
        {
            stringstream ss(line);
            string territoryName;
            getline(ss, territoryName, ',');
            Territory *territory = nullptr;

            for (Territory *t : territories)
            {
                if (t->getName() == territoryName)
                {
                    territory = t;
                    break;
                }
            }

            if (territory)
            {
                string neighbors;
                while (getline(ss, neighbors, ','))
                {
                    Territory *neighbor = nullptr;

                    for (Territory *t : territories)
                    {
                        if (t->getName() == neighbors)
                        {
                            neighbor = t;
                            break;
                        }
                    }

                    if (neighbor)
                    {
                        territory->addNeighbor(neighbor);
                    }
                }

                for (Continent *continent : map->getContinents())
                {
                    if (territory->getContinent() == continent->getContinentName())
                    {
                        continent->addTerritory(territory);
                    }
                }
            }
        }
    }

    file.close();

    return map;
};

Map *MapLoader::loadMap_withName(string mapName)
{

    map = new Map();

    // Get the current working directory
    fs::path currentDir = fs::current_path();

    // Search for a ".map" file in the current directory
    string mapFileName = mapName;

    // Check if a ".map" file with "[Map]" as the first line was found
    if (mapFileName.empty())
    {
        std::cerr << "No '.map' file with '[Map]' as the first line found in the current directory." << std::endl;
    }

    // Open the selected ".map" file
    std::ifstream file(mapFileName);

    // Check if the file is open
    if (!file.is_open())
    {
        std::cerr << "Failed to open the '.map' file: " << mapFileName << std::endl;
    }

    string line;
    bool isContinentSection = false;
    bool isTerritorySection = false;

    vector<Territory *> territories; // Store territories temporarily

    while (getline(file, line))
    {
        if (line == "[Continents]")
        {
            isTerritorySection = false;
            isContinentSection = true;
            continue;
        }
        else if (line == "[Territories]")
        {
            isContinentSection = false;
            isTerritorySection = true;
            continue;
        }

        if (isContinentSection && line != "")
        {
            string continentName = line.substr(0, line.find('='));
            int bonus = stoi(line.substr(line.find('=') + 1));
            Continent *continent = new Continent(continentName, bonus);
            map->addContinent(continent);
        }
        else if (isTerritorySection && line != "")
        {
            stringstream ss(line);
            string territoryName;
            getline(ss, territoryName, ',');
            string x, y, continentName;
            getline(ss, x, ',');
            getline(ss, y, ',');
            getline(ss, continentName, ',');
            Territory *territory = new Territory(territoryName, continentName);
            territories.push_back(territory);
        }
    }

    file.close();

    // Now that all territories are created, let's add their neighbors
    file.open(mapFileName); // Reopen the file
    isContinentSection = false;
    isTerritorySection = false;

    while (getline(file, line))
    {
        if (line == "[Continents]")
        {
            isTerritorySection = false;
            isContinentSection = true;
            continue;
        }
        else if (line == "[Territories]")
        {
            isContinentSection = false;
            isTerritorySection = true;
            continue;
        }

        if (isTerritorySection && line != "")
        {
            stringstream ss(line);
            string territoryName;
            getline(ss, territoryName, ',');
            Territory *territory = nullptr;

            for (Territory *t : territories)
            {
                if (t->getName() == territoryName)
                {
                    territory = t;
                    break;
                }
            }

            if (territory)
            {
                string neighbors;
                while (getline(ss, neighbors, ','))
                {
                    Territory *neighbor = nullptr;

                    for (Territory *t : territories)
                    {
                        if (t->getName() == neighbors)
                        {
                            neighbor = t;
                            break;
                        }
                    }

                    if (neighbor)
                    {
                        territory->addNeighbor(neighbor);
                    }
                }

                for (Continent *continent : map->getContinents())
                {
                    if (territory->getContinent() == continent->getContinentName())
                    {
                        continent->addTerritory(territory);
                    }
                }
            }
        }
    }

    file.close();

    return map;
};

/* Test for map functionality
int main(){

//     MapLoader* loader = new MapLoader();
//     string mapName = "Aden.map";
//     Map *testMap = loader->loadMap_withName(mapName);
//     // Map* testMap = loader.loadMap();

//     // cout << *testMap << endl;

//     // cout << testMap->getTerritories().size() << endl;


//     // gamestart command
//     int minLimit = 0;
//     int maxLimit = 0;
//     vector <int> numberOfPlayers = {1,2,3,4,5,6};

//     // set max limit
//     maxLimit = testMap->getTerritories().size()-1;
    
    

//     vector <Territory*> territories;
//     territories = testMap->getTerritories();
//     std::random_device rd;  // Seed the random number generator
//     std::mt19937 gen(rd()); // Mersenne Twister pseudo-random number generator
//     std::uniform_int_distribution<int> distribution(minLimit, maxLimit);

//     for (int i=0; i<maxLimit; i++){
//         int randomIndex1 = distribution(gen);
//         int randomIndex2 = distribution(gen);
//         swap (territories[randomIndex1], territories[randomIndex2]);
//     }

//     for (Territory* territory: territories){
//         cout << territory->getName() << endl;
//     }

//     cout<<"radomized order"<<endl;

//     int playerIndex =0;
//     int territoryIndex=0;
//     for (Territory* territory: territories){
//         territory->setPlayer(numberOfPlayers[playerIndex]);
//         playerIndex = (playerIndex+1)%numberOfPlayers.size();
//         territoryIndex = (territoryIndex+1)%territories.size();
//     }



//     cout << *testMap->getMap() << endl;
//     cout<<*testMap<<endl;

//     // vector <Territory*> testTerr;
//     // testTerr = testMap->getTerritories();

//     // int cP1 =0;
//     // int cP2 =0;
//     // int Cp3=0;
//     // int cP4 =0;
//     // int cP5 =0;
//     // int cP6 =0;

//     // for (Territory* territory: testTerr){
//     //     if (territory->getPlayer() == 1){
//     //         cP1++;
//     //     }
//     //     if (territory->getPlayer() == 2){
//     //         cP2++;
//     //     }
//     //     if (territory->getPlayer() == 3){
//     //         Cp3++;
//     //     }
//     //     if (territory->getPlayer() == 4){
//     //         cP4++;
//     //     }
//     //     if (territory->getPlayer() == 5){
//     //         cP5++;
//     //     }
//     //     if (territory->getPlayer() == 6){
//     //         cP6++;
//     //     }
//     // }

//     // cout<< cP1<<endl;
//     // cout<< cP2<<endl;
//     // cout<< Cp3<<endl;
//     // cout<< cP4<<endl;
//     // cout<< cP5<<endl;
//     // cout<< cP6<<endl;

//     if (testMap->validate())
//     {
//         cout << "\n\nMap is valid" << endl;
//     }
//     else
//     {
//         cout << "Map is not valid" << endl;
//     }

   

    return 0;
};

*/
