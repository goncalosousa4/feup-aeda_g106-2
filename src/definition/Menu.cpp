#include "Menu.h"
#include "Airline.h"
#include "Loader.h"
#include "../header/Graph.h"
#include <set>
#include <unordered_map>
#include <algorithm>

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
            case 5:
                break;
            case 0:


                std::cout<<"                            \\    "<<std::endl;
                std::cout<<"                            \\ \\"<<std::endl;
                std::cout<<"                             \\  \\"<<std::endl;
                std::cout<<"                      |\\      \\   \\"<<std::endl;
                std::cout<<"--------------------  >}(|||||A E D|||[  )  --    "<<std::endl;
                std::cout<<"                      |/      /   /"<<std::endl;
                std::cout<<"                             /  /"<<std::endl;
                std::cout<<" Thank you for choosing us  / /"<<std::endl;
                std::cout<<"      See you soon...       /"<<std::endl;

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
        std::cout << " The number of flights out of " << airportCode << " is " << numFlights  << std::endl;
        std::cout << "  -Flights have " << airlines.size() << " different Airlines    \n";

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
        std::cout << "2. Show the number of different destinations reachable from an Airport\n";
        std::cout << "3. Rankings\n";
        std::cout << "4. Reachable destinations with stops\n";
        std::cout << "\n0. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                countFlightsOutOfAirport(ap);
                break;

            case 2:
                printNumDestinationsForAirport(ap);
                break;

            case 3:
                int k;
                std::cout << "Which ranking would you like to check? Top ";
                std::cin >> k;
                std::cout << std::endl;
                ranking(ap, k);
                break;

            case 4:
                numReachableDestinations(ap);
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
    int num = 0, count = 0;
    std::unordered_map<std::string, int> flightsPerAirline;

    for (const auto& vertex : ap.getVertexSet()) {
        if (vertex->getAirport().getCity() == city) {
            count++;
            for (const Edge& edge : vertex->getAdj()) {
                std::string airline = edge.getAirline();
                flightsPerAirline[airline]++;
                num++;
            }
        }
    }

    if (count==0){
        std::cout <<"City " << city << " not found. Please enter a valid city\n";
    }else{
        std::cout << "The number of flights from " << city << " is " << num << std::endl;
        std::cout << city << " has " << flightsPerAirline.size() << " airlines available\n";
        std::cout << "\nNumber of flights from " << city << " per airline:" << std::endl;
        for (const auto& entry : flightsPerAirline) {
            auto airlineCode = entry.first;
            Airline line = Loader::findAirlineByCode(airlineCode, "../dataset/airlines.csv");
            std::cout << "\t-" << airlineCode << " ("<< line.getName() <<  "): " << entry.second << std::endl; // insert airline name like - IBE (Iberia Airlines)
        }
    }
}

