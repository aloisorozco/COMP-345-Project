#include <iostream>
#include <chrono>
#include <thread>

// Including game components
#include "GameEngine/GameEngine.h"
#include "Cards/Cards.h"
#include "Orders/Orders.h"
#include "Player/Player.h"
#include "Observer/LoggingObserver.h"
#include "Map/Map.h"


void printMenu() {
    std::cout << "Test Game Components : \n";
    std::cout << "1. Map\n";
    std::cout << "2. Player\n";
    std::cout << "3. Orders list\n";
    std::cout << "4. Card deck/hand\n";
    std::cout << "5. Game Engine\n";
    std::cout << "6. Exit\n";
    std::cout << "7. Logs\n";
    std::cout << "10. Main Game Loop\n";
    std::cout << "Enter number > ";
}

int main() {
    std::chrono::seconds sleepDuration(1);

    while (true) {

        std::cout << "\x1B[2J\x1B[H"; // clear screen
        printMenu();
        int choice;
        std::cin >> choice;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            choice = 0; // Invalid input
        }

        switch (choice) {
            case 1:
                // call function to test map
                testLoadMaps();
                break;

            case 2:
                // call function to test player
                testPlayers();
                break;

            case 3:
                // call function to test orders list
                testOrdersLists();
                break;

            case 4:
                // call function to test card deck/hand
                testCards();
                break;

            case 5:
                // call function to test game engine
                testGameStates();
                break;

            case 6:
                return 0;  // Exit the program

            case 7:
                testLoggingObserver();
                break;  // Exit the program

            case 10:
                testMainGameLoop();

            default:
                std::cout << "Invalid choice. Please enter a number between 1 and 6.\n";
                std::this_thread::sleep_for(sleepDuration);
                break;
        }
    }
    return 0;
}
