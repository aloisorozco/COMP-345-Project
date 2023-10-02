#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    ifstream  inputFile ("Test.map)");
    if (!inputFile) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    string line;

    if (getline(inputFile, line))
    {
        vector<string> words;
        stringstream ss(line);
        string word;


        // Print line (read from file) in Console
        cout << line << endl;
    }

    // Close the file
    inputFile.close();

    return 0;
}