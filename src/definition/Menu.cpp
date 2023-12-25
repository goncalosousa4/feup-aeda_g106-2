#include "Menu.h"
#include <set>
#include <unordered_map>

void Menu::displayMenu(Graph ap) {
    int choice;
    do {
        std::cout << "\n-----------\n" ;
        std::cout << "  M E N U   \n";
        std::cout << "-----------\n" ;
        std::cout << "1. Check the global number of airports\n";
        std::cout << "2. Check the number of available flights\n";
        std::cout << "3. Show Airports' information\n";
        std::cout << "4. Check statistics\n";

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

            case 4:
                statsMenu(ap);
                break;

            case 0:


                std::cout<<"                            \\    "<<std::endl;
                std::cout<<"                            \\ \\"<<std::endl;
                std::cout<<"                             \\  \\"<<std::endl;
                std::cout<<"                      |\\      \\   \\"<<std::endl;
                std::cout<<"..................... >}==|||A E D|||[  ) ...    "<<std::endl;
                std::cout<<"                      |/      /   /"<<std::endl;
                std::cout<<"                             /  /"<<std::endl;
                std::cout<<" Thank you for choosing us  / /"<<std::endl;
                std::cout<<"       See you soon...      /"<<std::endl;

                exit(0);

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 9);
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
        std::cout << "\n-----------\n" ;
        std::cout << "  I N F O  \n";
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

void Menu::statsMenu(Graph ap){
    int choice;
    do {
        std::cout << "\n-------------\n" ;
        std::cout << "  S T A T S  \n";
        std::cout << "-------------\n" ;
        std::cout << "1. Check City statistics\n";
        std::cout << "2. Check Airline statistics\n";
        std::cout << "3. Check countries from a city\n";
        std::cout << "4. Check countries from an Airport\n";
        std::cout << "\n0. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                flightsPerCityPerAirline(ap);
                break;
            case 2:
                flightsPerAirline(ap);
                break;
            case 3:
                countCountriesForCity(ap);
                break;
            case 4:
                countCountriesForAirport(ap);
                break;
            case 0:
                displayMenu(ap);
                break;

            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

void Menu::flightsPerCityPerAirline(Graph ap) {
    std::string city;
    std::cout << "Enter the city: ";
    std::cin.ignore();
    std::getline(std::cin, city);
    std::cout << std::endl;
    int num = 0;
    std::unordered_map<std::string, int> flightsPerAirline;

    for (const auto& vertex : ap.getVertexSet()) {
        if (vertex->getAirport().getCity() == city) {
            for (const Edge& edge : vertex->getAdj()) {
                std::string airline = edge.getAirline();
                flightsPerAirline[airline]++;
                num++;
            }
        }
    }
    std::cout << "The number of flights from " << city << " is " << num << std::endl;
    std::cout << city << " has " << flightsPerAirline.size() << " airlines available\n";
    std::cout << "\nNumber of flights from " << city << " per airline:" << std::endl;
    for (const auto& entry : flightsPerAirline) {
        auto airline = entry.first;
        std::cout << "\t-" << airline << ": " << entry.second << std::endl; // insert airline name like - IBE (Iberia Airlines)
    }
}

void Menu::flightsPerAirline(Graph ap){
    std::string airline;
    std::cout << "Enter the airline: ";
    std::cin.ignore();
    std::getline(std::cin, airline);
    std::cout << std::endl;

    int totalFlights = 0;

    for (const auto& vertex : ap.getVertexSet()) {
        for (const Edge& edge : vertex->getAdj()) {
            if (edge.getAirline() == airline) {
                totalFlights++;
            }
        }
    }

    std::cout << "The number of flights for " << airline << " is " << totalFlights << std::endl; // insert airline name like - IBE (Iberia Airlines)
}

void Menu::countCountriesForAirport(Graph ap) {
    std::string airportCode;
    std::cout << "Enter the airport code: ";
    std::cin >> airportCode;
    std::cout << std::endl;

    const Vertex* airportVertex = ap.findVertex(airportCode);
    if (!airportVertex) {
        std::cout << "Airport with code " << airportCode << " not found." << std::endl;
        return;
    }

    std::set<std::string> countries;

    for (const Edge& edge : airportVertex->getAdj()) {
        Vertex* dest = edge.getDest();
        countries.insert(dest->getAirport().getCountry());
    }

    std::cout << "The number of different countries able to reach departing from " << airportCode << " is " << countries.size() << std::endl;
}


void Menu::countCountriesForCity(Graph ap) {
    std::string city;
    std::cout << "Enter the city: ";
    std::cin.ignore();
    std::getline(std::cin, city);
    std::cout << std::endl;

    std::set<std::string> countries;

    for (const auto& vertex : ap.getVertexSet()) {
        if (vertex->getAirport().getCity() == city) {
            for (const Edge& edge : vertex->getAdj()) {
                Vertex* dest = edge.getDest();

                countries.insert(dest->getAirport().getCountry());
            }
        }
    }
    std::cout << "The number of different countries able to reach departing from " << city << " is " << countries.size() << std::endl;
}




