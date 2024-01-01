#include "Menu.h"
#include "Airline.h"
#include "Loader.h"
#include "../header/Graph.h"
#include <set>
#include <unordered_map>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <math.h>
#include <map>
#include <limits>
#include <sstream>
#include <fstream>
#include <string>

void Menu::displayMenu(Graph ap) {
    int choice;
    do {
        std::cout << "\n-----------\n" ;
        std::cout << "  M E N U   \n";
        std::cout << "-----------\n" ;
        std::cout << "1. Check the global number of airports and flights (3.1)\n";
        std::cout << "2. Show Airports' information\n";
        std::cout << "3. Check statistics\n";
        std::cout << "4. Make your flight\n";
        std::cout << "\n0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                printAvailableAirports(ap);
                printAvailableFlights(ap);
                break;

            case 2:
                airportInfoMenu(ap);
                break;
            case 3:
                statsMenu(ap);
                break;
            case 4:
                int option;
                std::cout << "!MAKE YOUR FLIGHT!\n";
                std::cout << "\n1. Best flight option (4)\n";
                std::cout << "2. Filter your search (5)\n";
                std::cout << "Choose your option!";
                std::cin >> option;
                std::cout << std::endl;
                switch(option){
                    case 1:
                        bestFlightOption(ap);
                        break;
                    case 2:
                        searchFlightsWithFilters(ap);
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                }
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
    std::cout << "The global number of Airports is " << numAirports << "\n";
}

void Menu::printAvailableFlights(Graph ap) {
    int numFlights = ap.getNumEdges();
    std::cout << "The number of available flights is " << numFlights << "\n";
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
        std::cout << "1. Check the number of flights out of an Airport (3.2)\n";
        std::cout << "2. Show the number of different destinations reachable from an Airport (3.5)\n";
        std::cout << "3. Rankings (3.8)\n";
        std::cout << "4. Reachable destinations for given stops (3.6)\n";
        std::cout << "5. Maximum possible trip (3.7)\n";
        std::cout << "6. Identify the airports that are essential to the network (3.9)\n";
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
                ranking(ap);
                break;

            case 4:
                numReachableDestinations(ap);
                break;

            case 5:
                findMaxStopsTrip(ap);
                break;

            case 6:
                std::cout << "Identifying essential airports...\n";
                ap.findArticulationPoints();
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
        std::cout << "1. Check city and airline statistics (3.3)\n";
        std::cout << "2. Check flyable countries from a city (3.4)\n";
        std::cout << "3. Check flyable countries from an Airport (3.4)\n";
        std::cout << "\n0. Return to Main Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice) {
            case 1:
                flightsPerCityPerAirline(ap);
                flightsPerAirline(ap);
                break;
            case 2:
                countCountriesForCity(ap);
                break;
            case 3:
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
            auto line = getAirlineName(airlineCode);
            std::cout << "\t-" << airlineCode << " ("<< line <<  "): " << entry.second << std::endl; // insert airline name like - IBE (Iberia Airlines)
        }
    }
}

