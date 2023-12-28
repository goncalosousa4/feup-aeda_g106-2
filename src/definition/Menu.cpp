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
        std::cout << "5. Maximum trip and corresponding pair of source-destination airports (or pairs, if more than one), that is, the flight trip(s) with the greatest number of stops in between them\n";
        std::cout << "6. Identify the airports that are essential to the network’s circulation capability (airports are essential if, when removed, areas of the network start to be unreachable)\n";
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

void Menu::numReachableDestinations(Graph ap) {
    std::string src;
    int stops;
    int countAirports = 0;
    int repeatedCities = 0; // count cities from diff countries with the same name

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

    std::queue<std::pair<Vertex*, int>> k; // empty queue for BFS
    std::set<std::string> visited;
    std::set<std::string> cities;   // visited cities
    std::set<std::string> countries;    // visited countries
    std::set<std::string> visitedAir;   //visited airports


    // Inserting the src airport and making it with -1 stops (not accessible)
    k.push({ap.findVertex(src), -1});
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
     for(auto a: visitedAir){
         if(a!=src){    // excluding the src airport;
             countAirports++;
             for (auto city: cities){
                 if (city==ap.findVertex(a)->getAirport().getCity()){   //missing the rest of the implementation
                     repeatedCities++;
                 }
             }
             cities.insert(ap.findVertex(a)->getAirport().getCity());
             countries.insert(ap.findVertex(a)->getAirport().getCountry());
         } else {
             continue;
         }
     }

    std::cout << "Number of reachable destinations departing from " << src << " within " << stops
              << " stops is: "<<std::endl;
    std::cout << "-" << countAirports << " airports\n";
    std::cout << "-" << cities.size() << " cities" << std::endl;
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

/*void Menu::bestFlightOption(Graph ap){
    std::string source, destination;
    std::cout << "Enter the source airport code: ";
    std::cin >> source;
    std::cout << std::endl;
    std::cout << "Enter the destination airport code: ";
    std::cin >> destination;
    std::cout << std::endl;

    Vertex* sourceVertex = ap.findVertex(source);
    Vertex* destinationVertex = ap.findVertex(destination);

    if (!sourceVertex || !destinationVertex) {
        std::cout << "Invalid source or destination location." << std::endl;
        return;
    }

    // bfs-like implementation
    std::queue<std::pair<Vertex*, std::vector<Vertex*>>> q;
    std::unordered_set<std::string> visited;

    q.push({sourceVertex, {sourceVertex}});
    visited.insert(source);

    int bestLayovers = 10000000;  // load a big and impossible value to bestLayovers to apply a min function further
    std::vector<std::vector<Vertex*>> bestPaths;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current.first == destinationVertex) {

            bestLayovers = std::min(bestLayovers, static_cast<int>(current.second.size()) - 1);
            bestPaths.push_back(current.second);
            continue;
        }

        for (const auto& edge : current.first->getAdj()) {
            auto neighbor = edge.getDest();
            if (visited.find(neighbor->getAirport().getCode()) == visited.end()) {
                visited.insert(neighbor->getAirport().getCode());
                auto newPath = current.second;
                newPath.push_back(neighbor);
                q.push({neighbor, newPath});
            }
        }
    }

    std::cout << "Best flight options with the least layovers (" << bestLayovers << "):" << std::endl;

    if (bestLayovers == 10000000) {
        std::cout << "No direct flight found." << std::endl;
    } else {
        for (const auto& path : bestPaths) {
            if (static_cast<int>(path.size()) - 1 == bestLayovers) {
                int i = 0;
                for (const auto& vertex : path) {
                    Airline airline = Loader::findAirlineByCode(ap.findEdgeByDest(vertex->getAirport().getCode())->getAirline(), "../dataset/Airlines.csv");
                    std::cout << vertex->getAirport().getCode() << " (by " << airline.getName() << ")";
                    if (i < path.size() - 1) {
                        std::cout << " - ";
                    }
                    i++;
                }
                std::cout << std::endl;
            }
        }
    }
}
*/

#include <limits>

void Menu::bestFlightOption(Graph ap) {
    int searchOption;
    std::cout << "Choose search option:" << std::endl;
    std::cout << "1. Search by airport code or name" << std::endl;
    std::cout << "2. Search by city name" << std::endl;
    std::cout << "3. Search by geographical coordinates" << std::endl;
    std::cout << "Enter option: ";
    std::cin >> searchOption;

    std::set<std::string> sourceLocations, destinationLocations;
    std::string source, destination;

    switch (searchOption) {
        case 1:
            std::cout << "Enter the source airport code or name: ";
            std::cin >> source;
            std::cout << std::endl;
            std::cout << "Enter the destination airport code or name: ";
            std::cin >> destination;
            std::cout << std::endl;
            sourceLocations.insert(source);
            destinationLocations.insert(destination);
            break;
        case 2:
            std::cout << "Enter the source city name: ";
            std::cin >> source; // Using source for city name
            std::cout << std::endl;
            std::cout << "Enter the destination city name: ";
            std::cin >> destination;
            std::cout << std::endl;

            sourceLocations = ap.findVertexCity(source);
            destinationLocations = ap.findVertexCity(destination);


            break;
        case 3:
            double srcLat, srcLon, destLat, destLon;
            std::cout << "Enter your source latitude: ";
            std::cin >> srcLat;
            std::cout << std::endl;
            std::cout << "Enter your source longitude: ";
            std::cin >> srcLon;
            std::cout << std::endl;
            std::cout << "Enter your destination latitude: ";
            std::cin >> destLat;
            std::cout << std::endl << "Enter your destination longitude: ";
            std::cout << std::endl;



            std::vector<Vertex*> closestSrcAirport = findClosestAirports(ap, srcLat, srcLon);
            std::vector<Vertex*> closestDestAirports = findClosestAirports(ap, destLat, destLon);




            break;
        default:
            std::cout << "Invalid option." << std::endl;
            return;
    }

    // Perform BFS to find the best flight option

    std::queue<std::pair<Vertex*, std::vector<Vertex*>>> q;
    std::unordered_set<std::string> visited;

    Vertex* sourceVertex = ap.findVertex(source);
    Vertex* destinationVertex = ap.findVertex(destination);

    if (!sourceVertex || (!destination.empty() && !destinationVertex)) {
        std::cout << "Invalid source or destination location." << std::endl;
        return;
    }

    q.push({sourceVertex, {sourceVertex}});
    visited.insert(source);

    int bestLayovers = std::numeric_limits<int>::max();  // Initialize with a large value
    std::vector<std::vector<Vertex*>> bestPaths;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if ((!destination.empty() && current.first == destinationVertex) || destination.empty()) {
            // Found a path to the destination (if destination is not empty) or considering all paths (if destination is empty)
            if (current.second.size() - 1 < bestLayovers) {
                bestLayovers = current.second.size() - 1;
                bestPaths.clear();
            }

            if (current.second.size() - 1 == bestLayovers) {
                bestPaths.push_back(current.second);
            }

            continue;  // No need to explore further from this node
        }

        for (const auto& edge : current.first->getAdj()) {
            auto neighbor = edge.getDest();
            if (visited.find(neighbor->getAirport().getCode()) == visited.end()) {
                visited.insert(neighbor->getAirport().getCode());
                auto newPath = current.second;
                newPath.push_back(neighbor);
                q.push({neighbor, newPath});
            }
        }
    }

    // Print the best flight options
    std::cout << "Best flight option(s) with the least layovers (" << bestLayovers << "):" << std::endl;
    for (const auto& path : bestPaths) {
        for (size_t i = 0; i < path.size(); ++i) {
            std::cout << path[i]->getAirport().getCode();
            if (i < path.size() - 1) {
                // Print airline information for all edges except the last one
                std::string airlineCode = ap.findEdgeByDest(path[i]->getAirport().getCode())->getAirline();
                Airline airline = Loader::findAirlineByCode(airlineCode, "../dataset/Airlines.csv");
                std::cout << " (by " << airline.getName() << ") - ";
            }
        }
        std::cout << std::endl;
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