void Menu::flightsPerAirline(Graph ap){
    std::string airline;
    std::cout << "Enter the airline: ";
    std::cin.ignore();
    std::getline(std::cin, airline);
    std::cout << std::endl;
    Airline line = Loader::findAirlineByCode(airline, "../dataset/airlines.csv");
    int totalFlights = 0;

    for (const auto& vertex : ap.getVertexSet()) {
        for (const Edge& edge : vertex->getAdj()) {
            if (edge.getAirline() == airline) {
                totalFlights++;
            }
        }
    }

    if (totalFlights==0){
        std::cout << "Airline " << airline << " not found. Please enter a valid Airline\n";
    } else{
        std::cout << "The number of flights for " << airline << " (" << line.getName() << ")" << " is " << totalFlights << std::endl; // insert airline name like - IBE (Iberia Airlines)
    }

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
void Menu::printNumDestinationsForAirport(Graph ap) {
    std::string airportCode;
    std::cout << "Enter the airport code: ";
    std::cin >> airportCode;
    std::cout<<std::endl;

    auto uniqueAirports = ap.bfs(airportCode);

    if (airportCode.size()==3) {

        std::set<std::string> uniqueCities;         // sets wont let the dest repeat
        std::set<std::string> uniqueCountries;

        for (const auto& airp: uniqueAirports){
            uniqueCities.insert(ap.findVertex(airp)->getAirport().getCity());
            uniqueCountries.insert((ap.findVertex(airp)->getAirport().getCountry()));
        }

        int numAirports = (uniqueAirports.size());
        int numCities = (uniqueCities.size());
        int numCountries = (uniqueCountries.size());

        std::cout << "Airport " << airportCode << " (" << ap.findVertex(airportCode)->getAirport().getName() << ") can get to:"<< std::endl <<"-"<< numAirports
        << " different airports\n" << "-" <<numCities << " different cities\n"
        << "-"<<numCountries << " different countries\n" << std::endl;
    } else {
        std::cerr << "Airport with code " << airportCode << " not found." << std::endl;
    }
}
void Menu::ranking(Graph ap, int k) {
    std::vector<std::pair<std::string, int>> airportFlights; // vector of pairs to store the airports their flights number


    for (const Vertex *vertex: ap.getVertexSet()) {
        const std::vector<Edge> &adjEdges = vertex->getAdj();
        int numFlights = (adjEdges.size());
        airportFlights.emplace_back(vertex->getAirport().getCode(), numFlights);   // populationg the vector
    }


    std::sort(airportFlights.begin(), airportFlights.end(),[](const auto& a, const auto& b) {    // sorting the vector
                  return a.second > b.second;
              });


    std::cout << "        T O P  " << k << std::endl;
    std::cout << "+----------------------+\n";
    std::cout <<" AIRPORT\tFLIGHTS\n";
    for (int i = 0; i < k && i < airportFlights.size(); ++i) {              // selecting just the k first
        const auto &airportCount = airportFlights[i];
        std::cout << "   " << airportCount.first << "\t\t  " << airportCount.second << std::endl;
    }
}


/*void Menu::reachableDest(Graph ap) {
    std::string src;
    int stops;
    int count = 0;

    std::cout << "Enter the departing airport code: ";
    std::cin >> src;
    std::cout << std::endl;
    std::cout << "How many lay-overs do you want to make? ";
    std::cin >> stops;
    std::cout << std::endl;

    std::unordered_map<std::string, int> reachableDestinations = ap.bfsLayOver(src);

    for (const auto& dest : reachableDestinations) {
        if (dest.second >= 0 && dest.second <= stops) {
            count++;
        }
    }

    std::cout << "Number of reachable destinations within " << stops << " lay-overs: " << count << std::endl;
}*/

/*void Menu::reachableDest(Graph ap) {
    std::string src;
    int stops;
    int count  = 0;
    std::cout << "Enter the departing airport code: ";
    std::cin >> src;
    std::cout << std::endl;

    std::cout << "How many lay-overs do you want to make? ";
    std::cin >> stops;
    std::cout << std::endl;

    std::unordered_map<std::string, int> reachableDestinations = ap.bfsLayOver(src);

    std::cout << "Reachable airports within " << stops << " layovers from " << src << " are:" << std::endl; //debug
    for (const auto& dest : reachableDestinations) {
        if (dest.second >= 0 && dest.second <= stops) {
            std::cout << dest.first << " (Layovers: " << dest.second << ")" << std::endl; //debug
            count++;
        }
    }
    std::cout << "The number of reachable airports for " << src << " within " << stops << " lay-overs is " << count << std::endl;
    auto a = "MAG";
    std::set<Vertex*> direct;
    std::cout << "Direct Airports ";                                                     // debug
    for (const auto& a :ap.findVertex(a)->getAdj()){
        direct.insert(a.getDest());
    }
    std::cout << direct.size() << std::endl;
}*/
void Menu::numReachableDestinations(Graph ap) {
    std::string src;
    int stops;
    int countAirports = 0;
    int countCities = 0;
    int countCountries = 0;

    std::cout << "Enter the departing airport code: ";
    std::cin >> src;
    std::cout << std::endl;

    std::cout << "How many lay-overs would you like to make? ";
    std::cin >> stops;
    std::cout << std::endl;

    if (ap.findVertex(src) == nullptr) {
        std::cout << "Airport not found." << std::endl;
        return;
    }

    std::queue<std::pair<Vertex*, int>> q; // empty queue for BFS
    std::set<std::string> visited;
    int numReachableDestinations = 0;

    // Inserting the src airport and making it with -1 stops (not accessible)
    q.push({ap.findVertex(src), -1});
    visited.insert(src);

    // BFS-like implementation for this context

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current.second <= stops) {
            numReachableDestinations++;
        } else {
            break;
        }

        // Process the current airport
        countAirports++;

        // Extract city and country information from the current airport
        std::string currentCity = current.first->getAirport().getCity();
        std::string currentCountry = current.first->getAirport().getCountry();

        // Check if the city has not been visited
        if (visited.find(currentCity) == visited.end()) {
            visited.insert(currentCity);
            countCities++;
        }

        // Check if the country has not been visited
        if (visited.find(currentCountry) == visited.end()) {
            visited.insert(currentCountry);
            countCountries++;
        }

        // Enqueue neighboring airports
        for (const auto& edge : current.first->getAdj()) {
            auto dest = edge.getDest();
            if (visited.find(dest->getAirport().getCode()) == visited.end()) {
                q.push({dest, current.second + 1});
                visited.insert(dest->getAirport().getCode());
            }
        }
    }

    std::cout << "Number of reachable destinations departing from " << src << " within " << stops
              << " stops is: "<<std::endl;
    std::cout << "-" << numReachableDestinations -1 << " airports\n";
    std::cout << "-" << countCities << " cities" << std::endl;
    std::cout << "-" << countCountries << " countries" << std::endl;
}





