#include "src/header/Graph.h"
#include "src/header/Loader.h"
#include "src/header/Menu.h"
#include <iostream>


int main() {
    Graph Airport;
    Loader::loadAirports(Airport, "airports.csv");
    Loader::loadFlights(Airport, "flights.csv");
    std::cout << "--> Welcome to Flight Management Services AED <--\n           press 0 + ENTER to continue\n";
    int space;
    std::cin >> space;
    if (space == 0){Menu::displayMenu(Airport);} else {std::cout<< "Enter a valid key!";}


}
