#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include "Map.h"

void loadMap(string filename) {
    ifstream file(filename);
    string line;
    bool isContinentSection = false;
    bool isTerritorySection = false;
    
    Map* map = new Map();

    while (getline(file, line)) {
        if (line == "[Continents]") {
            isContinentSection = true;
            isTerritorySection = false;
            continue;
        }
        else if (line == "[Territories]") {
            isContinentSection = false;
            isTerritorySection = true;
            continue;
        }

        if (isContinentSection) {
            string continentName = line.substr(0, line.find('='));
            Continent* continent = new Continent(continentName);
            map->addContinent(continent);
            std::cout << "New continent created : " << continent->getContinentName() << endl;
        }
        else if (isTerritorySection) {
            stringstream ss(line);
            string territoryName;
            getline(ss, territoryName, ',');
            string x, y, continentName;
            getline(ss, x, ',');
            getline(ss, y, ',');
            getline(ss, continentName, ',');
            Territory* territory= new Territory(territoryName, continentName);
            std::cout << "New Teritory created : " << territory->getName() << endl;
            string neighbors;
            while (getline(ss, neighbors, ',')) {
                
                Territory* neighbor = new Territory(neighbors, continentName);
                territory->addNeighbor(neighbor);
                std::cout << "\t New Neighbor created : " << neighbor->getName() << endl;
            }
            
            map->addTerritory(territory);
        }
    }
    
    file.close();
}



int main() {
    loadMap("Z.map");

    return 0;
}