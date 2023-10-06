#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    // Open the input file
    std::ifstream inputFile("Africa.map");

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the input file." << std::endl;
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
