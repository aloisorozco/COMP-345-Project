#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <filesystem>
#include "Map.h"

using namespace std;
namespace fs = std::filesystem; // Namespace alias for filesystem

void testLoadMaps()
{
    // Get the current working directory
    fs::path currentDir = fs::current_path();

    // Search for a ".map" file in the current directory
    std::string mapFileName;

    while (true)
    {
        // Get the current working directory
        fs::path currentDir = fs::current_path();
        
        

        // Search for a ".map" file in the current directory
        vector<string> mapFiles;
        std::string mapFileName;

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

        while (true)
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
                cout << "\nLoading: " << mapFileName <<"...\n\n"<< endl;
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

        // Check if the file is open
        if (!file.is_open())
        {
            std::cerr << "Failed to open the '.map' file: " << mapFileName << std::endl;
        }

        string line;
        bool isContinentSection = false;
        bool isTerritorySection = false;

        Map *map = new Map();
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
                Continent *continent = new Continent(continentName);
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

        cout << *map << endl;

        if (map->validate())
        {
            cout << "\n\nMap is valid" << endl;
        }
        else
        {
            cout << "Map is not valid" << endl;
        }

        break;
    }
};

