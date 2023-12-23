#include "src/header/Graph.h"
#include "src/header/Loader.h"
#include <iostream>


int main() {
    Graph Airport;
    Loader::loadAirports(Airport, "airports.csv");
    Loader::loadFlights(Airport, "flights.csv");
    std::cout << "Number of airports loaded: " << Airport.getNumVertex() << std::endl;

    for (auto vertex : Airport.getVertexSet()) {
        std::cout << "Airport Code: " << vertex->getAirport().getCode() << std::endl;
        std::cout << "Airport Name: " << vertex->getAirport().getName() << std::endl;


        for (auto edge : vertex->getAdj()) {
            std::cout << "  Destination Airport Code: " << edge.getDest()->getAirport().getCode() << std::endl;
            std::cout << "  Distance: " << edge.getWeight() << " km" << std::endl;
            std::cout << std::endl;
        }
    }
}