void Menu::flightsPerAirline(Graph ap){
    std::string airline;
    std::cout << "Enter the airline: ";
    std::cin >> airline;
    std::cout << std::endl;
    auto line = getAirlineName(airline);
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
        std::cout << "The number of flights for " << airline << " (" << line << ")" << " is " << totalFlights << std::endl; // insert airline name like - IBE (Iberia Airlines)
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

        std::set<std::pair<std::string, std::string>> uniqueCities;         // sets wont let the dest repeat
        std::set<std::string> uniqueCountries;

        for (const auto& airp: uniqueAirports){
            uniqueCities.insert({ap.findVertex(airp)->getAirport().getCity(), ap.findVertex(airp)->getAirport().getCountry()});
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

void Menu::ranking(Graph ap) {
    int k;
    std::cout << "Which ranking would you like to check? Top ";
    std::cin >> k;
    std::cout << std::endl;

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

void Menu::numReachableDestinations(Graph ap) {
    std::string src;
    int stops;
    int countAirports = 0;
    int repeatedCities = 0;

    std::cout << "Enter the departing airport code: ";
    std::cin >> src;
    std::cout << std::endl;

    std::cout << "How many lay-overs would you like to make? ";
    std::cin >> stops;
    std::cout << std::endl;

    Vertex* srcVertex = ap.findVertex(src);
    if (srcVertex == nullptr) {
        std::cout << "Airport not found." << std::endl;
        return;
    }

    std::queue<std::pair<Vertex*, int>> k;
    std::set<std::string> visited;
    std::set<std::pair<std::string, std::string>> cities;
    std::set<std::string> countries;
    std::set<std::string> visitedAir;

    // Inserting the src airport and making it with -1 stops (not accessible)
    k.push({srcVertex, -1});
    visited.insert(src);

    // bfs-like implementation for this context
    while (!k.empty()) {
        auto current = k.front();
        k.pop();

        if (current.second <= stops) {
            Vertex* a = current.first;
            visitedAir.insert(a->getAirport().getCode());
        } else {
            break;
        }

        for (const auto& edge : current.first->getAdj()) {
            auto dest = edge.getDest();
            if (visited.find(dest->getAirport().getCode()) == visited.end()) {
                k.push({dest, current.second + 1});
                visited.insert(dest->getAirport().getCode());
            }
        }
    }

    for (auto a : visitedAir) {
        if (a != src) {
            countAirports++;

            cities.insert({ap.findVertex(a)->getAirport().getCity(), ap.findVertex(a)->getAirport().getCountry()});
            countries.insert(ap.findVertex(a)->getAirport().getCountry());
        }
    }

    std::cout << "Number of reachable destinations departing from " << src << " within " << stops
              << " stops is: " << std::endl;
    std::cout << "-" << countAirports << " airports\n";
    std::cout << "-" << cities.size()<< " cities" << std::endl;
    std::cout << "-" << countries.size() << " countries" << std::endl;
}


void Menu::findMaxStopsTrip(Graph& graph) {
    int maxStops = 0;
    std::vector<std::pair<std::string, std::string>> maxStopsPairs;

    for (const auto& vertex : graph.getVertexSet()) {
        std::queue<std::pair<Vertex*, int>> q;
        std::unordered_set<Vertex*> visited;

        q.push({vertex, 0});
        visited.insert(vertex);

        while (!q.empty()) {
            auto [currentVertex, stops] = q.front();
            q.pop();

            if (stops > maxStops) {
                maxStops = stops;
                maxStopsPairs.clear(); // Clear the previous pairs since we found a higher number of stops
                maxStopsPairs.emplace_back(vertex->getAirport().getCode(), currentVertex->getAirport().getCode());
            } else if (stops == maxStops) {
                maxStopsPairs.emplace_back(vertex->getAirport().getCode(), currentVertex->getAirport().getCode());
            }

            for (const Edge& edge : currentVertex->getAdj()) {
                Vertex* destVertex = edge.getDest();
                if (visited.find(destVertex) == visited.end()) {
                    visited.insert(destVertex);
                    q.push({destVertex, stops + 1});
                }
            }
        }
    }

    if (!maxStopsPairs.empty()) {
        std::cout << "Maximum trip(s) with the greatest number of stops (" << maxStops << " stops):" << std::endl;
        for (const auto& pair : maxStopsPairs) {
            std::cout << "Source Airport: " << pair.first << " - " << graph.findVertex(pair.first)->getAirport().getCity() << ", " << graph.findVertex(pair.first)->getAirport().getCountry() << std::endl;
            std::cout << "Destination Airport: " << pair.second << " - " << graph.findVertex(pair.second)->getAirport().getCity() << ", " << graph.findVertex(pair.second)->getAirport().getCountry() << std::endl;
            std::cout << "---------------------" << std::endl;
        }
    } else {
        std::cout << "No flights found in the graph." << std::endl;
    }
}

void Menu::bestFlightOption(Graph ap) {
    int searchOption;

    std::cout << "Choose search option for source:" << std::endl;
    std::cout << "1. Search by airport code or name" << std::endl;
    std::cout << "2. Search by city name" << std::endl;
    std::cout << "3. Search by geographical coordinates" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> searchOption;
    std::cout << std::endl;
    std::set<std::string> sourceLocations, destinationLocations;
    std::string source, destination;

    switch (searchOption) {
        case 1:

            std::cout << "Enter the source airport code or name: ";
            std::cin.ignore();
            std::getline(std::cin, source);
            if (source.size() > 3) {
                Vertex* vertex = ap.findVertexByName(source);
                    if (vertex) {
                        source = vertex->getAirport().getCode();
                    } else {
                        std::cout << "Source airport not found!" << std::endl;

                    }
            }
            std::cout << std::endl;


            sourceLocations.insert(source);


            break;
        case 2:
            std::cout << "Enter the source city name: ";
            std::cin >> source; // Using source for city name
            std::cout << std::endl;

            sourceLocations = ap.findVertexCity(source);



            break;
        case 3:
            double srcLat, srcLon;

            std::cout << "Enter your source latitude: ";
            std::cin >> srcLat;
            std::cout << std::endl;
            std::cout << "Enter your source longitude: ";
            std::cin >> srcLon;
            std::cout << std::endl;


            sourceLocations = findClosestAirports(ap, srcLat, srcLon);

            break;
    }
    int destOption;

    std::cout << "Choose search option for destination:" << std::endl;
    std::cout << "1. Search by airport code or name" << std::endl;
    std::cout << "2. Search by city name" << std::endl;
    std::cout << "3. Search by geographical coordinates" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> destOption;
    std::cout << std::endl;

    switch (destOption) {
        case 1:

            std::cout << "Enter the destination airport code or name: ";

            std::getline(std::cin, destination);

            if (destination.size() > 3) {
                Vertex* vertex = ap.findVertexByName(destination);
                    if (vertex) {
                        destination = vertex->getAirport().getCode();
                    } else {
                        std::cout << "Destination airport not found!" << std::endl;

                    }
                }

            std::cout << std::endl;


            destinationLocations.insert(destination);

            break;
        case 2:

            std::cout << "Enter the destination city name: ";
            std::cin >> destination;
            std::cout << std::endl;

            destinationLocations = ap.findVertexCity(destination);


            break;
        case 3:
            double destLat, destLon;

            std::cout << "Enter your destination latitude: ";
            std::cin >> destLat;
            std::cout << std::endl;
            std::cout << "Enter your destination longitude: ";
            std::cin >> destLon;
            std::cout << std::endl;

            destinationLocations = findClosestAirports(ap, destLat, destLon);

            break;
    }

    std::vector<Vertex*> sourceVertexes;
    std::vector<Vertex*> destinationVertexes;

    for (auto a: sourceLocations){
        sourceVertexes.push_back(ap.findVertex(a));
    }
    for (auto a: destinationLocations){
        destinationVertexes.push_back(ap.findVertex(a));
    }

    if (sourceVertexes.empty()||destinationVertexes.empty()) {
        std::cout << "Invalid source or destination location." << std::endl;
        return;
    }
    std::vector<std::string> emptyVector;       // to load the function
    std::vector<std::vector<std::vector<Vertex*>>> bestPaths;

    for (const auto& src:sourceVertexes){
        for (const auto& dest: destinationVertexes){
            bestPaths.push_back(ap.findFlightsWithFilters(src->getAirport().getCode(), dest->getAirport().getCode(), emptyVector, false));
        }
    }


    std::cout << "Best flight option(s) with the least layovers: " << std::endl;

    if (bestPaths.empty()) {
        std::cout << "No flights found" << std::endl;
    } else {

        for (const auto& dif: bestPaths)
            for (const auto& path : dif) {
                for (size_t i = 0; i < path.size() - 1; ++i) {
                std::cout << path[i]->getAirport().getCode() << " -> ";

                // Find the airline for each leg
                for (const Edge& edge : path[i]->getAdj()) {
                    if (edge.getDest() == path[i + 1]) {
                        std::string airlineName = getAirlineName(edge.getAirline());
                        std::cout << path[i + 1]->getAirport().getCode() << " (by " << airlineName << ")";
                        if (i < path.size() - 2) {
                            std::cout << " || ";
                        }
                        break;
                    }
                }
            }
            std::cout << std::endl;
            }
        }

    }



std::set<std::string> Menu::findClosestAirports(Graph ap, double lat, double lon) {
    std::set<std::string> closestAirports;
    std::map<std::string, double> airportsDist;

    double lat1 = lat;
    double lon1 = lon;
    lat1 = lat1 * M_PI / 180.0;
    lon1 = lon1 * M_PI / 180.0;

    for (const auto& a: ap.getVertexSet()){
        double lat2 = a->getAirport().getLatitude();
        double lon2 = a->getAirport().getLongitude();

        lat2 = lat2 * M_PI / 180.0;
        lon2 = lon2 * M_PI / 180.0;


        double dlat = lat2 - lat1;
        double dlon = lon2 - lon1;
        double b = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
        double c = 2 * atan2(sqrt(b), sqrt(1 - b));


        const double radius = 6371.0;
        double w = radius * c;
        airportsDist.insert({a->getAirport().getCode(), w});
    }

    std::vector<double> values;
    for(const auto& p: airportsDist){
        values.push_back(p.second);
    }
    auto min = std::min_element(values.begin(), values.end());
    for(const auto& p: airportsDist){
        if (p.second==*min){
            closestAirports.insert(p.first);
        }
    }
    return closestAirports;
}

void Menu::searchFlightsWithFilters(Graph ap) {
    std::string source, destination;
    bool minimizeAirlineChanges;
    std::string input;

    // Get Source Airport
    std::cout << "Enter the source airport code: ";
    std::cin >> source;
    std::cout << std::endl;

    // Get Destination Airport
    std::cout << "Enter the destination airport code: ";
    std::cin >> destination;
    std::cout << std::endl;

    // Get Preferred Airlines
    std::cout << "Enter preferred airlines (separated by space, enter 'none' for no preference): ";
    std::cin.ignore();  // To clear the input buffer
    std::getline(std::cin, input);
    std::cout << std::endl;
    std::vector<std::string> selectedAirlines;
    if (input != "none") {
        std::istringstream iss(input);
        std::string airline;
        while (iss >> airline) {
            selectedAirlines.push_back(airline);
        }
    }

// Get Minimize Airline Changes Option
    std::cout << "Minimize airline changes? (yes/no): ";
    std::cin >> input;
    std::cout << std::endl;
    minimizeAirlineChanges = (input == "yes");

// Search for flights
    auto flights = ap.findFlightsWithFilters(source, destination, selectedAirlines, minimizeAirlineChanges);

// Display the found flights
    if (flights.empty()) {
        std::cout << "No flights found with the given criteria." << std::endl;
    } else {
        std::cout << "Found flight options:" << std::endl;
        for (const auto& path : flights) {
            for (size_t i = 0; i < path.size() - 1; ++i) {
                std::cout << path[i]->getAirport().getCode() << " -> ";

                // Find the airline for each leg
                for (const Edge& edge : path[i]->getAdj()) {
                    if (edge.getDest() == path[i + 1]) {
                        std::string airlineName = getAirlineName(edge.getAirline());
                        std::cout << path[i + 1]->getAirport().getCode() << " (by " << airlineName << ")";
                        if (i < path.size() - 2) {
                            std::cout << " || ";
                        }
                        break;
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}


std::string Menu::getAirlineName(const std::string& airlineCode) {
    std::ifstream file("../dataset/airlines.csv"); // Specify the correct path to your file
    std::string line;

    // Check if file is open
    if (!file.is_open()) {
        std::cerr << "Unable to open airlines.csv" << std::endl;
        return "Unknown Airline";
    }

    // Skip the header line
    std::getline(file, line);

    // Read the file line by line
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string code, name, callsign, country;

        // Parse the line
        std::getline(iss, code, ',');
        std::getline(iss, name, ',');
        std::getline(iss, callsign, ',');
        std::getline(iss, country);

        // Check if the current line's code matches the airlineCode
        if (code == airlineCode) {
            file.close();
            return name;
        }
    }

    // Close the file and return unknown if not found
    file.close();
    return "Unknown Airline";
}
