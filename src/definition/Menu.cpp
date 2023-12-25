#include "Menu.h"
#include <set>

void Menu::displayMenu(Graph ap) {
    int choice;
    do {
        std::cout << "\n-----------\n" ;
        std::cout << "  M E N U   \n";
        std::cout << "-----------\n" ;
        std::cout << "1. Check the global number of airports\n";
        std::cout << "2. Check the number of available flights\n";
        std::cout << "3. Show Airports' information\n";
        std::cout << "\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                printAvailableAirports(ap);
                break;
            case 2:
                printAvailableFlights(ap);
                break;

            case 3:
                airportInfoMenu(ap);
                break;
            case 0:
                std::cout << "Thank you for choosing us. See you soon...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void Menu::printAvailableAirports(Graph ap) {
    int numAirports = ap.getNumVertex();
    std::cout << "The global number of Airports: " << numAirports << "\n";
}

void Menu::printAvailableFlights(Graph ap) {
    int numFlights = ap.getNumEdges();
    std::cout << "The number of available flights: " << numFlights << "\n";
}

void Menu::countFlightsOutOfAirport(Graph ap) {
    std::set<std::string> airlines;

    std::string airportCode;
    std::cout << "Enter the airport code: ";
    std::cin >> airportCode;
    std::cout << std::endl;

    Vertex* airportVertex = ap.findVertex(airportCode);
    for (const Edge &edge: airportVertex->getAdj()) {
        airlines.insert(edge.getAirline());
    }

    if (airportVertex) {
        int numFlights = airportVertex->getAdj().size();
        std::cout << "           A I R P O R T   " << airportCode << "          \n";
        std::cout << "+-----------------------------------------+\n";
        std::cout << "| The number of flights out of " << airportCode << " is " << numFlights << " |"  << std::endl;
        std::cout << "|  -Flights have " << airlines.size() << " different Airlines    |\n";
        std::cout << "+-----------------------------------------+\n";
    } else {
        std::cout << "Airport with code " << airportCode << " not found." << std::endl;
    }

}
void Menu::airportInfoMenu(Graph ap){
    int choice;
    do {

        std::cout << "\n  I N F O  \n";
        std::cout << "-----------\n" ;
        std::cout << "1. Check the number of flights out of an Airport\n";

        std::cout << "\n0. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                countFlightsOutOfAirport(ap);
                break;

            case 0:
                displayMenu(ap);
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}


