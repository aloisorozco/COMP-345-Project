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
    
    MapLoader loader;
    Map *testMap = loader.loadMap();

    cout << *testMap << endl;

    if (testMap->validate())
    {
        cout << "\n\nMap is valid" << endl;
    }
    else
    {
        cout << "Map is not valid" << endl;
    }

    delete testMap;

};