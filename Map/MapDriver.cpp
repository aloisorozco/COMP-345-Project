#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>

#include "Map.h"

using namespace std;
namespace fs = std::filesystem; // Namespace alias for filesystem

int testLoadMaps(){
    // Get the current working directory
    fs::path currentDir = fs::current_path();

    // Search for a ".map" file in the current directory
    std::string mapFileName;

    while (true){
           // Get the current working directory
    fs::path currentDir = fs::current_path();

    // Search for a ".map" file in the current directory
    std::string mapFileName;
    for (const auto& entry : fs::directory_iterator(currentDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".map" || entry.is_regular_file() && entry.path().extension() == ".txt") {
            mapFileName = entry.path().string();

            // Open the ".map" file
            std::ifstream inputFile(mapFileName);
            cout<<"Opened: "<< mapFileName<<endl;

            // Check if the file is open
            if (!inputFile.is_open()) {
                std::cerr << "Failed to open the '.map' file: " << mapFileName << std::endl;
                continue; // Skip to the next file
            }

            std::string firstLine;
            if (std::getline(inputFile, firstLine) && firstLine.find("[Map]") == 0) {
                // The first line starts with "[Map]", so this is the correct file
                inputFile.close();
                break; // Exit the loop
            }

            inputFile.close(); // Close the file, as it doesn't start with "[Map]"
        }
    }

    // Check if a ".map" file with "[Map]" as the first line was found
    if (mapFileName.empty()) {
        std::cerr << "No '.map' file with '[Map]' as the first line found in the current directory." << std::endl;
        return 1; // Return an error code
    }

    // Open the selected ".map" file
    std::ifstream inputFile(mapFileName);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the '.map' file: " << mapFileName << std::endl;
        return 1; // Return an error code
    }

    std::string line;

    // Read the file line by line
    while (std::getline(inputFile, line)) {
        // If the line is empty or contains only spaces and tabs, consider it a new line
        if (line.empty() || line.find_first_not_of(" \t\n\r\f\v") == std::string::npos) {
            std::cout << "New Line" << std::endl;
        } else {
            // Create a stringstream to parse the line
            std::stringstream ss(line);
            std::string word;

            // Vector to store words
            std::vector<std::string> words;

            // Split the line using commas as delimiters
            while (std::getline(ss, word, ',')) {
                // Remove leading and trailing spaces from each word
                word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
                word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);
                
                // Add the word to the vector if it's not empty
                if (!word.empty()) {
                    words.push_back(word);
                }
            }

            // Process the words (you can replace this with your logic)
            for (const std::string& w : words) {
                std::cout << "Word: " << w << std::endl;
            }
        }
    }

    // Close the input file
    inputFile.close();

    return 0; // Return 0 to indicate success
    }
};

int main(){
    testLoadMaps();
    return 0;
};
